/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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

/** \addtogroup secumod_module Working with Security Module
 * \ingroup peripherals_module
 * The SECUMOD driver provides the interface to configure and use the SECUMOD (Security Module).
 *
 * It provides secure functions to avoid attacks on the chip.
 *
 * To use these functions,the user has to follow these few steps:
 * <ul>
 * <li> Configure the SECUMOD according to its requirements and special needs, which
 * could be broken down into several parts:
 * - Configure PIOBU pins and JTAG pins protection mode if necessary</li>
 * - Configure secure memories' access rights</li>
 * - Configure scrambling mode</li>
 * - Configure the interrupts
 </li>
 * <li> Access violation occurs once there's no right to access the secure memories. </li>
 * <li> Once attacks occur the tamper info will be recorded or.</li>
 * <li> Lower 6 Kbytes and 512-bit register bank will be erasing automatically incase of intrusion.</li>
 * </ul>
 *
 * \section Usage
 * <ul>
 * <li> Initialize the SECUMOD peripheral using secumod_set_auto_backup(), secumod_set_scrambling()
 * and secumod_piobu_config().
 * <li> Enable & disable SECUMOD interrupt using secumod_enable_it() and secumod_disable_it().
 * <li> Get interrupt mask using secumod_get_normal_it_mask().
 * <li> Register SECUMOD_BMPR and SECUMOD_NMPR can be toggled the appearance using secumod_toggle_protection_reg().
 * <li> Get & set protections in normal mode using secumod_get_normal_mode_protections() and secumod_set_normal_mode_protections().
 * <li> Get & set protections in backup mode using secumod_get_backup_mode_protections() and secumod_set_backup_mode_protections().
 * <li> Get & set protections in wakeup mode using secumod_get_wakeup_protections() and secumod_set_wakeup_protections().
 * <li> Set the secure RAM's access rights using secumod_set_ram_access_rights().
 * <li> Get & set RAM Scrambling Key using secumod_get_scrambling_key() and secumod_set_scrambling_key().
 * <li> Read & write the secure RAM using secumod_read_internal_memory() and secumod_write_internal_memory()
  or directly by SECURAM->SECURAM_4KB[], SECURAM->SECURAM_1KB[] and SECURAM->SECURAM_256b[].
 * <li> Enable/Disable alarm regenerated periodically while intrusion is maintained
 using secumod_periodic_alarm().
 * <li> PIOBU pins can set to static or dynamic intrusion mode using secumod_spiobu_set_static_mode()
  or secumod_piobu_set_dynamic_mode();
 * <li> JTAG pins protection options can be set using secumod_set_jtag_protection();
 * <li> Tuning dynamic signatures by period and threshold using secumod_dynamic_signatures_tuning();
 * <li> Using secumod_software_protection() can start clear the secure RAM;
 * <li> Switch to normal or backup mode using secumod_switch_to_normal_mode() or secumod_switch_to_backup_mode();
 * <li> Two dedicated ISR are used: SECUMOD_IrqHandler() for SECUMOD's alarm and
 SECURAM_IrqHandler() for secure RAM;
 * </li>
 * </ul>
 *
 * For more accurate information, please look at datasheet “SAMA5D2 Security
 *  Module” (Atmel literature No. 44036).
 *
 * \see secumod_driver
 *
 * Related files :\n
 * \ref secumodc.c\n
 * \ref secumodc.h.\n
*/
/*@{*/
/*@}*/

/**
 * \file
 *
 * Interface for Security Module (SECUMOD).
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "secumod.h"

#include "peripherals/aic.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/rtc.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

struct _secumod {
	/** tamper information */
	struct _tamper_info tamper_info;

	/** Callback for access violations */
	secumod_access_violation_callback_t access_callback;

	/** Callback for internal memory erased */
	secumod_memory_erased_callback_t erased_callback;

	/** Callback for tamper */
	secumod_tamper_callback_t tamper_callback;
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** SECUMOD driver instance */
static struct _secumod secumod_inst;

