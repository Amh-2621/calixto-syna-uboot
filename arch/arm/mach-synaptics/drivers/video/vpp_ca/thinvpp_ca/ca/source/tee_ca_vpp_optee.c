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

#ifdef CONFIG_FASTLOGO
#include <dm/device.h>

#include "avpll.h"
#include "vdec_com.h"
#include "vpp_api.h"
#endif

#include "OSAL_api.h"
#include "common.h"
#include "vpp_cmd.h"
#include "tee.h"

#define TA_FASTLOGO_UUID {0x1316a183, 0x894d, 0x43fe,	\
			 {0x98, 0x93, 0xbb, 0x94, 0x6a, 0xe1, 0x03, 0xf5}}

static struct udevice *tee_dev;
static u32 session;

static int match(struct tee_version_data *vers, const void *data)
{
	return vers->gen_caps & TEE_GEN_CAP_GP;
}

int VppInitialize(void)
{
	const struct tee_optee_ta_uuid fastlogo_uuid = TA_FASTLOGO_UUID;
	struct tee_open_session_arg sess_arg = {0};
	struct tee_version_data vers;
	int ret;

	tee_dev = tee_find_device(NULL, match, NULL, &vers);
	if (!tee_dev) {
		debug("dev not found\n");
		return -1;
	}
	tee_optee_ta_uuid_to_octets(sess_arg.uuid, &fastlogo_uuid);

	ret = tee_open_session(tee_dev, &sess_arg, 0, NULL);
	if (ret || sess_arg.ret) {
		if (!ret)
			ret = -EIO;
		return ret;
	}

	session = sess_arg.session;

	return ret;
}

static int InvokeCommandHelper(VPP_CMD_ID commandID, struct tee_param *param,
			       int nParam)
{
	struct tee_invoke_arg arg;
	int ret;

	memset(&arg, 0, sizeof(arg));
	arg.func = commandID;
	arg.session = session;

	ret = tee_invoke_func(tee_dev, &arg, nParam, param);
	if (ret || arg.ret) {
		if (!ret)
			ret = -ENODEV;
		debug("tee_invoke_func invoke commandID = %d err: 0x%x 0x%x\n",
		      commandID, ret, arg.ret);

		return ret;
	}

	return 0;
}

int VppInit(VPP_INIT_PARM *vpp_init_parm)
{
	struct tee_param param[4];
	int ret;

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INOUT;
	param[0].u.value.a = vpp_init_parm->iHDMIEnable;
	param[0].u.value.b = vpp_init_parm->iVdacEnable;

	param[1].attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param[1].u.value.a = 0xDEADBEEF;

	param[2].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[2].u.value.a = vpp_init_parm->uiShmPA;
	param[2].u.value.b = vpp_init_parm->uiShmSize;

	ret = InvokeCommandHelper(VPP_INIT, param, 3);
	if (ret != 0)
		return -ENODEV;

	if (param[1].u.value.a != 0) {
		debug("VPP_INIT failed\n");
		return -ENODEV;
	}

	return param[1].u.value.a;
}

int VppCreate(void)
{
	struct tee_param param;
	int ret;

	memset(&param, 0, sizeof(param));
	param.attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param.u.value.a = 0xDEADBEEF;

	ret = InvokeCommandHelper(VPP_CREATE, &param, 1);
	if (ret != 0)
		return -ENODEV;

	if (param.u.value.a != 0) {
		debug("VPP_CREATE failed\n");
		return -ENODEV;
	}

	return param.u.value.a;
}

int VppReset(void)
{
	struct tee_param param;
	int ret;

	memset(&param, 0, sizeof(param));
	param.attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param.u.value.a = 0xDEADBEEF;

	ret = InvokeCommandHelper(VPP_RESET, &param, 1);
	if (ret != 0)
		return -ENODEV;

	if (param.u.value.a != 0) {
		debug("VPP_RESET failed\n");
		return -ENODEV;
	}


	return param.u.value.a;
}

