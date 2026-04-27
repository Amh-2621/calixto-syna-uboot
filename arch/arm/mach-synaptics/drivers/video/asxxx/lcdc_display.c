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

#include "common.h"
#include <malloc.h>
#include "includes.h"
#include "dsih_api.h"
#include "hal_dhub.h"
#include "vpp_api.h"
#include "vpp_priv.h"
#include "dsih_displays.h"
#include "avpll.h"

#define MP_BERLIN_INTR_ID(id)   (id + 32)
#define PIXEL_CLOCK_RATE(FREQ)  (4 * FREQ)

void syna_lcdc_ISR_Handler(void *param)
{
	HDL_semaphore *pSemHandle;
	int instat, intmask;
	int no = 0;

	/* VPP interrupt handling  */
	pSemHandle = dhub_semaphore(&VPP_dhubHandle.dhub);
	intmask = instat = semaphore_chk_full(pSemHandle, -1);

	while (intmask)
	{
		if(instat & (1 << no)) {
			semaphore_pop(pSemHandle, no, 1);
			semaphore_clr_full(pSemHandle, no);
			syna_lcdc_irq(instat & (1 << no));
		}
		++no;
		intmask >>= 1;
	}
}

void syna_lcdc_Enable_IRQ(int intrno)
{
	irq_install_handler(MP_BERLIN_INTR_ID(intrno), syna_lcdc_ISR_Handler, NULL);
}

void syna_lcdc_Disable_IRQ(int intrno)
{
	irq_free_handler(MP_BERLIN_INTR_ID(intrno));
}

int lcdc_push_frame(struct berlin_fb_priv *priv, VBUF_INFO *pVppBuf,
		    int display, int width, int height)
{
	SYNA_LCDC_PANEL lcdcConfig = {0};
	PANEL_TIMING_INFO *pTimingInfo;
	int ret;

	pTimingInfo = &priv->lcdc_config_data->pTimingInfo[DISPLAY_TYPE_TFT];

	lcdcConfig.hsync_len = pTimingInfo[display].hsa;
	lcdcConfig.right_margin = pTimingInfo[display].hfp; //FP
	lcdcConfig.xres = pTimingInfo[display].hact;
	lcdcConfig.left_margin = pTimingInfo[display].hbp;  //BP

	/*vtotal = vsync_len + upper_margin + yres + lower_margin*/
	lcdcConfig.vsync_len = pTimingInfo[display].vsa;
	lcdcConfig.lower_margin = pTimingInfo[display].vfp; //FP
	lcdcConfig.yres = pTimingInfo[display].vact;
	lcdcConfig.upper_margin = pTimingInfo[display].vbp; //BP
	lcdcConfig.pixclock = pTimingInfo[display].pixelclock;
	lcdcConfig.mode = pTimingInfo[display].outformat;
	lcdcConfig.bits_per_pixel = pTimingInfo[display].bpp;
	lcdcConfig.rgb_swap = pTimingInfo[display].rgbswap;

	AVPLL_SetClockGenericFreq(display,
				  PIXEL_CLOCK_RATE(lcdcConfig.pixclock));

	syna_lcdc_hw_config(display, &lcdcConfig);
	ret = syna_lcdc_pushframe(display, pVppBuf);
	if (ret) {
		printf("LCDC frame push failed\n");
		return ret;
	}

	return 0;
}

int syna_get_display_modeinfo(struct berlin_fb_priv *priv, int *width,
			      int *height, int display, avio_fastlogo_info *dispinfo)
{
	struct lcdc_config *lcdc_config_data;
	PANEL_TIMING_INFO *pTimingInfo;

	lcdc_config_data = priv->lcdc_config_data;
	pTimingInfo = &lcdc_config_data->pTimingInfo[DISPLAY_TYPE_TFT];

	if (lcdc_config_data->is_dev_avail[display]) {
		*width = pTimingInfo[display].hact;
		*height = pTimingInfo[display].vact;
		return 0;
	}

	return -EINVAL;
}

