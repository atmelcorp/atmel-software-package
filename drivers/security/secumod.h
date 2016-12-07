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

/**
 * \file
 *
 * Interface for Security Module (SECUMOD) controller.
 *
 */

#ifndef _SECUMOD_H_
#define _SECUMOD_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

#include "chip.h"
#include "peripherals/rtc.h"

/*----------------------------------------------------------------------------
 *        Macros
 *----------------------------------------------------------------------------*/

/** Total number of regions divided in RAM of SECUMOD */
#define SECUMOD_RAM_REGION_NUM  6   /* 5Kbyte + 256bit */

/** Definition of SECUMOD RAM access rights control */
#define SECUMOD_RAM_ACC_RIGHTS_NO_ACCESS    (0x0u)  /**< \brief (SECUMOD_RAMACCSR) No access violation occurred */
#define SECUMOD_RAM_ACC_RIGHTS_WR_ACCESS    (0x1u)  /**< \brief (SECUMOD_RAMACCSR) Only write access violation occurred */
#define SECUMOD_RAM_ACC_RIGHTS_RD_ACCESS    (0x2u)  /**< \brief (SECUMOD_RAMACCSR) Only read access violation occurred */
#define SECUMOD_RAM_ACC_RIGHTS_RD_WR_ACCESS (0x3u)  /**< \brief (SECUMOD_RAMACCSR) Read and write access violation occurred */


/** Description for the attribute of one PIOBU pin. */
struct _secumod_piobu
{
	/* PIOBU alarm filter value, range: 0~9 */
	uint32_t afv:4;

	/* PIOBU error reset filter value, range: 0~9 */
	uint32_t rfv:4;

	/* I/O line mode, 0-pure input; 1-enabled in output */
	uint32_t mode:1;

	/* Set/Clear the I/O line when configured in output mode, 0-clear; 1-set */
	uint32_t outputLevel:1;

	uint32_t reserved1:1;
	uint32_t reserved2:1;

	/* pull-up/down option: 0-none; 1: pull-up; 2: pull-down; 3: reserved */
	uint32_t pullUpState:2;

	/* Pull-up/Down Scheduled: 0-no, 1-yes */
	uint32_t scheduled:1;

	/* level of PIOBUx input default state */
	uint32_t inputDefaultLevel:1;

	uint32_t reserved3:4;

	/* Mode of detection intrusion, 0-static; 1-dynamic */
	uint32_t dynamic:1;

	/* filter for dynamic signatures input 0: 3 stages majority vote; 1: 5 stages */
	uint32_t filter3_5:1;

	uint32_t reserved4:2;
	uint32_t reserved5:5;

	/* index of PIOBU pin's */
	uint32_t pinIndex:3;
};

/** Data and Time of tamper */
struct _tamper_detail {
	struct _date date;
	struct _time time;
	uint32_t     source; /**< tamper source */
};

/** informations of tamper */
struct _tamper_info {
	bool jtag_sel_ca5; /**< JTAGSEL, CA5 Tap response or CA5 debug ACK detected */
	bool jtag_tck_tms; /**< JTAG TCK/TMS activity detected */

	/** tamper counter */
	uint32_t tampers;

	/** total number of tampers occured */
	uint32_t total_tampers;

	/** detail information of first and last tamper */
	struct _tamper_detail details[2];
};

/** Access violation callback */
typedef void (*secumod_access_violation_callback_t)(uint8_t region, uint32_t status);

/** Access violation callback */
typedef void (*secumod_memory_erased_callback_t)(void);

/** Tamper callback */
typedef void (*secumod_tamper_callback_t)(void);

/*------------------------------------------------------------------------------ */