/*----------------------------------------------------------------------------
 *        Interrupt Service Routines
 *----------------------------------------------------------------------------*/

/**
 * \brief Interrupt handler for SECURAM.
 */
static void securam_irq_handler(void)
{
	uint32_t status, protections;
	uint32_t tmp;
	uint32_t i;

	protections = secumod_get_normal_mode_protections();

	/* Read Periodic Interval Timer Value, also clears the PICNT */
	(void)pit_get_pivr();

	/* Read RAM access violation flags */
	status = SECUMOD->SECUMOD_RAMACCSR;

	for (i = 0; i < SECUMOD_RAM_REGION_NUM; i++)
	{
		tmp = (status >> (2 * i)) & 3;
		if (tmp != SECUMOD_RAMACCSR_NO_VIOLATION && secumod_inst.access_callback)
			secumod_inst.access_callback(i, tmp);
	}

	/* process the end of erase signalling */
	do {
		status = SECUMOD->SECUMOD_SYSR;
	} while (status & SECUMOD_SYSR_ERASE_ON);

	if (SECUMOD_SYSR_ERASE_DONE == (status & SECUMOD_SYSR_ERASE_DONE))
	{
		/* Clear the flag ERASE_DONE */
		SECUMOD->SECUMOD_SYSR = SECUMOD_SYSR_ERASE_DONE;

		/* call the callback routine */
		if (secumod_inst.erased_callback)
			secumod_inst.erased_callback();
	}

	/* wait at least one slow clock */
	while ((1000000 / pmc_get_slow_clock()) >=
			((pit_get_piir() & PIT_PIIR_PICNT_Msk) >> PIT_PIIR_PICNT_Pos));

	/* Clear RAM access violation flags */
	SECUMOD->SECUMOD_RAMACCSR = status;

	/* Read alarm status */
	status = secumod_get_status();

	/* Clear corresponding alarm flag bit to make sure the protection can
	 * be detected next time when the corresponding tamper happens */
	secumod_clear_status(status);

	secumod_set_normal_mode_protections(protections);
}

/**
 * \brief Interrupt handler for SECUMOD.
 */
