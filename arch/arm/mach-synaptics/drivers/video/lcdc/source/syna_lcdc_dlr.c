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
#include "lcdc.h"
#include "syna_lcdc_dev.h"
#include "hal_dhub.h"
#include "bcmbuf.h"
#include "vdec_com.h"

#include "asm/io.h"

#define START_2DDMA(dhubID, dmaID, start_addr, stride, width, height, cfgQ) \
		dhub2d_channel_cfg(&VPP_dhubHandle, dmaID, start_addr, stride, width, height,\
							1, 0, 0, 0, 0, 1, cfgQ)
#define START_2NDDMA(dhubID, dmaID, start_addr, burst, step1, size1, step2, size2, cfgQ) \
		dhub2nd_channel_cfg(&VPP_dhubHandle, dmaID, start_addr, burst, step1, size1, step2,\
							size2, 0, 0, 0, 1, cfgQ)

//BGRA output
static unsigned char syna_lcdc_bitmap_table[SYNA_LCDC_PIXFMT_MAX][SYNA_LCDC_PIXORDER_MAX][32] = {
	{//ARGB32 input
		{ //ARGB
			24, 25, 26, 27, 28, 29, 30, 31, 16, 17, 18, 19, 20, 21, 22, 23,
			8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4 ,5, 6, 7,
		},
		{ //ABGR
			8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
			24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4 ,5, 6, 7,
		},
		{ //RGBA
			16, 17, 18, 19, 20, 21, 22, 23, 8, 9, 10, 11, 12, 13, 14, 15,
			0, 1, 2, 3, 4 ,5, 6, 7, 24, 25, 26, 27, 28, 29, 30, 31,
		},
		{ //BGRA
			0, 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
			16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
		}
	},
	{ //ARGB32_PM
		{ //ARGB
			24, 25, 26, 27, 28, 29, 30, 31, 16, 17, 18, 19, 20, 21, 22, 23,
			8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4 ,5, 6, 7,
		},
		{ //ABGR
			8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
			25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4 ,5, 6, 7,
		},
		{ //RGBA
			16, 17, 18, 19, 20, 21, 22, 23, 8, 9, 10, 11, 12, 13, 14, 15,
			0, 1, 2, 3, 4 ,5, 6, 7, 24, 25, 26, 27, 28, 29, 30, 31,
		},
		{ //BGRA
			0, 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
			16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
		}
	},
	{ //RGB565
		{ //RGB
			11, 12, 13, 14, 15, 5, 6, 7, 8, 9, 10, 0, 1, 2, 3, 4,
			27, 28, 29, 30, 31, 21, 22, 23, 24, 25, 26, 16, 17, 18, 19, 20,
		},
		{ //BGR
			0, 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
			17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
		},
		{//RGB
			11, 12, 13, 14, 15, 5, 6, 7, 8, 9, 10, 0, 1, 2, 3, 4,
			27, 28, 29, 30, 31, 21, 22, 23, 24, 25, 26, 16, 17, 18, 19, 20,
		},
		{ //BGR
			0, 1, 2, 3, 4 ,5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
			16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
		}
	},
	{ //RGB888
		{ //RGB
			24, 25, 26, 27, 28, 29, 30, 31, 16, 17, 18, 19, 20, 21, 22, 23,
			8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4 ,5, 6, 7,
		},
		{ //BGR
			24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7,
			8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
		},
		{ //RGB
			24, 25, 26, 27, 28, 29, 30, 31, 16, 17, 18, 19, 20, 21, 22, 23,
			8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4 ,5, 6, 7,
		},
		{ //BGR
			24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7,
			8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
		}
	}
};

static void syna_lcdc_dlr_frameupdate(struct syna_lcdc_dev *dev)
{
	dev->prev_frame = dev->curr_frame;
}

static void syna_lcdc_dlr_startClient(struct syna_lcdc_dev *dev)
{
	T32LCDC_CTRL3 ctrl3;

	ctrl3.u32 = 0;
	ctrl3.uCTRL3_ClientR0_start = 1;
	ctrl3.uCTRL3_ClientR0_clear = 0;
	syna_lcdc_writel(dev, RA_LCDC_CTRL3, ctrl3.u32);
}

