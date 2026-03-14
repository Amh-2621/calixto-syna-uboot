// SPDX-License-Identifier: GPL-2.0+
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

#include "includes.h"
#include "dsih_core.h"
#include "DPHYTX.h"

void mipi_dphy_BiuCtrlPHYEn(dphy_t *phy, int en)
{
	T32DPHYTX_DPHY_CTL0 ctrl;

	ioread32(phy->base + RA_DPHYTX_DPHY_CTL0, &ctrl.u32);
	ctrl.uDPHY_CTL0_BiuCtrlPhyEn = en;
	iowrite32(phy->base + RA_DPHYTX_DPHY_CTL1, ctrl.u32);

	return;
}

void mipi_dphy_shutdown(dphy_t *phy, int shutdown)
{
	T32DPHYTX_DPHY_CTL1 ctrl;

	ioread32(phy->base + RA_DPHYTX_DPHY_CTL1, &ctrl.u32);
	ctrl.uDPHY_CTL1_shutdownz = shutdown;
	iowrite32(phy->base + RA_DPHYTX_DPHY_CTL1, ctrl.u32);
	return;
}

void mipi_dphy_resetz(dphy_t *phy, int resetz)
{
	T32DPHYTX_DPHY_CTL1 ctrl;

	ioread32(phy->base + RA_DPHYTX_DPHY_CTL1, &ctrl.u32);
	ctrl.uDPHY_CTL1_rstz = resetz;
	iowrite32(phy->base + RA_DPHYTX_DPHY_CTL1, ctrl.u32);
	return;
}

void mipi_dphy_enable_lanes(dphy_t *phy, int lanes)
{
	int lane_mask = 0x1;
	T32DPHYTX_DPHY_CTL1 ctrl;

	ioread32(phy->base + RA_DPHYTX_DPHY_CTL1, &ctrl.u32);

	if (lanes & lane_mask) {
	   ctrl.uDPHY_CTL1_enable_0 =  1;
	} else {
		ctrl.uDPHY_CTL1_enable_0 =  0;
	}

	lane_mask = (lane_mask << 1);
	if (lanes & lane_mask) {
		ctrl.uDPHY_CTL1_enable_1 =  1;
	} else {
		ctrl.uDPHY_CTL1_enable_1 =  0;
	}

	lane_mask = (lane_mask << 1);
	if (lanes & lane_mask) {
		ctrl.uDPHY_CTL1_enable_2 =  1;
	} else {
		ctrl.uDPHY_CTL1_enable_2 =  0;
	}

	lane_mask = (lane_mask << 1);
	if (lanes & lane_mask) {
		ctrl.uDPHY_CTL1_enable_1 =  1;
	} else {
		ctrl.uDPHY_CTL1_enable_1 =  0;
	}

	iowrite32(phy->base + RA_DPHYTX_DPHY_CTL1, ctrl.u32);

	return;
}

void mipi_dphy_EnableClkBIU(dphy_t *phy, int en)
{
	T32DPHYTX_DPHY_CTL1 ctrl;

	ioread32(phy->base + RA_DPHYTX_DPHY_CTL1, &ctrl.u32);
	ctrl.uDPHY_CTL1_enableclkBIU = en;
	iowrite32( phy->base + RA_DPHYTX_DPHY_CTL1, ctrl.u32);
	return;
}

void mipi_dphy_CfgClkFreqRange(dphy_t *phy, int range)
{
	T32DPHYTX_DPHY_CTL1 ctrl;

	ioread32( phy->base + RA_DPHYTX_DPHY_CTL1, &ctrl.u32);
	ctrl.uDPHY_CTL1_cfgclkfreqrange = range;
	iowrite32( phy->base + RA_DPHYTX_DPHY_CTL1, ctrl.u32);
	return;
}

void mipi_dphy_pll_shadow_control_en(dphy_t *phy, int en)
{
	T32DPHYTX_DPHY_PLL2 ctrl;

	ioread32(phy->base + RA_DPHYTX_DPHY_PLL2, &ctrl.u32);
	ctrl.uDPHY_PLL2_pll_shadow_control = en;
	iowrite32( phy->base + RA_DPHYTX_DPHY_PLL2, ctrl.u32);
}

void mipi_dphy_pll_clksel(dphy_t *phy, int clksel)
{
	T32DPHYTX_DPHY_PLL2 ctrl;

	ioread32(phy->base + RA_DPHYTX_DPHY_PLL2, &ctrl.u32);
	ctrl.uDPHY_PLL2_clksel = clksel;
	iowrite32( phy->base + RA_DPHYTX_DPHY_PLL2, ctrl.u32);
}

void mipi_dphy_stopstate_wait(dphy_t *phy, int lanes)
{
	T32DPHYTX_DPHY_RB0 rb0, cond;
	unsigned int wait = 0xF00;

	lanes = (1<<lanes)-1;
	cond.u32 = 0;
	cond.uDPHY_RB0_stopstateclk = 1;
	cond.uDPHY_RB0_stopstatedata_0 = (lanes & 0x1)?1:0;
	cond.uDPHY_RB0_stopstatedata_1 = (lanes & 0x2)?1:0;
	cond.uDPHY_RB0_stopstatedata_2 = (lanes & 0x4)?1:0;
	cond.uDPHY_RB0_stopstatedata_3 = (lanes & 0x8)?1:0;
	do {
		ioread32(phy->base + RA_DPHYTX_DPHY_RB0, &rb0.u32);
		rb0.u32 = (rb0.u32 & 0x3D000);
		if (!wait)
			break;
		wait = wait - 1;
	} while (rb0.u32 != cond.u32);
}
