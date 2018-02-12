/*
 * Atmel PTC System driver for SAMA5D2 devices and compatible.
 *
 * Copyright (C) 2017 Microchip,
 *               2017 Ludovic Desroches <ludovic.desroches@microchip.com>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */

#ifndef _PTC_H
#define _PTC_H

#ifdef __KERNEL__
#include <linux/types.h>
#else
#include <stdint.h>
#endif

#define ATMEL_PTC_MAX_NODES	64
#define ATMEL_PTC_MAX_SCROLLERS	4
/*----------------------------------------------------------------------------
 *        Constants
 *----------------------------------------------------------------------------*/

enum atmel_qtm_command {
	QTM_CMD_FIRM_VERSION		= 8,
	QTM_CMD_DEEPSLEEP		= 16,
	QTM_CMD_ACQ			= 17,
	QTM_CMD_INIT			= 18,
	QTM_CMD_RUN			= 19,
	QTM_CMD_STATUS			= 20,
	QTM_CMD_STOP			= 21,
	QTM_CMD_UPDATE_TOUCH_CFG	= 22,
	QTM_CMD_SET_ACQ_MODE_ON_DEMAND	= 23,
	QTM_CMD_SET_ACQ_MODE_TIMER	= 24,
	QTM_CMD_SET_ACQ_MODE_WCOMP	= 25,
	QTM_CMD_SET_TIMER_INTERVAL	= 26,
	QTM_CMD_STOP_TIMER		= 27,
	QTM_CMD_START_TIMER		= 28,
	QTM_CMD_RESET			= 29,
	QTM_CMD_WATCHDOG_CHECK		= 30,
};

/*
 * PTC acquisition frequency delay setting.
 *
 * The PTC acquisition frequency is dependent on the Generic clock
 * input to PTC and PTC clock prescaler setting. This delay setting
 * inserts "n" PTC clock cycles between consecutive measurements on
 * a given sensor, thereby changing the PTC acquisition frequency.
 * FREQ_HOP_SEL_1 setting inserts 1 PTC clock cycle between consecutive
 * measurements. FREQ_HOP_SEL_14 setting inserts 14 PTC clock cycles.
 * Hence, higher delay setting will increase the total time taken for
 * capacitance measurement on a given sensor as compared to a lower
 * delay setting.
 *
 * A desired setting can be used to avoid noise around the same frequency
 * as the acquisition frequency.
 */
enum atmel_ptc_freq_sel {
	PTC_FREQ_SEL_0,
	PTC_FREQ_SEL_1,
	PTC_FREQ_SEL_2,
	PTC_FREQ_SEL_3,
	PTC_FREQ_SEL_4,
	PTC_FREQ_SEL_5,
	PTC_FREQ_SEL_6,
	PTC_FREQ_SEL_7,
	PTC_FREQ_SEL_8,
	PTC_FREQ_SEL_9,
	PTC_FREQ_SEL_10,
	PTC_FREQ_SEL_11,
	PTC_FREQ_SEL_12,
	PTC_FREQ_SEL_13,
	PTC_FREQ_SEL_14,
	PTC_FREQ_SEL_15,
	PTC_FREQ_SEL_SPREAD,
};

/*
 * Series resistor setting. For Mutual cap mode, this series
 * resistor is switched internally on the Y-pin. For Self cap mode,
 * this series resistor is switched internally on the Sensor pin.
 */
enum atmel_ptc_rsel_val {
	PTC_RSEL_0,
	PTC_RSEL_20,
	PTC_RSEL_50,
	PTC_RSEL_100,
};

enum atmel_ptc_prsc_div_sel {
	PTC_PRSC_DIV_1,
	PTC_PRSC_DIV_2,
	PTC_PRSC_DIV_4,
	PTC_PRSC_DIV_8,
};

enum atmel_ptc_gain {
	PTC_GAIN_1,
	PTC_GAIN_2,
	PTC_GAIN_4,
	PTC_GAIN_8,
	PTC_GAIN_16,
	PTC_GAIN_32,
};

enum atmel_ptc_filter_level {
	PTC_FILTER_LEVEL_1,
	PTC_FILTER_LEVEL_2,
	PTC_FILTER_LEVEL_4,
	PTC_FILTER_LEVEL_8,
	PTC_FILTER_LEVEL_16,
	PTC_FILTER_LEVEL_32,
	PTC_FILTER_LEVEL_64,
};