static void syna_lcdc_dlr_clearClient(struct syna_lcdc_dev *dev)
{
	T32LCDC_CTRL3 ctrl3;

	ctrl3.u32 = 0;
	ctrl3.uCTRL3_ClientR0_clear = 1;
	syna_lcdc_writel(dev, RA_LCDC_CTRL3, ctrl3.u32);
}

static void syna_lcdc_dlr_setbitmap(struct syna_lcdc_dev *dev,
									int src_fmt,
									int order)
{
	unsigned char *bitmap_table = NULL;
	T32LCDC_CTRL4 ctrl4;
	T32BITMAP32_SEL sel;
	T32BITMAP32_SEL5 sel5;
	int index = 0;

	ctrl4.u32 = syna_lcdc_readl(dev, RA_LCDC_CTRL4);
	ctrl4.uCTRL4_bitmap32_en = 1;
	syna_lcdc_writel(dev, RA_LCDC_CTRL4, ctrl4.u32);

	bitmap_table = &syna_lcdc_bitmap_table[src_fmt][order][0];

	do {
		sel.uSEL_BIT_POS0 = bitmap_table[index + 0];
		sel.uSEL_BIT_POS1 = bitmap_table[index + 1];
		sel.uSEL_BIT_POS2 = bitmap_table[index + 2];
		sel.uSEL_BIT_POS3 = bitmap_table[index + 3];
		sel.uSEL_BIT_POS4 = bitmap_table[index + 4];
		sel.uSEL_BIT_POS5 = bitmap_table[index + 5];
		syna_lcdc_writel(dev, RA_LCDC_bitmap32_ctrl + 4 * (index / 6), sel.u32);
		index += 6;
	} while(index < 30);

	sel5.uSEL_BIT_POS30 = bitmap_table[index + 0];
	sel5.uSEL_BIT_POS31 = bitmap_table[index + 1];
	syna_lcdc_writel(dev, RA_LCDC_bitmap32_ctrl + 4 * (index / 6), sel5.u32);
}

static void syna_lcdc_dlr_start2DDMA(struct syna_lcdc_dev *dev, VBUF_INFO *pinfo)
{
	int *cfgQ = NULL;
	int *cfgQ_shadow = NULL;
	int *cfgQ_len = NULL;
	unsigned int start_addr;
	unsigned int stride;
	unsigned int width_byte;

	start_addr = pinfo->m_pbuf_start;
	width_byte = (pinfo->m_content_width * pinfo->m_bits_per_pixel)/8;
	stride = (width_byte * 16 + 15)/16; /*16-byte alignment*/

	if (dev->bcm_enable) {
		cfgQ_shadow = (void *) CURR_VBI_DMA_CFGQ->addr;
		cfgQ_len = &CURR_VBI_DMA_CFGQ->len;
		cfgQ = cfgQ_shadow + *cfgQ_len * 2;//cfgQ_shadow + *cfgQ_len;
		*cfgQ_len += START_2NDDMA(dev->dhubID, dev->dmaRID,
								start_addr, width_byte, width_byte,
								1, stride, pinfo->m_content_height,
								(T64b*) cfgQ);
	}
	else {
		START_2NDDMA(dev->dhubID, dev->dmaRID, start_addr,
					width_byte,	width_byte, 1, stride,
					pinfo->m_content_height, NULL);
	}
}

static void syna_lcdc_dlr_setdisplay_bpp(struct syna_lcdc_dev *dev,
										int m_bits_per_pixel,
										int move_alpha)
{
	unsigned int bpp = 0;

	if (m_bits_per_pixel != 16) {
		bpp = 1;
		if (m_bits_per_pixel == 24) {
			//Bit map setting for RGB888
			bpp |= 1 << 4;
		}
		else if (m_bits_per_pixel == 32){
			//Bit map setting = A[31:24] B[23:16] G[15:8] R[7:0]
			bpp |= 1 << 4;

			//MSB Alpha
			if (move_alpha)
				bpp |= 1 << 3;
		}
	}
	//Input type mode register (IBCR)
	syna_lcdc_writel(dev, LCDC_REG_INTMR, bpp);

	return;
}

