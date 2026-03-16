// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2018, Linaro Limited
 */

#include <common.h>
#include <log.h>
#include <tee.h>
#include <linux/types.h>

#include "optee_msg.h"
#include "optee_msg_supplicant.h"
#include "optee_private.h"
#include "optee_smc.h"
#include "teec_ta_load.h"

static int get_value(size_t num_params, struct optee_msg_param *params,
		     const uint32_t idx, struct tee_param_value **value)
{
	if (idx >= num_params)
		return -1;

	switch (params[idx].attr & OPTEE_MSG_ATTR_TYPE_MASK) {
	case OPTEE_MSG_ATTR_TYPE_VALUE_INPUT:
	case OPTEE_MSG_ATTR_TYPE_VALUE_OUTPUT:
	case OPTEE_MSG_ATTR_TYPE_VALUE_INOUT:
		*value = (void *)&params[idx].u.value.a;
		return 0;
	default:
		return -1;
	}
}

/* Get parameter allocated by secure world */
static int get_param(struct udevice *dev, size_t num_params, struct optee_msg_param *params,
		     const uint32_t idx, struct tee_shm *shm)
{
	size_t sz = 0;
	struct tee_shm *tshm = NULL;

	if (idx >= num_params)
		return -1;

	switch (params[idx].attr & OPTEE_MSG_ATTR_TYPE_MASK) {
	case OPTEE_MSG_ATTR_TYPE_RMEM_INPUT:
	case OPTEE_MSG_ATTR_TYPE_RMEM_OUTPUT:
	case OPTEE_MSG_ATTR_TYPE_RMEM_INOUT:
	case OPTEE_MSG_ATTR_TYPE_TMEM_INPUT:
	case OPTEE_MSG_ATTR_TYPE_TMEM_OUTPUT:
	case OPTEE_MSG_ATTR_TYPE_TMEM_INOUT:
		break;
	default:
		return -1;
	}

	memset(shm, 0, sizeof(*shm));

	tshm = (struct tee_shm *)(params[idx].u.rmem.shm_ref);

	if (!tee_shm_is_registered(tshm, dev)) {
		/*
		 * It doesn't make sense to query required size of an
		 * input buffer.
		 */
		if ((params[idx].attr & OPTEE_MSG_ATTR_TYPE_MASK) == OPTEE_MSG_ATTR_TYPE_RMEM_INPUT) {
			return -1;
		}


		/*
		 * Buffer isn't found, the caller is querying required size
		 * of the buffer.
		 */
		return 0;
	}

	sz = params[idx].u.tmem.size;

	shm->size = sz;
	shm->addr = tshm->addr + params[idx].u.rmem.offs;

	return 0;
}

static void cmd_load_ta(struct udevice *dev, struct optee_msg_arg *arg)
{
	int ta_found = 0;
	size_t size = 0;
	struct tee_param_value *val_cmd = NULL;
	struct tee_optee_ta_uuid uuid;
	struct tee_shm shm_ta;

	memset(&uuid, 0, sizeof(uuid));

	if (arg->num_params != 2 || get_value(arg->num_params, arg->params, 0, &val_cmd) ||
		get_param(dev, arg->num_params, arg->params, 1, &shm_ta)) {
		arg->ret = TEE_ERROR_BAD_PARAMETERS;
		return;
	}

	tee_optee_ta_uuid_from_octets(&uuid, (void *)val_cmd);

	size = shm_ta.size;

	ta_found = teeci_loadsecuremodule(&uuid, shm_ta.addr, &size);
	if (ta_found != TA_BINARY_FOUND) {
		printf("TA not found\n");
		arg->ret =  TEE_ERROR_ITEM_NOT_FOUND;
		return;
	}

	arg->params[1].u.rmem.size = size;

	/*
	 * If a buffer wasn't provided, just tell which size it should be.
	 * If it was provided but isn't big enough, report an error.
	 */
	if (shm_ta.addr && size > shm_ta.size) {
		arg->ret = TEE_ERROR_BAD_PARAMETERS;
		return;
	}

	arg->ret = TEE_SUCCESS;
}

static void cmd_shm_alloc(struct udevice *dev, struct optee_msg_arg *arg,
			  void **page_list)
{
	int rc;
	struct tee_shm *shm;
	void *pl;
	u64 ph_ptr;

	arg->ret_origin = TEE_ORIGIN_COMMS;

	if (arg->num_params != 1 ||
	    arg->params[0].attr != OPTEE_MSG_ATTR_TYPE_VALUE_INPUT) {
		arg->ret = TEE_ERROR_BAD_PARAMETERS;
		return;
	}

	rc = __tee_shm_add(dev, 0, NULL, arg->params[0].u.value.b,
			   TEE_SHM_REGISTER | TEE_SHM_ALLOC, &shm);
	if (rc) {
		if (rc == -ENOMEM)
			arg->ret = TEE_ERROR_OUT_OF_MEMORY;
		else
			arg->ret = TEE_ERROR_GENERIC;
		return;
	}

	pl = optee_alloc_and_init_page_list(shm->addr, shm->size, &ph_ptr);
	if (!pl) {
		arg->ret = TEE_ERROR_OUT_OF_MEMORY;
		tee_shm_free(shm);
		return;
	}

	*page_list = pl;
	arg->params[0].attr = OPTEE_MSG_ATTR_TYPE_TMEM_OUTPUT |
			      OPTEE_MSG_ATTR_NONCONTIG;
	arg->params[0].u.tmem.buf_ptr = ph_ptr;
	arg->params[0].u.tmem.size = shm->size;
	arg->params[0].u.tmem.shm_ref = (ulong)shm;
	arg->ret = TEE_SUCCESS;
}

static void cmd_shm_free(struct optee_msg_arg *arg)
{
	arg->ret_origin = TEE_ORIGIN_COMMS;

	if (arg->num_params != 1 ||
	    arg->params[0].attr != OPTEE_MSG_ATTR_TYPE_VALUE_INPUT) {
		arg->ret = TEE_ERROR_BAD_PARAMETERS;
		return;
	}

	tee_shm_free((struct tee_shm *)(ulong)arg->params[0].u.value.b);
	arg->ret = TEE_SUCCESS;
}

void optee_suppl_cmd(struct udevice *dev, struct tee_shm *shm_arg,
		     void **page_list)
{
	struct optee_msg_arg *arg = shm_arg->addr;

	switch (arg->cmd) {
	case OPTEE_MSG_RPC_CMD_LOAD_TA:
		cmd_load_ta(dev, arg);
		break;
	case OPTEE_MSG_RPC_CMD_SHM_ALLOC:
		cmd_shm_alloc(dev, arg, page_list);
		break;
	case OPTEE_MSG_RPC_CMD_SHM_FREE:
		cmd_shm_free(arg);
		break;
	case OPTEE_MSG_RPC_CMD_FS:
		debug("REE FS storage isn't available\n");
		arg->ret = TEE_ERROR_STORAGE_NOT_AVAILABLE;
		break;
	case OPTEE_MSG_RPC_CMD_RPMB:
		optee_suppl_cmd_rpmb(dev, arg);
		break;
	default:
		arg->ret = TEE_ERROR_NOT_IMPLEMENTED;
	}

	arg->ret_origin = TEE_ORIGIN_COMMS;
}
