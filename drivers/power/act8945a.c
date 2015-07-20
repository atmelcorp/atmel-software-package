/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/flexcom.h"
#include "peripherals/twi.h"
#include "peripherals/twid_legacy.h"
#include "peripherals/shdwc.h"

#include "power/act8945a.h"

#include "trace.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/*------------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

static uint8_t init_interrupt_done = 0;

struct _handler_twi htwi = {0};

// ACT8945A hardware interface

// Using Flexcom0 TWI
#define ACT8945A_TWI_ID	ID_FLEXCOM4

static const struct _pin pins_twi_act8945a[] = PINS_FLEXCOM4_TWI_IOS3;

static const struct _pin pins_chglev_act8945a[] = PIN_ACT8945A_CHGLEV;

static const struct _pin pins_irq_act8945a[] = PIN_ACT8945A_IRQ;

static const struct _pin pins_lbo_act8945a[] = PIN_ACT8945A_LBO;

struct save_bitfield {
	uint8_t syst00;
	uint8_t apch78;
	uint8_t apch79;
	uint8_t apch7A;
	uint8_t count_lbo;
};

struct save_bitfield sbf;

//------------------------------------------------------------------------------
static const sActReg ActReg[] =
{
	{"SYSTEM0 ", 0x00},
	{"SYSTEM1 ", 0x01},
	{"REG1_20 ", 0x20},
	{"REG1_21 ", 0x21},
	{"REG1_22 ", 0x22},
	{"REG2_30 ", 0x30},
	{"REG2_31 ", 0x31},
	{"REG2_32 ", 0x32},
	{"REG3_40 ", 0x40},
	{"REG3_41 ", 0x41},
	{"REG3_42 ", 0x42},
	{"REG4_50 ", 0x50},
	{"REG4_51 ", 0x51},
	{"REG5_54 ", 0x54},
	{"REG5_55 ", 0x55},
	{"REG6_60 ", 0x60},
	{"REG6_61 ", 0x61},
	{"REG7_64 ", 0x64},
	{"REG7_65 ", 0x65},
};
#define NB_REG_ACT (sizeof(ActReg)/sizeof(ActReg[0]))

static sActReg VoltReg[] =
{
	{"V_OUT1 ", V_OUT1},
	{"V_OUT2 ", V_OUT2},
	{"V_OUT3 ", V_OUT3},
	{"V_OUT4 ", V_OUT4},
	{"V_OUT5 ", V_OUT5},
	{"V_OUT6 ", V_OUT6},
	{"V_OUT7 ", V_OUT7},
};
#define NB_REG_VOLT (sizeof(VoltReg)/sizeof(VoltReg[0]))

static sActReg ActAcph[] =
{
	{"APCH_70 ", ADD_APCH_70},
	{"APCH_71 ", ADD_APCH_71},
	{"APCH_78 ", ADD_APCH_78},
	{"APCH_79 ", ADD_APCH_79},
	{"APCH_7A ", ADD_APCH_7A},
};
#define NB_REG_APCH (sizeof(ActAcph)/sizeof(ActAcph[0]))

static char OvpSet[4][8] =
{
	{"6.6V "},
	{"7.0V "},
	{"7.5V "},
	{"8.0V "},
} ;

static char ChargState[4][24] =
{
	{"Suspend/Disable/Fault"},
	{"End of charge        "},
	{"Fast charge/Top-off  "},
	{"Precondition         "},
} ;

