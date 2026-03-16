// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (c) 2024, Linaro Limited
 */

#include <common.h>
#include "tee.h"
#include "teec_ta_load.h"

__weak int teeci_loadsecuremodule(const struct tee_optee_ta_uuid *destination, void *ta,
			   size_t *ta_size)
{
	int res = TA_BINARY_NOT_FOUND;

	debug("Default function isn't available\n");

	return res;
}