static void syna_lcdc_dlr_setplane_position(struct syna_lcdc_dev *dev,
											int x, int y,
											int width, int height)
{
	syna_lcdc_writel(dev, LCDC_REG_INDXSR, width - 1);
	syna_lcdc_writel(dev, LCDC_REG_INDYSR, height - 1);

	/* display position */
	syna_lcdc_writel(dev, LCDC_REG_DISPXSPOSR, 0);
	syna_lcdc_writel(dev, LCDC_REG_DISPXEPOSR, width - 1);
	syna_lcdc_writel(dev, LCDC_REG_DISPYEPOS1R, height - 1);
}

static void syna_lcdc_dlr_start(struct syna_lcdc_dev *dev)
{
	VBUF_INFO *pinfo;
	T32LCDC_CTRL1 ctrl1;
	T32LCDC_CTRL2 ctrl2;

	pinfo = dev->curr_frame;
	if (!pinfo) {
		return;
	}

	if ((pinfo->m_srcfmt != dev->m_srcfmt) ||
		(pinfo->m_order != dev->m_order) ||
		(pinfo->m_content_width != dev->m_content_width) ||
		(pinfo->m_content_height != dev->m_content_height) ||
		(pinfo->m_bits_per_pixel != dev->m_bits_per_pixel)) {

		ctrl2.u32 = 0;
		ctrl2.uCTRL2_flushCnt_R0 = 0x5;
		if ((pinfo->m_bits_per_pixel == 32) ||
			(pinfo->m_bits_per_pixel == 16)) {
			ctrl2.uCTRL2_packSel_R0 = 0; //32-bit packing
		}
		else if (pinfo->m_bits_per_pixel == 24) {
			ctrl2.uCTRL2_packSel_R0 = 1; //24-bit packing
		}

		//ceil( ohres*ovres*bpp/128 )
		ctrl1.uCTRL1_wordTot_R0 = \
					(pinfo->m_content_width * pinfo->m_bits_per_pixel)/8;

		if (ctrl1.uCTRL1_wordTot_R0 % 16) {
			ctrl2.uCTRL2_nonStdResEn_R0 = 1;
			ctrl1.uCTRL1_wordTot_R0 = ctrl1.uCTRL1_wordTot_R0/16 + 1;
		}
		else {
			ctrl2.uCTRL2_nonStdResEn_R0 = 0;
			ctrl1.uCTRL1_wordTot_R0 = ctrl1.uCTRL1_wordTot_R0/16;
		}
		ctrl1.uCTRL1_wordTot_R0 *= pinfo->m_content_height;

		//width * bpp/32
		ctrl2.uCTRL2_pixlineTot_R0 = \
					(pinfo->m_content_width * pinfo->m_bits_per_pixel)/32;

		syna_lcdc_writel(dev, RA_LCDC_CTRL1, ctrl1.u32);
		syna_lcdc_writel(dev, RA_LCDC_CTRL2, ctrl2.u32);

		syna_lcdc_dlr_setdisplay_bpp(dev, pinfo->m_bits_per_pixel, 1);

		syna_lcdc_dlr_setplane_position(dev, 0, 0,
					pinfo->m_content_width,
					pinfo->m_content_height);

		syna_lcdc_dlr_setbitmap(dev, pinfo->m_srcfmt, pinfo->m_order);
		dev->m_srcfmt = pinfo->m_srcfmt;
		dev->m_order = pinfo->m_order;
		dev->m_content_width = pinfo->m_content_width;
		dev->m_content_height = pinfo->m_content_height;
		dev->m_bits_per_pixel = pinfo->m_bits_per_pixel;
	}

	syna_lcdc_dlr_start2DDMA(dev, pinfo);
}

