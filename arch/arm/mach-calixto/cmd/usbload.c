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
#include <command.h>
#include "bm_generic.h"
#ifdef CONFIG_SYNA_SUBOOT
#include <linux/arm-smccc.h>

#define SYNA_SIP_SMC64_USBLOAD_CONFIG 0xC2000009
#endif

static int do_bcm_disable_usb(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int cmdid = BM_CMD_TURN_OFF_USB_DEVICE;
	u32 ret = call_bm_process(BM_STDCALL(cmdid), 0, 0, 0, 0, 0, 0);
	return ret;
}

static u32 request_img_from_usbs_by_name(char *image_name, u32 uboot_img_load_addr)
{
	u32 arg0, arg1, arg2, arg3;
#ifdef CONFIG_SYNA_SUBOOT
	struct arm_smccc_res res;
#else
	u32 ret;
#endif

	arg0 = 0xff;
	arg1 = uboot_img_load_addr;
	arg2 = (u32)(u64)&image_name[0];
	arg3 = strlen(image_name) + 1;
	debug("load usbs image: arg0=0x%x, arg1=0x%x, arg2=0x%x, arg3=0x%x\n",
	      arg0, arg1, arg2, arg3);

#ifdef CONFIG_SYNA_SUBOOT
	arm_smccc_smc(SYNA_SIP_SMC64_USBLOAD_CONFIG, arg0, arg1, arg2, arg3, 0, 0, 0, &res);
	return 0;
#else
	ret = call_bm_process(BM_STDCALL(BM_CMD_LOAD_USB_IMAGE), arg0, arg1, arg2, arg3, 0, 0);
	return ret;
#endif
}

static int do_usbload(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 load_addr, ret;
	u8 buff[1024];
	char image_name[256] = "07_IMAGE";
	u64 buff_addr = 0;
	#define BM_LOAD_RERTY_INITIAL	3
	u32 retry_bm = BM_LOAD_RERTY_INITIAL;
	u32 img_size;

	if (argc < 3)
		return -1;

	if (strlen(argv[1]) > 255) {
		printf("%s, file name %s is too long.\n", __func__, argv[1]);
		return -1;
	}
	load_addr = simple_strtoull(argv[2], NULL, 16);
	flush_dcache_all();
	printf("%s, loading image %s to addr %x.\n", __func__, argv[1], load_addr);
	ret = request_img_from_usbs_by_name(argv[1], load_addr);
	if (ret != 0) {
		printf("can not load image from usb.\n");
		return ret;
	}

	ret = request_img_from_usbs_by_name(image_name, (u32)(u64)buff);
	if (ret != 0) {
		printf("can not get image size from usb.\n");
		return ret;
	}

	invalidate_dcache_range((unsigned long)buff, (unsigned long)buff + sizeof(u32));
	buff_addr = (u64)buff;
	img_size = *(u32 *)buff_addr;
	while (!img_size && retry_bm) {
		mdelay(1);
		ret = request_img_from_usbs_by_name(image_name, (u32)(u64)buff);
		if (ret != 0) {
			printf("can not get image size from usb.\n");
			return ret;
		}
		buff_addr = (u64)buff;
		img_size = *(u32 *)buff_addr;

		retry_bm--;
	}
	printf("usbload done, get size %d by retry %d.\n", img_size, (BM_LOAD_RERTY_INITIAL - retry_bm));

	/* set the parameters to env */
	env_set_hex("fileaddr", load_addr);
	env_set_hex("filesize", img_size);

	return 0;
}

static char usbload_help[] =
	"Download image from host over USB connection.";

static char usbload_usage[] =
	"\nexamples:\n"
	"    usbload uNAND_full.img 0x7000000 to load image $(IMG_DIR_IN_HOST)/uNAND_full.img to addr 0x7000000\n"
	;

U_BOOT_CMD(usbload, 3, 0, do_usbload, usbload_help, usbload_usage);

U_BOOT_CMD(
	bcmusboff, 1, 0, do_bcm_disable_usb,
	"bcm disable usb device",
	"- bcm disable usb device"
);
