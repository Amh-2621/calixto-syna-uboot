// SPDX-License-Identifier: GPL-2.0+
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

#include <common.h>
#include <asm/io.h>
#include "Galois_memmap.h"
#include "global.h"
#include "mem_init.h"

#ifdef CONFIG_SYNA_RESCUE_MODE
#define GPIO_RESCUE_SET     48   // GPIO39 / PortB16
#define GPIO_RESCUE_DETECT  47   // GPIO38 / PortB15
#endif

#if defined(CONFIG_SYNA_SPI_UBOOT) || defined(CONFIG_SYNA_USB_UBOOT)
static void init_clock(void)
{
	writel(0x00000008, 0xF7EA0710);
	writel(0x00000012, 0xF7922000);
	writel(0x00000013, 0xF7922000);
	writel(0x00000000, 0xF7922008);
	writel(0x00000032, 0xF792200C);
	writel(0x00000000, 0xF7922010);
	writel(0x00000000, 0xF7922004);
	writel(0x0000001B, 0xF7922000);
	writel(0x00000001, 0xF7922014);
	writel(0x00000002, 0xF7922018);
	writel(0x0000001A, 0xF7922000);
	writel(0x00000018, 0xF7922000);
	writel(0x00000000, 0xF7EA0710);
	writel(0x00000001, 0xF7EA0710);
	writel(0x00000012, 0xF7EA0200);
	writel(0x00000013, 0xF7EA0200);
	writel(0x00000000, 0xF7EA0208);
	writel(0x00000017, 0xF7EA020C);
	writel(0x00000000, 0xF7EA0210);
	writel(0x00000000, 0xF7EA0204);
	writel(0x0000001B, 0xF7EA0200);
	writel(0x00000001, 0xF7EA0214);
	writel(0x00000002, 0xF7EA0218);
	writel(0x0000001A, 0xF7EA0200);
	writel(0x00000018, 0xF7EA0200);
	writel(0x00000000, 0xF7EA0710);
	writel(0x00000002, 0xF7EA0710);
	writel(0x00000012, 0xF7EA0220);
	writel(0x00000013, 0xF7EA0220);
	writel(0x00000000, 0xF7EA0228);
	writel(0x00000013, 0xF7EA022C);
	writel(0x00000000, 0xF7EA0230);
	writel(0x00000000, 0xF7EA0224);
	writel(0x0000001B, 0xF7EA0220);
	writel(0x00000000, 0xF7EA0234);
	writel(0x00000004, 0xF7EA0238);
	writel(0x0000001A, 0xF7EA0220);
	writel(0x00000018, 0xF7EA0220);
	writel(0x00000000, 0xF7EA0710);
	writel(0x000002A9, 0xF7EA0720);
	writel(0x000002A9, 0xF7EA0720);
	writel(0x000002A3, 0xF7EA0720);
	writel(0x000002B3, 0xF7EA0720);
	writel(0x00000293, 0xF7EA0720);
	writel(0x000002A9, 0xF7EA0724);
	writel(0x000002A9, 0xF7EA0724);
	writel(0x000002A3, 0xF7EA0724);
	writel(0x000002B3, 0xF7EA0724);
	writel(0x000000B3, 0xF7EA0724);
	writel(0x000002A9, 0xF7EA0728);
	writel(0x000002A9, 0xF7EA0728);
	writel(0x000002A1, 0xF7EA0728);
	writel(0x000002A1, 0xF7EA0728);
	writel(0x000001A1, 0xF7EA0728);
	writel(0x000002A9, 0xF7EA072C);
	writel(0x000002A9, 0xF7EA072C);
	writel(0x000002A1, 0xF7EA072C);
	writel(0x000002A1, 0xF7EA072C);
	writel(0x000001A1, 0xF7EA072C);
	writel(0x000002A9, 0xF7EA0730);
	writel(0x000002A9, 0xF7EA0730);
	writel(0x000002A1, 0xF7EA0730);
	writel(0x000002A1, 0xF7EA0730);
	writel(0x000001A1, 0xF7EA0730);
	writel(0x000002A9, 0xF7EA0768);
	writel(0x000002A9, 0xF7EA0768);
	writel(0x000002A1, 0xF7EA0768);
	writel(0x000002A1, 0xF7EA0768);
	writel(0x000002E1, 0xF7EA0768);
	writel(0x000002A9, 0xF7EA076C);
	writel(0x000002A9, 0xF7EA076C);
	writel(0x000002A1, 0xF7EA076C);
	writel(0x000002A1, 0xF7EA076C);
	writel(0x000002E1, 0xF7EA076C);
	writel(0x000002A9, 0xF7EA0770);
	writel(0x000002A9, 0xF7EA0770);
	writel(0x000002A7, 0xF7EA0770);
	writel(0x000002B7, 0xF7EA0770);
	writel(0x00000137, 0xF7EA0770);
	writel(0x000002A9, 0xF7EA0778);
	writel(0x000002A9, 0xF7EA0778);
	writel(0x000002A9, 0xF7EA0778);
	writel(0x000002B9, 0xF7EA0778);
	writel(0x00000299, 0xF7EA0778);
	writel(0x000002A9, 0xF7EA077C);
	writel(0x000002A9, 0xF7EA077C);
	writel(0x000002A1, 0xF7EA077C);
	writel(0x000002A1, 0xF7EA077C);
	writel(0x000002E1, 0xF7EA077C);
	writel(0x000002A9, 0xF7EA0780);
	writel(0x000002A9, 0xF7EA0780);
	writel(0x000002A1, 0xF7EA0780);
	writel(0x000002A1, 0xF7EA0780);
	writel(0x000002E1, 0xF7EA0780);
	writel(0x000002A9, 0xF7EA0784);
	writel(0x000002A9, 0xF7EA0784);
	writel(0x000002A1, 0xF7EA0784);
	writel(0x000002A1, 0xF7EA0784);
	writel(0x000001A1, 0xF7EA0784);
	writel(0x000002A9, 0xF7EA0788);
	writel(0x000002A9, 0xF7EA0788);
	writel(0x000002A3, 0xF7EA0788);
	writel(0x000002B3, 0xF7EA0788);
	writel(0x00000293, 0xF7EA0788);
	writel(0x000002A9, 0xF7EA078C);
	writel(0x000002A9, 0xF7EA078C);
	writel(0x000002A1, 0xF7EA078C);
	writel(0x000002A1, 0xF7EA078C);
	writel(0x000000A1, 0xF7EA078C);
	writel(0x000002A9, 0xF7EA0790);
	writel(0x000002A9, 0xF7EA0790);
	writel(0x000002A1, 0xF7EA0790);
	writel(0x000002A1, 0xF7EA0790);
	writel(0x000000A1, 0xF7EA0790);
	writel(0x000002A9, 0xF7EA0794);
	writel(0x000002A9, 0xF7EA0794);
	writel(0x000002A1, 0xF7EA0794);
	writel(0x000002A1, 0xF7EA0794);
	writel(0x000002E1, 0xF7EA0794);
	writel(0x000002A9, 0xF7EA0798);
	writel(0x000002A9, 0xF7EA0798);
	writel(0x000002A1, 0xF7EA0798);
	writel(0x000002A1, 0xF7EA0798);
	writel(0x000002E1, 0xF7EA0798);
	writel(0x000002A9, 0xF7EA079C);
	writel(0x000002A9, 0xF7EA079C);
	writel(0x000002A1, 0xF7EA079C);
	writel(0x000002A1, 0xF7EA079C);
	writel(0x000001A1, 0xF7EA079C);
	writel(0x000002A9, 0xF7EA07A0);
	writel(0x000002A9, 0xF7EA07A0);
	writel(0x000002A1, 0xF7EA07A0);
	writel(0x000002A1, 0xF7EA07A0);
	writel(0x000000A1, 0xF7EA07A0);
	writel(0x000002A9, 0xF7EA07A4);
	writel(0x000002A9, 0xF7EA07A4);
	writel(0x000002A1, 0xF7EA07A4);
	writel(0x000002A1, 0xF7EA07A4);
	writel(0x000000A1, 0xF7EA07A4);
}
#endif

