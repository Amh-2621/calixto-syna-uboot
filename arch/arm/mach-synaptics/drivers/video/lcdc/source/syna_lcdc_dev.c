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

#include <common.h>
#include <malloc.h>
#include <string.h>
#include "Galois_memmap.h"
#include "avioGbl.h"
#include "avio_memmap.h"
#include "lcdc.h"
#include "vpp_api.h"
#include "drv_lcdc.h"

struct syna_lcdc_dev *syna_lcdc[SYNA_LCDC_MAX];

unsigned long syna_lcdc_readl(struct syna_lcdc_dev *dev, unsigned long addr)
{
	unsigned int val;

	GA_REG_WORD32_READ(dev->core_addr + addr, &val);
	return val;
}

void syna_lcdc_writel(struct syna_lcdc_dev *dev, unsigned long addr, unsigned long val)
{
	addr += dev->core_addr;
	if (dev->bcm_enable)
		bcmbuf_write(CURR_VBI_BCM_BUF, addr, val);
	else
		GA_REG_WORD32_WRITE(addr, val);
}

static void syna_lcdc_hw_param_update(struct syna_lcdc_dev *dev)
{
	syna_lcdc_writel(dev, LCDC_REG_PARUP, 1);

	if (dev->panel->intf_type & SYNA_LCDC_TYPE_DPI_MCU)
		syna_lcdc_writel(dev, LCDC_REG_CDISPUPR, 1); /*start sending display command & data*/

	if (dev->panel->intf_type & SYNA_LCDC_INTF_TYPE_DSI)
		/* send single new frame */
		syna_lcdc_writel(dev, LCDC_REG_LCDCCR, 1);
}


static void syna_lcdc_wrap_interrupt_enable(void)
{
	unsigned int addr;
	T32avioGbl_INTR_CTRL lcdc_intr;

	addr = SYNA_MEMMAP_AVIO_GBL_BASE + RA_avioGbl_INTR_CTRL;
	GA_REG_WORD32_READ(addr, &lcdc_intr.u32);
	lcdc_intr.uINTR_CTRL_mipi_int_en = 1;
	lcdc_intr.uINTR_CTRL_lcdc1_int_en = 1;
	lcdc_intr.uINTR_CTRL_lcdc2_int_en = 1;
	GA_REG_WORD32_WRITE(addr, lcdc_intr.u32);
}

static void syna_lcdc_semaintr_enable(int intr, int enable)
{
	HDL_semaphore *pSemHandle = dhub_semaphore(&VPP_dhubHandle.dhub);

	semaphore_cfg(pSemHandle, intr, 1, 0);
	semaphore_clr_full(pSemHandle, intr);
	semaphore_intr_enable(pSemHandle, intr, 0, enable, 0, 0, 0);
}

static void syna_lcdc_wrap_lcdcclk_enable(void)
{
	unsigned int addr;
	T32avioGbl_LCDC_CTRL lcdc_ctrl;

	addr = MEMMAP_AVIO_REG_BASE + AVIO_MEMMAP_AVIO_GBL_BASE + RA_avioGbl_LCDC_CTRL;
	GA_REG_WORD32_READ(addr, &lcdc_ctrl.u32);
	lcdc_ctrl.uLCDC_CTRL_lcdc1_clk_sel = 0;
	lcdc_ctrl.uLCDC_CTRL_lcdc1_ClkEn = 1;
	lcdc_ctrl.uLCDC_CTRL_lcdc1_sysClk_en = 1;

	lcdc_ctrl.uLCDC_CTRL_lcdc2_clk_sel = 1;
	lcdc_ctrl.uLCDC_CTRL_lcdc2_ClkEn = 1;
	lcdc_ctrl.uLCDC_CTRL_lcdc2_sysClk_en = 1;

	lcdc_ctrl.uLCDC_CTRL_lcdc1_ClkSel = 2;
	lcdc_ctrl.uLCDC_CTRL_lcdc1_ClkSwitch = 1;
	lcdc_ctrl.uLCDC_CTRL_lcdc1_ClkD3Switch = 0;

	lcdc_ctrl.uLCDC_CTRL_lcdc2_ClkSel = 2;
	lcdc_ctrl.uLCDC_CTRL_lcdc2_ClkSwitch = 1;
	lcdc_ctrl.uLCDC_CTRL_lcdc2_ClkD3Switch = 0;

	GA_REG_WORD32_WRITE(addr, lcdc_ctrl.u32);
}