void syna_lcdc_dlr_flipbuf(struct syna_lcdc_dev *dev)
{
	dev->bufferCurSet = !dev->bufferCurSet;
}

void syna_lcdc_dlr_resetbuf(struct syna_lcdc_dev *dev)
{
	if (dev->bcm_enable) {
		/* reset vbi bcm & dma cfgQ length */
		CURR_VBI_BCM_CFGQ->len = 0;
		CURR_VBI_DMA_CFGQ->len = 0;
		bcmbuf_reset(CURR_VBI_BCM_BUF);

		/* select BCM sub-buffer to dump register settings */
		bcmbuf_select(CURR_VBI_BCM_BUF, 0);
	}
}

static void syna_lcdc_dlr_mergebuf(struct syna_lcdc_dev *dev)
{
	if (dev->bcm_enable) {
		bcmbuf_to_CFGQ(&AG_dhubHandle, avioDhubChMap_aio64b_BCM_R,
						BCM_SCHED_Q13, CURR_VBI_BCM_BUF,
						CURR_VBI_BCM_CFGQ);

		flush_dcache_range((long unsigned int)CURR_VBI_DMA_CFGQ->addr,
			((int)(long long)CURR_VBI_DMA_CFGQ->addr) + DMA_CMD_BUFFER_SIZE);

		bcmbuf_CFGQ_To_CFGQ(&AG_dhubHandle, avioDhubChMap_aio64b_BCM_R,
							BCM_SCHED_Q13, CURR_VBI_DMA_CFGQ,
							CURR_VBI_BCM_CFGQ);
	}
}

static void syna_lcdc_dlr_commitbuf(struct syna_lcdc_dev *dev, int use_vbi)
{
	int schedQ;

	if (!dev->bcm_enable) {
		return;
	}

	flush_dcache_range((long unsigned int)CURR_VBI_BCM_CFGQ->addr,
		((int)(long long) CURR_VBI_BCM_CFGQ->addr) + DMA_CMD_BUFFER_SIZE);

	schedQ = (dev->lcdcID == 0) ? BCM_SCHED_Q0 : BCM_SCHED_Q1;
	if (use_vbi) {
		bcmbuf_DHUB_CFGQ_Commit(&AG_dhubHandle,
							avioDhubChMap_aio64b_BCM_R,
							schedQ,
							CURR_VBI_BCM_CFGQ, dev->lcdcID, 0);

		if (dev->bcm_autopush_en) {
			if (CURR_VBI_BCM_CFGQ->len != 0 && CURR_VBI_DMA_CFGQ->len != 0) {
				bcmbuf_DHUB_AutoPush(
							schedQ,
							dev->dmaRID, dev->bcm_autopush_en);
			}
		}
		else {
			bcmbuf_DHUB_AutoPush(
					schedQ,
					dev->dmaRID, 0);
		}
	}
	else {
		bcmbuf_cfgq_hardwaretrans(&AG_dhubHandle,
								avioDhubChMap_aio64b_BCM_R,
								BCM_SCHED_Q12,
								CURR_VBI_BCM_CFGQ, 1);
		if (dev->bcm_enable) {
			//To avoid issue for 2nd Frame
			bcmbuf_DHUB_CFGQ_Commit(&AG_dhubHandle,
					avioDhubChMap_aio64b_BCM_R,
					schedQ,
					CURR_VBI_BCM_CFGQ, dev->lcdcID, 0);
		}
	}
}

void syna_bcmbuf_flip(struct syna_lcdc_dev *dev)
{
	/*flip dhub - bcm bufs*/
	syna_lcdc_dlr_flipbuf(dev);
	syna_lcdc_dlr_resetbuf(dev);
}

void syna_bcmbuf_submit(struct syna_lcdc_dev *dev, int use_vbi)
{
	syna_lcdc_dlr_mergebuf(dev);
	syna_lcdc_dlr_commitbuf(dev, use_vbi);
}