static void set_ge_pad_strength(void)
{
	u32 i, strength, strength0, ds0, ds1, ds2;
	T32Gbl_RGMIITXCCntl reg_value;
	T32Gbl_TW2_SCLCntl regMDIO_value;
	unsigned char *reg_addr;

	ds0 = 0;
	ds1 = 1;
	ds2 = 1;
	
	//O:RGMIIB_MDC IO:RGMIIB_MDIO is used in FPGA release, 4BIT set drive to 7;
	regMDIO_value.u32 = readl(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_TW2_SCLCntl);
	regMDIO_value.uTW2_SCLCntl_DS0 = 1;
	regMDIO_value.uTW2_SCLCntl_DS1 = 1;
	regMDIO_value.uTW2_SCLCntl_DS2 = 1;
	regMDIO_value.uTW2_SCLCntl_DS3 = 0;
	writel(regMDIO_value.u32, MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_TW2_SCLCntl);

	regMDIO_value.u32 = readl(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_TW2_SDACntl);
	regMDIO_value.uTW2_SCLCntl_DS0 = 1;
	regMDIO_value.uTW2_SCLCntl_DS1 = 1;
	regMDIO_value.uTW2_SCLCntl_DS2 = 1;
	regMDIO_value.uTW2_SCLCntl_DS3 = 0;
	writel(regMDIO_value.u32, MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_TW2_SDACntl);

	reg_value.u32 = readl(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_GPIO_A0Cntl);
	reg_value.uRGMIITXCCntl_DS0 = 0;
	reg_value.uRGMIITXCCntl_DS1 = 1;
	reg_value.uRGMIITXCCntl_DS2 = 1;
	writel(reg_value.u32, MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_GPIO_A0Cntl);

	reg_value.u32 = readl(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_GPIO_A1Cntl);
	reg_value.uRGMIITXCCntl_DS0 = 0;
	reg_value.uRGMIITXCCntl_DS1 = 1;
	reg_value.uRGMIITXCCntl_DS2 = 1;
	writel(reg_value.u32, MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_GPIO_A1Cntl);

	reg_addr = (void *)(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_RGMII_CLK_OUTCntl);
	for (i = 0; i < (RA_Gbl_RGMIIRXCTLCntl - RA_Gbl_RGMII_CLK_OUTCntl) / 4 + 1; i++, reg_addr += 4) {
		reg_value.u32 = readl(reg_addr);
		if (i == 0) {
			strength0 = reg_value.uRGMIITXCCntl_DS2;
			strength0 *= 2;
			strength0 += reg_value.uRGMIITXCCntl_DS1;
			strength0 *= 2;
			strength0 += reg_value.uRGMIITXCCntl_DS0;
		}
		reg_value.uRGMIITXCCntl_DS0 = ds0;
		reg_value.uRGMIITXCCntl_DS1 = ds1;
		reg_value.uRGMIITXCCntl_DS2 = ds2;
		writel(reg_value.u32, reg_addr);
	}
	debug("GE Pad Strenth change from %d to %d\n", strength0, strength);
}