static void syna_lcdc_wrap_clkgating_disable(void)
{
	unsigned int addr;
	T32avioGbl_CTRL gbl_ctrl;

	addr = MEMMAP_AVIO_REG_BASE + AVIO_MEMMAP_AVIO_GBL_BASE + RA_avioGbl_CTRL;
	GA_REG_WORD32_READ(addr, &gbl_ctrl.u32);
	gbl_ctrl.uCTRL_AIODHUB_dyCG_en = 0;
	gbl_ctrl.uCTRL_AIODHUB_CG_en = 0;
	gbl_ctrl.uCTRL_VPPDHUB_dyCG_en = 0;
	gbl_ctrl.uCTRL_VPPDHUB_CG_en = 0;
	GA_REG_WORD32_WRITE(addr, gbl_ctrl.u32);
}

static void syna_lcdc_set_hw_init(struct syna_lcdc_dev *dev)
{
	int dispir = 0, pancsr;
	unsigned int gpsel = 0;
	T32LCDC_CTRL5 lcdc_ctrl;
	struct syna_lcdc_panel_t *panel = dev->panel;

	lcdc_ctrl.u32 = syna_lcdc_readl(dev, RA_LCDC_CTRL5);

	if (panel->intf_type & SYNA_LCDC_TYPE_DPI_MCU)
		syna_lcdc_writel(dev, LCDC_REG_LCDCCR, 2); /* FIF0 Reset */

	/* clear all pending interrupts (may exist from u-boot) */
	syna_lcdc_writel(dev, LCDC_REG_INTSR,syna_lcdc_readl(dev, LCDC_REG_INTSR)); //clear all interrupts

	syna_lcdc_writel(dev, LCDC_REG_INTER, INT_FRAME_DONE);

	if (panel->intf_type & SYNA_LCDC_TYPE_DPI_MCU) {
		dispir = 4; //CPU type LCD
		gpsel = 0;
		if ((panel->bits_per_pixel != 8) && (panel->bits_per_pixel != 9)) {
			dispir |= 0x20; //CPU type MODE16
		}

		lcdc_ctrl.uCTRL5_full_level_14_en = 0;
		if (panel->bits_per_pixel == 9) {
			lcdc_ctrl.uCTRL5_cpu_mode18 = 1; //cpu_mode18
		}
		else if (panel->bits_per_pixel == 16) {
			switch (panel->mode) {
				case SYNA_LCDC_MODE_3:
					lcdc_ctrl.uCTRL5_cpu_mux_exp_en = 1;
					lcdc_ctrl.uCTRL5_cpu_mode16as24 = 1;
					break;
				case SYNA_LCDC_MODE_2:
					lcdc_ctrl.uCTRL5_cpu_mux_exp_en = 1;
					lcdc_ctrl.uCTRL5_cpu_mode16as18 = 1;//cpu_mux_exp_en | cpu_mode16as18
					break;
				case SYNA_LCDC_MODE_1:
					lcdc_ctrl.uCTRL5_cpu_mux_exp_en = 1;
					lcdc_ctrl.uCTRL5_cpu_cmd_shift1 = 1;//cpu_mux_exp_en | cpu_cmd_shift1
					break;
				case SYNA_LCDC_MODE_0:
					lcdc_ctrl.uCTRL5_cpu_mux_exp_en = 1; //cpu_mux_exp_en
				default:
					break;
			}
		}
		else if (panel->bits_per_pixel == 18) {
			switch (panel->mode) {
				case SYNA_LCDC_MODE_1:
					lcdc_ctrl.uCTRL5_cpu_mux_exp_en = 1;
					lcdc_ctrl.uCTRL5_cpu_cmd_shift1 = 1;
					lcdc_ctrl.uCTRL5_cpu_mode18 = 1;
					break;
				case SYNA_LCDC_MODE_0:
				default:
					lcdc_ctrl.uCTRL5_cpu_mux_exp_en = 1;
					lcdc_ctrl.uCTRL5_cpu_mode18 = 1;
					break;
			}
		}
		else if (panel->bits_per_pixel == 24) {
			switch (panel->mode) {
				case SYNA_LCDC_MODE_1:
					lcdc_ctrl.uCTRL5_cpu_mux_exp_en = 1;
					lcdc_ctrl.uCTRL5_cpu_cmd_shift1 = 1;
					break;
				case SYNA_LCDC_MODE_0:
				default:
					lcdc_ctrl.uCTRL5_cpu_mux_exp_en = 1;
					lcdc_ctrl.uCTRL5_cpu_mode18 = 1;
					break;
			}
		}
	}
	else if (panel->intf_type & SYNA_LCDC_TYPE_DSI_CMD)
		dispir = LCDC_DSI_CMD_MODE;
	else {
		if (panel->bits_per_pixel == 24) {
			dispir = 1;
			gpsel = 0;
		}
		else if (panel->bits_per_pixel == 18) {
			switch (panel->mode) {
				case SYNA_LCDC_MODE_3:
					gpsel = (1 << 1); //GPMUX18B
					lcdc_ctrl.uCTRL5_cpu_mux_exp_en = 1;
					break;
				case SYNA_LCDC_MODE_2:
					gpsel = (1 << 4); //LBPPM
					break;
				case SYNA_LCDC_MODE_1:
					gpsel = (1 << 6)| (1 << 4); //ROUND666 | LBPPM
					break;
				 case SYNA_LCDC_MODE_0:
				default:
					gpsel = 0;
					break;
			}
		}
		else if (panel->bits_per_pixel == 16) {
			switch (panel->mode) {
				case SYNA_LCDC_MODE_3:
					gpsel = (1 << 2); //GPMUX16B
					lcdc_ctrl.uCTRL5_cpu_mux_exp_en = 1;
					break;
				case SYNA_LCDC_MODE_2:
					//LBPPM | ROUND565
					gpsel = (1 << 4) | (1 << 5);
					break;
				case SYNA_LCDC_MODE_1:
					gpsel = 0;
					lcdc_ctrl.uCTRL5_b16as18 = 1; //b16as18
					break;
				case SYNA_LCDC_MODE_0:
				default:
					gpsel = 0;
					//contiguous16
					lcdc_ctrl.uCTRL5_contiguous16 = 1;
					break;
			}
		}
	}
	if (panel->ext_te)
		dispir |= LCDC_WAIT_FOR_TE;

	syna_lcdc_writel(dev, LCDC_REG_DISPIR, dispir);
	syna_lcdc_writel(dev, LCDC_REG_GPSELR, gpsel);
	syna_lcdc_writel(dev, RA_LCDC_CTRL5, lcdc_ctrl.u32);

	pancsr = (panel->iclk) | (panel->rgb_swap << 4);
	syna_lcdc_writel(dev, LCDC_REG_PANCSR, pancsr);
}

