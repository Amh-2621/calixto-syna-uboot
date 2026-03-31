/* SPDX-License-Identifier: GPL-2.0+ */
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

#ifndef _TEE_COMM_H_
#define _TEE_COMM_H_

enum {
	TEE_SUCCESS			= 0x00000000,	/* TEEC_SUCCESS		*/
	TEE_ERROR_CORRUPT_OBJECT		= 0xF0100001,
	TEE_ERROR_CORRUPT_OBJECT_2		= 0xF0100002,
	TEE_ERROR_STORAGE_NOT_AVAILABLE	= 0xF0100003,
	TEE_ERROR_STORAGE_NOT_AVAILABLE_2	= 0xF0100004,
	TEE_ERROR_GENERIC			= 0xFFFF0000,	/* TEEC_ERROR_GENERIC		*/
	TEE_ERROR_ACCESS_DENIED		= 0xFFFF0001,	/* TEEC_ERROR_ACCESS_DENIED */
	TEE_ERROR_CANCEL			= 0xFFFF0002,	/* TEEC_ERROR_CANCEL		*/
	TEE_ERROR_ACCESS_CONFLICT		= 0xFFFF0003,	/* TEEC_ERROR_ACCESS_CONFLICT	*/
	TEE_ERROR_EXCESS_DATA			= 0xFFFF0004,	/* TEEC_ERROR_EXCESS_DATA	*/
	TEE_ERROR_BAD_FORMAT			= 0xFFFF0005,	/* TEEC_ERROR_BAD_FORMAT	*/
	TEE_ERROR_BAD_PARAMETERS		= 0xFFFF0006,	/* TEEC_ERROR_BAD_PARAMETERS	*/
	TEE_ERROR_BAD_STATE		= 0xFFFF0007,	/* TEEC_ERROR_BAD_STATE	*/
	TEE_ERROR_ITEM_NOT_FOUND		= 0xFFFF0008,	/* TEEC_ERROR_ITEM_NOT_FOUND	*/
	TEE_ERROR_NOT_IMPLEMENTED		= 0xFFFF0009,	/* TEEC_ERROR_NOT_IMPLEMENTED	*/
	TEE_ERROR_NOT_SUPPORTED		= 0xFFFF000A,	/* TEEC_ERROR_NOT_SUPPORTED */
	TEE_ERROR_NO_DATA			= 0xFFFF000B,	/* TEEC_ERROR_NO_DATA		*/
	TEE_ERROR_OUT_OF_MEMORY		= 0xFFFF000C,	/* TEEC_ERROR_OUT_OF_MEMORY */
	TEE_ERROR_BUSY				= 0xFFFF000D,	/* TEEC_ERROR_BUSY		*/
	TEE_ERROR_COMMUNICATION		= 0xFFFF000E,	/* TEEC_ERROR_COMMUNICATION */
	TEE_ERROR_SECURITY			= 0xFFFF000F,	/* TEEC_ERROR_SECURITY		*/
	TEE_ERROR_SHORT_BUFFER			= 0xFFFF0010,	/* TEEC_ERROR_SHORT_BUFFER	*/
	TEE_ERROR_EXTERNAL_CANCEL		= 0xFFFF0011,	/* TEEC_ERROR_EXTERNAL_CANCEL	*/
	TEE_ERROR_TIMEOUT			= 0xFFFF3001,
	TEE_ERROR_OVERFLOW			= 0xFFFF300F,
	TEE_ERROR_TARGET_DEAD			= 0xFFFF3024,	/* TEEC_ERROR_TARGET_DEAD	*/
	TEE_ERROR_STORAGE_NO_SPACE		= 0xFFFF3041,
	TEE_ERROR_MAC_INVALID			= 0xFFFF3071,
	TEE_ERROR_SIGNATURE_INVALID	= 0xFFFF3072,
	TEE_ERROR_TIME_NOT_SET			= 0xFFFF5000,
	TEE_ERROR_TIME_NEEDS_RESET		= 0xFFFF5001,
};

typedef u32 TEE_Result;

