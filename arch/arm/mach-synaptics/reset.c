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
#include <asm/utils.h>
#include <watchdog.h>

#if defined(CONFIG_TARGET_DOLPHIN) || defined(CONFIG_TARGET_PLATYPUS)
#include <watchdog_def.h>
#endif

#if !defined(CONFIG_TARGET_DOLPHIN) && !defined(CONFIG_TARGET_PLATYPUS)
#ifdef CONFIG_TARGET_MYNA2
#define RA_Gbl_WDTSysRstMask			0x0610
#define CONFIG_DW_WDT_BASE			0xF7E83400
#define SOC_CHIP_CTRL_REG_BASE			0xF7EA0000
#else
#define CONFIG_DW_WDT_BASE			0xF7FC5000
#define SOC_SM_SYS_CTRL_REG_BASE		0xF7FE2000
#endif

#define CONFIG_DW_WDT_CLOCK_KHZ			25000

#define DW_WDT_CR	0x00
#define DW_WDT_TORR	0x04
#define DW_WDT_CRR	0x0C

#define DW_WDT_CR_EN_OFFSET	0x00
#define DW_WDT_CR_RMOD_OFFSET	0x01
#define DW_WDT_CR_RMOD_VAL	0
#define DW_WDT_CRR_RESTART_VAL	0x76
#define DW_WDT_CR_RPL_OFFSET	0x02
#define DW_WDT_CR_RPL_MASK	0x07
#define DW_WDT_CR_RPL_PCLK_8	0x02

static void berlin_dw_wdt_set_rspmode(int mode)
{
	unsigned int reg = readl(CONFIG_DW_WDT_BASE + DW_WDT_CR);

	if (mode)
		reg |= (1 << DW_WDT_CR_RMOD_OFFSET);
	else
		reg &= ~(1 << DW_WDT_CR_RMOD_OFFSET);
	writel(reg, CONFIG_DW_WDT_BASE + DW_WDT_CR);
}

static void berlin_dw_wdt_set_rpl(unsigned int rpl)
{
	unsigned int reg = readl(CONFIG_DW_WDT_BASE + DW_WDT_CR);

	reg &= ~(DW_WDT_CR_RPL_MASK << DW_WDT_CR_RPL_OFFSET);
	reg |= (rpl << DW_WDT_CR_RPL_OFFSET);
	writel(reg, CONFIG_DW_WDT_BASE + DW_WDT_CR);
}

/*
 * Set the watchdog time interval.
 * Counter is 32 bit.
 */
static int berlin_dw_wdt_settimeout(unsigned int timeout)
{
	signed int i;

	/* calculate the timeout range value */
	i = (log_2_n_round_up(timeout * CONFIG_DW_WDT_CLOCK_KHZ)) - 16;
	if (i > 15)
		i = 15;
	if (i < 0)
		i = 0;

	writel((i | (i << 4)), (CONFIG_DW_WDT_BASE + DW_WDT_TORR));
	return 0;
}

static void berlin_dw_wdt_init(void)
{
	unsigned int wdt_mask;
#if defined(CONFIG_TARGET_MYNA2)
	wdt_mask = readl(SOC_CHIP_CTRL_REG_BASE + RA_Gbl_WDTSysRstMask);

	//Clear bit0 for wdt0 mask, bit1 for wdt1, bit2 for wdt2
	wdt_mask &= ~(1 << 0);
	writel(wdt_mask, SOC_CHIP_CTRL_REG_BASE + RA_Gbl_WDTSysRstMask);
#else
	#define RA_smSysCtl_SM_WDT_MASK         0x003c
	wdt_mask = readl(SOC_SM_SYS_CTRL_REG_BASE + RA_smSysCtl_SM_WDT_MASK);
	//clear bit2 for wdt2 sm reset and bit 5 for wdt2 soc reset
	wdt_mask &= ~(1 << 2);
	wdt_mask &= ~(1 << 5);
	writel(wdt_mask, SOC_SM_SYS_CTRL_REG_BASE + RA_smSysCtl_SM_WDT_MASK);
#endif

	//interrupt mode, and reset signal pulse repeat 8 pclk cycles
	berlin_dw_wdt_set_rspmode(DW_WDT_CR_RMOD_VAL);
	berlin_dw_wdt_set_rpl(DW_WDT_CR_RPL_PCLK_8);
	berlin_dw_wdt_settimeout(0); // 2-3ms
}

static void berlin_dw_wdt_enable(void)
{
	unsigned int reg = readl(CONFIG_DW_WDT_BASE + DW_WDT_CR);

	reg |= 0x1 << DW_WDT_CR_EN_OFFSET;
	writel(reg, CONFIG_DW_WDT_BASE + DW_WDT_CR);
}

static unsigned int berlin_dw_wdt_is_enabled(void)
{
	unsigned long val;

	val = readl((CONFIG_DW_WDT_BASE + DW_WDT_CR));
	return val & 0x1;
}

void berlin_dw_wdt_reset(void)
{
	if (berlin_dw_wdt_is_enabled())
		/* restart the watchdog counter */
		writel(DW_WDT_CRR_RESTART_VAL,
		       (CONFIG_DW_WDT_BASE + DW_WDT_CRR));
}
#endif

#if defined(CONFIG_TARGET_DOLPHIN) || defined(CONFIG_TARGET_PLATYPUS)
void syna_dw_wdt_init(void)
{
	unsigned int wdt_mask;
		wdt_mask = readl(SOC_SM_SYS_CTRL_REG_BASE + RA_smSysCtl_SM_WDT_MASK);
		//clear bit2 for wdt2 sm reset and bit 5 for wdt2 soc reset
		wdt_mask &= ~(1 << 2);
		wdt_mask &= ~(1 << 5);
		writel(wdt_mask, SOC_SM_SYS_CTRL_REG_BASE + RA_smSysCtl_SM_WDT_MASK);
}

#endif

void reset_cpu(unsigned long ignored)
{
#if !defined(CONFIG_TARGET_DOLPHIN) && !defined(CONFIG_TARGET_PLATYPUS)
	berlin_dw_wdt_init();
	berlin_dw_wdt_enable();
	berlin_dw_wdt_reset();
#else
	syna_dw_wdt_init();
	hw_watchdog_init();
	mdelay(5);
	hw_watchdog_reset();
#endif
	while (1)
		;
}

void reset_misc(void)
{
#if CONFIG_IS_ENABLED(CMD_SF)
	run_command("sf remove", 0);
#endif
}