enum atmel_ptc_aks_group {
	QTM_KEY_NO_AKS_GROUP,
	QTM_KEY_AKS_GROUP_1,
	QTM_KEY_AKS_GROUP_2,
	QTM_KEY_AKS_GROUP_3,
	QTM_KEY_AKS_GROUP_4,
	QTM_KEY_AKS_GROUP_5,
	QTM_KEY_AKS_GROUP_6,
	QTM_KEY_AKS_GROUP_7,
	MAX_QTM_KEY_AKS_GROUP,
};

enum atmel_ptc_key_hysteresis {
	QTM_KEY_HYST_50,
	QTM_KEY_HYST_25,
	QTM_KEY_HYST_12_5,
	QTM_KEY_HYST_6_25,
	MAX_QTM_KEY_HYST,
};

enum atmel_ptc_key_recal_thr {
	QTM_KEY_RECAL_THR_100,
	QTM_KEY_RECAL_THR_50,
	QTM_KEY_RECAL_THR_25,
	QTM_KEY_RECAL_THR_12_5,
	QTM_KEY_RECAL_THR_6_25,
	MAX_QTM_KEY_RECAL_THR,
};

/*
 * Reburst mode:
 * 0 = none (application calls only)
 * 1 = Unresolved - i.e. sensors in process of calibration / filter in / filter out and AKS groups
 * 2 = All keys
 */
enum atmel_ptc_key_reburst {
	QTM_KEY_REBURST_NONE,
	QTM_KEY_REBURST_UNRESOLVED,
	QTM_KEY_REBURST_ALL,
};

struct atmel_qtm_cmd {
	uint16_t id;
	uint16_t addr;
	uint32_t data;
} __attribute__ ((packed));

struct atmel_qtm_node_group_config {
	uint16_t count;		/* Number of sensor nodes */
	uint8_t	ptc_type;	/* Self or mutual sensors */
	uint8_t	freq_option;	/* SDS or ASDV setting */
	uint8_t	calib_option;	/* Hardware tuning: XX | TT 3/4/5 Tau | X | XX None/RSEL/PRSC/CSD */
	uint8_t	unused;
} __attribute__ ((packed));

struct  atmel_qtm_node_config {
	uint16_t mask_x;	/* Selects the X Pins for this node (NONE for selfcapacitance configuration) */
	uint32_t mask_y;	/* Selects the Y Pins for this node */
	uint8_t	csd;		/* Charge Share Delay */
	uint8_t	rsel;		/* Resistor */
	uint8_t	prsc;		/* Prescaler */
	uint8_t	gain_analog;	/* Analog gain setting (Cint Selection) */
	uint8_t	gain_digital;	/* Digital gain (Accum / Dec) */
	uint8_t	oversampling;	/* Accumulator setting */
} __attribute__ ((packed));

struct atmel_qtm_node_data {
	uint8_t	status;
	uint8_t	unused;
	uint16_t signals;
	uint16_t comp_caps;
} __attribute__ ((packed));

struct atmel_qtm_key_config {
	uint8_t	threshold;	/* Touch detection threshold */
	uint8_t	hysteresis;	/* Percentage of threshold reduction to exit detect state */
	uint8_t	aks_group;	/* 0 = None, 1-255 = group number */
	uint8_t	unused;
} __attribute__ ((packed));

struct atmel_qtm_key_group_config {
	uint16_t count;			/* Number of sensors */
	uint8_t	touch_di;		/* Count in to Detect */
	uint8_t	max_on_time;		/* Max on duration x 200ms */
	uint8_t	anti_touch_di;		/* Count in to Anti-touch recal */
	uint8_t	anti_touch_recal_thr;	/* Anti-touch recal threshold % */
	uint8_t	touch_drift_rate;	/* One count per <200> ms */
	uint8_t	anti_touch_drift_rate;	/* One count per <200> ms */
	uint8_t	drift_hold_time;	/* Drift hold time */
	uint8_t	reburst_mode;		/* None / Unresolved / All */
} __attribute__ ((packed));

