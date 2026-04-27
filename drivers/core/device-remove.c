// SPDX-License-Identifier: GPL-2.0+
/*
 * Device manager
 *
 * Copyright (c) 2014 Google, Inc
 *
 * (C) Copyright 2012
 * Pavel Herrmann <morpheus.ibis@gmail.com>
 */

#include <common.h>
#include <errno.h>
#include <malloc.h>
#include <dm/device.h>
#include <dm/device-internal.h>
#include <dm/uclass.h>
#include <dm/uclass-internal.h>
#include <dm/util.h>

int device_chld_unbind(struct udevice *dev, struct driver *drv)
{
	struct udevice *pos, *n;
	int ret, saved_ret = 0;

	assert(dev);

	list_for_each_entry_safe(pos, n, &dev->child_head, sibling_node) {
		if (drv && (pos->driver != drv))
			continue;

		ret = device_unbind(pos);
		if (ret && !saved_ret)
			saved_ret = ret;
	}

	return saved_ret;
}

int device_chld_remove(struct udevice *dev, struct driver *drv,
		       uint flags)
{
	struct udevice *pos, *n;
	int result = 0;

	assert(dev);

	list_for_each_entry_safe(pos, n, &dev->child_head, sibling_node) {
		int ret;

		if (drv && (pos->driver != drv))
			continue;

		ret = device_remove(pos, flags);
		if (ret == -EPROBE_DEFER)
			result = ret;
		else if (ret && ret != -EKEYREJECTED)
			return ret;
	}

	return result;
}

int device_unbind(struct udevice *dev)
{
	const struct driver *drv;
	int ret;

	if (!dev)
		return -EINVAL;

	if (dev->flags & DM_FLAG_ACTIVATED)
		return -EINVAL;

	if (!(dev->flags & DM_FLAG_BOUND))
		return -EINVAL;

	drv = dev->driver;
	assert(drv);

	if (drv->unbind) {
		ret = drv->unbind(dev);
		if (ret)
			return ret;
	}

	ret = device_chld_unbind(dev, NULL);
	if (ret)
		return ret;

	if (dev->flags & DM_FLAG_ALLOC_PDATA) {
		free(dev->platdata);
		dev->platdata = NULL;
	}
	if (dev->flags & DM_FLAG_ALLOC_UCLASS_PDATA) {
		free(dev->uclass_platdata);
		dev->uclass_platdata = NULL;
	}
	if (dev->flags & DM_FLAG_ALLOC_PARENT_PDATA) {
		free(dev->parent_platdata);
		dev->parent_platdata = NULL;
	}
	ret = uclass_unbind_device(dev);
	if (ret)
		return ret;

	if (dev->parent)
		list_del(&dev->sibling_node);

	devres_release_all(dev);

	if (dev->flags & DM_FLAG_NAME_ALLOCED)
		free((char *)dev->name);
	free(dev);

	return 0;
}

/**
 * device_free() - Free memory buffers allocated by a device
 * @dev:	Device that is to be started
 */
void device_free(struct udevice *dev)
{
	int size;

	if (dev->driver->priv_auto_alloc_size) {
		free(dev->priv);
		dev->priv = NULL;
	}
	size = dev->uclass->uc_drv->per_device_auto_alloc_size;
	if (size) {
		free(dev->uclass_priv);
		dev->uclass_priv = NULL;
	}
	if (dev->parent) {
		size = dev->parent->driver->per_child_auto_alloc_size;
		if (!size) {
			size = dev->parent->uclass->uc_drv->
					per_child_auto_alloc_size;
		}
		if (size) {
			free(dev->parent_priv);
			dev->parent_priv = NULL;
		}
	}

	devres_release_probe(dev);
}

/**
 * flags_remove() - Figure out whether to remove a device
 *
 * If this is called with @flags == DM_REMOVE_NON_VITAL | DM_REMOVE_ACTIVE_DMA,
 * then it returns 0 (=go head and remove) if the device is not matked vital
 * but is marked DM_REMOVE_ACTIVE_DMA.
 *
 * If this is called with @flags == DM_REMOVE_ACTIVE_DMA,
 * then it returns 0 (=go head and remove) if the device is marked
 * DM_REMOVE_ACTIVE_DMA, regardless of whether it is marked vital.
 *
 * @flags: Flags passed to device_remove()
 * @drv_flags: Driver flags
 * Return: 0 if the device should be removed,
 * -EKEYREJECTED if @flags includes a flag in DM_REMOVE_ACTIVE_ALL but
 *	@drv_flags does not (indicates that this device has nothing to do for
 *	DMA shutdown or OS prepare)
 * -EPROBE_DEFER if @flags is DM_REMOVE_NON_VITAL but @drv_flags contains
 *	DM_FLAG_VITAL (indicates the device is vital and should not be removed)
 */
static int flags_remove(uint flags, uint drv_flags)
{
	if (!(flags & DM_REMOVE_NORMAL)) {
		bool vital_match;
		bool active_match;

		active_match = !(flags & DM_REMOVE_ACTIVE_ALL) ||
			(drv_flags & flags);
		vital_match = !(flags & DM_REMOVE_NON_VITAL) ||
			!(drv_flags & DM_FLAG_VITAL);
		if (!vital_match)
			return -EPROBE_DEFER;
		if (!active_match)
			return -EKEYREJECTED;
	}

	return 0;
}

int device_remove(struct udevice *dev, uint flags)
{
	const struct driver *drv;
	int ret;

	if (!dev)
		return -EINVAL;

	if (!(dev->flags & DM_FLAG_ACTIVATED))
		return 0;

	ret = device_chld_remove(dev, NULL, flags);
	if (ret)
		goto err;

	/*
	 * Remove the device if called with the "normal" remove flag set,
	 * or if the remove flag matches any of the drivers remove flags
	 */
	drv = dev->driver;
	assert(drv);
	ret = flags_remove(flags, drv->flags);
	if (ret) {
		log_debug("%s: When removing: flags=%x, drv->flags=%x, err=%d\n",
			  dev->name, flags, drv->flags, ret);
		return ret;
	}

	ret = uclass_pre_remove_device(dev);
	if (ret)
		return ret;

	if (drv->remove) {
		ret = drv->remove(dev);
		if (ret)
			goto err_remove;
	}

	if (dev->parent && dev->parent->driver->child_post_remove) {
		ret = dev->parent->driver->child_post_remove(dev);
		if (ret) {
			dm_warn("%s: Device '%s' failed child_post_remove()",
				__func__, dev->name);
		}
	}

	device_free(dev);
	dev->seq = -1;
	dev->flags &= ~DM_FLAG_ACTIVATED;

	return ret;

err_remove:
	/* We can't put the children back */
	dm_warn("%s: Device '%s' failed to remove, but children are gone\n",
		__func__, dev->name);
err:
	ret = uclass_post_probe_device(dev);
	if (ret) {
		dm_warn("%s: Device '%s' failed to post_probe on error path\n",
			__func__, dev->name);
	}

	return ret;
}
