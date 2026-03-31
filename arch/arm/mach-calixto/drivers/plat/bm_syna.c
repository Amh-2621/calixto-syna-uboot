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

u64 call_bm_process(u64 func_id, u64 arg1, u64 arg2,
		    u64 arg3, u64 arg4, u64 arg5, u64 arg6)
{
	register u64 l_x0 asm("x0") = func_id;
	l_x0 = l_x0;
	register u64 l_x1 asm("x1") = arg1;
	l_x1 = l_x1;
	register u64 l_x2 asm("x2") = arg2;
	l_x2 = l_x2;
	register u64 l_x3 asm("x3") = arg3;
	l_x3 = l_x3;
	register u64 l_x4 asm("x4") = arg4;
	l_x4 = l_x4;
	register u64 l_x5 asm("x5") = arg5;
	l_x5 = l_x5;
	register u64 l_x6 asm("x6") = arg6;
	l_x6 = l_x6;

	asm volatile ("smc #0\n");
	register u64 ret asm("x0");
	return ret;
}