static void secumod_irq_handler(void)
{
	uint32_t status, index, protections;
	struct _tamper_detail *detail;

	/* Read Periodic Interval Timer Value, also clears the PICNT */
	(void)pit_get_pivr();

	/* Read alarm status */
	status = secumod_get_status();

	/* Disable the interrupt */
	protections = secumod_get_normal_it_mask();
	secumod_disable_it(status & protections);
	//secumod_set_normal_mode_protections((~status) & protections);

	/*Clear the tamper_info bits before checking the tamper type*/
	secumod_inst.tamper_info.jtag_sel_ca5 = false;
	secumod_inst.tamper_info.jtag_tck_tms = false;

	/* Read auxiliary status if needed */
	if (status & SECUMOD_SR_JTAG) {
		uint32_t jtag = SECUMOD->SECUMOD_ASR;
		secumod_inst.tamper_info.jtag_sel_ca5 = (jtag & SECUMOD_ASR_JTAG) != 0;
		secumod_inst.tamper_info.jtag_tck_tms = (jtag & SECUMOD_ASR_TCK) != 0;
	}

	/* Read tamper counter */
	secumod_inst.tamper_info.tampers = rtc_get_tamper_event_counter();

	/* Update the total counter */
	if (secumod_inst.tamper_info.total_tampers < 0xFFFFFFF0)
		secumod_inst.tamper_info.total_tampers += secumod_inst.tamper_info.tampers;

	/* Read tamper information */
	index = (secumod_inst.tamper_info.tampers >= 2 ) ? 2 : secumod_inst.tamper_info.tampers;
	while (index) {
		index--;
		detail = &(secumod_inst.tamper_info.details[index]);
		rtc_get_tamper_time(&detail->time, index);
		rtc_get_tamper_date(&detail->date, index);
		detail->source = rtc_get_tamper_source(index);
	}

	/* call the callback routine */
	if (secumod_inst.tamper_callback)
		secumod_inst.tamper_callback();

	/* ==== ATTENTION ====
	* it is recommended to wait at lease one slow clock period after reading
	* the Status register before clearing the status bits. */

	/* wait at least one slow clock */
	while ((1000000 / pmc_get_slow_clock()) >=
			((pit_get_piir() & PIT_PIIR_PICNT_Msk) >> PIT_PIIR_PICNT_Pos)) ;

	/* Clear corresponding alarm flag bit */
	secumod_clear_status(status);

	/* Enable the interrupt */
	secumod_enable_it(status & protections);

	/* To only get an interrupt when tamper error happens without Auto
	 * Erasing SECURAM, the following line need to be commented */
	//secumod_set_normal_mode_protections(protections);
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Initialize SECUMOD driver instance.
 */
void secumod_initialize(void)
{
	/* Enable SECUMOD module clock in PMC */
	pmc_enable_peripheral(ID_SECUMOD);

	secumod_inst.tamper_info.total_tampers = 0;
	secumod_inst.tamper_info.tampers = 0;
	secumod_inst.tamper_info.jtag_sel_ca5 = false;
	secumod_inst.tamper_info.jtag_tck_tms = false;

	/* Set irq handler */
	aic_set_source_vector(ID_SECUMOD, secumod_irq_handler);
	aic_set_source_vector(ID_SECURAM, securam_irq_handler);
}

/**
 * \brief Set the callback function for Access Violations in SECUMOD.
 * \param callback Pointer to callback function.
 */
void secumod_set_access_callback(secumod_access_violation_callback_t callback)
{
	secumod_inst.access_callback = callback;
}

/**
 * \brief Set the callback function for Internal Memory Erased in SECUMOD.
 * \param callback Pointer to callback function.
 */
void secumod_set_erased_callback(secumod_memory_erased_callback_t callback)
{
	secumod_inst.erased_callback = callback;
}

/**
 * \brief Set the callback function for tamper in SECUMOD.
 * \param callback Pointer to callback function.
 */
void secumod_set_tamper_callback(secumod_tamper_callback_t callback)
{
	secumod_inst.tamper_callback = callback;
}

/**
 * \brief Get tamper information
 * \return Pointer to tamper information structure.
 */
struct _tamper_info * secumod_get_tamper_info(void)
{
	return &secumod_inst.tamper_info;
}

/**
 * \brief Switch to backup mode.
 */
void secumod_switch_to_backup_mode(void)
{
	SECUMOD->SECUMOD_CR = SECUMOD_CR_BACKUP;
}

/**
 * \brief Switch to normal mode.
 */
void secumod_switch_to_normal_mode(void)
{
	SECUMOD->SECUMOD_CR = SECUMOD_CR_NORMAL;
}

/**
 * \brief Start clear content of SECUMOD internal RAM 4Kbyte and 256bits.
 */
void secumod_software_protection(void)
{
	SECUMOD->SECUMOD_CR = SECUMOD_CR_SWPROT;
}

/**
 * \brief Enable/Disable Auto-Backup
 * \param enable Enable auto-backup if true, disable otherwise.
 */
void secumod_set_auto_backup(bool enable)
{
	if (enable)
		SECUMOD->SECUMOD_CR = SECUMOD_CR_AUTOBKP_AUTO_SWITCH;
	else
		SECUMOD->SECUMOD_CR = SECUMOD_CR_AUTOBKP_SW_SWITCH;
}

/**
 * \brief Enable/Disable Memory Scrambling
 * \param enable Enable memory scrambling if true, disable otherwise.
 */
void secumod_set_scrambling(bool enable)
{
	if (enable)
		SECUMOD->SECUMOD_CR = SECUMOD_CR_SCRAMB_ENABLE;
	else
		SECUMOD->SECUMOD_CR = SECUMOD_CR_SCRAMB_DISABLE;
}

/**
 * \brief Toggle normal or backup protection registers appear and disappear.
 */
void secumod_toggle_protection_reg(void)
{
	SECUMOD->SECUMOD_CR = SECUMOD_CR_KEY_TOGGLE;
}

/**
 * \brief Get system status.
 *
 * \return system status.
 */
uint32_t secumod_get_system_status(void)
{
	return SECUMOD->SECUMOD_SYSR;
}

/**
 * \brief Set system status.
 *
 * \param status system status to set.
 */
void secumod_set_system_status(uint32_t status)
{
	SECUMOD->SECUMOD_SYSR = status;
}

/**
 * \brief Get status register.
 *
 * \return status register.
 */
uint32_t secumod_get_status(void)
{
	return SECUMOD->SECUMOD_SR;
}

/**
 * \brief Clear status register bits.
 *
 * \param status status bits to clear.
 */
void secumod_clear_status(uint32_t status)
{
	SECUMOD->SECUMOD_SCR = status;
}

/**
 * \brief Configures PIOBU pin instances.
 *
 * \param pBiobu    Pointer to struct _secumod_piobu instances list.
 * \param dwSize    Number of PIOBU pin instances.
 */
void secumod_piobu_config(struct _secumod_piobu *list, uint32_t size)
{
	uint32_t uwI;
	uint32_t dwTmp;
	uint8_t ucPiobu;
	struct _secumod_piobu *pBiobu;

	for (uwI = 0; uwI < size; uwI++) {
		ucPiobu = list[uwI].pinIndex;
		pBiobu = &list[uwI];

		/* AFV and RFV fields must be set to 0 when dynamic intrusion is selected. */
		if (pBiobu->dynamic) {
		    dwTmp = 0;
		} else {
		    dwTmp = (pBiobu->afv << SECUMOD_PIOBU_AFV_Pos ) | (pBiobu->rfv << SECUMOD_PIOBU_RFV_Pos);
		}

		if (pBiobu->mode) {
			dwTmp |= SECUMOD_PIOBU_OUTPUT;
			if (pBiobu->outputLevel)
				dwTmp |= SECUMOD_PIOBU_PIO_SOD;
		}

		dwTmp |= pBiobu->pullUpState << SECUMOD_PIOBU_PULLUP_Pos;

		if (pBiobu->scheduled)
			dwTmp |= SECUMOD_PIOBU_SCHEDULE;

		if (pBiobu->inputDefaultLevel)
			dwTmp |= SECUMOD_PIOBU_SWITCH;

		/* FILTER3_5 and DYNSTAT fields exist only for even PIOBUs */
		if (0 == (ucPiobu & 0x01))
		{
			if (pBiobu->dynamic)
				dwTmp |= SECUMOD_PIOBU_DYNSTAT;

			if (pBiobu->filter3_5)
				dwTmp |=  SECUMOD_PIOBU_FILTER3_5;
		}

		SECUMOD->SECUMOD_PIOBU[ucPiobu] = dwTmp;
	}
}

/**
 * \brief Change a pair of PIOBU pins to dynamic intrusion mode.
 *
 * \param pair Pair index, range 0~3.
 */
void secumod_piobu_set_dynamic_mode(uint8_t pair)
{
	uint32_t tmp;
	volatile uint32_t *reg;

	reg = &SECUMOD->SECUMOD_PIOBU[pair * 2];

	tmp = reg[0] & ~(SECUMOD_PIOBU_RFV_Msk | SECUMOD_PIOBU_AFV_Msk);
	reg[0] = tmp | SECUMOD_PIOBU_DYNSTAT;

	tmp = reg[1] & ~(SECUMOD_PIOBU_RFV_Msk | SECUMOD_PIOBU_AFV_Msk);
	reg[1] = tmp;
}

/**
 * \brief Change a pair of PIOBU pins to static intrusion mode.
 *
 * \param pair          Pair index, range 0~3.
 * \param reset_filter0 Reset filter value of the 1st pin in the pair, range 0~9.
 * \param alarm_filter0 Alarm filter value of the 1st pin in the pair, range 0~9.
 * \param reset_filter1 Reset filter value of the 2nd pin in the pair, range 0~9.
 * \param alarm_filter1 Alarm filter value of the 2nd pin in the pair, range 0~9.
 */
void secumod_piobu_set_static_mode(uint8_t pair,
		uint8_t reset_filter0, uint8_t alarm_filter0,
		uint8_t reset_filter1, uint8_t alarm_filter1)
{
	uint32_t tmp;
	volatile uint32_t *reg;

	reg = &SECUMOD->SECUMOD_PIOBU[pair * 2];

	tmp = reg[0];
	tmp &= ~(SECUMOD_PIOBU_DYNSTAT | SECUMOD_PIOBU_RFV_Msk | SECUMOD_PIOBU_AFV_Msk);
	reg[0] = tmp | SECUMOD_PIOBU_RFV(reset_filter0) | SECUMOD_PIOBU_AFV(alarm_filter0);

	tmp = reg[1];
	tmp &= ~(SECUMOD_PIOBU_RFV_Msk | SECUMOD_PIOBU_AFV_Msk);
	reg[0] = tmp | SECUMOD_PIOBU_RFV(reset_filter1) | SECUMOD_PIOBU_AFV(alarm_filter1);
}

/**
 * \brief Set JTAG protection options of SECUMOD.
 *
 * \param force_reset       Whether preventing debug state and BSD (Boundary Scan Diagnostics) to work.
 * \param debug_permissions Debug permissions.
 * \param ack_monitoring    Whether monitor the DBGACK signal.
 */
void secumod_set_jtag_protection(bool force_reset, uint8_t debug_permissions,
		bool ack_monitoring)
{
	uint32_t jtag_cr;

	jtag_cr = debug_permissions << SECUMOD_JTAGCR_CA5_DEBUG_MODE_Pos;

	if (force_reset)
		jtag_cr |= SECUMOD_JTAGCR_FNTRST;

	if (ack_monitoring)
		jtag_cr |= SECUMOD_JTAGCR_CA5_DEBUG_MON;

	SECUMOD->SECUMOD_JTAGCR = jtag_cr;
}

/**
 * \brief Tuning dynamic signatures by period and threshold.
 *
 * \param period        Signature Clock Period.
 * \param detection_thr Error Detection Threshold.
 * \param reset_thr     Error Counter Reset Threshold.
 */
void secumod_dynamic_signatures_tuning(uint16_t period,
		uint8_t detection_thr, uint8_t reset_thr)
{
	uint32_t dystune;
	dystune = SECUMOD->SECUMOD_DYSTUNE & SECUMOD_DYSTUNE_NOPA;
	dystune |= SECUMOD_DYSTUNE_PERIOD(period);
	dystune |= SECUMOD_DYSTUNE_RX_ERROR_THRESHOLD(detection_thr);
	dystune |= SECUMOD_DYSTUNE_RX_OK_CORREL_NUMBER(reset_thr);
	SECUMOD->SECUMOD_DYSTUNE = dystune;
}

/**
 * \brief Enable/Disable alarm regenerated periodically while intrusion is maintained.
 *
 * \param enable periodic alarm while intrusion is maintained, true - disable, false - enable.
 */
void secumod_periodic_alarm(bool enable)
{
	uint32_t tmp;

	tmp = SECUMOD->SECUMOD_DYSTUNE & ~SECUMOD_DYSTUNE_NOPA;
	if (!enable)
		tmp |= SECUMOD_DYSTUNE_NOPA;
	SECUMOD->SECUMOD_DYSTUNE = tmp;
}

/**
 * \brief Set scrambling key for secure RAM in SECUMOD.
 *
 * \param key Scrambling key.
 */
void secumod_set_scrambling_key(uint32_t key)
{
	SECUMOD->SECUMOD_SCRKEY = key;
}

/**
 * \brief Get scrambling key for secure RAM in SECUMOD.
 *
 * \return Scrambling key.
 */
uint32_t secumod_get_scrambling_key(void)
{
	return SECUMOD->SECUMOD_SCRKEY;
}

/**
 * \brief Set access rights for secure RAM in SECUMOD.
 *
 * \param region  RAM region N,
 *                for N = 0~5: RAM range (N)Kbyte ~ (N+1)Kbyte;
 *                for N = 5: register bank 256bit.
 * \param rights  0: No access allowed;
 *                1: Only write access allowed;
 *                2: Only read access allowed;
 *                3: Read and write access allowed.
 */
void secumod_set_ram_access_rights(uint32_t region, uint8_t rights)
{
	uint32_t tmp;
	tmp = SECUMOD->SECUMOD_RAMACC & ~SECUMOD_RAMACC_RWx_Msk(region);
	SECUMOD->SECUMOD_RAMACC = tmp | (rights << SECUMOD_RAMACC_RWx_Pos(region));
}

/**
 * \brief Set protections enabled in backup mode.
 * \note Make sure registers appears before call this function, to toggle the
 * appearance of the registers using secumod_toggle_protection_reg().
 *
 * \param sources Bitwise OR of protections.
 */
void secumod_set_backup_mode_protections(uint32_t sources)
{
	SECUMOD->SECUMOD_BMPR = sources;
}

/**
 * \brief Get protections enabled in backup mode.
 * \note Make sure registers appears before call this function, to toggle the
 * appearance of the registers using secumod_toggle_protection_reg().
 *
 * \return Bitwise OR of protections.
 */
uint32_t secumod_get_backup_mode_protections()
{
	return SECUMOD->SECUMOD_BMPR;
}

/**
 * \brief Set protections enabled in normal mode.
 * \note Make sure registers appears before call this function, to toggle the
 * appearance of the registers using secumod_toggle_protection_reg().
 *
 * \param sources Bitwise OR of protections.
 */
void secumod_set_normal_mode_protections(uint32_t sources)
{
	SECUMOD->SECUMOD_NMPR = sources;

	if (SECUMOD->SECUMOD_NMPR != sources) {
		secumod_toggle_protection_reg();
		SECUMOD->SECUMOD_NMPR = sources;
	}
}

/**
 * \brief Get protections enabled in normal mode.
 * \note This function would makes the Normal and Backup Protection Registers appear.
 *
 * \return Bitwise OR of protections.
 */
uint32_t secumod_get_normal_mode_protections(void)
{
	return SECUMOD->SECUMOD_NMPR;
}

/**
 * \brief Set protection sources which can cause wake up signal generated.
 *
 * \param sources Bitwise OR of protection sources.
 */
void secumod_set_wakeup_protections(uint32_t sources)
{
	SECUMOD->SECUMOD_WKPR = sources;
}

/**
 * \brief Get protection sources which can cause wake up signal generated.
 *
 * \return Bitwise OR of protection sources.
 */
uint32_t secumod_get_wakeup_protections(void)
{
	return SECUMOD->SECUMOD_WKPR;
}

/**
 * \brief Enables one or more interrupt sources of a SECUMOD.
 * \note Make sure registers appears before call this function, to toggle the
 * appearance of the registers using secumod_toggle_protection_reg().
 *
 * \param sources Bitwise OR of selected interrupt sources.
 */
void secumod_enable_it(uint32_t sources)
{
	SECUMOD->SECUMOD_NIEPR |= sources;
	if (sources) {
		/* Enable SECUMOD/Secure RAM interrupts */
		aic_enable(ID_SECUMOD);
		aic_enable(ID_SECURAM);
	}
}

/**
 * \brief Disables one or more interrupt sources of a SECUMOD.
 * \note Make sure registers appears before call this function, to toggle the
 * appearance of the registers using secumod_toggle_protection_reg().
 *
 * \param sources Bitwise OR of selected interrupt sources.
 */
void secumod_disable_it(uint32_t sources)
{
	SECUMOD->SECUMOD_NIDPR |= sources;
	if (SECUMOD_NIDPR_ALL == (sources & SECUMOD_NIDPR_ALL)) {
		/* Disable SECUMOD/Secure RAM interrupts */
		aic_disable(ID_SECUMOD);
		aic_disable(ID_SECURAM);
	}
}

/**
 * \brief Get interrupt mask of a SECUMOD.
 * \note Make sure registers appears before call this function, to toggle the
 * appearance of the registers using secumod_toggle_protection_reg().
 *
 * \param dwSources Bitwise OR of selected interrupt sources.
 */
uint32_t secumod_get_normal_it_mask()
{
	return SECUMOD->SECUMOD_NIMPR;
}

/**
 * \brief Read the SECUMOD internal memory from the specified address
 * \param data  Point to where the data read is stored
 * \param addr memory address
 * \param size The number of bytes to be read
 * \retval Bytes read
 */
uint32_t secumod_read_internal_memory(uint8_t *data, uint32_t addr, uint32_t size)
{
	uint32_t i;
	uint32_t region;
	uint32_t count;

	if (addr >= ((uint32_t)SECURAM))
		addr -= ((uint32_t)SECURAM);

	for (i = 0; i < size; i += count)
	{
		region = (addr + i) >> 10;
		if ((SECUMOD_RAMACC_RWx_NO_ACCESS(region) ==
				(SECUMOD->SECUMOD_RAMACC & SECUMOD_RAMACC_RWx_Msk(region))) ||
			(SECUMOD_RAMACC_RWx_WR_ACCESS(region) ==
				(SECUMOD->SECUMOD_RAMACC & SECUMOD_RAMACC_RWx_Msk(region))))
		{
			break;
		}

		count = size;
		if (((region + 1) << 10 ) <= (addr + i + size))
		{
			size = ((region + 1) << 10) - (addr + i);
		}

		memcpy(data + i, (uint8_t *)(((uint32_t)SECURAM) + addr + i), count);
	}
	return i;
}

/**
 * \brief Write data to the SECUMOD internal memory from the specified address
 * \param data Pointer to the data to be written
 * \param addr memory address
 * \param size The number of bytes to be be written
 * \retval Bytes written
 */
uint32_t secumod_write_internal_memory(uint8_t *data, uint32_t addr, uint32_t size)
{
	uint32_t i;
	uint32_t region;
	uint32_t count;

	if (addr >= ((uint32_t)SECURAM))
		addr -= ((uint32_t)SECURAM);

	for (i = 0; i < size; i += count)
	{
		region = (addr + i) >> 10;
		if ((SECUMOD_RAMACC_RWx_NO_ACCESS(region) ==
				(SECUMOD->SECUMOD_RAMACC & SECUMOD_RAMACC_RWx_Msk(region))) ||
			(SECUMOD_RAMACC_RWx_RD_ACCESS(region) ==
				(SECUMOD->SECUMOD_RAMACC & SECUMOD_RAMACC_RWx_Msk(region))))
		{
		    break;
		}

		count = size;
		if (((region + 1) << 10 ) <= (addr + i + size))
		{
			size = ((region + 1) << 10) - (addr + i);
		}

		memcpy((uint8_t *)(((uint32_t)SECURAM) + addr + i), data + i, count);
	}
	return i;
}
