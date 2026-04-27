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
#include "SysMgr.h"
#include "watchdog_def.h"
#include "mem_init.h"

#ifdef CONFIG_SYNA_RESCUE_MODE
#define GPIO_RESCUE_SET     79   // GPIO39 / PortB7
#define GPIO_RESCUE_DETECT  78   // GPIO38 / PortB6
#endif

#if defined(CONFIG_SYNA_SPI_UBOOT) || defined(CONFIG_SYNA_USB_UBOOT)
static void init_clock(void)
{
	writel(0x000002A9, 0xF7EA0720);
	writel(0x000002A9, 0xF7EA0720);
	writel(0x000002A3, 0xF7EA0720);
	writel(0x000002B3, 0xF7EA0720);
	writel(0x00000293, 0xF7EA0720);
	writel(0x000002A9, 0xF7EA0724);
	writel(0x000002A9, 0xF7EA0724);
	writel(0x000002A3, 0xF7EA0724);
	writel(0x000002B3, 0xF7EA0724);
	writel(0x00000293, 0xF7EA0724);
	writel(0x000002A9, 0xF7EA0740);
	writel(0x000002A9, 0xF7EA0740);
	writel(0x000002A9, 0xF7EA0740);
	writel(0x000002A9, 0xF7EA0740);
	writel(0x000002A9, 0xF7EA0740);
	writel(0x000002A9, 0xF7EA0744);
	writel(0x000002A9, 0xF7EA0744);
	writel(0x000002A9, 0xF7EA0744);
	writel(0x000002A9, 0xF7EA0744);
	writel(0x000002E9, 0xF7EA0744);
	writel(0x000002A9, 0xF7EA0748);
	writel(0x000002A9, 0xF7EA0748);
	writel(0x000002A9, 0xF7EA0748);
	writel(0x000002A9, 0xF7EA0748);
	writel(0x000002A9, 0xF7EA0748);
	writel(0x000002A9, 0xF7EA074C);
	writel(0x000002A9, 0xF7EA074C);
	writel(0x000002A1, 0xF7EA074C);
	writel(0x000002B1, 0xF7EA074C);
	writel(0x00000291, 0xF7EA074C);
	writel(0x000002A9, 0xF7EA0754);
	writel(0x000002A9, 0xF7EA0754);
	writel(0x000002A9, 0xF7EA0754);
	writel(0x000002B9, 0xF7EA0754);
	writel(0x00000299, 0xF7EA0754);
	writel(0x000002A9, 0xF7EA0758);
	writel(0x000002A9, 0xF7EA0758);
	writel(0x000002A9, 0xF7EA0758);
	writel(0x000002A9, 0xF7EA0758);
	writel(0x000002E9, 0xF7EA0758);
	writel(0x000002A9, 0xF7EA0760);
	writel(0x000002A9, 0xF7EA0760);
	writel(0x000002A5, 0xF7EA0760);
	writel(0x000002B5, 0xF7EA0760);
	writel(0x00000295, 0xF7EA0760);
	writel(0x000002A9, 0xF7EA0764);
	writel(0x000002A9, 0xF7EA0764);
	writel(0x000002A5, 0xF7EA0764);
	writel(0x000002B5, 0xF7EA0764);
	writel(0x00000295, 0xF7EA0764);
	writel(0x000002A9, 0xF7EA0770);
	writel(0x000002A9, 0xF7EA0770);
	writel(0x000002A9, 0xF7EA0770);
	writel(0x000002A9, 0xF7EA0770);
	writel(0x000000A9, 0xF7EA0770);
	writel(0x000002A9, 0xF7EA0774);
	writel(0x000002A9, 0xF7EA0774);
	writel(0x000002A9, 0xF7EA0774);
	writel(0x000002A9, 0xF7EA0774);
	writel(0x000000A9, 0xF7EA0774);
	writel(0x000002A9, 0xF7EA0778);
	writel(0x000002A9, 0xF7EA0778);
	writel(0x000002A9, 0xF7EA0778);
	writel(0x000002A9, 0xF7EA0778);
	writel(0x000002A9, 0xF7EA0778);
	writel(0x000002A9, 0xF7EA077C);
	writel(0x000002A9, 0xF7EA077C);
	writel(0x000002A1, 0xF7EA077C);
	writel(0x000002B1, 0xF7EA077C);
	writel(0x00000131, 0xF7EA077C);
	writel(0x000002A9, 0xF7EA0780);
	writel(0x000002A9, 0xF7EA0780);
	writel(0x000002A9, 0xF7EA0780);
	writel(0x000002A9, 0xF7EA0780);
	writel(0x000000A9, 0xF7EA0780);
	writel(0x000002A9, 0xF7EA0784);
	writel(0x000002A9, 0xF7EA0784);
	writel(0x000002A9, 0xF7EA0784);
	writel(0x000002A9, 0xF7EA0784);
	writel(0x000002E9, 0xF7EA0784);
	writel(0x000002A9, 0xF7EA0790);
	writel(0x000002A9, 0xF7EA0790);
	writel(0x000002A3, 0xF7EA0790);
	writel(0x000002B3, 0xF7EA0790);
	writel(0x00000293, 0xF7EA0790);
	writel(0x000002A9, 0xF7EA0794);
	writel(0x000002A9, 0xF7EA0794);
	writel(0x000002A9, 0xF7EA0794);
	writel(0x000002A9, 0xF7EA0794);
	writel(0x00000129, 0xF7EA0794);
	writel(0x000002A8, 0xF7EA079C);
	writel(0x000002A8, 0xF7EA079C);
	writel(0x000002A8, 0xF7EA079C);
	writel(0x000002A8, 0xF7EA079C);
	writel(0x000001A8, 0xF7EA079C);
	writel(0x000002A9, 0xF7EA07A0);
	writel(0x000002A9, 0xF7EA07A0);
	writel(0x000002A9, 0xF7EA07A0);
	writel(0x000002A9, 0xF7EA07A0);
	writel(0x000001A9, 0xF7EA07A0);
	writel(0x000002A9, 0xF7EA07B0);
	writel(0x000002A9, 0xF7EA07B0);
	writel(0x000002A9, 0xF7EA07B0);
	writel(0x000002A9, 0xF7EA07B0);
	writel(0x000002E9, 0xF7EA07B0);
	writel(0x000002A9, 0xF7EA07B4);
	writel(0x000002A9, 0xF7EA07B4);
	writel(0x000002A9, 0xF7EA07B4);
	writel(0x000002A9, 0xF7EA07B4);
	writel(0x000001A9, 0xF7EA07B4);
	writel(0x000002A9, 0xF7EA07C0);
	writel(0x000002A9, 0xF7EA07C0);
	writel(0x000002A1, 0xF7EA07C0);
	writel(0x000002B1, 0xF7EA07C0);
	writel(0x00000131, 0xF7EA07C0);
	writel(0x000002A9, 0xF7EA07C4);
	writel(0x000002A9, 0xF7EA07C4);
	writel(0x000002A3, 0xF7EA07C4);
	writel(0x000002B3, 0xF7EA07C4);
	writel(0x00000293, 0xF7EA07C4);
	writel(0x000002A8, 0xF7EA07E0);
	writel(0x000002A8, 0xF7EA07E0);
	writel(0x000002A0, 0xF7EA07E0);
	writel(0x000002B0, 0xF7EA07E0);
	writel(0x00000230, 0xF7EA07E0);
	writel(0x000002A8, 0xF7EA07F0);
	writel(0x000002A8, 0xF7EA07F0);
	writel(0x000002A2, 0xF7EA07F0);
	writel(0x000002B2, 0xF7EA07F0);
	writel(0x000002B2, 0xF7EA07F0);
	writel(0x000002A8, 0xF7EA07F4);
	writel(0x000002A8, 0xF7EA07F4);
	writel(0x000002A6, 0xF7EA07F4);
	writel(0x000002B6, 0xF7EA07F4);
	writel(0x00000136, 0xF7EA07F4);
	writel(0x000002A9, 0xF7EA07F8);
	writel(0x000002A9, 0xF7EA07F8);
	writel(0x000002A9, 0xF7EA07F8);
	writel(0x000002A9, 0xF7EA07F8);
	writel(0x000002E9, 0xF7EA07F8);
	writel(0x000002A9, 0xF7EA0810);
	writel(0x000002A9, 0xF7EA0810);
	writel(0x000002A1, 0xF7EA0810);
	writel(0x000002B1, 0xF7EA0810);
	writel(0x00000131, 0xF7EA0810);
	writel(0x000002A9, 0xF7EA0814);
	writel(0x000002A9, 0xF7EA0814);
	writel(0x000002A5, 0xF7EA0814);
	writel(0x000002B5, 0xF7EA0814);
	writel(0x00000295, 0xF7EA0814);
	writel(0x000002A9, 0xF7EA0818);
	writel(0x000002A9, 0xF7EA0818);
	writel(0x000002A3, 0xF7EA0818);
	writel(0x000002B3, 0xF7EA0818);
	writel(0x00000293, 0xF7EA0818);
	writel(0x000002A9, 0xF7EA081C);
	writel(0x000002A9, 0xF7EA081C);
	writel(0x000002A9, 0xF7EA081C);
	writel(0x000002A9, 0xF7EA081C);
	writel(0x000002E9, 0xF7EA081C);
	writel(0x000002A8, 0xF7EA0820);
	writel(0x000002A8, 0xF7EA0820);
	writel(0x000002A0, 0xF7EA0820);
	writel(0x000002B0, 0xF7EA0820);
	writel(0x00000130, 0xF7EA0820);
	writel(0x000002A9, 0xF7EA0824);
	writel(0x000002A9, 0xF7EA0824);
	writel(0x000002A9, 0xF7EA0824);
	writel(0x000002B9, 0xF7EA0824);
	writel(0x000000B9, 0xF7EA0824);
	writel(0x000002A9, 0xF7EA0828);
	writel(0x000002A9, 0xF7EA0828);
	writel(0x000002A9, 0xF7EA0828);
	writel(0x000002A9, 0xF7EA0828);
	writel(0x000000A9, 0xF7EA0828);
	writel(0x000002A9, 0xF7EA082C);
	writel(0x000002A9, 0xF7EA082C);
	writel(0x000002A9, 0xF7EA082C);
	writel(0x000002A9, 0xF7EA082C);
	writel(0x000002E9, 0xF7EA082C);
	writel(0x000002A9, 0xF7EA0830);
	writel(0x000002A9, 0xF7EA0830);
	writel(0x000002A3, 0xF7EA0830);
	writel(0x000002B3, 0xF7EA0830);
	writel(0x00000293, 0xF7EA0830);
	writel(0x000002A9, 0xF7EA0834);
	writel(0x000002A9, 0xF7EA0834);
	writel(0x000002A9, 0xF7EA0834);
	writel(0x000002A9, 0xF7EA0834);
	writel(0x000000A9, 0xF7EA0834);
	writel(0x000002A9, 0xF7EA0838);
	writel(0x000002A9, 0xF7EA0838);
	writel(0x000002A9, 0xF7EA0838);
	writel(0x000002A9, 0xF7EA0838);
	writel(0x00000129, 0xF7EA0838);
	writel(0x000002A9, 0xF7EA083C);
	writel(0x000002A9, 0xF7EA083C);
	writel(0x000002A1, 0xF7EA083C);
	writel(0x000002B1, 0xF7EA083C);
	writel(0x00000131, 0xF7EA083C);
	writel(0x000002A8, 0xF7EA0840);
	writel(0x000002A8, 0xF7EA0840);
	writel(0x000002A8, 0xF7EA0840);
	writel(0x000002A8, 0xF7EA0840);
	writel(0x00000128, 0xF7EA0840);
	writel(0x000002A8, 0xF7EA0844);
	writel(0x000002A8, 0xF7EA0844);
	writel(0x000002A0, 0xF7EA0844);
	writel(0x000002B0, 0xF7EA0844);
	writel(0x000000B0, 0xF7EA0844);
	writel(0x000002A8, 0xF7EA0848);
	writel(0x000002A8, 0xF7EA0848);
	writel(0x000002A0, 0xF7EA0848);
	writel(0x000002B0, 0xF7EA0848);
	writel(0x000000B0, 0xF7EA0848);
	writel(0x000002A8, 0xF7EA084C);
	writel(0x000002A8, 0xF7EA084C);
	writel(0x000002A0, 0xF7EA084C);
	writel(0x000002B0, 0xF7EA084C);
	writel(0x000000B0, 0xF7EA084C);
	writel(0x000002A8, 0xF7EA0850);
	writel(0x000002A8, 0xF7EA0850);
	writel(0x000002A8, 0xF7EA0850);
	writel(0x000002A8, 0xF7EA0850);
	writel(0x000002A8, 0xF7EA0850);
	writel(0x000002A8, 0xF7EA0854);
	writel(0x000002A8, 0xF7EA0854);
	writel(0x000002A8, 0xF7EA0854);
	writel(0x000002A8, 0xF7EA0854);
	writel(0x000002A8, 0xF7EA0854);
	writel(0x000002A8, 0xF7EA0858);
	writel(0x000002A8, 0xF7EA0858);
	writel(0x000002A8, 0xF7EA0858);
	writel(0x000002A8, 0xF7EA0858);
	writel(0x000002A8, 0xF7EA0858);
	writel(0x000002A8, 0xF7EA085C);
	writel(0x000002A8, 0xF7EA085C);
	writel(0x000002A8, 0xF7EA085C);
	writel(0x000002A8, 0xF7EA085C);
	writel(0x000002A8, 0xF7EA085C);
	writel(0x000002A8, 0xF7EA0860);
	writel(0x000002A8, 0xF7EA0860);
	writel(0x000002A8, 0xF7EA0860);
	writel(0x000002A8, 0xF7EA0860);
	writel(0x000002A8, 0xF7EA0860);
	writel(0x000002A8, 0xF7EA0864);
	writel(0x000002A8, 0xF7EA0864);
	writel(0x000002A8, 0xF7EA0864);
	writel(0x000002A8, 0xF7EA0864);
	writel(0x000001A8, 0xF7EA0864);
	writel(0x000002A8, 0xF7EA0868);
	writel(0x000002A8, 0xF7EA0868);
	writel(0x000002A8, 0xF7EA0868);
	writel(0x000002A8, 0xF7EA0868);
	writel(0x000001A8, 0xF7EA0868);
	writel(0x000002A8, 0xF7EA086C);
	writel(0x000002A8, 0xF7EA086C);
	writel(0x000002A0, 0xF7EA086C);
	writel(0x000002B0, 0xF7EA086C);
	writel(0x000000B0, 0xF7EA086C);
	writel(0x000002A8, 0xF7EA0870);
	writel(0x000002A8, 0xF7EA0870);
	writel(0x000002A8, 0xF7EA0870);
	writel(0x000002A8, 0xF7EA0870);
	writel(0x000001A8, 0xF7EA0870);
	writel(0x000002A9, 0xF7EA0874);
	writel(0x000002A9, 0xF7EA0874);
	writel(0x000002A3, 0xF7EA0874);
	writel(0x000002B3, 0xF7EA0874);
	writel(0x000000B3, 0xF7EA0874);
	writel(0x00000012, 0xF7922000);
	writel(0x00000013, 0xF7922000);
	writel(0x00000000, 0xF7922008);
	writel(0x00000023, 0xF792200C);
	writel(0x00000000, 0xF7922010);
	writel(0x00000000, 0xF7922004);
	writel(0x0000001B, 0xF7922000);
	writel(0x00000000, 0xF7922014);
	writel(0x00000001, 0xF7922018);
	writel(0x0000001A, 0xF7922000);
	writel(0x00000018, 0xF7922000);
	writel(0x00000012, 0xF7EA0200);
	writel(0x00000013, 0xF7EA0200);
	writel(0x00000000, 0xF7EA0208);
	writel(0x00000017, 0xF7EA020C);
	writel(0x00000000, 0xF7EA0210);
	writel(0x00000000, 0xF7EA0204);
	writel(0x0000001B, 0xF7EA0200);
	writel(0x00000000, 0xF7EA0214);
	writel(0x00000002, 0xF7EA0218);
	writel(0x0000001A, 0xF7EA0200);
	writel(0x00000018, 0xF7EA0200);
	writel(0x00000012, 0xF7EA0220);
	writel(0x00000013, 0xF7EA0220);
	writel(0x00000000, 0xF7EA0228);
	writel(0x00000014, 0xF7EA022C);
	writel(0x00000000, 0xF7EA0230);
	writel(0x00000000, 0xF7EA0224);
	writel(0x0000001B, 0xF7EA0220);
	writel(0x00000000, 0xF7EA0234);
	writel(0x00000002, 0xF7EA0238);
	writel(0x0000001A, 0xF7EA0220);
	writel(0x00000018, 0xF7EA0220);
	writel(0x00000012, 0xF7EA0240);
	writel(0x00000013, 0xF7EA0240);
	writel(0x00000000, 0xF7EA0248);
	writel(0x00000013, 0xF7EA024C);
	writel(0x00000000, 0xF7EA0250);
	writel(0x00000000, 0xF7EA0244);
	writel(0x0000001B, 0xF7EA0240);
	writel(0x00000000, 0xF7EA0254);
	writel(0x00000004, 0xF7EA0258);
	writel(0x0000001A, 0xF7EA0240);
	writel(0x00000018, 0xF7EA0240);
}
#endif

