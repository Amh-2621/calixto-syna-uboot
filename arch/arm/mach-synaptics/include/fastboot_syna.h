/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2016~2023 Synaptics Incorporated. All rights reserved.
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

#define BOOTSEL_A			0x0
#define BOOTSEL_B			0x1
#define BOOTSEL_DEFAULT			BOOTSEL_A
#define BOOTSEL_INVALID			0xff

int get_current_slot(void);
int try_abmode(int abmode_sel);

void fb_mmc_flash_read_from_offset(const char *cmd, void *read_buffer, unsigned int read_bytes, unsigned int offset);
void fb_mmc_flash_read(const char *cmd, void *read_buffer, unsigned int read_bytes);
int f_mmc_save_part_table(int mmc_dev);
int f_mmc_get_hwpart_from_table(const char *part_name);
int f_mmc_get_part_from_table(const char *part_name);

#ifdef CONFIG_SYNA_SPI_SUBOOT
struct mtd_info *fb_spi_setup_mtd_dev(void);
int syna_mtdparts_get_info_by_name(struct mtd_info *mtd, const char *name, disk_partition_t *info);
#endif