int VppConfig(INT handle,
		const INT *pvinport_cfg,
		const INT *pdv_cfg,
		const INT *pzorder_cfg,
		const INT *pvoutport_cfg,
		const INT *pfeature_cfg)
{
	static UINT8 cfg_mem[256];
	int plane_size = sizeof(INT32)* (MAX_NUM_PLANES_ALL);
	int vout_size = sizeof(INT32)* (MAX_NUM_VOUTS);
	int feature_size = sizeof(INT32)* (MAX_NUM_FEATURE_CFG);

	memcpy(&cfg_mem[0], pvinport_cfg, plane_size);
	memcpy(&cfg_mem[plane_size], pdv_cfg, plane_size);
	memcpy(&cfg_mem[(plane_size*2)], pzorder_cfg, plane_size);
	memcpy(&cfg_mem[(plane_size*3)], pvoutport_cfg, vout_size);
	memcpy(&cfg_mem[(plane_size*3)+vout_size], pfeature_cfg, feature_size);

	return VppInvokePassShm_Helper(&cfg_mem[0], VPP_OBJCONFIG, sizeof(cfg_mem));
}

int VppIsrHandler(unsigned int MsgId, unsigned int IntSts)
{
	struct tee_param param[2];
	int ret;

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = MsgId;
	param[0].u.value.b = IntSts;
	param[1].attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param[1].u.value.a = 0xDEADBEEF;

	ret = InvokeCommandHelper(VPP_HANDLEINT, param, 2);
	if (ret != 0)
		return -ENODEV;

	if (param[1].u.value.a != 0) {
		debug("VPP_HANDLEINT failed\n");
		return -ENODEV;
	}

	return param[1].u.value.a;
}

int VppSetOutRes(int CpcbId, int ResId, int BitDepth)
{
	struct tee_param param[3];
	int ret;

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = CpcbId;
	param[0].u.value.b = ResId;
	param[1].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[1].u.value.a = BitDepth;
	param[2].attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param[2].u.value.a = 0xDEADBEEF;

	ret = InvokeCommandHelper(VPP_SETRES, param, 3);
	if (ret != 0)
		return -ENODEV;

	if (param[2].u.value.a != 0) {
		debug("VPP_SETRES failed\n");
		return -ENODEV;
	}

	return param[2].u.value.a;
}

int VppHdmiSetVidFmt(int ColorFmt, int BitDepth, int PixelRep)
{
	struct tee_param param[3];
	int ret;

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = ColorFmt;
	param[0].u.value.b = BitDepth;
	param[1].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[1].u.value.a = PixelRep;
	param[2].attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param[2].u.value.a = 0xDEADBEEF;

	ret = InvokeCommandHelper(VPP_HDMISETVIDFMT, param, 3);
	if (ret != 0)
		return -ENODEV;

	if (param[2].u.value.a != 0) {
		debug("VPP_HDMISETVIDFMT failed\n");
		return -ENODEV;
	}

	return param[2].u.value.a;
}

int VppSetHdmiTxControl(int Enable)
{
	struct tee_param param[2];
	int ret;

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = Enable;
	param[1].attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param[1].u.value.a = 0xDEADBEEF;

	ret = InvokeCommandHelper(VPP_HDMISETTXCTRL, param, 2);
	if (ret != 0)
		return -ENODEV;

	if (param[1].u.value.a != 0) {
		debug("VPP_HDMISETTXCTRL failed\n");
		return -ENODEV;
	}


	return param[1].u.value.a;
}

int VppOpenDispWin(int PlaneId, int WinX, int WinY, int WinW, int WinH,
		   int BgClr, int Alpha, int GlobalAlpha)
{
	struct tee_param param[4];
	int ret;

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = PlaneId;
	param[0].u.value.b = WinX;
	param[1].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[1].u.value.a = WinY;
	param[1].u.value.b = WinW;
	param[2].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[2].u.value.a = WinH;
	param[2].u.value.b = BgClr;
	param[3].attr = TEE_PARAM_ATTR_TYPE_VALUE_INOUT;
	param[3].u.value.a = Alpha;
	param[3].u.value.a |= (GlobalAlpha<<16);
	param[3].u.value.b = 0xdeadbeef;

	ret = InvokeCommandHelper(VPP_OPENDISPWIN, param, 4);
	if (ret != 0)
		return -ENODEV;

	if (param[3].u.value.b != 0) {
		debug("VPP_OPENDISPWIN failed\n");
		return -ENODEV;
	}

	return param[3].u.value.b;
}

