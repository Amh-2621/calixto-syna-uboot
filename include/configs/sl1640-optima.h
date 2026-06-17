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

#define CONFIG_ENV_SIZE			(64 << 10) /* 64KiB */

#ifdef CONFIG_ENV_IS_IN_SPI_FLASH
/* Environment in SPI NOR flash */
#define SPI_FLASH_BL_END		(2 << 20) /* 2MiB */
#define CONFIG_ENV_OFFSET		(SPI_FLASH_BL_END - CONFIG_ENV_SIZE)
#define CONFIG_ENV_SECT_SIZE		(64 << 10) /* 64KiB sectors */
#endif

#ifdef CONFIG_ENV_IS_IN_MMC
/* Environment in eMMC, at the end of "bl_x" */
#define ENV_MMC_PART_NAME		"bl_a"
#ifndef CONFIG_SYNA_RESCUE_MODE
#define CONFIG_ENV_OFFSET_REDUND	1 /* only a flag */
#define ENV_MMC_PART_NAME_REDUND	"bl_b"
#endif
#endif

#define COUNTER_FREQUENCY			25000000 /* 25MHz */

#define CONFIG_SYS_MAX_NAND_DEVICE     1

#define CONFIG_SYS_LOAD_ADDR		0xcf00000
#define CONFIG_SYS_AUTOLOAD		"n"			/* disable autoload image via tftp after dhcp */

//max malloc length
#define CONFIG_SYS_MALLOC_LEN		(1480 << 20)

#define CONFIG_SYS_FLASH_BASE		0xF0000000
#define CONFIG_SYS_MAX_FLASH_BANKS		1

#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_TEXT_BASE - (2 << 20))

#define CONFIG_SYS_BOOTM_LEN	(64 << 20)

/* Watchdog configs*/
#define CONFIG_HW_WATCHDOG
#define CONFIG_DESIGNWARE_WATCHDOG

#define CONFIG_DW_WDT_BASE		0xF7FC5000

#define CONFIG_DW_WDT_CLOCK_KHZ	25000
#define CONFIG_WATCHDOG_TIMEOUT_MSECS 	0

/* Fastboot configs*/
#define CONFIG_GICV2
#define GICD_BASE				0xf7901000
#define GICC_BASE				0xf7902000

#ifdef CONFIG_SYNA_RESCUE_MODE
#define CONFIG_EXTRA_ENV_SETTINGS \
	"upgrade_available=0\0" \
	"rescue_load=ext4load mmc 0:2 0x10000000 Image.gz; "\
		     "ext4load mmc 0:2 0x17c00000 board.dtb; "\
		     "ext4load mmc 0:2 0x8c00000 initramfs.rootfs.cpio.gz\0" \
	"rescue_setup=setenv kernel_comp_addr_r 0x7c00000; "\
		      "setenv kernel_comp_size $filesize; "\
		      "setenv bootm_low 0x0; "\
		      "setenv bootm_size 0x10000000; "\
		      "setenv bootargs shell earlycon console=ttyS0,115200 rootwait rootfstype=ext4\0" \
	"rescue_exec=booti 0x10000000 0x8c00000:$filesize 0x17c00000\0" \
	"rescue_boot=echo \"*** RESCUE MODE TRIGGERED ***\"; "\
		     "run rescue_load; run rescue_setup; run rescue_exec\0"
#else
#define CONFIG_EXTRA_ENV_SETTINGS \
	"upgrade_available=0\0" \
	"rootfs_mmc_dev=1\0" \
	"rootfs_mmc_part=7\0" \
	"kernel_addr=0x10000000\0" \
	"fdt_addr=0x17c00000\0" \
	"initramfs_addr=0x8c00000\0" \
	"kernel_file=/boot/Image-5.15.140\0" \
	"fdt_file=/boot/sl1640-calixto-optima.dtb\0" \
	"initramfs_file=/boot/initramfs.cpio.gz\0" \
	\
	/* Custom SD Card Boot Flow */ \
	"sd_load=ext4load mmc ${rootfs_mmc_dev}:${rootfs_mmc_part} ${kernel_addr} ${kernel_file}; " \
			"ext4load mmc ${rootfs_mmc_dev}:${rootfs_mmc_part} ${fdt_addr} ${fdt_file}; " \
			"ext4load mmc ${rootfs_mmc_dev}:${rootfs_mmc_part} ${initramfs_addr} ${initramfs_file}; " \
			"setenv initramfs_size ${filesize}\0" \
	"sd_args=setenv bootargs console=ttyS0,115200 rootwait rw\0" \
	"sd_exec=booti ${kernel_addr} ${initramfs_addr}:${initramfs_size} ${fdt_addr}\0" \
	"sd_boot=run sd_load; run sd_args; run sd_exec\0" \
	\
	/* Main Boot Command - Runs AFTER the countdown delay */ \
	"bootcmd=mmc rescan; " \
			"if mmc dev ${rootfs_mmc_dev}; then " \
				"echo '--- SD Card detected! Launching custom boot... ---'; " \
				"run sd_boot; " \
			"else " \
				"echo '--- No SD Card. Proceeding to eMMC boot... ---'; " \
				"run altbootcmd; " \
			"fi\0" \
	\
	/* Factory default altbootcmd preserved exactly */ \
	"altbootcmd=if test ${boot_slot}  = 1; then bootslot set b; bootcount reset;bootcount reset; run bootcmd; else bootslot set a; bootcount reset; bootcount reset; run bootcmd;  fi\0"
#endif