/** Universally Unique IDentifier (UUID) type as defined in [RFC4122].A
 *
 * UUID is the mechanism by which a service (Trusted Application) is
 * identified.
 * It's same as TEEC_UUID.
 */
typedef struct {
	u32		timeLow;
	u16		timeMid;
	u16		timeHiAndVersion;
	u8		clockSeqAndNode[8];
} TEE_UUID;

/* FIXME: to support 32-bit user-land APP and
 * 32-bit EL1 TZ kernel, change void * to u32,
 * change size_t to u32. needs to refine later
 * if to support 64-bit EL1 TZ kernel and 64-bit
 * user-land app.
 */
typedef union TEE_Param {
	struct {
		u32	buffer;
		u32	size;
	} memref;
	struct {
		u32	a;
		u32	b;
	} value;
} TEE_Param;

enum {
	TEE_PARAM_TYPE_NONE	= 0,
	TEE_PARAM_TYPE_VALUE_INPUT	= 1,
	TEE_PARAM_TYPE_VALUE_OUTPUT = 2,
	TEE_PARAM_TYPE_VALUE_INOUT	= 3,
	TEE_PARAM_TYPE_MEMREF_INPUT = 5,
	TEE_PARAM_TYPE_MEMREF_OUTPUT	= 6,
	TEE_PARAM_TYPE_MEMREF_INOUT = 7,
};

#define tee_param	TEE_Param

#define TEE_COMM_CHANNEL_SIZE		(2048)
#define TEE_COMM_HEADER_SIZE		(32)
#define TEE_COMM_PARAM_SIZE		\
	((TEE_COMM_CHANNEL_SIZE - TEE_COMM_HEADER_SIZE) / 2)
/* the basic parameter doesn't include the param_ext */
#define TEE_COMM_PARAM_BASIC_SIZE	(52)
#define TEE_COMM_PARAM_EXT_SIZE		\
	(TEE_COMM_PARAM_SIZE - TEE_COMM_PARAM_BASIC_SIZE)

struct tee_comm_param {
	u32 session_id;
	u32 cmd_id;
	u32 flags;
	u32 param_types;
	union tee_param params[4];
	u32 param_ext_size;
	u8 param_ext[TEE_COMM_PARAM_EXT_SIZE];
};

struct tee_comm {
	u32	used;
	/* FIXME: to support 32-bit user-land APP and
	 * 32-bit EL1 TZ kernel, change void * to u32,
	 * needs to refine later if to support 64-bit EL1
	 * TZ kernel and 64-bit user-land app.
	 */
	u32	pa;
	u32	va;
	u8		reserved[TEE_COMM_HEADER_SIZE -
				3 * sizeof(u32)];
	struct tee_comm_param	call_param;
	struct tee_comm_param	callback_param;
};

#define TZ_TASK_ID_MGR			(4)
#define TZ_CMD_SYS			(0x00008000)
#define TZ_CMD_TEE			TOS_STDCALL(16)
#define TZ_CMD_TEE_SYS			(TZ_CMD_SYS | TZ_CMD_TEE)

struct tz_cmd {
	unsigned long task_id;	/* for client: it's callee; for server, it's caller */
	unsigned long cmd_id;
	unsigned long param;
};

struct tz_cmd_result {
	unsigned long cmd_id;
	unsigned long result;
	unsigned long origin;
};

union tz_smc_return {
	struct tz_cmd		cb;
	struct tz_cmd_result	res;
};

enum tz_comm_rsp_flags {
	TZ_COMM_RSP_NONE		= 0x00000000,
	TZ_COMM_RSP_DONE		= 0x80000000,
	TZ_COMM_RSP_BUSY		= 0x40000000,
	TZ_COMM_RSP_IRQ_TRAP		= 0x20000000,
	TZ_COMM_RSP_CALLBACK		= 0x10000000,
	TZ_COMM_RSP_LOOPBACK		= 0x08000000,
	TZ_COMM_RSP_MAX
};

#endif /* _TEE_COMM_H_ */
