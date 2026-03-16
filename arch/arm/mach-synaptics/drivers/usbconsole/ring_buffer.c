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
#include "linux/types.h"
#include "ring_buf.h"

#define CODE4(c0_, c1_, c2_, c3_) (((c3_) & 0xff) |		\
				(((c2_) & 0xff) << 8) |	\
				(((c1_) & 0xff) << 16) |	\
				(((c0_) & 0xff) << 24))
#define _RING_BUFFER_MAGIC CODE4('R', 'I', 'N', 'G')
#define _MIN_BUFFER_SIZE (512)

typedef struct {
	uint32_t magic;
	volatile uint32_t cur_rd;
	volatile uint32_t cur_wr;
	uint32_t flags;
	uint32_t buffer_end;
	uint32_t rsv[3];
} ring_buffer_head_t;

typedef struct _ring_buffer_t {
	ring_buffer_head_t header;
	uint8_t data[0];
} ring_buffer_t;

rb_handle ring_buffer_attach(uint32_t base_address, uint32_t size)
{
	ring_buffer_t *instance = (ring_buffer_t *)(uint64_t)base_address;

	if (base_address == 0 ||
	    size <= sizeof(ring_buffer_head_t) + _MIN_BUFFER_SIZE)
		return NULL;

	if (instance->header.magic != _RING_BUFFER_MAGIC) {
		memset(instance, 0, sizeof(ring_buffer_head_t));

		instance->header.buffer_end = size - 1
				- sizeof(ring_buffer_head_t);
		instance->header.magic = _RING_BUFFER_MAGIC;
	} else {
		if (instance->header.buffer_end != size - 1
		    - sizeof(ring_buffer_head_t))
			return NULL;
	}

	return instance;
}

int32_t ring_buffer_push(rb_handle handle, uint8_t *buffer, uint32_t size)
{
	ring_buffer_t *instance = (ring_buffer_t *)handle;
	ring_buffer_head_t *header = &(instance->header);
	uint32_t remaining = 0;

	assert(header != NULL);
	assert(header->magic == _RING_BUFFER_MAGIC);
	assert(header->buffer_end > size);

	while (header->cur_wr + 1 == header->cur_rd ||
	       (header->cur_rd == 0 &&
	       header->cur_wr == header->buffer_end))
		;

	remaining = header->buffer_end - header->cur_wr + 1;
	if (remaining > size) {
		memcpy(instance->data + header->cur_wr, buffer, size);
		header->cur_wr = header->cur_wr + size;
	} else {
		uint32_t rollback = size - remaining;

		assert(remaining < header->buffer_end);
		assert(rollback <= size);
		memcpy(instance->data + header->cur_wr, buffer, remaining);
		memcpy(instance->data, buffer + remaining, rollback);
		header->cur_wr = rollback;
	}

	return size;
}

int32_t ring_buffer_pop(rb_handle handle, uint8_t *buffer, uint32_t max_size)
{
	ring_buffer_t *instance = (ring_buffer_t *)handle;
	ring_buffer_head_t *header = &instance->header;
	uint32_t data_size = 0;
	uint32_t cur_rd = header->cur_rd;
	uint32_t cur_wr = header->cur_wr;

	assert(header != NULL);
	assert(header->magic == _RING_BUFFER_MAGIC);

	if (cur_rd == cur_wr) {
		return 0;
	} else if (cur_rd < cur_wr) {
		data_size = cur_wr - cur_rd;

		if (max_size < data_size)
			data_size = max_size;

		assert(data_size <= cur_wr);
		memcpy(buffer, instance->data + cur_rd, data_size);
		header->cur_rd = cur_rd + data_size;
	} else {
		uint32_t remaining = header->buffer_end - cur_rd + 1;
		uint32_t rollback = 0;

		if (max_size < remaining) {
			memcpy(buffer, instance->data + cur_rd, max_size);
			header->cur_rd = cur_rd + max_size;
			return max_size;
		}

		data_size = remaining + cur_wr;
		if (max_size < data_size)
			data_size = max_size;

		rollback = data_size - remaining;
		assert(remaining <= header->buffer_end);
		assert(rollback <= data_size);
		memcpy(buffer, instance->data + cur_rd, remaining);
		memcpy(buffer + remaining, instance->data, rollback);

		header->cur_rd = rollback;
	}

	return data_size;
}

int32_t ring_buffer_not_empty(rb_handle handle)
{
	ring_buffer_t *instance = (ring_buffer_t *)handle;
	ring_buffer_head_t *header = &instance->header;
	uint32_t cur_rd = header->cur_rd;
	uint32_t cur_wr = header->cur_wr;

	assert(header != NULL);
	assert(header->magic == _RING_BUFFER_MAGIC);

	if (cur_rd == cur_wr)
		return 0;

	return 1;
}
