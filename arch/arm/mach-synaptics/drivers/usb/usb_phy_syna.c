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
#include <dm.h>
#include <fdtdec.h>
#include <reset.h>
#include <asm/io.h>
#include <generic-phy.h>

#define USB_PHY_CTRL0		0x0
#define USB_PHY_CTRL1		0x4
#define USB_PHY_CTRL0_DEF		0x533DADF0
#define USB_PHY_CTRL1_DEF		0x01B10000

struct syna_usb_phy_priv {
	struct udevice *dev;
	const struct phy_ops *ops;
	fdt_addr_t base;
	struct reset_ctl_bulk	rsts;
};

static int usb2_phy_init(struct phy *phy)
{
	int ret;
	struct udevice *dev = phy->dev;
	struct syna_usb_phy_priv *priv = dev_get_priv(dev);

	ret = reset_assert_bulk(&priv->rsts);
	if (ret) {
		reset_release_bulk(&priv->rsts);
		dev_err(dev, "Failed to reset: %d\n", ret);
		return ret;
	}
	udelay(1);

	return 0;
}

static int usb2_phy_power_on(struct phy *phy)
{
	struct syna_usb_phy_priv *priv = dev_get_priv(phy->dev);
	int ret;

	writel(USB_PHY_CTRL0_DEF, priv->base + USB_PHY_CTRL0);
	writel(USB_PHY_CTRL1_DEF, priv->base + USB_PHY_CTRL1);

	ret = reset_deassert_bulk(&priv->rsts);
	if (ret) {
		reset_release_bulk(&priv->rsts);
		dev_err(phy->dev, "Failed to reset: %d\n", ret);
		return ret;
	}

	/* must have a delay here, followed by usb0CoreRstn */
	mdelay(1);

	return 0;
}

static const struct phy_ops usb2_phy_ops = {
	.init		= usb2_phy_init,
	.power_on	= usb2_phy_power_on,
};

#define USB3_PHY_CLK_CTRL		0x001C
#define REF_SSP_EN			BIT(16)

static int usb3_phy_init(struct phy *phy)
{
	struct syna_usb_phy_priv *priv = dev_get_priv(phy->dev);
	int ret;

	ret = reset_deassert_bulk(&priv->rsts);
	if (ret) {
		reset_release_bulk(&priv->rsts);
		dev_err(phy->dev, "Failed to reset: %d\n", ret);
		return ret;
	}
	udelay(1);
	return 0;
}

static int usb3_phy_power_on(struct phy *phy)
{
	struct syna_usb_phy_priv *priv = dev_get_priv(phy->dev);
	u32 val;
	int ret;

	val = readl(priv->base + USB3_PHY_CLK_CTRL);
	val |= REF_SSP_EN;
	writel(val, priv->base + USB3_PHY_CLK_CTRL);
	udelay(1);

	ret = reset_deassert_bulk(&priv->rsts);
	if (ret) {
		reset_release_bulk(&priv->rsts);
		dev_err(phy->dev, "Failed to reset: %d\n", ret);
		return ret;
	}
	udelay(10);
	return 0;
}

static const struct phy_ops usb3_phy_ops = {
	.init		= usb3_phy_init,
	.power_on	= usb3_phy_power_on,
};

static int syna_usb_phy_init(struct phy *phy)
{
	struct syna_usb_phy_priv *priv = dev_get_priv(phy->dev);

	return priv->ops->init(phy);
}

static int syna_usb_phy_power_on(struct phy *phy)
{
	struct syna_usb_phy_priv *priv = dev_get_priv(phy->dev);

	return priv->ops->power_on(phy);
}

const struct phy_ops syna_usb_phy_ops = {
	.init		= syna_usb_phy_init,
	.power_on	= syna_usb_phy_power_on,
};

static int syna_usb_phy_probe(struct udevice *dev)
{
	struct syna_usb_phy_priv *priv = dev_get_priv(dev);
	int ret;

	priv->base = dev_read_addr(dev);
	if (priv->base == FDT_ADDR_T_NONE) {
		debug("%s: Failed to find address (err=%d\n)", __func__, ret);
		return -EINVAL;
	}

	priv->dev = dev;
	priv->ops = (const struct phy_ops *)dev_get_driver_data(dev);
	ret = reset_get_bulk(dev, &priv->rsts);
	if (ret) {
		dev_warn(dev, "Can't get reset: %d\n", ret);
		/* Return 0 if error due to !CONFIG_DM_RESET and reset
		 * DT property is not present.
		 */
		if (ret == -ENOENT || ret == -ENOTSUPP)
			return 0;
		else
			return ret;
	}

	return 0;
}

static const struct udevice_id syna_usb_phy_match[] = {
	{	.compatible = "syna,usb2-phy", .data = (ulong)&usb2_phy_ops,},
	{	.compatible = "syna,usb3-phy", .data = (ulong)&usb3_phy_ops,},
	{},
};

U_BOOT_DRIVER(syna_usb_phy) = {
	.name = "syna_usb_phy",
	.id = UCLASS_PHY,
	.of_match = syna_usb_phy_match,
	.probe = syna_usb_phy_probe,
	.ops = &syna_usb_phy_ops,
	.priv_auto_alloc_size = sizeof(struct syna_usb_phy_priv),
};

