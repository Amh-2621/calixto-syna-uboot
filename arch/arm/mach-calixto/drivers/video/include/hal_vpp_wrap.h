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

#ifndef _HAL_VPP_WRAP_H
#define _HAL_VPP_WRAP_H

#include "common.h"
#include <dm.h>
#include "vpp_api.h"

struct vpp_fops {
	int (*MV_VPP_InitVPPS)(struct berlin_fb_priv *priv);
	int (*MV_VPP_Create)(void);
	int (*MV_VPP_Reset)(void);
	int (*MV_VPP_Config)(const int *pvinport_cfg, const int *pdv_cfg,
				const int *pzorder_cfg, const int *pvoutport_cfg, const int *pfeature_cfg);
	int (*MV_VPP_Set_Format)(struct berlin_fb_priv *priv);
	int (*MV_VPP_SetHdmiTxControl)(void);
	int (*MV_VPP_Config_Display)(struct berlin_fb_priv *priv);
	int (*MV_VPP_Mipi_LoadInfoTable)(struct berlin_fb_priv *priv);
	int (*MV_VPP_Mipi_LoadConfig)(struct berlin_fb_priv *priv);
	void (*MV_VPP_Enable_Interrupt)(struct berlin_fb_priv *priv);
	int (*MV_VPP_Display_Frame)(struct berlin_fb_priv *priv,
				    VBUF_INFO *pVppBuf, int display, int width, int height);
	void (*MV_VPP_Stop)(void);
	void (*MV_VPP_DeInit)(struct berlin_fb_priv *priv);
};

void wrap_vpp_initialize_fops(struct vpp_fops *vpp_fops);
int wrap_MV_VPP_InitVPPS(struct berlin_fb_priv *priv);
int wrap_MV_VPP_Create(void);
int wrap_MV_VPP_Reset(void);
int wrap_MV_VPP_Config(const int *pvinport_cfg, const int *pdv_cfg,
			const int *pzorder_cfg, const int *pvoutport_cfg, const int *pfeature_cfg);
int wrap_MV_VPP_Set_Format(struct berlin_fb_priv *priv);
int wrap_MV_VPP_SetHdmiTxControl(void);
int wrap_MV_VPP_Config_Display(struct berlin_fb_priv *priv);
int wrap_MV_VPP_Mipi_LoadInfoTable(struct berlin_fb_priv *priv);
int wrap_MV_VPP_Mipi_LoadConfig(struct berlin_fb_priv *priv);
void wrap_MV_VPP_Enable_Interrupt(struct berlin_fb_priv *priv);
int wrap_MV_VPP_Display_Frame(struct berlin_fb_priv *priv, VBUF_INFO *pVppBuf,
			      int display, int width, int height);
void wrap_MV_VPP_Stop(void);
void wrap_MV_VPP_DeInit(struct berlin_fb_priv *priv);

#endif