static void syna_lcdc_config_tg(struct syna_lcdc_dev *dev)
{
	SYNA_LCDC_PANEL *panel = dev->panel;

	syna_lcdc_writel(dev, LCDC_REG_LCDCCR, 0);
	syna_lcdc_writel(dev, LCDC_REG_DISPCR, 0);

	syna_lcdc_writel(dev, LCDC_REG_VSTR, panel->vsync_len - 1);
	syna_lcdc_writel(dev, LCDC_REG_VFTR, panel->upper_margin);
	syna_lcdc_writel(dev, LCDC_REG_VATR, panel->yres - 1 + panel->vskip);
	syna_lcdc_writel(dev, LCDC_REG_VETR, panel->lower_margin);
	syna_lcdc_writel(dev, LCDC_REG_HSTR, panel->hsync_len - 1);
	syna_lcdc_writel(dev, LCDC_REG_HFTR, panel->left_margin - 1);
	syna_lcdc_writel(dev, LCDC_REG_HADSTR, panel->xres - 1 + panel->hskip);
	syna_lcdc_writel(dev, LCDC_REG_HAPWR, panel->xres - 1 + panel->hskip);
	syna_lcdc_writel(dev, LCDC_REG_HETR, panel->right_margin - 1);

	syna_lcdc_writel(dev, LCDC_REG_INDXSR, panel->xres - 1);
	syna_lcdc_writel(dev, LCDC_REG_INDYSR, panel->yres - 1);

	/* display position */
	syna_lcdc_writel(dev, LCDC_REG_DISPXSPOSR, 0);
	syna_lcdc_writel(dev, LCDC_REG_DISPXEPOSR, panel->xres - 1);
	syna_lcdc_writel(dev, LCDC_REG_DISPYEPOS1R, panel->yres - 1);

	/* input buffer */
	//start DMA command
	if (dev->panel->intf_type & SYNA_LCDC_TYPE_DPI_MCU) {
		syna_lcdc_writel(dev, LCDC_REG_CMDFSR, LCDC_CMD_SIZE); //CMDSIZE
		syna_lcdc_writel(dev, LCDC_REG_GP0A_H_HI, 0x0E);
		syna_lcdc_writel(dev, LCDC_REG_GP0A_V_ST, 0x0E);
		syna_lcdc_writel(dev, LCDC_REG_GP0A_H_LO, 0x06);
		syna_lcdc_writel(dev, LCDC_REG_GP0B_H_HI, 0x00);
		syna_lcdc_writel(dev, LCDC_REG_GP0B_V_ST, 0x00);
		syna_lcdc_writel(dev, LCDC_REG_GP0B_H_LO, 0x0B);
		syna_lcdc_writel(dev, LCDC_REG_GP0B_V_END, 0x0B);
		syna_lcdc_writel(dev, LCDC_REG_GP0BCNTR, 0xA800);
		syna_lcdc_writel(dev, LCDC_REG_GP1B_H_HI, 0x02);
		syna_lcdc_writel(dev, LCDC_REG_GP1B_V_ST, 0x03);
		syna_lcdc_writel(dev, LCDC_REG_GP1B_H_LO, 0x07);
		syna_lcdc_writel(dev, LCDC_REG_GP1B_V_END, 0x07);
		syna_lcdc_writel(dev, LCDC_REG_GP1BCNTR, 0x20A0);
		syna_lcdc_writel(dev, LCDC_REG_GP2_H_HI, 0x02);
		syna_lcdc_writel(dev, LCDC_REG_GP2_V_ST, 0x03);
		syna_lcdc_writel(dev, LCDC_REG_GP2_H_LO, 0x08);
		syna_lcdc_writel(dev, LCDC_REG_GP2_V_END, 0x07);
		syna_lcdc_writel(dev, LCDC_REG_GP2CNTR, 0xA800);
		syna_lcdc_writel(dev, LCDC_REG_GP3_H_HI, 0x01);
		syna_lcdc_writel(dev, LCDC_REG_GP3_V_ST, 0x02);
		syna_lcdc_writel(dev, LCDC_REG_GP3_H_LO, 0x09);
		syna_lcdc_writel(dev, LCDC_REG_GP3_V_END, 0x08);
		syna_lcdc_writel(dev, LCDC_REG_GP3CNTR, 0xA8A0);
		syna_lcdc_writel(dev, LCDC_REG_CTLTR0, 0x800);
		syna_lcdc_writel(dev, LCDC_REG_GP0A_V_END, 0x0B);
		syna_lcdc_writel(dev, LCDC_REG_GP0ACNTR, 0xA800);
		syna_lcdc_writel(dev, LCDC_REG_GP_HMAXR, 0x103);
		syna_lcdc_writel(dev, LCDC_REG_GP_VMAXR, 0x9C);
	}
	syna_lcdc_dlr_handler(dev);

	syna_lcdc_hw_param_update(dev);

	syna_lcdc_writel(dev, LCDC_REG_DISPCR, 1);
	syna_lcdc_writel(dev, LCDC_REG_LCDCCR, 1);
}