int VppSetRefWin(int PlaneId, int WinX, int WinY, int WinW, int WinH)
{
	struct tee_param param[4];
	int ret;

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = PlaneId;
	param[0].u.value.b = WinX;
	param[1].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[1].u.value.a = WinY;
	param[1].u.value.b = WinW;
	param[2].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[2].u.value.a = WinH;
	param[3].attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param[3].u.value.a = 0xdeadbeef;

	ret = InvokeCommandHelper(VPP_SETREFWIN, param, 4);
	if (ret != 0)
		return -ENODEV;

	if (param[3].u.value.a != 0) {
		debug("VPP_SETREFWIN failed\n");
		return -ENODEV;
	}

	return param[3].u.value.a;
}

int VppChangeDispWin(int PlaneId, int WinX, int WinY, int WinW, int WinH,
		     int BgClr, int Alpha, int GlobalAlpha)
{
	struct tee_param param[4];
	int ret;

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = PlaneId;
	param[0].u.value.b = WinX;
	param[1].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[1].u.value.a = WinY;
	param[1].u.value.b = WinW;
	param[2].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[2].u.value.a = WinH;
	param[2].u.value.b = BgClr;
	param[3].attr = TEE_PARAM_ATTR_TYPE_VALUE_INOUT;
	param[3].u.value.a = Alpha;
	param[3].u.value.a |= (GlobalAlpha<<16);
	param[3].u.value.b = 0xDEADBEEF;

	ret = InvokeCommandHelper(VPP_CHANGEDISPWIN, param, 4);
	if (ret != 0)
		return -ENODEV;

	if (param[3].u.value.b != 0) {
		debug("VPP_CHANGEDISPWIN failed\n");
		return -ENODEV;
	}

	return param[3].u.value.b;
}

int VppSetPlaneMute(int planeID, int mute)
{
	struct tee_param param[2];
	int ret;

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = planeID;
	param[0].u.value.a = mute;
	param[1].attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param[1].u.value.a = 0xDEADBEEF;

	ret = InvokeCommandHelper(VPP_SETPLANEMUTE, param, 2);
	if (ret != 0)
		return -ENODEV;

	if (param[1].u.value.a != 0) {
		debug("VPP_SETPLANEMUTE failed\n");
		return -ENODEV;
	}

	return param[1].u.value.a;
}

int VppSetDispMode(int PlaneId, int Mode)
{
	struct tee_param param[2];
	int ret;

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = PlaneId;
	param[0].u.value.b = Mode;
	param[1].attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param[1].u.value.a = 0xDEADBEEF;

	ret = InvokeCommandHelper(VPP_SETDISPMODE, param, 2);
	if (ret != 0)
		return -ENODEV;

	if (param[1].u.value.a != 0) {
		debug("VPP_SETDISPMODE failed\n");
		return -ENODEV;
	}

	return param[1].u.value.a;
}

int VppRecycleFrame(int PlaneId)
{
	struct tee_param param[2];
	int ret;

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = PlaneId;
	param[1].attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param[1].u.value.a = 0xDEADBEEF;

	ret = InvokeCommandHelper(VPP_RECYCLEFRAME, param, 2);
	if (ret != 0)
		return -ENODEV;

	if (param[1].u.value.a != 0) {
		debug("VPP_RECYCLEFRAME failed\n");
		return -ENODEV;
	}

	return param[1].u.value.a;
}

int Vppstop(void)
{
	struct tee_param param;
	int ret;

	memset(&param, 0, sizeof(param));
	param.attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param.u.value.a = 0xDEADBEEF;

	ret = InvokeCommandHelper(VPP_STOP, &param, 1);
	if (ret != 0)
		return -ENODEV;

	if (param.u.value.a != 0) {
		debug("VPP_STOP failed\n");
		return -ENODEV;
	}

	return param.u.value.a;
}

int VppDestroy(void)
{
	struct tee_param param;
	int ret;

	memset(&param, 0, sizeof(param));
	param.attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param.u.value.a = 0xDEADBEEF;

	ret = InvokeCommandHelper(VPP_DESTROY, &param, 1);
	if (ret != 0)
		return -ENODEV;

	if (param.u.value.a != 0) {
		debug("VPP_DESTROY failed\n");
		return -ENODEV;
	}

	return param.u.value.a;
}