/*------------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static uint8_t _twi_handler_init (struct _handler_twi* phtwi)
{
	uint8_t status = phtwi->Status;
	static struct _twid twid;
	Twi* pTwi = NULL;
	Flexcom* pflexc = NULL;

	assert(phtwi->Twck != 0);
	assert(phtwi->IdTwi != 0);

	memset((void*)&twid, 0x00, sizeof(twid));

	pmc_enable_peripheral(ACT8945A_TWI_ID);
	pio_configure(pins_twi_act8945a, ARRAY_SIZE(pins_twi_act8945a));
	pmc_enable_peripheral(ACT8945A_TWI_ID);

	// Use a flexcom, then init flexcom operating mode TWI
	pflexc = get_flexcom_addr_from_id(ACT8945A_TWI_ID);
	flexcom_select(pflexc, FLEX_MR_OPMODE_TWI);
	// Init twi
	pTwi = &pflexc->twi;
	twi_configure_master(pTwi, phtwi->Twck);
	twid_initialize(&twid, pTwi);

	phtwi->Status = status | TWI_STATUS_HANDLE;
	memcpy ((void*)&phtwi->twid, (void*)&twid, sizeof(twid));
	return phtwi->Status;
}

static uint8_t _is_twi_ready (struct _handler_twi* handler_twi)
{
	return handler_twi->Status & TWI_STATUS_READY;
}

static uint8_t _twid_rd_wr (struct _handler_twi* handler_twi, enum TWI_CMD Cmd)
{
	if (Cmd == TWI_RD)
		return (uint8_t)twid_read(&handler_twi->twid, handler_twi->PeriphAddr,
					  handler_twi->RegMemAddr, handler_twi->AddSize,
					  (uint8_t*)handler_twi->pData, handler_twi->LenData, 0);
	else
		return (uint8_t)twid_write(&handler_twi->twid, handler_twi->PeriphAddr,
					   handler_twi->RegMemAddr, handler_twi->AddSize,
					   (uint8_t*)handler_twi->pData, handler_twi->LenData, 0);
}

static uint8_t _act8945a_rw_register(uint8_t addr,
				     uint8_t* pdata,
				     enum TWI_CMD Cmd)
{
	htwi.RegMemAddr = addr;
	htwi.LenData = 1;
	htwi.pData = pdata;
	return _twid_rd_wr(&htwi, Cmd);
}

static void _act8945a_delay_ms (uint32_t delay)
{
	unsigned int count;
	for(;delay>0;delay--)
		for(count=0;count<(pmc_get_master_clock()/1000000);count++);
}

static void _act8945a_twi_error (void)
{
	printf(" -E- Twi Error \n\r");
}

// Dump and display the registers
static void _act8945a_registers_dump(void)
{
	uint8_t data, i = 0;

	if (!_is_twi_ready(&htwi))
		return;

	printf("\n\r *** DUMP Registers ACT8945A\n\r");
	for (i=0; i<NB_REG_ACT; i++) {
		_act8945a_rw_register (ActReg[i].Address, &data, TWI_RD);
		_act8945a_delay_ms(10);
		printf(" %s: 0x%02x \n\r", ActReg[i].RegName, data);
	}
}

// Dump and display the ACPH registers
static void _act8945a_registers_dump_APCH (void)
{
	uint8_t data, i = 0;

	if (!_is_twi_ready(&htwi))
		return ;

	printf("\n\r");
	printf(" -I- DUMP Registers APCH ACT8945A\n\r");
	for (i=0; i<NB_REG_APCH; i++) {
		_act8945a_rw_register (ActAcph[i].Address, &data, TWI_RD);
		_act8945a_delay_ms(10);
		printf(" %s: 0x%02X \n\r", ActAcph[i].RegName, data);
	}
}


/*------------------------------------------------------------------------------
 * Handler interrupt
 *----------------------------------------------------------------------------*/
void act8945a_irq_handler (uint32_t group, uint32_t status, void* user_arg)
{
	struct _bitfield_sys0 syst0;
	struct _bitfield_apch78 apch78;
	struct _bitfield_apch79 apch79;
	struct _bitfield_apch7a apch7a;

	/* unused */
	(void)user_arg;

	if (status & pins_irq_act8945a[0].mask)	{

		_act8945a_rw_register(ADD_SYSTEM0, (uint8_t*)&syst0, TWI_RD);
		_act8945a_rw_register(ADD_APCH_7A, (uint8_t*)&apch7a, TWI_RD);
		_act8945a_rw_register(ADD_APCH_78, (uint8_t*)&apch78, TWI_RD);
		_act8945a_rw_register(ADD_APCH_79, (uint8_t*)&apch79, TWI_RD);

		if (sbf.syst00 != *htwi.pData) {
			printf("SYST00 \n\r");
			sbf.syst00 = *htwi.pData;
		} else if (sbf.apch7A != *htwi.pData) {
			printf("\n\r %s \n\r", &ChargState[apch7a.cstate][0]);
			sbf.apch7A = *htwi.pData;
		} else if (sbf.apch78 != *htwi.pData) {
			if (apch78.chgdat == 0x01)
				printf("\n\r charger state machine: END-OF-CHARGE state \n\r");
			sbf.apch78 = *htwi.pData;
		} else if (sbf.apch79 != *htwi.pData) {
			printf("APCH79 \n\r");
			sbf.apch79 = *htwi.pData;
		}
	}
}

/*------------------------------------------------------------------------------
 * Handler interrupt
 *----------------------------------------------------------------------------*/
void act8945a_lbo_handler (uint32_t group, uint32_t status, void* user_arg)
{
	/* unused */
	(void)user_arg;

	if (status & pins_lbo_act8945a[0].mask) {
		printf(" Int: Low Battery output \n\r");
		pio_disable_it(&pins_lbo_act8945a[0]);
		printf(" Launch Shutdown mode \n\r");
		_act8945a_delay_ms(2);
		/* shdwc_configure_wakeup_mode (SHDW_MR_LPDBCEN0_ENABLE | */
		/* 			     SHDW_MR_LPDBC_2_RTCOUT0 | */
		/* 			     SHDW_MR_WKUPDBC_32_SLCK); */
		/* shdwc_set_wakeup_input (SHDW_WUIR_WKUPEN0_ENABLE, */
		/* 			SHDW_WUIR_WKUPT0_LOW); */
		/* shdwc_do_shutdown(); */
	}
}