int syna_lcdc_mipi_dsi_config(struct berlin_fb_priv *priv)
{
	VPP_MIPI_CONFIG_PARAMS *pResCfg;
	PANEL_TIMING_INFO *pTimingInfo;
	struct mipi_dsi_dev *dsi_dev;
	SYNA_DSI_DESC *synaDsiInfo;

	pResCfg = priv->vpp_config_param.mipi_resinfo_params;

	pTimingInfo = &priv->lcdc_config_data->pTimingInfo[DISPLAY_TYPE_DSI];

	pTimingInfo->hact = pResCfg->infoparams.resInfo.active_width;
	pTimingInfo->hfp = pResCfg->infoparams.resInfo.hfrontporch;
	pTimingInfo->hsa = pResCfg->infoparams.resInfo.hsyncwidth;
	pTimingInfo->hbp = pResCfg->infoparams.resInfo.hbackporch;
	pTimingInfo->vact = pResCfg->infoparams.resInfo.active_height;
	pTimingInfo->vfp = pResCfg->infoparams.resInfo.vfrontporch;
	pTimingInfo->vsa = pResCfg->infoparams.resInfo.vsyncwidth;
	pTimingInfo->vbp = pResCfg->infoparams.resInfo.vbackporch;
	pTimingInfo->pixelclock = pResCfg->infoparams.resInfo.freq;
	pTimingInfo->bpp = priv->vpp_config_param.disp2_bpp;
	pTimingInfo->outformat = priv->vpp_config_param.disp2_outformat;

	synaDsiInfo = &priv->lcdc_config_data->synaDsiInfo;

	synaDsiInfo->htotal = pResCfg->infoparams.resInfo.width;
	synaDsiInfo->byteclock = pResCfg->initparams.byte_clock;
	synaDsiInfo->lanes = pResCfg->initparams.no_of_lanes;
	synaDsiInfo->video_mode = pResCfg->initparams.video_mode;
	synaDsiInfo->receive_ack = pResCfg->initparams.receive_ack_packets;
	synaDsiInfo->is_18_loose = pResCfg->initparams.is_18_loosely;
	synaDsiInfo->h_polarity = pResCfg->initparams.h_polarity;
	synaDsiInfo->v_polarity = pResCfg->initparams.v_polarity;
	synaDsiInfo->data_polarity = pResCfg->initparams.data_en_polarity;
	synaDsiInfo->eotp_tx = pResCfg->initparams.eotp_tx_en;
	synaDsiInfo->eotp_rx = pResCfg->initparams.eotp_rx_en;
	synaDsiInfo->non_continuous_clock = pResCfg->initparams.non_continuous_clock;
	synaDsiInfo->lpcmd = pResCfg->initparams.dpi_lp_cmd_en;
	synaDsiInfo->color_coding = pResCfg->initparams.color_coding;
	synaDsiInfo->chunks = pResCfg->initparams.no_of_chunks;
	synaDsiInfo->null_pkt = pResCfg->initparams.null_packet_size;

	synaDsiInfo->cmdbufferSize = pResCfg->vppMipiCmd.bufsize;
	synaDsiInfo->pcmd = pResCfg->vppMipiCmd.pcmd + MIPI_CMD_HEADER_SIZE;

	if (!synaDsiInfo->cmdbufferSize || !synaDsiInfo->pcmd) {
		printf("Invalid MIPI commands\n");
		return -EINVAL;
	}

	dsi_dev = priv->lcdc_config_data->dsi_dev;

	dsi_dev->dpi_video.virtual_channel = 0;
	dsi_dev->dpi_video.display_type = 0;
	dsi_dev->dpi_video.no_of_lanes = synaDsiInfo->lanes;
	dsi_dev->dpi_video.video_mode = synaDsiInfo->video_mode;
	dsi_dev->dpi_video.receive_ack_packets = synaDsiInfo->receive_ack;
	dsi_dev->dpi_video.is_18_loosely = synaDsiInfo->is_18_loose;
	dsi_dev->dpi_video.data_en_polarity = synaDsiInfo->data_polarity;
	dsi_dev->dpi_video.h_polarity = synaDsiInfo->h_polarity;
	dsi_dev->dpi_video.v_polarity = synaDsiInfo->v_polarity;
	dsi_dev->dpi_video.color_coding = synaDsiInfo->color_coding;
	dsi_dev->dpi_video.eotp_rx_en = synaDsiInfo->eotp_rx;
	dsi_dev->dpi_video.eotp_tx_en = synaDsiInfo->eotp_tx;
	dsi_dev->dpi_video.non_continuous_clock = synaDsiInfo->non_continuous_clock;
	dsi_dev->dpi_video.no_of_chunks = synaDsiInfo->chunks;
	dsi_dev->dpi_video.null_packet_size = synaDsiInfo->null_pkt;
	dsi_dev->dpi_video.dpi_lp_cmd_en = synaDsiInfo->lpcmd;
	dsi_dev->dpi_video.byte_clock = synaDsiInfo->byteclock;
	dsi_dev->dpi_video.h_total_pixels = synaDsiInfo->htotal;
	dsi_dev->dpi_video.h_sync_pixels = pTimingInfo->hsa;
	dsi_dev->dpi_video.h_back_porch_pixels = pTimingInfo->hbp;
	dsi_dev->dpi_video.v_sync_lines = pTimingInfo->vsa;
	dsi_dev->dpi_video.v_back_porch_lines = pTimingInfo->vbp;
	dsi_dev->dpi_video.h_active_pixels = pTimingInfo->hact;
	dsi_dev->dpi_video.v_active_lines = pTimingInfo->vact;
	dsi_dev->dpi_video.pixel_clock = pTimingInfo->pixelclock;
	dsi_dev->dpi_video.v_total_lines = pTimingInfo->vact + pTimingInfo->vsa +
					   pTimingInfo->vfp + pTimingInfo->vbp;

	priv->lcdc_config_data->is_dev_avail[DISPLAY_TYPE_DSI] = 1;

	return 0;
}

int syna_lcdc_init(struct berlin_fb_priv *priv)
{
	struct lcdc_config *lcdc_config_data;
	int ret;

	lcdc_config_data = priv->lcdc_config_data;

	ret = drv_dhub_initialize_dhub(NULL);
	if (ret) {
		printf("dhub init fail\n");
		return ret;
	}

	ret = drv_lcdc_init(NULL);
	if (ret) {
		printf("LCDC init fail\n");
		return ret;
	}

	lcdc_config_data->dsi_dev = malloc(sizeof(struct mipi_dsi_dev));
	if (!lcdc_config_data->dsi_dev) {
		printf("Error in allocating memory for dsi_dev");
		return -ENOMEM;
	}

	ret = mipi_dsi_init(lcdc_config_data->dsi_dev);
	if (ret) {
		printf("MIPI-DSI init fail\n");
		return ret;
	}

	dsi_register_device(lcdc_config_data->dsi_dev);

	return 0;
}
