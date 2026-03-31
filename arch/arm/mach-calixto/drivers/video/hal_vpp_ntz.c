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

#include "hal_vpp_wrap.h"
#include "includes.h"
#include "vpp_api.h"
#include "syna_lcdc_dev.h"
#include "vpp_priv.h"
#include "dsih_displays.h"

int NTZ_MV_VPP_InitVPPS(struct berlin_fb_priv *priv)
{
	return syna_lcdc_init(priv);
}

int NTZ_MV_VPP_Mipi_LoadInfoTable(struct berlin_fb_priv *priv)
{
	int ret;

	ret = syna_lcdc_mipi_dsi_config(priv);
	if (ret)
		printf("Invalid MIPI-DSI config\n");

	return ret;
}

int NTZ_MV_VPP_Mipi_LoadConfig(struct berlin_fb_priv *priv)
{
	struct lcdc_config *lcdc_config_data = priv->lcdc_config_data;

	if (!lcdc_config_data->is_dev_avail[DISPLAY_TYPE_DSI] &&
		!lcdc_config_data->is_dev_avail[DISPLAY_TYPE_TFT]) {
		printf("Error: DSI or RGB panel not available\n");
		return -ENODEV;
	}

	if (lcdc_config_data->is_dev_avail[DISPLAY_TYPE_DSI]) {
		dsi_platform_init(lcdc_config_data->dsi_dev, 0, 0,
				  lcdc_config_data->synaDsiInfo.lanes);

		/* For the PHY  Reset to first command Need a Delay of 0.5 ms */
		udelay(500);
		dsi_panel_send_cmd(lcdc_config_data->synaDsiInfo.cmdbufferSize,
				   lcdc_config_data->synaDsiInfo.pcmd);
	}

	return 0;
}

void NTZ_MV_VPP_Enable_Interrupt(struct berlin_fb_priv *priv)
{
	syna_lcdc_Enable_IRQ(priv->lcdc_config_data->irqno);
}

int NTZ_MV_VPP_Display_Frame(struct berlin_fb_priv *priv, VBUF_INFO *pVppBuf,
			     int display, int width, int height)
{
	return lcdc_push_frame(priv, pVppBuf, display, width, height);
}

void NTZ_MV_VPP_Stop(void)
{
	syna_lcdc_clear_disable_interrupts();
}

void NTZ_MV_VPP_DeInit(struct berlin_fb_priv *priv)
{
	syna_lcdc_Disable_IRQ(priv->lcdc_config_data->irqno);
}

void wrap_vpp_initialize_fops(struct vpp_fops *vpp_fops)
{
	vpp_fops->MV_VPP_InitVPPS = NTZ_MV_VPP_InitVPPS;
	vpp_fops->MV_VPP_Create = NULL;
	vpp_fops->MV_VPP_Reset = NULL;
	vpp_fops->MV_VPP_Config = NULL;
	vpp_fops->MV_VPP_Set_Format = NULL;
	vpp_fops->MV_VPP_SetHdmiTxControl = NULL;
	vpp_fops->MV_VPP_Config_Display = NULL;
	vpp_fops->MV_VPP_Mipi_LoadInfoTable = NTZ_MV_VPP_Mipi_LoadInfoTable;
	vpp_fops->MV_VPP_Mipi_LoadConfig = NTZ_MV_VPP_Mipi_LoadConfig;
	vpp_fops->MV_VPP_Enable_Interrupt = NTZ_MV_VPP_Enable_Interrupt;
	vpp_fops->MV_VPP_Display_Frame = NTZ_MV_VPP_Display_Frame;
	vpp_fops->MV_VPP_Stop = NTZ_MV_VPP_Stop;
	vpp_fops->MV_VPP_DeInit = NTZ_MV_VPP_DeInit;
}