void syna_lcdc_dlr_handler(struct syna_lcdc_dev *dev)
{
	//update current frame
	syna_lcdc_dlr_frameupdate(dev);

	if (dev->curr_frame) {

		//client clear
		syna_lcdc_dlr_clearClient(dev);

		//start channel data loader
		syna_lcdc_dlr_start(dev);

		//client start
		syna_lcdc_dlr_startClient(dev);
	}
}

void syna_lcdc_dlr_init(struct syna_lcdc_dev *dev, int num)
{
	dev->prev_frame = NULL;
	dev->curr_frame = NULL;
	dev->dhubID = (int)(long long)&VPP_dhubHandle;

	/**
	  * Refer AVIO_BCM.pdf intrNo details
	  */
	dev->lcdcID = num;
	if (num == SYNA_LCDC_1) {
		dev->dmaRID = avioDhubChMap_vpp128b_LCDC1_R;
		dev->intrID = avioDhubSemMap_vpp128b_vpp_inr0;
		dev->intrNo = 0x18; //LCDC1 Frame end interrupt
	} else {
		dev->dmaRID = avioDhubChMap_vpp128b_LCDC2_R;
		dev->intrID = avioDhubSemMap_vpp128b_vpp_inr1;
		dev->intrNo = 0x1B; //LCDC2 Frame end interrupt
	}
}

static void syna_lcdc_create_BcmCfgQ(struct syna_lcdc_dev *dev,
								DHUB_CFGQ *cfgQ,
								void *pvpp_mem)
{
	cfgQ->handle = malloc(DMA_CMD_BUFFER_SIZE);
	cfgQ->addr = cfgQ->handle;
	cfgQ->phy_addr = cfgQ->handle;
}

int syna_lcdc_dlr_create(struct syna_lcdc_dev *dev, int num)
{
	int i;

	for (i = 0; i < BCM_BUF_COUNT; i++) {
		/* create VBI BCM buffer */
		if (bcmbuf_create(&(dev->bcmbuf[i].vbi_bcm_buf),
			BCM_BUFFER_SIZE,
			dev->vpp_mem_list) != SYNA_LCDC_OK) {
			printf("failed to create bcmbuf\n");
			return SYNA_LCDC_ENOMEM;
		}

		syna_lcdc_create_BcmCfgQ(dev,
			&dev->bcmbuf[i].vbi_cfgQ[SYNA_DHUB_CFGQ_TYPE_DMA],
			&dev->bcmbuf[i].vpp_mem_handle[SYNA_DHUB_CFGQ_TYPE_DMA]);

		syna_lcdc_create_BcmCfgQ(dev,
			&dev->bcmbuf[i].vbi_cfgQ[SYNA_DHUB_CFGQ_TYPE_BCM],
			&dev->bcmbuf[i].vpp_mem_handle[SYNA_DHUB_CFGQ_TYPE_BCM]);

		dev->bufferCurSet = 0;
	}

	/*For first frame, Direct write method used for Register & DHUB Write*/
	dev->prev_frame = NULL;
	dev->curr_frame = NULL;

	syna_lcdc_dlr_init(dev, num);

	return SYNA_LCDC_OK;
}

void syna_lcdc_dlr_intr_enable(int intr, int enable)
{
	HDL_semaphore *pSemHandle = dhub_semaphore(&VPP_dhubHandle.dhub);

	semaphore_cfg(pSemHandle, intr, 1, 0);
	semaphore_clr_full(pSemHandle, intr);
	semaphore_intr_enable(pSemHandle, intr,
						0/*empty*/, enable/*full*/,
						0/*almost empty*/,
						0/*almost full*/,
						0/*cpu id*/);
}

void syna_lcdc_dlr_destroy(struct syna_lcdc_dev *dev)
{
	int i;

	for (i = 0; i < BCM_BUF_COUNT; i++) {
		free(dev->bcmbuf[i].vbi_cfgQ[SYNA_DHUB_CFGQ_TYPE_DMA].addr);
		free(dev->bcmbuf[i].vbi_cfgQ[SYNA_DHUB_CFGQ_TYPE_BCM].addr);

		bcmbuf_destroy(&(dev->bcmbuf[i].vbi_bcm_buf));
	}
}