static void set_drive_strength(void)
{
	unsigned int offset, val, drv;

	for (offset = RA_Gbl_SDIO_CDnCntl; offset <= RA_Gbl_I2S3_DICntl; offset += 4) {
		switch (offset) {
		case RA_Gbl_SDIO_CDnCntl ... RA_Gbl_SDIO_WPCntl:
		case RA_Gbl_TW0_SCLCntl ... RA_Gbl_TW0_SDACntl:
		case RA_Gbl_TX_EDDC_SCLCntl ... RA_Gbl_TX_EDDC_SDACntl:
			drv = 0x7;
			break;
		case RA_Gbl_RGMII_RXCTLCntl + 4 ... RA_Gbl_I2S1_DO0Cntl - 4:
			continue;
		default:
			drv = 0x3;
			break;
		}

		val = readl(MEMMAP_CHIP_CTRL_REG_BASE + offset);
		val |= drv;
		writel(val, MEMMAP_CHIP_CTRL_REG_BASE + offset);
	}

	for (offset = RA_smSysCtl_SM_TW3_SCLCntl; offset <= RA_smSysCtl_SM_TW3_SDACntl; offset += 4) {
		switch (offset) {
		case RA_smSysCtl_SM_TW3_SCLCntl ... RA_smSysCtl_SM_TW3_SDACntl:
			drv = 0x7;
			break;
		default:
			continue;
		}

		val = readl(SOC_SM_SYS_CTRL_REG_BASE + offset);
		val |= drv;
		writel(val, SOC_SM_SYS_CTRL_REG_BASE + offset);
	}
}

static void set_chip_control(void)
{
	unsigned int val;

	val = readl(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_chipCntl);
	val |= (1 << LSb32Gbl_chipCntl_TW1_SEL);
	writel(val, MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_chipCntl);

	val = readl(SOC_SM_SYS_CTRL_REG_BASE + RA_smSysCtl_SM_PORT_SEL_CTRL);
	val |= (1 << LSb32smSysCtl_SM_PORT_SEL_CTRL_TW2);
	writel(val, SOC_SM_SYS_CTRL_REG_BASE + RA_smSysCtl_SM_PORT_SEL_CTRL);
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
	set_chip_control();
	return 0;
}

#ifdef CONFIG_SYNA_SM
extern int syna_init_sm(void);
#endif

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

#ifdef CONFIG_SYNA_SM
	result = syna_init_sm();
	if (result)
		printf("Init SM failed, ret= 0x%08x\n", result);
#endif

#ifdef CONFIG_CMD_SYNA_MTDPARTS
	syna_init_mtdparts();
#endif

	return result;
}
