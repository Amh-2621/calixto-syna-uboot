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

#ifndef VPP_H
#define VPP_H

#include "vpp_api.h"

#define IS_MODE_MIPI(mode)		((mode == VOUT_DISP_SINGLE_MODE_SEC) || \
					 (mode == VOUT_DISP_DUAL_MODE_PIP))

#define IS_MODE_DUAL(mode)		(mode == VOUT_DISP_DUAL_MODE_PIP)

int MV_VPP_Init(struct berlin_fb_priv *priv);
int MV_VPP_Config_Display(struct berlin_fb_priv *priv);
void MV_VPP_Enable_Interrupt(struct berlin_fb_priv *priv);
int MV_VPP_Display_Frame(struct berlin_fb_priv *priv, VBUF_INFO *pVppBuf,
			 int display, int width, int height);
void MV_VPP_Stop(void);
void MV_VPP_DeInit(struct berlin_fb_priv *priv);
int syna_load_logo_info (int width, int height, VBUF_INFO *pVppBuf, FASTLOGO_INFO *fl_info);

#endif
