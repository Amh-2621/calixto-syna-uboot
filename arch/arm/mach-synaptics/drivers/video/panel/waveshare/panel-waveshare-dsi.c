// SPDX-License-Identifier: GPL-2.0+
#include <common.h>
#include <fdtdec.h>
#include <errno.h>
#include <dm.h>
#include <i2c.h>
#include <panel.h>

struct ws_panel_priv {
	int addr;
};

static int ws_panel_ofdata_to_platdata(struct udevice *dev)
{
	ofnode node;
	struct udevice *newdev, *bus;
	int ret;
	u32 chip_addr;
	struct ws_panel_priv *priv = dev_get_priv(dev);

	node = ofnode_by_compatible(ofnode_null(), "waveshare,13.3inch-4lane-panel");
	if (!ofnode_valid(node))
		return -ENODEV;

	ret = ofnode_read_u32(node, "reg", &chip_addr);
	if (ret) {
		printf("ws_panel_ofdata_to_platdata, reg not found in dts\n");
		return -EINVAL;
	}

	priv->addr = chip_addr;
	ret = uclass_get_device_by_ofnode(UCLASS_I2C, ofnode_get_parent(node),
					  &bus);
	if (ret) {
		printf("ws_panel_ofdata_to_platdata: bus not found\n");
		return -ENODEV;
	}

	ret = dm_i2c_probe(bus, chip_addr, 0, &newdev);
	if (ret) {
		printf("ws_panel_ofdata_to_platdata: dm_i2c_probe failed (ret: %d)\n", ret);
	}

	return ret;
}

static int ws_panel_i2c_write(struct udevice *dev, uint8_t buf, uint8_t reg)
{
	int ret;

	ret = dm_i2c_write(dev, reg, &buf, 1);
	if (ret) {
		printf("ws_panel_i2c_write Failed Reg: %x, ret:%d\n", reg, ret);
	} else {
		udelay(5000);
	}

	return ret;
}

static int ws_panel_i2c_read(struct udevice *dev, uint8_t *buf, uint8_t reg)
{
	struct ws_panel_priv *priv = dev_get_priv(dev);
	uint8_t addr_buf[1] = { reg };
	uint8_t data_buf[1] = { 0, };
	struct i2c_msg msgs[1];
	int ret;

	/* Write register address */
	msgs[0].addr = priv->addr;
	msgs[0].flags = 0;
	msgs[0].len = ARRAY_SIZE(addr_buf);
	msgs[0].buf = addr_buf;

	ret = dm_i2c_xfer(dev, msgs, ARRAY_SIZE(msgs));
	if (ret) {
		printf("ws_panel_i2c_read reg Failed @addr[0x%x] Reg: 0x%x, ret:%d\n",
				priv->addr, reg, ret);
		return ret;
	}

	udelay(5000);

	/* Read data from register */
	msgs[0].addr = priv->addr;
	msgs[0].flags = I2C_M_RD;
	msgs[0].len = 1;
	msgs[0].buf = data_buf;

	ret = dm_i2c_xfer(dev, msgs, ARRAY_SIZE(msgs));
	if (ret) {
		printf("ws_panel_i2c_read data Failed @addr[0x%x] Reg: 0x%x, ret:%d\n",
				priv->addr, reg, ret);
		return ret;
	}

	*buf = data_buf[0];

	return ret;
}

static int ws_panel_set_backlight(struct udevice *dev, int percent)
{
	int brightness_level, ret;

	brightness_level = (percent * 0xff)/100;
	if((ret = ws_panel_i2c_write(dev, (0xff - brightness_level), 0xab)) < 0) {
		printf("ws_panel_set_backlight reg ab write failed!\n");
		return ret;
	}

	if((ret = ws_panel_i2c_write(dev, 0x01, 0xaa)) < 0) {
		printf("ws_panel_set_backlight reg aa write failed!\n");
		return ret;
	}

	debug("ws_panel_set_backlight success!\n");
	return 0;
}

static int ws_panel_enable_backlight(struct udevice *dev)
{
	int ret;

	if((ret = ws_panel_i2c_write(dev, 0x01, 0xad)) < 0) {
		printf("ws_panel_enable_backlight reg ad write failed!\n");
		return ret;
	}

	if((ret = ws_panel_i2c_write(dev, 0x7f, 0xab)) < 0) {
		printf("ws_panel_enable_backlight reg ab write failed!\n");
		return ret;
	}

	if((ret = ws_panel_i2c_write(dev, 0x01, 0xaa)) < 0) {
		printf("ws_panel_enable_backlight reg aa write failed!\n");
		return ret;
	}

	debug("ws_panel_enable_backlight success!\n");
	/* Set default backlight brightness to max*/
	ret = ws_panel_set_backlight(dev, 100);

	return ret;
}

static int ws_panel_get_display_timing(struct udevice *dev,
                                              struct display_timing *timing)
{
	// Do we need to do something here?
	printf("ws_panel_get_display_timing\n");
	return 0;
}

static const struct panel_ops ws_panel_ops = {
	.enable_backlight	= ws_panel_enable_backlight,
	.set_backlight	= ws_panel_set_backlight,
	.get_display_timing	= ws_panel_get_display_timing,
};

static int ws_panel_probe(struct udevice *dev)
{
	int ret;

	if((ret = ws_panel_i2c_write(dev, 0x01, 0xc0)) < 0) {
		printf("ws_panel_probe write reg 0xc0 failed!\n");
		return ret;
	}

	if((ret = ws_panel_i2c_write(dev, 0x01, 0xc2)) < 0) {
		printf("ws_panel_probe write reg 0xc2 failed!\n");
		return ret;
	}

	if((ret = ws_panel_i2c_write(dev, 0x01, 0xac)) < 0) {
		printf("ws_panel_probe write reg 0xac failed!\n");
		return ret;
	}

	debug("ws_panel_probe success!\n");
	/* Enable the panel */
	ret = ws_panel_enable_backlight(dev);

	return ret;
}

static const struct udevice_id ws_panel_ids[] = {
	{ .compatible = "waveshare,13.3inch-4lane-panel" },
	{ }
};

U_BOOT_DRIVER(ws_panel) = {
	.name		= "ws_panel",
	.id		= UCLASS_PANEL_BACKLIGHT,
	.of_match	= ws_panel_ids,
	.ops		= &ws_panel_ops,
	.probe		= ws_panel_probe,
	.ofdata_to_platdata = &ws_panel_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct ws_panel_priv),
};