#ifdef __cplusplus
 extern "C" {
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Initialize SECUMOD driver instance.
 */
extern void secumod_initialize(void);

/**
 * \brief Set the callback function for Access Violations in SECUMOD.
 * \param callback Pointer to callback function.
 */
extern void secumod_set_access_callback(secumod_access_violation_callback_t callback);

/**
 * \brief Set the callback function for Internal Memory Erased in SECUMOD.
 * \param callback Pointer to callback function.
 */
extern void secumod_set_erased_callback(secumod_memory_erased_callback_t callback);

/**
 * \brief Set the callback function for tamper in SECUMOD.
 * \param callback Pointer to callback function.
 */
extern void secumod_set_tamper_callback(secumod_tamper_callback_t callback);

/**
 * \brief Get tamper information
 * \return Pointer to tamper information structure.
 */
extern struct _tamper_info *secumod_get_tamper_info(void);

/**
 * \brief Switch to backup mode.
 */
extern void secumod_switch_to_backup_mode(void);

/**
 * \brief Switch to normal mode.
 */
extern void secumod_switch_to_normal_mode(void);

/**
 * \brief Start clear content of SECUMOD internal RAM 4Kbyte and 256bits.
 */
extern void secumod_software_protection(void);

/**
 * \brief Enable/Disable Auto-Backup
 * \param enable Enable auto-backup if true, disable otherwise.
 */
extern void secumod_set_auto_backup(bool enable);

/**
 * \brief Enable/Disable Memory Scrambling
 * \param enable Enable memory scrambling if true, disable otherwise.
 */
extern void secumod_set_scrambling(bool enable);

/**
 * \brief Toggle normal or backup protection registers appear and disappear.
 */
extern void secumod_toggle_protection_reg(void);

/**
 * \brief Get system status.
 *
 * \return system status.
 */
extern uint32_t secumod_get_system_status(void);

/**
 * \brief Set system status.
 *
 * \param status system status to set.
 */
extern void secumod_set_system_status(uint32_t status);

/**
 * \brief Get status register.
 *
 * \return status register.
 */
extern uint32_t secumod_get_status(void);

/**
 * \brief Clear status register bits.
 *
 * \param status status bits to clear.
 */
extern void secumod_clear_status(uint32_t status);

/**
 * \brief Configures PIOBU pin instances.
 *
 * \param list Pointer to struct _secumod_piobu instances list.
 * \param size Number of PIOBU pin instances.
 */
extern void secumod_piobu_config(struct _secumod_piobu *list, uint32_t size);

/**
 * \brief Change a pair of PIOBU pins to dynamic intrusion mode.
 *
 * \param pair Pair index, range 0~3.
 */
extern void secumod_piobu_set_dynamic_mode(uint8_t pair);

/**
 * \brief Change a pair of PIOBU pins to static intrusion mode.
 *
 * \param pair          Pair index, range 0~3.
 * \param reset_filter0 Reset filter value of the 1st pin in the pair, range 0~9.
 * \param alarm_filter0 Alarm filter value of the 1st pin in the pair, range 0~9.
 * \param reset_filter1 Reset filter value of the 2nd pin in the pair, range 0~9.
 * \param alarm_filter1 Alarm filter value of the 2nd pin in the pair, range 0~9.
 */
extern void secumod_piobu_set_static_mode(uint8_t pair,
		uint8_t reset_filter0, uint8_t alarm_filter0,
		uint8_t reset_filter1, uint8_t alarm_filter1);

/**
 * \brief Set JTAG protection options of SECUMOD.
 *
 * \param force_reset       Whether preventing debug state and BSD (Boundary Scan Diagnostics) to work.
 * \param debug_permissions Debug permissions.
 * \param ack_monitoring    Whether monitor the DBGACK signal.
 */
extern void secumod_set_jtag_protection(bool force_reset, uint8_t debug_permissions,
		bool ack_monitoring);

/**
 * \brief Tuning dynamic signatures by period and threshold.
 *
 * \param period        Signature Clock Period.
 * \param detection_thr Error Detection Threshold.
 * \param reset_thr     Error Counter Reset Threshold.
 */
extern void secumod_dynamic_signatures_tuning(uint16_t period,
		uint8_t detection_thr, uint8_t reset_thr);

/**
 * \brief Enable/Disable alarm regenerated periodically while intrusion is maintained.
 *
 * \param enable periodic alarm while intrusion is maintained, true - disable, false - enable.
 */
extern void secumod_periodic_alarm(bool enable);

/**
 * \brief Set scrambling key for secure RAM in SECUMOD.
 *
 * \param key Scrambling key.
 */
extern void secumod_set_scrambling_key(uint32_t key);

/**
 * \brief Get scrambling key for secure RAM in SECUMOD.
 *
 * \return Scrambling key.
 */
extern uint32_t secumod_get_scrambling_key(void);

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
extern void secumod_set_ram_access_rights(uint32_t region, uint8_t rights);

/**
 * \brief Set protections enabled in backup mode.
 * \note Make sure registers appears before call this function, to toggle the
 * appearance of the registers using secumod_toggle_protection_reg().
 *
 * \param sources Bitwise OR of protections.
 */
extern void secumod_set_backup_mode_protections(uint32_t sources);

/**
 * \brief Get protections enabled in backup mode.
 * \note Make sure registers appears before call this function, to toggle the
 * appearance of the registers using secumod_toggle_protection_reg().
 *
 * \return Bitwise OR of protections.
 */
extern uint32_t secumod_get_backup_mode_protections(void);

/**
 * \brief Set protections enabled in normal mode.
 * \note Make sure registers appears before call this function, to toggle the
 * appearance of the registers using secumod_toggle_protection_reg().
 *
 * \param sources Bitwise OR of protections.
 */
extern void secumod_set_normal_mode_protections(uint32_t sources);

/**
 * \brief Get protections enabled in normal mode.
 * \note This function would makes the Normal and Backup Protection Registers appear.
 *
 * \return Bitwise OR of protections.
 */
extern uint32_t secumod_get_normal_mode_protections(void);

/**
 * \brief Set protection sources which can cause wake up signal generated.
 *
 * \param sources Bitwise OR of protection sources.
 */
extern void secumod_set_wakeup_protections(uint32_t sources);

/**
 * \brief Get protection sources which can cause wake up signal generated.
 *
 * \return Bitwise OR of protection sources.
 */
extern uint32_t secumod_get_wakeup_protections(void);

/**
 * \brief Enables one or more interrupt sources of a SECUMOD.
 * \note Make sure registers appears before call this function, to toggle the
 * appearance of the registers using secumod_toggle_protection_reg().
 *
 * \param sources Bitwise OR of selected interrupt sources.
 */
extern void secumod_enable_it(uint32_t sources);

/**
 * \brief Disables one or more interrupt sources of a SECUMOD.
 * \note Make sure registers appears before call this function, to toggle the
 * appearance of the registers using secumod_toggle_protection_reg().
 *
 * \param sources Bitwise OR of selected interrupt sources.
 */
extern void secumod_disable_it(uint32_t sources);

/**
 * \brief Get interrupt mask of a SECUMOD.
 * \note Make sure registers appears before call this function, to toggle the
 * appearance of the registers using secumod_toggle_protection_reg().
 *
 * \param dwSources Bitwise OR of selected interrupt sources.
 */
extern uint32_t secumod_get_normal_it_mask(void);

/**
 * \brief Read the SECUMOD internal memory from the specified address
 * \param data  Point to where the data read is stored
 * \param addr memory address
 * \param size The number of bytes to be read
 * \retval Bytes read
 */
extern uint32_t secumod_read_internal_memory(uint8_t *data, uint32_t addr, uint32_t size);

/**
 * \brief Write data to the SECUMOD internal memory from the specified address
 * \param data Pointer to the data to be written
 * \param addr memory address
 * \param size The number of bytes to be be written
 * \retval Bytes written
 */
extern uint32_t secumod_write_internal_memory(uint8_t *data, uint32_t addr, uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* _SECUMOD_H_ */
