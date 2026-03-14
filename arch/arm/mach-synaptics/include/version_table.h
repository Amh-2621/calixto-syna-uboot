/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2016~2024 Synaptics Incorporated. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 or
 * later as published by the Free Software Foundation.
 *
 * INFORMATION CONTAINED IN THIS DOCUMENT IS PROVIDED "AS-IS," AND
 * SYNAPTICS EXPRESSLY DISCLAIMS ALL EXPRESS AND IMPLIED WARRANTIES,
 * INCLUDING ANY IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE, AND ANY WARRANTIES OF NON-INFRINGEMENT OF ANY
 * INTELLECTUAL PROPERTY RIGHTS. IN NO EVENT SHALL SYNAPTICS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE, OR
 * CONSEQUENTIAL DAMAGES ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OF THE INFORMATION CONTAINED IN THIS DOCUMENT, HOWEVER CAUSED AND
 * BASED ON ANY THEORY OF LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, AND EVEN IF SYNAPTICS WAS
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. IF A TRIBUNAL OF
 * COMPETENT JURISDICTION DOES NOT PERMIT THE DISCLAIMER OF DIRECT
 * DAMAGES OR ANY OTHER DAMAGES, SYNAPTICS' TOTAL CUMULATIVE LIABILITY
 * TO ANY PARTY SHALL NOT EXCEED ONE HUNDRED U.S. DOLLARS.
 */

#ifndef _VERSION_TABLE_H_
#define _VERSION_TABLE_H_

#define PART_NAME_MAX_LEN	15

struct version_t {
	union {
		struct {
			u32 minor_version;
			u32 major_version;
		};
		u64 version;
	};
} __packed __aligned(4);

struct ver_table_entry_t {
	char name[PART_NAME_MAX_LEN + 1];
	struct version_t part1_version;
	u32 part1_start_blkind;
	u32 part1_blks;
#ifdef CONFIG_EMMC_WRITE_PROTECT
	u32 write_protect_flag;
	u8 reserved[12];
#else
	struct version_t part2_version;
	u32 part2_start_blkind;
	u32 part2_blks;
	u32 write_protect_flag;
	char part_type[PART_NAME_MAX_LEN + 1];
#endif
} __packed __aligned(4);

struct version_table_t {
	u32 magic;
	u32 ou_status;
	u32 num_entries;
	struct ver_table_entry_t table[];
};

#endif
