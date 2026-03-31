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
#include <stdarg.h>
#include "smc.h"
#include "mem_init.h"
#include "tee_client.h"

#define TEEC_PARAM_TYPES(t0, t1, t2, t3)	\
	((t0) | ((t1) << 4) | ((t2) << 8) | ((t3) << 12))
#define TEEC_PARAM_TYPE_GET(t, i)	(((t) >> ((i) * 4)) & 0xF)

static u32 TEEC_CallParamToComm(union tee_param *commParam,
				TEEC_Parameter *param, u32 paramType)
{
	u32 t = paramType & 0x7;	/* covented paramType for communication */

	switch (paramType) {
	case TEEC_VALUE_INPUT:
	case TEEC_VALUE_OUTPUT:
	case TEEC_VALUE_INOUT:
		commParam->value.a = param->value.a;
		commParam->value.b = param->value.b;
		break;
	case TEEC_MEMREF_WHOLE:
		t = TEE_PARAM_TYPE_MEMREF_INOUT;
		commParam->memref.buffer = (u32)((unsigned long)
				param->memref.parent->phyAddr);
		commParam->memref.size   = param->memref.parent->size;
		break;
	case TEEC_MEMREF_PARTIAL_INPUT:
	case TEEC_MEMREF_PARTIAL_OUTPUT:
	case TEEC_MEMREF_PARTIAL_INOUT:
		commParam->memref.buffer = (u32)((unsigned long)
				(param->memref.parent->phyAddr +
				param->memref.offset));
		commParam->memref.size   = param->memref.size;
		break;
	}

	return t;
}

TEEC_Result tee_register_ta(void *pta, size_t size)
{
	TEEC_Result result = 1;
	union tz_smc_return ret;
	int i = 0;
	u32 status = 1;

	TEEC_Operation operation = {0};
	TEEC_SharedMemory tmp;
	struct tee_comm_param *cmd;
	struct tee_comm *comm = NULL;
	int t[4];
	u32 param;

	/* init tee memory */
	comm = (struct tee_comm *)(uintptr_t)malloc_ion_noncacheable(sizeof(struct tee_comm));

	if (!comm) {
		printf("register_ta: no enough memory! %ld\n", sizeof(struct tee_comm));
		goto done;
	}

	comm->pa = (u32)((unsigned long)comm);
	comm->va = (u32)((unsigned long)comm);

	tmp.buffer = pta;
	tmp.phyAddr = pta;
	tmp.size = size;
	tmp.flags = TEEC_MEM_INPUT | TEEC_MEM_OUTPUT;
	tmp.allocated = true;
	tmp.operationCount = 0;

	operation.paramTypes = TEEC_PARAM_TYPES(
			TEEC_MEMREF_PARTIAL_INPUT,
			TEEC_VALUE_INPUT,
			TEEC_NONE,
			TEEC_NONE);

	operation.params[0].memref.parent = &tmp;
	operation.params[0].memref.size = size;
	operation.params[0].memref.offset = 0;
	operation.params[1].value.a = 4;

	cmd = &comm->call_param;
	/* pack the command */
	memset(cmd, 0, TEE_COMM_PARAM_BASIC_SIZE);

	cmd->cmd_id = TAMGR_CMD_REGISTER;

	for (i = 0; i < 4; i++) {
		int paramType = TEEC_PARAM_TYPE_GET(operation.paramTypes, i);

		t[i] = TEEC_CallParamToComm(&cmd->params[i],
					    &operation.params[i], paramType);
	}

	cmd->param_types = TEEC_PARAM_TYPES(t[0], t[1], t[2], t[3]);

	param = (u32)((unsigned long)comm->pa) + offsetof(struct tee_comm, call_param);

	flush_dcache_all();
	invalidate_dcache_all();
	do {
		status = __smc_tee(TZ_CMD_TEE_SYS, TZ_TASK_ID_MGR, param, 0, (unsigned long *)&ret);
	} while (status != TZ_COMM_RSP_DONE);

	if ((status & TZ_COMM_RSP_DONE) && !ret.res.result) {
		result = TEEC_SUCCESS;
	} else {
		result = TEEC_ERROR_GENERIC;
		printf("register_ta:tz comm rsp error! %x, %lx\n", status, ret.res.result);
	}

done:
	if (comm)
		free_ion_noncacheable(comm);

	return result;
}

/* the first parameter is the number of other parameters */
unsigned long tee_verify_image(int num, ...)
{
	unsigned long param[6], result[4];
	int i = 0, argnum = 0;
	va_list params;

	argnum = (num > 6) ? 6 : num;

	va_start(params, num);
	for (i = 0; i < argnum; i++)
		param[i] = va_arg(params, unsigned long);

	va_end(params);

	__smc6(SMC_FUNC_TOS_CRYPTO_VERIFY_IMAGE, param, result);

	if (result[0] == 0)
		return result[1];
	else
		return result[0];
}

unsigned long tee_enter_boot_stage(int stage, int mode)
{
	return __smc(SMC_FUNC_TOS_BOOT_STAGE, stage, mode, 0);
}

unsigned long tee_get_mem_region_list(void *region, unsigned long max_num,
				      unsigned long attr_mask, unsigned long attr_val)
{
	unsigned long param[6];

	param[0] = (unsigned long)region;
	param[1] = max_num;
	param[2] = attr_mask;
	param[3] = attr_val;
	return __smc6(SMC_FUNC_TOS_MEM_REGION_LIST, param, 0);
}