// Convert the voltage setting to display value
static float _act8945a_Convert_voltage_setting (uint8_t Reg)
{
	float result = 0;
	uint8_t mul20, mul53;

	mul20 = (Reg & 0x07) >>0;
	mul53 = (Reg & 0x38) >>3;

	if (Reg <= 0x17)
		result = 0.6 + (0.2*mul53) + (0.025*mul20);
	else if (Reg <= 0x2F)
		result = 1.2 + (0.4*(mul53-3)) + (0.050*mul20);
	else
		result = 2.4 + (0.8*(mul53-6)) + (0.1*mul20);
	return result;
}

static void _act8945a_display_system_setting (void)
{
	uint8_t status;
	float value;
	struct _bitfield_sys0 syst0;
	struct _bitfield_sys1 syst1;

	status= _act8945a_rw_register(ADD_SYSTEM0,
				      (uint8_t*)&syst0, TWI_RD);
	if(status!=ACT8945A_RET_OK) return;

	value = 2.3 + (syst0.syslev*0.1);

	printf("\n\r");
	printf(" -I- System Registers ACT8945A \n\r");
	printf(" -I- SYST0 @0x00: 0x%02X \n\r", *htwi.pData);
	printf(" Reset Timer Setting:           %s \n\r",
	       (syst0.trst)? "65ms":"260ms");
	printf(" SYSLEV Mode Select:            %s \n\r",
	       (syst0.nsysmode)?"int":"shutdown");
	printf(" System Voltage Level Int.Mask: %s \n\r",
	       (syst0.nsyslevmsk)?"int":"no int");
	printf(" System Voltage Status:         %s \n\r",
	       (syst0.nsysstat)?"vsys<syslev":"vsys>syslev");
	printf(" SYSLEV Failing Treshold value: %.2fv \n\r", value);

	status =_act8945a_rw_register(ADD_SYSTEM1,
				      (uint8_t*)&syst1, TWI_RD);
	if(status!=ACT8945A_RET_OK) return;

	printf("\n\r");
	printf(" -I- SYST1 @0x01: 0x%02X \n\r", *htwi.pData);
	printf(" Master Off Ctrl, All regul:    %s \n\r",
	       (syst1.mstroff)?"OFF ":"ON ");
	printf(" Scratchpad Bits, free user:    0x%02x \n\r",
	       syst1.scratch);
}

// Display detailled infos of the register ACT8865 and ACT8945A
void act8945a_display_voltage_setting(void)
{
	uint8_t data, x, status;
	float x1;
	struct _bitfield_ctrl1 ctrl1;
	struct _bitfield_ctrl2 BitField_Ctrl2;

	printf(" * Voltage Setting & State ACT8945A \n\r");

	for (x=0; x<NB_REG_VOLT ; x++)
	{
		status = _act8945a_rw_register(VoltReg[x].Address,
					       &data, TWI_RD);
		if(status!=ACT8945A_RET_OK) return;
		x1= _act8945a_Convert_voltage_setting(data);

		status = _act8945a_rw_register(VoltReg[x].Address+1,
					       &data, TWI_RD);
		if(status!=ACT8945A_RET_OK) return;

		printf(" -I- %s= %.2fv ", VoltReg[x].RegName, (float)x1);

		if (VoltReg[x].Address >= V_OUT4) {
			memcpy (&BitField_Ctrl2, &data, 1);
			printf("0x%02X %s", data, (BitField_Ctrl2.on) ? "ON ":"OFF");
			printf(" %s", (BitField_Ctrl2.dis)?"OFF":"ON ");
			printf(" %s", (BitField_Ctrl2.lowiq)?"Normal":"LowPwr");
			printf("\tDelay:0x%02X", BitField_Ctrl2.delay);
			printf(" %s ", (BitField_Ctrl2.nfltmsk)?"En":"Dis");
			printf(" %s", (BitField_Ctrl2.ok)?"OK":".<Tresh");
		} else {
			memcpy (&ctrl1, &data, 1);
			printf("0x%02X %s", data, (ctrl1.on) ? "ON  ":"OFF");
			printf(" %s", (ctrl1.phase)?"180":"Osc");
			printf(" %s", (ctrl1.mode)?"PWM":"PowSav");
			printf("\tDelay:0x%02X", ctrl1.delay);
			printf(" %s ", (ctrl1.nfltmsk)?"En":"Dis");
			printf(" %s", (ctrl1.ok)?"OK":".<Tresh");
		}
		printf("\n\r");
	}
}