int VppPassVbufInfo(unsigned int *Vbuf, unsigned int VbufSize,
		unsigned int *Clut, unsigned int ClutSize,
		int PlaneID, int ClutValid, VPP_SHM_ID ShmID)
{
	struct tee_param param[4];
	struct tee_shm *VbufShm;
	int ret, rc;

	rc = tee_shm_register(tee_dev, Vbuf, VbufSize, 0, &VbufShm);
	if (rc) {
		debug("Shm register failed\n");
		return -ENODEV;
	}

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = ShmID;

	param[1].attr = TEE_PARAM_ATTR_TYPE_MEMREF_INPUT;
	param[1].u.memref.shm = VbufShm;
	param[1].u.memref.size = VbufSize;

	param[2].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[2].u.value.a = 0;

	param[3].attr = TEE_PARAM_ATTR_TYPE_VALUE_INOUT;
	param[3].u.value.a = PlaneID;
	param[3].u.value.b = 0xdeadbeef;

	ret = InvokeCommandHelper(VPP_PASSSHM, param, 4);
	if (ret != 0)
		return -ENODEV;

	if (param[3].u.value.b != 0) {
		debug("VPP_PASSSHM failed\n");
		return -ENODEV;
	}

	return param[3].u.value.b;
}

int VppPassVbufInfoPar(unsigned int *Vbuf, unsigned int VbufSize,
		       unsigned int *Clut, unsigned int ClutSize,
		       int PlaneID, int ClutValid, VPP_SHM_ID ShmID)
{
	VBUF_INFO *pVBufInfo = (VBUF_INFO*) Vbuf;
	struct tee_param param[4];
	int i, flag;
	int ret;

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INOUT;
	param[1].attr = TEE_PARAM_ATTR_TYPE_VALUE_INOUT;
	param[2].attr = TEE_PARAM_ATTR_TYPE_VALUE_INOUT;
	param[3].attr = TEE_PARAM_ATTR_TYPE_VALUE_INOUT;

	for (i = 0; i < 5; i++) {
		flag = 0;
		switch(i) {
		case 0:
			param[1].u.value.a = (unsigned int)((intptr_t)pVBufInfo->m_pbuf_start);;
			param[1].u.value.b = pVBufInfo->m_bytes_per_pixel;
			param[2].u.value.a = pVBufInfo->m_bits_per_pixel;
			param[2].u.value.b = pVBufInfo->m_srcfmt;
			param[3].u.value.a = pVBufInfo->m_order;
			flag = 1;
			break;
		case 1:
			param[1].u.value.a = pVBufInfo->m_content_width;
			param[1].u.value.b = pVBufInfo->m_content_height;
			param[2].u.value.a = pVBufInfo->m_buf_stride;
			param[2].u.value.b = pVBufInfo->m_buf_pbuf_start_UV;
			param[3].u.value.a = pVBufInfo->m_buf_size;
			flag = 1;
			break;
		case 2:
			param[1].u.value.a = pVBufInfo->m_allocate_type;
			param[1].u.value.b = pVBufInfo->m_buf_type;
			param[2].u.value.a = pVBufInfo->m_buf_use_state;
			param[2].u.value.b = pVBufInfo->m_flags;
			param[3].u.value.a = pVBufInfo->m_is_frame_seq;
			flag = 1;
			break;
		case 3:
			param[1].u.value.a = pVBufInfo->m_frame_rate_num;
			param[1].u.value.b = pVBufInfo->m_frame_rate_den;
			param[2].u.value.a = pVBufInfo->m_active_width;
			param[2].u.value.b = pVBufInfo->m_active_height;
			param[3].u.value.a = pVBufInfo->m_active_left;
			flag = 1;
			break;
		case 4:
			param[1].u.value.a = pVBufInfo->m_active_top;
			param[1].u.value.b = pVBufInfo->m_content_offset;
			param[2].u.value.a = pVBufInfo->m_is_progressive_pic;
			param[2].u.value.b = pVBufInfo->m_hDesc;
			flag = 1;
			break;
		}

		if (flag) {
			param[0].u.value.a = (ShmID | (PlaneID<<8));
			param[0].u.value.b = i;
			param[3].u.value.b = 0xdeadbeef;
			ret = InvokeCommandHelper(VPP_PASSPAR, param, 4);
			if (ret != 0)
				return -ENODEV;

			if (param[3].u.value.b != 0) {
				debug("VPP_PASSPAR failed\n");
				return -ENODEV;
			}
		}
	}

	return ret;
}