struct atmel_qtm_key_data {
	uint8_t	status;			/* Disabled, Off, On, Filter, Cal... */
	uint8_t	status_counter;		/* State counter */
	uint16_t node_struct_ptr;	/* Pointer to node struct */
	uint16_t reference;		/* Reference signal */
} __attribute__ ((packed));

struct atmel_qtm_auto_scan_config {
	uint16_t unused;
	uint16_t node_number;	/* Node Index that will be used */
	uint8_t	node_threshold;
	uint8_t	trigger;
} __attribute__ ((packed));

struct atmel_qtm_scroller_group_config {
	uint16_t key_data;
	uint8_t	count;
	uint8_t unused;
} __attribute__ ((packed));

struct atmel_qtm_scroller_config {
	uint8_t	type;
	uint8_t	unused;
	uint16_t key_start;
	uint8_t	key_count;
	uint8_t	resol_deadband;
	uint8_t	position_hysteresis;
	uint8_t	unused2;
	uint16_t contact_min_threshold;
} __attribute__ ((packed));

struct atmel_qtm_scroller_data {
	uint8_t	status;
	uint8_t	right_hyst;
	uint8_t	left_hyst;
	uint8_t	unused;
	uint16_t raw_position;
	uint16_t position;
	uint16_t contact_size;
} __attribute__ ((packed));

struct atmel_qtm_fh_autotune_config {
	uint8_t	count;			/* Number of sensors */
	uint8_t	num_freqs;
	uint16_t freq_option_select;
	uint16_t median_filter_freq;	/* PTC frequencies to be used on the median filter samples */
	uint8_t	enable_freq_autotune;
	uint8_t	max_variance_limit;
	uint8_t	autotune_count_in_limit;
	uint8_t	unused;
} __attribute__ ((packed));

struct atmel_qtm_fh_autotune_data {
	uint8_t	status;			/* Obligatory status byte: Bit 7 = Reburst... */
	uint8_t	current_freq;		/* PTC Sampling Delay Selection - 0 to 15 PTC CLK cycles */
	uint16_t filter_buffer;		/* Filter buffer used to store past cycle signal values of sensor */
	uint16_t acq_node_data;
	uint16_t freq_tune_count_ins;
} __attribute__ ((packed));

struct atmel_qtm_fh_freq {
	uint8_t	freq0;
	uint8_t	freq1;
	uint8_t	freq2;
	uint8_t	unused;
} __attribute__ ((packed));

struct atmel_qtm_touch_events {
        uint32_t key_event_id0;
	uint32_t key_event_id1;
	uint32_t key_enable_state0;
	uint32_t key_enable_state1;
	uint32_t scroller_event_id;
} __attribute__ ((packed));

struct atmel_qtm_watchdog_regs {
	uint32_t reg_a;
	uint32_t reg_b;
} __attribute__ ((packed));

struct atmel_qtm_mailbox {
	struct atmel_qtm_cmd			cmd;
	uint8_t					unused[248];
	struct atmel_qtm_node_group_config	node_group_config;
	struct atmel_qtm_node_config		node_config[ATMEL_PTC_MAX_NODES];
	struct atmel_qtm_node_data		node_data[ATMEL_PTC_MAX_NODES];
	struct atmel_qtm_key_group_config	key_group_config;
	struct atmel_qtm_key_config		key_config[ATMEL_PTC_MAX_NODES];
	struct atmel_qtm_key_data		key_data[ATMEL_PTC_MAX_NODES];
	struct atmel_qtm_auto_scan_config	auto_scan_config;
	struct atmel_qtm_scroller_group_config	scroller_group_config;
	struct atmel_qtm_scroller_config	scroller_config[ATMEL_PTC_MAX_SCROLLERS];
	struct atmel_qtm_scroller_data		scroller_data[ATMEL_PTC_MAX_SCROLLERS];
	struct atmel_qtm_fh_autotune_config	fh_autotune_config;
	struct atmel_qtm_fh_autotune_data	fh_autotune_data;
	struct atmel_qtm_fh_freq		fh_freq;
	struct atmel_qtm_touch_events		touch_events;
	struct atmel_qtm_watchdog_regs		watchdog_regs;
} __attribute__ ((packed));

#endif /* _PTC_H */
