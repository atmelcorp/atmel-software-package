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
#include "peripherals/twid.h"

#include "power/act8945a.h"

#include "trace.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/*------------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

struct _handler_twi htwi = {0};

// ACT8945A hardware interface

// Using Flexcom0 TWI
#define ACT8945A_TWI_ID	ID_FLEXCOM4

static const struct _pin pins_twi_act8945a[] = PINS_FLEXCOM4_TWI_IOS3;

static const struct _pin pins_ctrl_act8945a[] = PIN_ACT8945A_CHGLEV;

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

//------------------------------------------------------------------------------
///        Local functions
//------------------------------------------------------------------------------

static uint8_t _twi_handler_init (struct _handler_twi* phtwi)
{
	uint8_t Status = phtwi->Status;
	static struct _twid twid;
	Twi* pTwi = NULL;
	Flexcom* pflexc = NULL;

	assert( phtwi->Twck != 0 );
	assert( phtwi->IdTwi != 0 );

	memset((void*)&twid, 0x00, sizeof(twid));

	pmc_enable_peripheral(ACT8945A_TWI_ID);
	/* PMC->PMC_PCR = PMC_PCR_PID(ACT8945A_TWI_ID) | PMC_PCR_CMD | PMC_PCR_EN | PMC_PCR_DIV_PERIPH_DIV4_MCK; */
	pio_configure(pins_twi_act8945a, ARRAY_SIZE(pins_twi_act8945a));
	pmc_enable_peripheral(ACT8945A_TWI_ID);

	// Use a flexcom, then init flexcom operating mode TWI
	pflexc = get_flexcom_addr_from_id(ACT8945A_TWI_ID);
	flexcom_select(pflexc, FLEX_MR_OPMODE_TWI);
	// Init twi
	pTwi = &pflexc->twi;
	twi_configure_master(pTwi, phtwi->Twck);
	twid_initialize(&twid, pTwi);

	phtwi->Status = Status | TWI_STATUS_HANDLE;
	memcpy ((void*)&phtwi->twid, (void*)&twid, sizeof(twid));
	return phtwi->Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

static uint8_t _is_twi_ready (struct _handler_twi* handler_twi)
{
	return handler_twi->Status & TWI_STATUS_READY;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

static void _act8945a_delay_ms (uint32_t delay)
{
	unsigned int count;
	for(;delay>0;delay--)
		for(count=0;count<(pmc_get_master_clock()/1000000);count++);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

uint8_t bf_SYST0 = 0;
uint8_t bf_APCH78 = 0;
uint8_t bf_APCH79 = 0;
uint8_t bf_APCH7A = 0;

void act8945a_irq_handler(void)
{
	BITFIELD_SYS0 BitField_Syst0;
	BITFIELD_APCH78 BitField_APCH78;
	BITFIELD_APCH78 BitField_APCH79;
	BITFIELD_APCH7A BitField_APCH7A;

	htwi.RegMemAddr = ADD_SYSTEM0;
	htwi.LenData = 1;
	htwi.pData = (uint8_t*)&BitField_Syst0;
	_twid_rd_wr(&htwi, TWI_RD);

	if ( bf_SYST0 != *htwi.pData)
	{
		printf("&");
		bf_SYST0 = *htwi.pData;
	}

	htwi.RegMemAddr = ADD_APCH_7A;
	htwi.pData = (uint8_t*)&BitField_APCH7A;
	_twid_rd_wr(&htwi, TWI_RD);

	if ( bf_APCH7A != *htwi.pData)
	{
		printf("\n\r %s \n\r", &ChargState[BitField_APCH7A.cstate][0]);
		bf_APCH7A = *htwi.pData;
	}

	htwi.RegMemAddr = ADD_APCH_78;
	htwi.pData = (uint8_t*)&BitField_APCH78;
	_twid_rd_wr(&htwi, TWI_RD);

	if ( bf_APCH78 != *htwi.pData)
	{
		if (BitField_APCH78.chgdat == 0x01) printf("\n\rcharger state machine: END-OF-CHARGE state \n\r");
		bf_APCH78 = *htwi.pData;
	}

	htwi.RegMemAddr = ADD_APCH_79;
	htwi.pData = (uint8_t*)&BitField_APCH79;
	_twid_rd_wr(&htwi, TWI_RD);

	if ( bf_APCH79 != *htwi.pData)
	{
		printf("#");
		bf_APCH79 = *htwi.pData;
	}
	printf("*");
}

//------------------------------------------------------------------------------
///        Display register functions
//------------------------------------------------------------------------------

static void _act8945a_twi_error (void)
{
	printf(" -E- Twi Error \n\r");
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Dump and display the registers
static void _act8945a_registers_dump(void)
{
	uint8_t data, i = 0;

	if (_is_twi_ready(&htwi))
	{
		printf("\n\r *** DUMP Registers ACT8945A\n\r");
		htwi.LenData = 1;
		htwi.pData = &data;
		for (i=0; i<NB_REG_ACT; i++)
		{
			htwi.RegMemAddr = ActReg[i].Address;
			_twid_rd_wr(&htwi, TWI_RD);
			_act8945a_delay_ms(10);
			printf("%s: 0x%02x", ActReg[i].RegName, data);
			printf("\n\r");
		}
	}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Dump and display the ACPH registers
static void _act8945a_registers_dump_APCH (void)
{
	uint8_t data, i = 0;

	if (_is_twi_ready(&htwi))
	{
		printf("\n\r");
		printf(" -I- DUMP Registers APCH ACT8945A\n\r");
		htwi.LenData = 1;
		htwi.pData = &data;
		for (i=0; i<NB_REG_APCH; i++)
		{
			htwi.RegMemAddr = ActAcph[i].Address;
			_twid_rd_wr(&htwi, TWI_RD);
			_act8945a_delay_ms(10);
			printf(" -I- %s: 0x%02X", ActAcph[i].RegName, data);
			printf("\n\r");
		}
	}
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Convert the voltage setting to display value
static float _act8945a_Convert_voltage_setting (uint8_t Reg)
{
	float Result = 0;
	uint8_t Mul20, Mul53;

	Mul20 = (Reg & 0x07) >>0;
	Mul53 = (Reg & 0x38) >>3;

	if (Reg <= 0x17)
		Result = 0.6 + (0.2*Mul53) + (0.025*Mul20);
	else if (Reg <= 0x2F)
		Result = 1.2 + (0.4*(Mul53-3)) + (0.050*Mul20);
	else
		Result = 2.4 + (0.8*(Mul53-6)) + (0.1*Mul20);
	return Result;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
static void _act8945a_display_system_setting (void)
{
	uint8_t Status;
	float Value;
	BITFIELD_SYS0 BitField_Syst0;
	BITFIELD_SYS1 BitField_Syst1;

	htwi.RegMemAddr = ADD_SYSTEM0;
	htwi.LenData = 1;
	htwi.pData = (uint8_t*)&BitField_Syst0;
	Status = _twid_rd_wr(&htwi, TWI_RD);
	if(Status!=ACT8945A_RET_OK) return;

	Value = 2.3 + (BitField_Syst0.syslev*0.1);

	printf("\n\r");
	printf(" -I- System Registers ACT8945A \n\r");
	printf(" -I- SYST0 @0x00: 0x%02X \n\r", *htwi.pData);
	printf(" Reset Timer Setting:           %s \n\r", (BitField_Syst0.trst)? "65ms":"260ms");
	printf(" SYSLEV Mode Select:            %s \n\r", (BitField_Syst0.nsysmode)?"int":"shutdown");
	printf(" System Voltage Level Int.Mask: %s \n\r", (BitField_Syst0.nsyslevmsk)?"int":"no int");
	printf(" System Voltage Status:         %s \n\r", (BitField_Syst0.nsysstat)?"vsys<syslev":"vsys>syslev");
	printf(" SYSLEV Failing Treshold value: %.2fv \n\r", Value );

	htwi.RegMemAddr = ADD_SYSTEM1;
	htwi.pData = (uint8_t*)&BitField_Syst1;
	Status = _twid_rd_wr(&htwi, TWI_RD);
	if(Status!=ACT8945A_RET_OK) return;

	printf("\n\r");
	printf(" -I- SYST1 @0x01: 0x%02X \n\r", *htwi.pData);
	printf(" Master Off Ctrl, All regul:    %s \n\r", (BitField_Syst1.mstroff)?"OFF ":"ON ");
	printf(" Scratchpad Bits, free user:    0x%02x \n\r", BitField_Syst1.scratch);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Display detailled infos of the register ACT8865 and ACT8945A
static void _act8945a_display_voltage_setting (void)
{
	uint8_t data, x, Status;
	float x1;
	BITFIELD_CTRL1 BitField_Ctrl1;
	BITFIELD_CTRL2 BitField_Ctrl2;

	printf(" * Voltage Setting & State ACT8945A \n\r");

	for (x=0; x<NB_REG_VOLT ; x++)
	{
		htwi.RegMemAddr = VoltReg[x].Address;
		htwi.LenData = 1;
		htwi.pData = &data;
		Status = _twid_rd_wr(&htwi, TWI_RD);
		if(Status!=ACT8945A_RET_OK) return;
		x1= _act8945a_Convert_voltage_setting(data);

		htwi.RegMemAddr = VoltReg[x].Address+1;
		htwi.LenData = 1;
		Status = _twid_rd_wr(&htwi, TWI_RD);
		if(Status!=ACT8945A_RET_OK) return;

		printf(" -I- %s= %.2fv ", VoltReg[x].RegName, (float)x1);

		if (VoltReg[x].Address >= V_OUT4)
		{
			memcpy (&BitField_Ctrl2, &data, 1);
			printf("0x%02X %s", data, (BitField_Ctrl2.on)?"ON ":"OFF");
			printf(" %s", (BitField_Ctrl2.dis)?"OFF":"ON ");
			printf(" %s", (BitField_Ctrl2.lowiq)?"Normal":"LowPwr");
			printf("\tDelay:0x%02X", BitField_Ctrl2.delay);
			printf(" %s ", (BitField_Ctrl2.nfltmsk)?"En":"Dis");
			printf(" %s", (BitField_Ctrl2.ok)?"OK":".<Tresh");
		}
		else
		{
			memcpy (&BitField_Ctrl1, &data, 1);
			printf("0x%02X %s", data, (BitField_Ctrl1.on)?"ON  ":"OFF");
			printf(" %s", (BitField_Ctrl1.phase)?"180°":"Osc");
			printf(" %s", (BitField_Ctrl1.mode)?"PWM":"PowSav");
			printf("\tDelay:0x%02X", BitField_Ctrl1.delay);
			printf(" %s ", (BitField_Ctrl1.nfltmsk)?"En":"Dis");
			printf(" %s", (BitField_Ctrl1.ok)?"OK":".<Tresh");
		}
		printf("\n\r");
	}
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Display detailled infos register APCH (ACT8945A)
static uint8_t _act8945a_display_active_path_charger (void)
{
	BITFIELD_APCH71 BitField_APCH71;
	BITFIELD_APCH78 BitField_APCH78;
	BITFIELD_APCH79 BitField_APCH79;
	BITFIELD_APCH7A BitField_APCH7A;

	uint8_t data, Status = ACT8945A_RET_OK;

	printf("\n\r");
	printf(" -I- ACPH Registers ACT8945A \n\r");

	htwi.RegMemAddr = ADD_APCH_70;
	htwi.LenData = 1;
	htwi.pData = &data;
	Status = _twid_rd_wr(&htwi, TWI_RD);
	if (Status) _act8945a_twi_error();
	else
	{
		printf(" -I- APCH @0x70: Reserved 0x%02X \n\r", data);
		printf("\n\r");
	}

	htwi.RegMemAddr = ADD_APCH_71;
	htwi.pData = (uint8_t*)&BitField_APCH71;
	Status = _twid_rd_wr(&htwi, TWI_RD);
	if (Status) _act8945a_twi_error();
	else
	{
		printf(" -I- APCH @0x71: 0x%02X \n\r", *htwi.pData);
		printf(" Charge Suspend Control Input:        %X \n\r", BitField_APCH71.suschg);
		printf(" Bit 6 reserved \n\r");
		printf(" Total Charge Time-out Selection:     %02X \n\r", BitField_APCH71.tottimo);
		printf(" Precondition Charge Time-out Sel:    %02X \n\r", BitField_APCH71.pretimo);
		printf(" Input Over-Volt Prot.Threshold Sel:  %02X ", BitField_APCH71.ovpset);
		printf(" equ %s \n\r", &OvpSet[BitField_APCH71.ovpset][0]);
		printf("\n\r");
	}

	htwi.RegMemAddr = ADD_APCH_78;
	htwi.pData = (uint8_t*)&BitField_APCH78;
	Status = _twid_rd_wr(&htwi, TWI_RD);
	if (Status) _act8945a_twi_error();
	else
	{
		printf(" -I- APCH @0x78: 0x%02X \n\r", *htwi.pData);
		printf(" Charge Time-out Interrupt Status:     %X \n\r", BitField_APCH78.timrstat);
		printf(" Battery Temperature Interrupt Status: %X \n\r", BitField_APCH78.tempstat);
		printf(" Input Voltage Interrupt Status:       %X \n\r", BitField_APCH78.instat);
		printf(" Charge State Interrupt Status:        %X \n\r", BitField_APCH78.chgstat);
		printf(" Charge Timer Status                   %X \n\r", BitField_APCH78.timrdat);
		printf(" Temperature Status                    %X \n\r", BitField_APCH78.tempdat);
		printf(" Input Voltage Status                  %X \n\r", BitField_APCH78.indat);
		printf(" Charge State Machine Status           %X \n\r", BitField_APCH78.chgdat);
		printf("\n\r");
	}

	htwi.RegMemAddr = ADD_APCH_79;
	htwi.pData = (uint8_t*)&BitField_APCH79;
	Status = _twid_rd_wr(&htwi, TWI_RD);
	if (Status) _act8945a_twi_error();
	else
	{
		printf(" -I- APCH @0x79: 0x%02X \n\r", *htwi.pData);
		printf(" Total Charge Time-out Int Control:    %X \n\r", BitField_APCH79.timrtot);
		printf(" Batt.Temp.Int.Ctrl into valid range:  %X \n\r", BitField_APCH79.tempin);
		printf(" Inp.Voltage Int.Ctrl into valid range:%X \n\r", BitField_APCH79.incon);
		printf(" Charge State Int Ctrl into EOC state: %X \n\r", BitField_APCH79.chgeocin);
		printf(" PRECHARGE Time-out Int Ctrl:          %X \n\r", BitField_APCH79.timrpre);
		printf(" Batt.Temp.Int.Ctrl. out valid range:  %X \n\r", BitField_APCH79.tempout);
		printf(" Inp.Voltage Int.Ctrl. out valid range:%X \n\r", BitField_APCH79.indis);
		printf(" Charge State Int.Ctrl. out EOC state: %X \n\r", BitField_APCH79.chgeocout);
		printf("\n\r");
	}

	htwi.RegMemAddr = ADD_APCH_7A;
	htwi.pData = (uint8_t*)&BitField_APCH7A;
	Status = _twid_rd_wr(&htwi, TWI_RD);
	if (Status) _act8945a_twi_error();
	else
	{
		printf(" -I- APCH @0x7A: 0x%02X \n\r", *htwi.pData);
		printf(" Bit 7-6 reserved:                     %02X \n\r", BitField_APCH7A.ruf76);
		printf(" Charge State:                         %02X ", BitField_APCH7A.cstate);
		printf(" %s \n\r", &ChargState[BitField_APCH7A.cstate][0]);
		printf(" Bit 3-2 reserved:                     %02X \n\r", BitField_APCH7A.ruf32);
		printf(" ACIN Status:                          %X \n\r", BitField_APCH7A.acinstat);
		printf(" Bit 0 reserved:                       %X \n\r", BitField_APCH7A.ruf0);
		printf("\n\r");
	}
	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Display the value of the register ACT8865 and ACT8945A
static uint8_t _act8945a_display_syslev_failing_threshold (void)
{
	BITFIELD_SYS0 BitField_SYS0;
	uint8_t Status = ACT8945A_RET_OK;
	float Value;

	htwi.RegMemAddr = ADD_SYSTEM0;
	htwi.LenData = 1;
	htwi.pData = (uint8_t*)&BitField_SYS0;
	Status = _twid_rd_wr(&htwi, TWI_RD);
	if (Status) _act8945a_twi_error();
	else
	{
		Value = 2.3 + (BitField_SYS0.syslev*0.1);
		printf("\n\r");
		printf(" -I- SYSLEV Failing Treshold value:0x%02X  %.2fv \n\r", BitField_SYS0.syslev, Value );
	}
	return Status;
}
//----------------------------------------------------------------------------
//        Exported functions
//----------------------------------------------------------------------------

// Configure the state (ON/OFF) of the regulator OUT1 to OUT3
// Set bit to 1 to enable the regulator, clear bit to 0 to disable the regulator.
// Input: VOUT base register address
uint8_t act8945a_set_regulator_state_out1to3 (uint8_t RegVout, REG_ON_OFF_enum ON_OFF)
{
	uint8_t Status = ACT8945A_RET_OK;
	BITFIELD_CTRL1 BitField_Ctrl1;

	if (!_is_twi_ready(&htwi)) return ACT8945A_RET_NOK;
	if (RegVout!=V_OUT1 && RegVout!=V_OUT2 && RegVout!=V_OUT3 ) return ACT8945A_RET_NOK;

	//enable/disable output
	htwi.RegMemAddr = RegVout+1;
	htwi.LenData = 1;
	htwi.pData = (uint8_t*)&BitField_Ctrl1;
	Status = _twid_rd_wr(&htwi, TWI_RD);
	if (Status) return Status;
	BitField_Ctrl1.on = (ON_OFF)? 1:0 ;
	return Status= _twid_rd_wr(&htwi, TWI_WR);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Configure the state (ON/OFF) of the regulator OUT4 to OUT7
// Input: VOUT base register address
uint8_t act8945a_set_regulator_state_out4to7 (uint8_t RegVout, REG_ON_OFF_enum ON_OFF)
{
	uint8_t Status = ACT8945A_RET_OK;
	BITFIELD_CTRL2 BitField_Ctrl2;

	if (!_is_twi_ready(&htwi)) return ACT8945A_RET_NOK;
	if (RegVout!=V_OUT4 && RegVout!=V_OUT5 && RegVout!=V_OUT6 && RegVout!=V_OUT7 ) return ACT8945A_RET_NOK;

	//enable/disable output
	htwi.RegMemAddr = RegVout+1;
	htwi.LenData = 1;
	htwi.pData = (uint8_t*)&BitField_Ctrl2;
	Status = _twid_rd_wr(&htwi, TWI_RD);
	if (Status) return Status;
	BitField_Ctrl2.on = (ON_OFF)? 1:0 ;
	return Status = _twid_rd_wr(&htwi, TWI_WR);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Set the ouptut value of the regulator OUT4 to OUT7
// Input: Vout: Value in mv
//      : RegVout base register address
uint8_t act8945a_set_regulator_voltage_out4to7 (uint8_t RegVout, uint16_t VOut)
{
	uint8_t data, RegSet;

	if (VOut>3900) return ACT8945A_RET_NOK;
	if (RegVout!=V_OUT4 && RegVout!=V_OUT5 && RegVout!=V_OUT6 && RegVout!=V_OUT7 ) return ACT8945A_RET_NOK;
	if (VOut<600) VOut = 600; // Min 0.6v

	if (VOut<1200) RegSet = (VOut-600)/25;
	else if (VOut>=1200 && VOut<2400) RegSet = 0x18+((VOut-1200)/50);
	else if (VOut>=2400 && VOut<=3900) RegSet = 0x30+((VOut-2400)/100);
	else return ACT8945A_RET_NOK;

	//Set Output Voltage Selection
	data = (RegSet&0x3F); // Bit[7:6] reserved
	htwi.pData = &data;
	htwi.RegMemAddr = RegVout;
	htwi.LenData = 1;
	return _twid_rd_wr(&htwi, TWI_WR);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// System Voltage Level Interrupt Mask. SYSLEV interrupt is masked by default,
// set to 1 to unmask this interrupt.
uint8_t act8945a_set_system_voltage_level_interrupt (INT_ON_OFF_enum ON_OFF)
{
	BITFIELD_SYS0 BitField_SYS0;
	uint8_t Status = ACT8945A_RET_OK;

	if (!_is_twi_ready(&htwi)) return ACT8945A_RET_NOK;

	htwi.RegMemAddr = ADD_SYSTEM0;
	htwi.LenData = 1;
	htwi.pData = (uint8_t*)&BitField_SYS0;
	Status = _twid_rd_wr(&htwi, TWI_RD);
	if (Status) _act8945a_twi_error();
	else
	{
		BitField_SYS0.nsyslevmsk = ON_OFF;
		Status = _twid_rd_wr(&htwi, TWI_WR);
	}
	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Regulator Fault Mask Control.
// Set bit to 1 enable fault-interrupts, clear bit to 0 to disable fault-interrupts
// Input: VOUT base register address
uint8_t act8945a_set_regulator_fault_interrupt (uint8_t RegVout, INT_ON_OFF_enum ON_OFF)
{
	uint8_t Status = ACT8945A_RET_OK;
	BITFIELD_CTRL1 BitField_Ctrl1;
	BITFIELD_CTRL2 BitField_Ctrl2;

	if (!_is_twi_ready(&htwi)) return ACT8945A_RET_NOK;

	htwi.RegMemAddr = RegVout+1;
	htwi.LenData = 1;

	switch (RegVout)
	{
	case V_OUT1:
	case V_OUT2:
	case V_OUT3:
		htwi.pData = (uint8_t*)&BitField_Ctrl1;
		Status = _twid_rd_wr(&htwi, TWI_RD);
		if (Status) return ACT8945A_RET_NOK;
		BitField_Ctrl1.nfltmsk = (ON_OFF)? 1:0 ;
		break;

	case V_OUT4:
	case V_OUT5:
	case V_OUT6:
	case V_OUT7:
		htwi.pData = (uint8_t*)&BitField_Ctrl2;
		Status = _twid_rd_wr(&htwi, TWI_RD);
		if (Status) return ACT8945A_RET_NOK;
		BitField_Ctrl2.nfltmsk = (ON_OFF)? 1:0 ;
		break;

	default:
		break;
	}
	//set Int
	return Status = _twid_rd_wr(&htwi, TWI_WR);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Set or Clear an APCH interrupt
// Set bit to 1 enable interrupt,
// Clear bit to 0 to disable interrupt

uint8_t act8945a_set_APCH_interrupt (INT_APCH_enum IntType, INT_ON_OFF_enum ON_OFF)
{
	uint8_t Status = ACT8945A_RET_OK;
	BITFIELD_APCH78 BitField_APCH78;
	BITFIELD_APCH79 BitField_APCH79;

	if (!_is_twi_ready(&htwi)) return ACT8945A_RET_NOK;

	htwi.RegMemAddr = ADD_APCH_78;
	htwi.LenData = 1;
	htwi.pData = (uint8_t*)&BitField_APCH78;
	Status = _twid_rd_wr(&htwi, TWI_RD);

	htwi.RegMemAddr = ADD_APCH_79;
	htwi.LenData = 1;
	htwi.pData = (uint8_t*)&BitField_APCH79;
	Status = _twid_rd_wr(&htwi, TWI_RD);

	switch (IntType)
	{
		// Interrupt generated any time the input supply is disconnected when
		// INSTAT[] bit is set to 1 and the INDIS[] bit is set to 1.
	case INPUT_VOLTAGE_OUT_VALID_RANGE_INT_CTRL: // Interrupt
		BitField_APCH78.instat = (ON_OFF)? 1:0 ;
		BitField_APCH79.indis = (ON_OFF)? 1:0 ;
		break;

		// Interrupt generated any time the input supply is connected when
		// INSTAT[] bit is set to 1 and the INCON[] bit is set to 1.
	case INPUT_VOLTAGE_INTO_VALID_RANGE_INT_CTRL:
		BitField_APCH78.instat = (ON_OFF)? 1:0 ;
		BitField_APCH79.incon = (ON_OFF)? 1:0 ;
		break;

		// Interrupts based upon the status of the battery temperature.
		// Set the TEMPOUT[] bit to 1 and TEMPSTAT[] bit to 1 to generate
		// an interrupt when battery temperature goes out of the valid
		// temperature range.
	case BATTERY_TEMPERATURE_OUT_RANGE_INT_CTRL:
		BitField_APCH78.tempstat = (ON_OFF)? 1:0 ;
		BitField_APCH79.tempout = (ON_OFF)? 1:0 ;
		break;

		// Interrupts based upon the status of the battery temperature.
		// Set the TEMPIN[] bit to 1 and TEMPSTAT[] bit to 1 to generate
		// an interrupt when battery temperature returns to the valid range.
	case BATTERY_TEMPERATURE_INTO_RANGE_INT_CTRL:
		BitField_APCH78.tempstat = (ON_OFF)? 1:0 ;
		BitField_APCH79.tempin = (ON_OFF)? 1:0 ;
		break;

		// Interrupt when the charger state machine goes into the
		// END-OF-CHARGE (EOC). Set CHGEOCIN[] bit to 1 and CHGSTAT[] bit
		// to 1 to generate an interrupt when the charger state machine goes
		// into the END-OF-CHARGE (EOC)state.
	case CHARGE_STATE_INTO_EOC_STATE_INT_CTRL:
		BitField_APCH78.chgstat = (ON_OFF)? 1:0 ;
		BitField_APCH79.chgeocin = (ON_OFF)? 1:0 ;
		break;

		// Interrupt when the charger state machine exit the
		// END-OF-CHARGE (EOC). Set CHGEOCOUT[] bit to 1 and CHGSTAT[] bit
		// to 1 to generate an interrupt when the charger state machine exits
		// the EOC state.
	case CHARGE_STATE_OUT_EOC_STATE_INT_CTRL:
		BitField_APCH78.chgstat = (ON_OFF)? 1:0 ;
		BitField_APCH79.chgeocout = (ON_OFF)? 1:0 ;
		break;

		// Interrupts based upon the status of the charge timers.
		// Set the TIMRPRE[] bit to 1 and TIMRSTAT[] bit to 1 to generate an
		// interrupt when the Precondition Timer expires.
	case PRECHARGE_TIME_OUT_INT_CTRL:
		BitField_APCH78.timrstat = (ON_OFF)? 1:0 ;
		BitField_APCH79.timrpre = (ON_OFF)? 1:0 ;
		break;

		// Set the TIMRTOT[] bit to 1 and TIMRSTAT[] bit to 1 to generate an
		// interrupt when the Total-Charge Timer expires.
	case TOTAL_CHARGE_TIME_OUT_INT_CTRL:
		BitField_APCH78.timrstat = (ON_OFF)? 1:0 ;
		BitField_APCH79.timrtot = (ON_OFF)? 1:0 ;
		break;

	default:
		break;
	}

	// Write configuration to registers
	htwi.RegMemAddr = ADD_APCH_78;
	Status = _twid_rd_wr(&htwi, TWI_WR);

	htwi.RegMemAddr = ADD_APCH_79;
	Status = _twid_rd_wr(&htwi, TWI_WR);

	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Disable all interrupt from APCH
uint8_t act8945a_disable_all_apch_interrupt (void)
{
	uint8_t Status = ACT8945A_RET_OK;

	Status |= act8945a_set_APCH_interrupt(CHARGE_STATE_OUT_EOC_STATE_INT_CTRL, ACT8945A_INT_OFF);
	Status |= act8945a_set_APCH_interrupt(INPUT_VOLTAGE_OUT_VALID_RANGE_INT_CTRL, ACT8945A_INT_OFF);
	Status |= act8945a_set_APCH_interrupt(BATTERY_TEMPERATURE_OUT_RANGE_INT_CTRL, ACT8945A_INT_OFF);
	Status |= act8945a_set_APCH_interrupt(PRECHARGE_TIME_OUT_INT_CTRL, ACT8945A_INT_OFF);
	Status |= act8945a_set_APCH_interrupt(CHARGE_STATE_INTO_EOC_STATE_INT_CTRL, ACT8945A_INT_OFF);
	Status |= act8945a_set_APCH_interrupt(INPUT_VOLTAGE_INTO_VALID_RANGE_INT_CTRL, ACT8945A_INT_OFF);
	Status |= act8945a_set_APCH_interrupt(BATTERY_TEMPERATURE_INTO_RANGE_INT_CTRL, ACT8945A_INT_OFF);
	Status |= act8945a_set_APCH_interrupt(TOTAL_CHARGE_TIME_OUT_INT_CTRL, ACT8945A_INT_OFF);
	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Set the Programmable System Voltage Monitor
// Input: Value in mv from 2300mv to 3800mv
uint8_t act8945a_set_system_voltage_level (uint16_t Value)
{
	BITFIELD_SYS0 BitField_SYS0;
	uint8_t Status = ACT8945A_RET_OK;

	if (Value<2300 || Value>3800) return ACT8945A_RET_NOK;
	htwi.RegMemAddr = ADD_SYSTEM0;

	Status = _twid_rd_wr(&htwi, TWI_RD);
	htwi.LenData = 1;
	htwi.pData = (uint8_t*)&BitField_SYS0;
	if (Status) _act8945a_twi_error();
	else
	{
		BitField_SYS0.syslev = (Value-2300)/100;
		Status = _twid_rd_wr(&htwi, TWI_WR);

#ifdef ECHO_CONSOLE
		_act8945a_display_syslev_failing_threshold();
#endif
	}
	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Charge Current Selection Input
// In USB-Mode: CHGLEV = 1 -> I charge 450mA
//               CHGLEV = 0 -> I charge 1000mA
uint8_t act8945a_set_state_CHGLEV_pin (CHG_LEVEL_enum State)
{
	return 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Low Battery Indicator Output. nLBO is asserted low whenever the voltage
// at LBI is lower than 1.2V,
uint8_t act8945a_get_state_lbo_pin (void)
{
	return 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Init TWI interface
uint8_t act8945a_begin (void)
{
	uint8_t data, Status = ACT8945A_RET_OK;

	memset ((void*)&htwi, 0x00, sizeof(htwi));
	if (!_is_twi_ready(&htwi))
	{
		// Configure pins
		pio_configure(pins_ctrl_act8945a, ARRAY_SIZE(pins_ctrl_act8945a));

		// Set TWI interface
		memset ((uint8_t*)&htwi, 0x00, sizeof(htwi));
		htwi.IdTwi = ACT8945A_TWI_ID;
		htwi.Twck = TWCK_400K;
		trace_info("@0x%02X TWCK:%dKHz \n\r", ACT8945A_ADDRESS, TWCK_400K/1000);
		Status = _twi_handler_init (&htwi);
		htwi.PeriphAddr = ACT8945A_ADDRESS;
		trace_info("act8945A @0x%02X TWCK:%dKHz \n\r",
			   (unsigned int)htwi.PeriphAddr,
			   (unsigned int)htwi.Twck/1000);
		Status = _twi_handler_init (&htwi);

		htwi.AddSize = 1;
		htwi.pData = &data;
		htwi.LenData = 1;
		htwi.Status |= TWI_STATUS_READY;
	}
	htwi.RegMemAddr = ADD_SYSTEM0;
	Status = _twid_rd_wr(&htwi, TWI_RD);
	if (!data) Status = ACT8945A_RET_NOK;
	else Status = ACT8945A_RET_OK;
	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Config interrupt on nIRQ pin to MPU
void act8945a_active_interrupt (void)
{
	pio_configure_it(&pins_irq_act8945a[0]);
	pio_enable_it(&pins_irq_act8945a[0]);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Disable PMIC I2C
// Fonction called to disable the TWI interface
// Issue on PMIC revision 304 and 305
void ACT8945A_disable_twi (void)
{
	uint8_t data;

	htwi.pData = &data;
	htwi.LenData = 1;

	//305
	htwi.RegMemAddr = 0xB;
	data = 0xEF;
	_twid_rd_wr(&htwi, TWI_WR);

	htwi.RegMemAddr = 0x2;
	data = 0x07;
	_twid_rd_wr(&htwi, TWI_WR);

	htwi.RegMemAddr = 0x3;
	data = 0x01;
	_twid_rd_wr(&htwi, TWI_WR);

	//304
	htwi.RegMemAddr = 0xB;
	data = 0xEE;
	_twid_rd_wr(&htwi, TWI_WR);

	htwi.RegMemAddr = 0x2;
	data = 0x07;
	_twid_rd_wr(&htwi, TWI_WR);

	htwi.RegMemAddr = 0x3;
	data = 0x01;
	_twid_rd_wr(&htwi, TWI_WR);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

uint8_t act8945a_test (void)
{
	uint8_t Status = ACT8945A_RET_OK;
	uint16_t x;

	if (!_is_twi_ready(&htwi)) {
		printf("\n\r -I- ACT8945A Reset State \n\r");
		Status = act8945a_begin();
		if (Status != ACT8945A_RET_OK)
		{
			_act8945a_twi_error();
			return Status;
		}
	}
	// Dump registers and display
	_act8945a_registers_dump();
	_act8945a_registers_dump_APCH();
	_act8945a_display_active_path_charger();
	_act8945a_display_voltage_setting();
	act8945a_set_system_voltage_level(3100);
	_act8945a_display_system_setting();

	Status = act8945a_set_system_voltage_level_interrupt(ACT8945A_INT_OFF);
	Status = act8945a_disable_all_apch_interrupt();

	act8945a_set_APCH_interrupt(CHARGE_STATE_INTO_EOC_STATE_INT_CTRL, ACT8945A_INT_ON);
	act8945a_set_APCH_interrupt(CHARGE_STATE_OUT_EOC_STATE_INT_CTRL, ACT8945A_INT_ON);

	act8945a_set_APCH_interrupt(PRECHARGE_TIME_OUT_INT_CTRL, ACT8945A_INT_ON);
	act8945a_set_APCH_interrupt(TOTAL_CHARGE_TIME_OUT_INT_CTRL, ACT8945A_INT_ON);

	_act8945a_registers_dump();
	_act8945a_registers_dump_APCH();

	act8945a_active_interrupt();

	// Change step by step (25mv) the output voltage OUT6 from 0.6v to max.
	act8945a_set_regulator_state_out4to7 (V_OUT6, ACT8945A_REG_ON);
	for (x=500; x<3300; x+=25)
	{
		act8945a_set_regulator_voltage_out4to7 (V_OUT6, x);
		_act8945a_delay_ms(10);
	}
	act8945a_set_regulator_voltage_out4to7 (V_OUT6, 600);
	act8945a_set_regulator_state_out4to7 (V_OUT6, ACT8945A_REG_OFF);

	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// End of file