// Display detailled infos register APCH (ACT8945A)
static uint8_t _act8945a_display_active_path_charger (void)
{
	struct _bitfield_apch71 BitField_APCH71;
	struct _bitfield_apch78 apch78;
	struct _bitfield_apch79 apch79;
	struct _bitfield_apch7a apch7a;

	uint8_t data, status = ACT8945A_RET_OK;

	printf("\n\r");
	printf(" -I- ACPH Registers ACT8945A \n\r");

	status = _act8945a_rw_register (ADD_APCH_70, &data, TWI_RD);
	if (status) _act8945a_twi_error();
	else
	{
		printf(" -I- APCH @0x70: Reserved 0x%02X \n\r", data);
		printf("\n\r");
	}

	status = _act8945a_rw_register(ADD_APCH_71,
				       (uint8_t*)&BitField_APCH71, TWI_RD);
	if (status) {
		_act8945a_twi_error();
	} else {
		printf(" -I- APCH @0x71: 0x%02X \n\r", *htwi.pData);
		printf(" Charge Suspend Control Input:         %X \n\r",
		       BitField_APCH71.suschg);
		printf(" Bit 6 reserved \n\r");
		printf(" Total Charge Time-out Selection:      %02X \n\r",
		       BitField_APCH71.tottimo);
		printf(" Precondition Charge Time-out Sel:     %02X \n\r",
		       BitField_APCH71.pretimo);
		printf(" Input Over-Volt Prot.Threshold Sel:   %02X ",
		       BitField_APCH71.ovpset);
		printf(" equ %s \n\r", &OvpSet[BitField_APCH71.ovpset][0]);
		printf("\n\r");
	}

	status = _act8945a_rw_register(ADD_APCH_78,
				       (uint8_t*)&apch78, TWI_RD);
	if (status) {
		_act8945a_twi_error();
	} else {
		printf(" -I- APCH @0x78: 0x%02X \n\r", *htwi.pData);
		printf(" Charge Time-out Interrupt Status:     %X \n\r",
		       apch78.timrstat);
		printf(" Battery Temperature Interrupt Status: %X \n\r",
		       apch78.tempstat);
		printf(" Input Voltage Interrupt Status:       %X \n\r",
		       apch78.instat);
		printf(" Charge State Interrupt Status:        %X \n\r",
		       apch78.chgstat);
		printf(" Charge Timer Status                   %X \n\r",
		       apch78.timrdat);
		printf(" Temperature Status                    %X \n\r",
		       apch78.tempdat);
		printf(" Input Voltage Status                  %X \n\r",
		       apch78.indat);
		printf(" Charge State Machine Status           %X \n\r",
		       apch78.chgdat);
		printf("\n\r");
	}

	status = _act8945a_rw_register(ADD_APCH_79,
				       (uint8_t*)&apch79, TWI_RD);
	if (status) {
		_act8945a_twi_error();
	} else {
		printf(" -I- APCH @0x79: 0x%02X \n\r", *htwi.pData);
		printf(" Total Charge Time-out Int Control:    %X \n\r",
		       apch79.timrtot);
		printf(" Batt.Temp.Int.Ctrl into valid range:  %X \n\r",
		       apch79.tempin);
		printf(" Inp.Voltage Int.Ctrl into valid range:%X \n\r",
		       apch79.incon);
		printf(" Charge State Int Ctrl into EOC state: %X \n\r",
		       apch79.chgeocin);
		printf(" Precharge Time-out Int Ctrl:          %X \n\r",
		       apch79.timrpre);
		printf(" Batt.Temp.Int.Ctrl. out valid range:  %X \n\r",
		       apch79.tempout);
		printf(" Inp.Voltage Int.Ctrl. out valid range:%X \n\r",
		       apch79.indis);
		printf(" Charge State Int.Ctrl. out EOC state: %X \n\r",
		       apch79.chgeocout);
		printf("\n\r");
	}

	status = _act8945a_rw_register(ADD_APCH_7A,
				       (uint8_t*)&apch7a, TWI_RD);
	if (status) {
		_act8945a_twi_error();
	} else {
		printf(" -I- APCH @0x7A: 0x%02X \n\r", *htwi.pData);
		printf(" Bit 7-6 reserved:                     %02X \n\r",
		       apch7a.ruf76);
		printf(" Charge State:                         %02X ",
		       apch7a.cstate);
		printf(" %s \n\r", &ChargState[apch7a.cstate][0]);
		printf(" Bit 3-2 reserved:                     %02X \n\r",
		       apch7a.ruf32);
		printf(" ACIN Status:                          %X \n\r",
		       apch7a.acinstat);
		printf(" Bit 0 reserved:                       %X \n\r",
		       apch7a.ruf0);
		printf("\n\r");
	}
	return status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Display the value of the register ACT8945A
static uint8_t _act8945a_display_syslev_failing_threshold (void)
{
	struct _bitfield_sys0 BitField_SYS0;
	uint8_t status = ACT8945A_RET_OK;
	float value;

	status = _act8945a_rw_register(ADD_SYSTEM0,
				       (uint8_t*)&BitField_SYS0, TWI_RD);
	if (status) {
		_act8945a_twi_error();
	} else {
		value = 2.3 + (BitField_SYS0.syslev*0.1);
		printf("\n\r");
		printf(" -I- SYSLEV Failing Treshold value:0x%02X  %.2fv \n\r",
		       BitField_SYS0.syslev, value);
	}
	return status;
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

// Configure the state (ON/OFF) of the regulator OUT1 to OUT3
// Set bit to 1 to enable the regulator, clear bit to 0 to disable the regulator.
// Input: VOUT base register address
uint8_t act8945a_set_regulator_state_out1to3 (uint8_t RegVout,
					      uint8_t on_off)
{
	uint8_t status = ACT8945A_RET_OK;
	struct _bitfield_ctrl1 ctrl1;

	if (!_is_twi_ready(&htwi)) {
		return ACT8945A_RET_NOK;
	}
	if (RegVout!=V_OUT1 && RegVout!=V_OUT2 && RegVout!=V_OUT3) {
		return ACT8945A_RET_NOK;
	}

	//enable/disable output
	status = _act8945a_rw_register(RegVout+1,
				       (uint8_t*)&ctrl1, TWI_RD);
	if (status) return status;
	ctrl1.on = (on_off)? 1:0 ;
	return status = _act8945a_rw_register(RegVout+1,
					      (uint8_t*)&ctrl1,
					      TWI_WR);
}

// Configure the state (ON/OFF) of the regulator OUT4 to OUT7
// Input: VOUT base register address
uint8_t act8945a_set_regulator_state_out4to7 (uint8_t RegVout, uint8_t on_off)
{
	uint8_t status = ACT8945A_RET_OK;
	struct _bitfield_ctrl2 BitField_Ctrl2;

	if (!_is_twi_ready(&htwi)) {
		return ACT8945A_RET_NOK;
	}

	if (RegVout!=V_OUT4 && RegVout!=V_OUT5
	    && RegVout!=V_OUT6 && RegVout!=V_OUT7) {
		return ACT8945A_RET_NOK;
	}

	//enable/disable output
	status = _act8945a_rw_register(RegVout+1,
				       (uint8_t*)&BitField_Ctrl2, TWI_RD);
	if (status) return status;
	BitField_Ctrl2.on = (on_off)? 1:0 ;
	return status = _act8945a_rw_register(RegVout+1,
					      (uint8_t*)&BitField_Ctrl2, TWI_WR);
}

// Set the ouptut value of the regulator OUT4 to OUT7
// Input: Vout: Value in mv
//      : RegVout base register address
uint8_t act8945a_set_regulator_voltage_out4to7 (uint8_t RegVout, uint16_t VOut)
{
	uint8_t data, RegSet;

	if (!_is_twi_ready(&htwi)) {
		return ACT8945A_RET_NOK;
	}
	if (VOut>3900) {
		return ACT8945A_RET_NOK;
	}
	if (RegVout!=V_OUT4 && RegVout!=V_OUT5
	    && RegVout!=V_OUT6 && RegVout!=V_OUT7) {
		return ACT8945A_RET_NOK;
	}

	if (VOut<600) {
		VOut = 600; // Min 0.6v
	}

	if (VOut<1200) {
		RegSet = (VOut-600)/25;
	} else if (VOut>=1200 && VOut<2400) {
		RegSet = 0x18+((VOut-1200)/50);
	} else if (VOut>=2400 && VOut<=3900) {
		RegSet = 0x30+((VOut-2400)/100);
	} else {
		return ACT8945A_RET_NOK;
	}

	//Set Output Voltage Selection
	data = (RegSet&0x3F); // Bit[7:6] reserved
	return _act8945a_rw_register (RegVout, &data, TWI_WR);
}

// System Voltage Level Interrupt Mask. SYSLEV interrupt is masked by default,
// set to 1 to unmask this interrupt.
uint8_t act8945a_set_system_voltage_level_interrupt (uint8_t on_off)
{
	struct _bitfield_sys0 BitField_SYS0;
	uint8_t status = ACT8945A_RET_OK;

	if (!_is_twi_ready(&htwi))
		return ACT8945A_RET_NOK;

	status = _act8945a_rw_register(ADD_SYSTEM0,
				       (uint8_t*)&BitField_SYS0, TWI_RD);
	if (status) {
		_act8945a_twi_error();
	} else {
		BitField_SYS0.nsyslevmsk = on_off;
		status = _act8945a_rw_register(ADD_SYSTEM0,
					       (uint8_t*)&BitField_SYS0,
					       TWI_WR);
	}
	return status;
}

// Regulator Fault Mask Control.
// Set bit to 1 enable fault-interrupts, clear bit to 0 to disable fault-interrupts
// Input: VOUT base register address
uint8_t act8945a_set_regulator_fault_interrupt (uint8_t RegVout, uint8_t on_off)
{
	uint8_t status = ACT8945A_RET_OK;
	struct _bitfield_ctrl1 ctrl1;
	struct _bitfield_ctrl2 BitField_Ctrl2;

	if (!_is_twi_ready(&htwi))
		return ACT8945A_RET_NOK;

	switch (RegVout)
	{
	case V_OUT1:
	case V_OUT2:
	case V_OUT3:
		status = _act8945a_rw_register(RegVout+1,
					       (uint8_t*)&ctrl1,
					       TWI_RD);
		if (status) return ACT8945A_RET_NOK;
		ctrl1.nfltmsk = (on_off)? 1:0 ;
		status = _act8945a_rw_register(RegVout+1,
					       (uint8_t*)&ctrl1,
					       TWI_WR);
		break;

	case V_OUT4:
	case V_OUT5:
	case V_OUT6:
	case V_OUT7:
		status = _act8945a_rw_register(RegVout+1,
					       (uint8_t*)&BitField_Ctrl2,
					       TWI_RD);
		if (status) return ACT8945A_RET_NOK;
		BitField_Ctrl2.nfltmsk = (on_off)? 1:0 ;
		status = _act8945a_rw_register(RegVout+1,
					       (uint8_t*)&BitField_Ctrl2,
					       TWI_WR);
		break;

	default:
		break;
	}
	return status;
}

// Set or Clear an APCH interrupt
// Set bit to 1 enable interrupt,
// Clear bit to 0 to disable interrupt
uint8_t act8945a_set_apch_interrupt (enum _it_apch IntType, uint8_t on_off)
{
	uint8_t status = ACT8945A_RET_OK;
	struct _bitfield_apch78 apch78;
	struct _bitfield_apch79 apch79;

	if (!_is_twi_ready(&htwi))
		return ACT8945A_RET_NOK;

	status = _act8945a_rw_register(ADD_APCH_78,
				       (uint8_t*)&apch78, TWI_RD);
	status = _act8945a_rw_register(ADD_APCH_79,
				       (uint8_t*)&apch79, TWI_RD);

	switch (IntType)
	{
	// Interrupt generated any time the input supply is disconnected when
	// INSTAT[] bit is set to 1 and the INDIS[] bit is set to 1.
	case INPUT_VOLTAGE_OUT_VALID_RANGE_INT_CTRL: // Interrupt
		apch78.instat = (on_off)? 1:0 ;
		apch79.indis = (on_off)? 1:0 ;
		break;

	// Interrupt generated any time the input supply is connected when
	// INSTAT[] bit is set to 1 and the INCON[] bit is set to 1.
	case INPUT_VOLTAGE_INTO_VALID_RANGE_INT_CTRL:
		apch78.instat = (on_off)? 1:0 ;
		apch79.incon = (on_off)? 1:0 ;
		break;

	// Interrupts based upon the status of the battery temperature.
	// Set the TEMPOUT[] bit to 1 and TEMPSTAT[] bit to 1 to generate
	// an interrupt when battery temperature goes out of the valid
	// temperature range.
	case BATTERY_TEMPERATURE_OUT_RANGE_INT_CTRL:
		apch78.tempstat = (on_off)? 1:0 ;
		apch79.tempout = (on_off)? 1:0 ;
		break;

	// Interrupts based upon the status of the battery temperature.
	// Set the TEMPIN[] bit to 1 and TEMPSTAT[] bit to 1 to generate
	// an interrupt when battery temperature returns to the valid range.
	case BATTERY_TEMPERATURE_INTO_RANGE_INT_CTRL:
		apch78.tempstat = (on_off)? 1:0 ;
		apch79.tempin = (on_off)? 1:0 ;
		break;

	// Interrupt when the charger state machine goes into the
	// END-OF-CHARGE (EOC). Set CHGEOCIN[] bit to 1 and CHGSTAT[] bit
	// to 1 to generate an interrupt when the charger state machine goes
	// into the END-OF-CHARGE (EOC)state.
	case CHARGE_STATE_INTO_EOC_STATE_INT_CTRL:
		apch78.chgstat = (on_off)? 1:0 ;
		apch79.chgeocin = (on_off)? 1:0 ;
		break;

	// Interrupt when the charger state machine exit the
	// END-OF-CHARGE (EOC). Set CHGEOCOUT[] bit to 1 and CHGSTAT[] bit
	// to 1 to generate an interrupt when the charger state machine exits
	// the EOC state.
	case CHARGE_STATE_OUT_EOC_STATE_INT_CTRL:
		apch78.chgstat = (on_off)? 1:0 ;
		apch79.chgeocout = (on_off)? 1:0 ;
		break;

	// Interrupts based upon the status of the charge timers.
	// Set the TIMRPRE[] bit to 1 and TIMRSTAT[] bit to 1 to generate an
	// interrupt when the Precondition Timer expires.
	case PRECHARGE_TIME_OUT_INT_CTRL:
		apch78.timrstat = (on_off)? 1:0 ;
		apch79.timrpre = (on_off)? 1:0 ;
		break;

	// Set the TIMRTOT[] bit to 1 and TIMRSTAT[] bit to 1 to generate an
	// interrupt when the Total-Charge Timer expires.
	case TOTAL_CHARGE_TIME_OUT_INT_CTRL:
		apch78.timrstat = (on_off)? 1:0 ;
		apch79.timrtot = (on_off)? 1:0 ;
		break;

	default:
		break;
	}

	// Write configuration to registers
	status = _act8945a_rw_register(ADD_APCH_78,
				       (uint8_t*)&apch78, TWI_WR);
	status |= _act8945a_rw_register(ADD_APCH_79,
					(uint8_t*)&apch79, TWI_WR);
	return status;
}

// Disable all interrupt from APCH
uint8_t act8945a_disable_all_APCH_interrupt (void)
{
	uint8_t status = ACT8945A_RET_OK;

	if (!_is_twi_ready(&htwi))
		return ACT8945A_RET_NOK;

	status |= act8945a_set_apch_interrupt(CHARGE_STATE_OUT_EOC_STATE_INT_CTRL, ACT8945A_SET_OFF);
	status |= act8945a_set_apch_interrupt(INPUT_VOLTAGE_OUT_VALID_RANGE_INT_CTRL, ACT8945A_SET_OFF);
	status |= act8945a_set_apch_interrupt(BATTERY_TEMPERATURE_OUT_RANGE_INT_CTRL, ACT8945A_SET_OFF);
	status |= act8945a_set_apch_interrupt(PRECHARGE_TIME_OUT_INT_CTRL, ACT8945A_SET_OFF);
	status |= act8945a_set_apch_interrupt(CHARGE_STATE_INTO_EOC_STATE_INT_CTRL, ACT8945A_SET_OFF);
	status |= act8945a_set_apch_interrupt(INPUT_VOLTAGE_INTO_VALID_RANGE_INT_CTRL, ACT8945A_SET_OFF);
	status |= act8945a_set_apch_interrupt(BATTERY_TEMPERATURE_INTO_RANGE_INT_CTRL, ACT8945A_SET_OFF);
	status |= act8945a_set_apch_interrupt(TOTAL_CHARGE_TIME_OUT_INT_CTRL, ACT8945A_SET_OFF);
	return status;
}

// Set the Programmable System Voltage Monitor
// Input: Value in mv from 2300mv to 3800mv
uint8_t act8945a_set_system_voltage_level (uint16_t value)
{
	struct _bitfield_sys0 BitField_SYS0;
	uint8_t status = ACT8945A_RET_OK;

	if (value<2300 || value>3800)
		return ACT8945A_RET_NOK;

	status = _act8945a_rw_register(ADD_SYSTEM0,
				       (uint8_t*)&BitField_SYS0, TWI_RD);
	if (status) _act8945a_twi_error();
	else
	{
		BitField_SYS0.syslev = (value-2300)/100;
		status =  _act8945a_rw_register(ADD_SYSTEM0,
						(uint8_t*)&BitField_SYS0, TWI_WR);

		_act8945a_display_syslev_failing_threshold();
	}
	return status;
}

// Charge Current Selection Input
// In USB-Mode: CHGLEV = 1 -> I charge 450mA
//               CHGLEV = 0 -> I charge 1000mA
uint8_t act8945a_set_state_chglev_pin(enum _pwr_usb_mode State)
{
	if (State == ACT8945A_USB_MODE_100mA) {
		pio_clear(&pins_chglev_act8945a[0]);
		printf(" Charge Level: 100mA \n\r");
	}
	else {
		pio_set(&pins_chglev_act8945a[0]);
		printf(" Charge Level: 450mA \n\r");
	}
	return 0;
}

// Low Battery Indicator Output. nLBO is asserted low whenever the voltage
// at LBI is lower than 1.2V,
uint8_t act8945a_get_state_lbo_pin(void)
{
	return pio_get(&pins_lbo_act8945a[0]);
}

// Init TWI interface
uint8_t act8945a_begin (void)
{
	uint8_t data = 0;
	uint8_t status = ACT8945A_RET_OK;

	if (!_is_twi_ready(&htwi))
	{
		memset ((void*)&htwi, 0x00, sizeof(htwi));
		pio_configure(pins_chglev_act8945a,
			      ARRAY_SIZE(pins_chglev_act8945a));
		pio_configure(pins_irq_act8945a, ARRAY_SIZE(pins_irq_act8945a));
		pio_configure(pins_lbo_act8945a, ARRAY_SIZE(pins_lbo_act8945a));

		// Set TWI interface
		memset ((uint8_t*)&htwi, 0x00, sizeof(htwi));
		htwi.IdTwi = ACT8945A_TWI_ID;
		htwi.Twck = TWCK_400K;
		htwi.PeriphAddr = ACT8945A_ADDRESS;
		printf("act8945A @0x%02X TWCK:%dKHz \n\r",
		       (unsigned int)htwi.PeriphAddr,
		       (unsigned int)htwi.Twck/1000);
		status = _twi_handler_init (&htwi);
		htwi.AddSize = 1;
		htwi.pData = &data;
		htwi.LenData = 1;
		htwi.Status |= TWI_STATUS_READY;
	}
	_act8945a_rw_register (ADD_SYSTEM0, htwi.pData, TWI_RD);
	if (!data) return status = ACT8945A_RET_NOK;
	else {
		/* Set Charge Level */
		act8945a_set_state_chglev_pin(ACT8945A_USB_MODE_450mA);

		/* Set level interrupt */
		act8945a_disable_all_APCH_interrupt();
		act8945a_set_apch_interrupt(CHARGE_STATE_INTO_EOC_STATE_INT_CTRL, ACT8945A_SET_ON);
		act8945a_set_apch_interrupt(CHARGE_STATE_OUT_EOC_STATE_INT_CTRL, ACT8945A_SET_ON);
		act8945a_set_apch_interrupt(PRECHARGE_TIME_OUT_INT_CTRL, ACT8945A_SET_ON);
		act8945a_set_apch_interrupt(TOTAL_CHARGE_TIME_OUT_INT_CTRL, ACT8945A_SET_ON);
		act8945a_set_system_voltage_level_interrupt(ACT8945A_SET_ON);

		act8945a_set_system_voltage_level_interrupt(ACT8945A_SET_ON);

		/* Update register status for interrupt state*/
		_act8945a_rw_register (ADD_SYSTEM0, &sbf.syst00, TWI_RD);
		_act8945a_rw_register (ADD_APCH_78, &sbf.apch78, TWI_RD);
		_act8945a_rw_register (ADD_APCH_79, &sbf.apch79, TWI_RD);
		_act8945a_rw_register (ADD_APCH_7A, &sbf.apch7A, TWI_RD);
		sbf.count_lbo = 0;

		/* Finally activ interrupt */
		act8945a_active_interrupt_handler();
		status = ACT8945A_RET_OK;
	}
	return status;
}

// Config interrupt on nIRQ pin to MPU
void act8945a_active_interrupt_handler (void)
{
	if (!init_interrupt_done) {
		/* Configure PMIC line interrupts. */
		pio_configure_it(&pins_irq_act8945a[0]);
		pio_add_handler_to_group(pins_irq_act8945a[0].group,
					 pins_irq_act8945a[0].mask,
					 act8945a_irq_handler,
					 NULL);
		pio_enable_it(&pins_irq_act8945a[0]);

		/* Configure PMIC LBO line interrupts. */
		sbf.count_lbo = 0;
		pio_configure_it(&pins_lbo_act8945a[0]);
		pio_add_handler_to_group(pins_lbo_act8945a[0].group,
					 pins_lbo_act8945a[0].mask,
					 act8945a_lbo_handler,
					 NULL);
		pio_enable_it(&pins_lbo_act8945a[0]);

		init_interrupt_done = 1;
	}
}

void test_out6 (void)
{
	uint16_t x;

	// Change step by step (25mv) the output voltage OUT6 from 0.6v to max.
	act8945a_set_regulator_state_out4to7 (V_OUT6, ACT8945A_SET_ON);
	for (x=500; x<3300; x+=25)
	{
		act8945a_set_regulator_voltage_out4to7 (V_OUT6, x);
		_act8945a_delay_ms(10);
	}
	act8945a_set_regulator_voltage_out4to7 (V_OUT6, 600);
	act8945a_set_regulator_state_out4to7 (V_OUT6, ACT8945A_SET_OFF);
}

uint8_t act8945a_test (void)
{
	uint8_t status = ACT8945A_RET_OK;

	if (!_is_twi_ready(&htwi)) {
		printf(" ACT8945A Reset State \n\r");
		status = act8945a_begin();
		if (status != ACT8945A_RET_OK)
		{
			_act8945a_twi_error();
			return status;
		}
	}
	// Dump registers and display
	_act8945a_registers_dump();
	_act8945a_registers_dump_APCH();
	_act8945a_display_active_path_charger();
	act8945a_display_voltage_setting();
	act8945a_set_system_voltage_level(3100);
	_act8945a_display_system_setting();

	status = act8945a_set_system_voltage_level_interrupt(ACT8945A_SET_OFF);
	status = act8945a_disable_all_APCH_interrupt();

	act8945a_set_apch_interrupt(CHARGE_STATE_INTO_EOC_STATE_INT_CTRL, ACT8945A_SET_ON);
	act8945a_set_apch_interrupt(CHARGE_STATE_OUT_EOC_STATE_INT_CTRL, ACT8945A_SET_ON);
	act8945a_set_apch_interrupt(PRECHARGE_TIME_OUT_INT_CTRL, ACT8945A_SET_ON);
	act8945a_set_apch_interrupt(TOTAL_CHARGE_TIME_OUT_INT_CTRL, ACT8945A_SET_ON);

	status = act8945a_set_system_voltage_level_interrupt(ACT8945A_SET_ON);

	act8945a_active_interrupt_handler();
	return status;
}