static struct syna_lcdc_dev *syna_lcdc_create(int num, SYNA_LCDC_PANEL *panel) {

	struct syna_lcdc_dev *dev;

	if (!panel)
		return NULL;

	dev = (struct syna_lcdc_dev *) malloc(sizeof(struct syna_lcdc_dev));
	if (!dev)
		return NULL;

	memset(dev, 0, sizeof(struct syna_lcdc_dev));

	if (!num)
		dev->core_addr = MEMMAP_AVIO_REG_BASE + AVIO_MEMMAP_AVIO_LCDC1_REG_BASE;
	else
		dev->core_addr = MEMMAP_AVIO_REG_BASE + AVIO_MEMMAP_AVIO_LCDC2_REG_BASE;
	//Save panel device pointer
	dev->panel = panel;

	if (SYNA_LCDC_OK != syna_lcdc_dlr_create(dev, num))
		return NULL;

	return dev;
}

int syna_lcdc_pushframe(int lcdcID, void *pnew)
{
	syna_lcdc[lcdcID]->curr_frame = pnew;
	syna_lcdc[lcdcID]->en_intr_handler = 1;

	return SYNA_LCDC_OK;
}

void syna_lcdc_hw_config(int lcdcID, SYNA_LCDC_PANEL *panelcfg)
{
	if (!syna_lcdc[lcdcID]->isTGConfig) {
		memcpy(syna_lcdc[lcdcID]->panel, panelcfg, sizeof(SYNA_LCDC_PANEL));

		// FIX ME: Caller Should Differentiate CPU type or RGB i/f
		syna_lcdc[lcdcID]->panel->intf_type = SYNA_LCDC_TYPE_DPI_RGB;
		syna_lcdc[lcdcID]->isTGConfig = 1;
		syna_lcdc[lcdcID]->bcm_enable = 1;
		syna_lcdc[lcdcID]->bcm_autopush_en = 1;

		syna_bcmbuf_flip(syna_lcdc[lcdcID]);
		syna_lcdc_set_hw_init(syna_lcdc[lcdcID]);
		syna_lcdc_config_tg(syna_lcdc[lcdcID]);
		syna_bcmbuf_submit(syna_lcdc[lcdcID], 0); //use VBI
		syna_lcdc_semaintr_enable(syna_lcdc[lcdcID]->intrID, 1);
	}
}

