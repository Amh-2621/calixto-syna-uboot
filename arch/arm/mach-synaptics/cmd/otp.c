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
#include <command.h>
#include <linux/arm-smccc.h>

#define SYNA_SIP_SMC64_OTP_PROGRAM 0xC2000008

static int do_otp(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	u32 data_addr, data_size;
	struct arm_smccc_res res;

	if (argc < 4)
		return -1;

	data_addr = simple_strtoull(argv[2], NULL, 16);
	data_size = simple_strtoull(argv[3], NULL, 16);

	flush_dcache_all();

	debug("program otp data at 0x%x, size=0x%x\n", data_addr, data_size);

	arm_smccc_smc(SYNA_SIP_SMC64_OTP_PROGRAM, data_addr, data_size, 0, 0, 0, 0, 0, &res);

	printf("otp operation %s\n", res.a0 == 0 ? "succeed" : "failed");

	if (res.a0 != 0) {
		printf("ret = 0x%x\n", res.a0);
	}

	return res.a0 == 0 ? CMD_RET_SUCCESS : CMD_RET_FAILURE;
}

static char otp_help[] =
	"Program OTP data from memory.";

static char otp_usage[] =
	"\nexamples:\n"
	"    otp write 0x7000000 0x500 to program OTP data(size 0x500) at addr 0x7000000\n"
	;

U_BOOT_CMD(otp, 4, 0, do_otp, otp_help, otp_usage);