INT VppSetFormat(INT handle, INT cpcbID, VPP_DISP_OUT_PARAMS *pDispParams)
{
	UINT32 aDispParamsData[VPP_SETFORMAT_SIZE];
	struct tee_param param[3];
	struct tee_shm *VbufShm;
	int ret;

	memcpy(&aDispParamsData[0], &cpcbID, sizeof(INT));
	memcpy(&aDispParamsData[1], pDispParams, sizeof(VPP_DISP_OUT_PARAMS));

	ret = tee_shm_register(tee_dev, (void*)&aDispParamsData,
			       VPP_SETFORMAT_SIZE, 0, &VbufShm);
	if (ret) {
		debug("Shm register failed\n");
		return -ENODEV;
	}

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = VPP_SETFORMAT;

	param[1].attr = TEE_PARAM_ATTR_TYPE_MEMREF_INPUT;
	param[1].u.memref.shm = VbufShm;
	param[1].u.memref.size = VPP_SETFORMAT_SIZE;

	param[2].attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param[2].u.value.a = 0xdeadbeef;

	ret = InvokeCommandHelper(VPP_PASSSHM, param, 3);
	if (ret != 0)
		return -ENODEV;

	if (param[2].u.value.a != 0) {
		debug("VPP_PASSSHM failed\n");
		return -ENODEV;
	}

	return param[2].u.value.a;
}

int VppPassShm(unsigned int *VirtAddr, VPP_SHM_ID AddrId, unsigned int Size)
{
	struct tee_invoke_arg arg;
	struct tee_param param[4];
	struct tee_shm *VbufShm;
	int ret;

	memset(&arg, 0, sizeof(arg));
	arg.func = VPP_PASSSHM;
	arg.session = session;

	ret = tee_shm_register(tee_dev, (void*)VirtAddr, Size, 0, &VbufShm);
	if (ret) {
		printf("Shm register failed\n");
		return ret;
	}

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = AddrId;

	param[1].attr = TEE_PARAM_ATTR_TYPE_MEMREF_INPUT;
	param[1].u.memref.shm = VbufShm;
	param[1].u.memref.size = Size;

	param[2].attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param[2].u.value.a = 0xdeadbeef;

	ret = tee_invoke_func(tee_dev, &arg, 3, param);
	if (ret || arg.ret) {
		if (!ret)
			ret = -EPROTO;
		printf("tee_invoke_func invoke err: 0x%x 0x%x\n", ret, arg.ret);
		return ret;
	}

	return param[2].u.value.a;
}

int VppInvokePassShm_Helper(void *pBuffer, VPP_SHM_ID shmCmdId, UINT32 sBufferSize)
{
	struct tee_invoke_arg arg;
	struct tee_param param[4];
	struct tee_shm *VbufShm;
	int ret;

	memset(&arg, 0, sizeof(arg));
	arg.func = VPP_PASSSHM;
	arg.session = session;

	ret = tee_shm_register(tee_dev, (void*)pBuffer, sBufferSize, 0, &VbufShm);
	if (ret) {
		printf("Shm register failed\n");
		return ret;
	}

	memset(param, 0, sizeof(param));
	param[0].attr = TEE_PARAM_ATTR_TYPE_VALUE_INPUT;
	param[0].u.value.a = shmCmdId;

	param[1].attr = TEE_PARAM_ATTR_TYPE_MEMREF_INPUT;
	param[1].u.memref.shm = VbufShm;
	param[1].u.memref.size = sBufferSize;

	param[2].attr = TEE_PARAM_ATTR_TYPE_VALUE_OUTPUT;
	param[2].u.value.a = 0xdeadbeef;

	ret = tee_invoke_func(tee_dev, &arg, 3, param);
	if (ret || arg.ret) {
		if (!ret)
			ret = -EPROTO;
		printf("tee_invoke_func invoke err: 0x%x 0x%x\n", ret, arg.ret);
		return ret;
	}

	return param[2].u.value.a;
}