void syna_lcdc_irq(int intrMask)
{
	struct syna_lcdc_dev *dev;
	int stat, i;

	for (i = 0; i < SYNA_LCDC_MAX; i++) {
		if (intrMask & ((1 << (avioDhubSemMap_vpp128b_vpp_inr0 + i)))) {
			dev = syna_lcdc[i];
			/* read & clear active interrupts */

			stat = syna_lcdc_readl(dev, LCDC_REG_INTSR);
			GA_REG_WORD32_WRITE(dev->core_addr + LCDC_REG_INTSR, stat);

			if (stat & INT_FRAME_DONE) {
				dev->interrupts++;
				if (dev->en_intr_handler) {
					syna_bcmbuf_flip(dev);
					syna_lcdc_writel(dev, LCDC_REG_INTSR, 0x2);
					syna_lcdc_dlr_handler(dev);
					syna_lcdc_hw_param_update(dev); //TO handle input change
					syna_bcmbuf_submit(dev, 1);
				}
			}
		}
	}
}

static void syna_lcdc_destroy(int lcdcId)
{
	syna_lcdc_dlr_destroy(syna_lcdc[lcdcId]);

	free(syna_lcdc[lcdcId]->panel);
	free(syna_lcdc[lcdcId]);
}

void syna_lcdc_dev_deinit(void)
{
	int i;

	for (i = 0; i < SYNA_LCDC_MAX; i++) {
		syna_lcdc_destroy(i);
	}
}