static void set_tw1_drive_strength(void)
{
	T32Gbl_TW1_SCLCntl tw1_value;

	tw1_value.u32 = readl(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_TW1_SCLCntl);
	tw1_value.uTW1_SCLCntl_DS0 = 1;
	tw1_value.uTW1_SCLCntl_DS1 = 1;
	tw1_value.uTW1_SCLCntl_DS2 = 1;
	tw1_value.uTW1_SCLCntl_DS3 = 0;
	writel(tw1_value.u32, MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_TW1_SCLCntl);

	tw1_value.u32 = readl(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_TW1_SDACntl);
	tw1_value.uTW1_SCLCntl_DS0 = 1;
	tw1_value.uTW1_SCLCntl_DS1 = 1;
	tw1_value.uTW1_SCLCntl_DS2 = 1;
	tw1_value.uTW1_SCLCntl_DS3 = 0;
	writel(tw1_value.u32, MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_TW1_SDACntl);
}

static void set_tw0_drive_strength(void)
{
	T32Gbl_TW0_SCLCntl tw0_value;

	tw0_value.u32 = readl(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_TW0_SCLCntl);
	tw0_value.uTW0_SCLCntl_DS0 = 1;
	tw0_value.uTW0_SCLCntl_DS1 = 1;
	tw0_value.uTW0_SCLCntl_DS2 = 1;
	tw0_value.uTW0_SCLCntl_DS3 = 0;
	writel(tw0_value.u32, MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_TW0_SCLCntl);

	tw0_value.u32 = readl(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_TW0_SDACntl);
	tw0_value.uTW0_SCLCntl_DS0 = 1;
	tw0_value.uTW0_SCLCntl_DS1 = 1;
	tw0_value.uTW0_SCLCntl_DS2 = 1;
	tw0_value.uTW0_SCLCntl_DS3 = 0;
	writel(tw0_value.u32, MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_TW0_SDACntl);
}

static void set_drive_strength(void)
{
	set_ge_pad_strength();
	set_tw0_drive_strength();
	set_tw1_drive_strength();
}

static void tw_init_mdio(void)
{
	u32 value;

	/* set to RGMII MDIO */
	value = readl(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_PERIF + RA_PERIF_TW_PORT_CTRL);
	value &=  ~(1 << LSb32PERIF_TW_PORT_CTRL_RGMII_MDIO_SEL);
	writel(value, MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_PERIF + RA_PERIF_TW_PORT_CTRL);
	udelay(1);
}

#ifdef CONFIG_SYNA_RESCUE_MODE
static void setup_rescue_mode_gpio(void)
{
	gpio_request(GPIO_RESCUE_SET, "SET");
	gpio_direction_output(GPIO_RESCUE_SET, 1);

	gpio_request(GPIO_RESCUE_DETECT, "DETECT");
	gpio_direction_input(GPIO_RESCUE_DETECT);
}

static void rescue_trigger_detect(void)
{
	// Clear detect pin to 0 briefly before reading input
	gpio_direction_output(GPIO_RESCUE_DETECT, 0);
	udelay(10);
	gpio_direction_input(GPIO_RESCUE_DETECT);

	if (gpio_get_value(GPIO_RESCUE_DETECT) == 1) {
		// Boot Rescue Image
		run_command("run rescue_boot", 0);
	}
}
#endif

int board_init(void)
{
	//board related things like clock may be inited here
#if defined(CONFIG_SYNA_SPI_UBOOT) || defined(CONFIG_SYNA_USB_UBOOT)
	init_clock();
#endif
	set_drive_strength();
	tw_init_mdio();

	return 0;
}

#ifdef CONFIG_CMD_SYNA_MTDPARTS
extern int syna_init_mtdparts(void);
#endif

int board_late_init(void)
{
	unsigned int result = 0;

#ifdef CONFIG_SYNA_RESCUE_MODE
	setup_rescue_mode_gpio();
	rescue_trigger_detect();
#endif

#ifdef CONFIG_SYNA_TZ_MR
	get_mem_region_list_from_tz();
#endif

#ifdef CONFIG_CMD_SYNA_MTDPARTS
	syna_init_mtdparts();
#endif

	return result;
}