static int syna_lcdc_dev_init(void)
{
	int i;
	SYNA_LCDC_PANEL *syna_panel_config;

	/*FIXME: configure based on resolution configuration*/
	GA_REG_WORD32_WRITE(MEMMAP_AVIO_REG_BASE + AVIO_MEMMAP_AVIO_GBL_BASE + RA_avioGbl_VPLL0_WRAP+RA_VPLL_WRAP_VPLL_CTRL, 0x820);
	GA_REG_WORD32_WRITE(MEMMAP_AVIO_REG_BASE + AVIO_MEMMAP_AVIO_GBL_BASE + RA_avioGbl_VPLL1_WRAP + RA_VPLL_WRAP_VPLL_CTRL, 0x820);
	GA_REG_WORD32_WRITE(MEMMAP_AVIO_REG_BASE + AVIO_MEMMAP_AVIO_GBL_BASE + RA_avioGbl_AVPLLA_CLK_EN, 0x4F);
	GA_REG_WORD32_WRITE(MEMMAP_AVIO_REG_BASE + AVIO_MEMMAP_AVIO_GBL_BASE + RA_avioGbl_LCDC2_CTRL, 0x39);

	syna_lcdc_wrap_lcdcclk_enable();
	syna_lcdc_wrap_clkgating_disable();
	syna_lcdc_wrap_interrupt_enable();

	for (i = 0; i < SYNA_LCDC_MAX; i++) {
		syna_panel_config = (SYNA_LCDC_PANEL *) malloc(sizeof(struct syna_lcdc_dev));
		if (syna_panel_config == NULL) {
			printf("failed to alloc panel mem lcdc\n");
			return SYNA_LCDC_EBADPARAM;
		}

		syna_lcdc[i] = syna_lcdc_create(i, syna_panel_config);
		if (syna_lcdc[i] == NULL) {
			printf("failed to create lcdc\n");
			if (i == 1)
				syna_lcdc_destroy(0);

			return SYNA_LCDC_EBADPARAM;
		}
		syna_lcdc[i]->m_srcfmt = -1;
		syna_lcdc[i]->interrupts = 0;
		//Set the interrupt driving the BCM Channel
		BCM_SCHED_SetMux(i, syna_lcdc[i]->intrNo);
	}

	return SYNA_LCDC_OK;
}

int drv_lcdc_init(void *ctxt)
{
	return syna_lcdc_dev_init();
}

void syna_lcdc_clear_disable_interrupts(void)
{
	int i;

	for (i = 0; i < SYNA_LCDC_MAX; i++) {
		/* clear all pending interrupts */
		if (syna_lcdc[i]->en_intr_handler) {
			/* Wait for MIN interrupts to push atleast a frame to o/p */
			while (syna_lcdc[i]->interrupts <= 4) {
				udelay(INTR_CLEAR_WAIT_DELAY);
			};

			GA_REG_WORD32_WRITE(syna_lcdc[i]->core_addr + LCDC_REG_INTSR,
							syna_lcdc_readl(syna_lcdc[i], LCDC_REG_INTSR));

			GA_REG_WORD32_WRITE(syna_lcdc[i]->core_addr + LCDC_REG_INTER, 0);
		}
	}
	return;
}
