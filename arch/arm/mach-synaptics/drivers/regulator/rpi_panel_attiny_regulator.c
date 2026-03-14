// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020 Marek Vasut <marex@denx.de>
 *
 * Based on rpi_touchscreen.c by Eric Anholt <eric@anholt.net>
 */
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
#include <fdtdec.h>
#include <errno.h>
#include <dm.h>
#include <i2c.h>
#include <power/regulator.h>

/* I2C registers of the Atmel microcontroller. */
#define REG_ID		0x80
#define REG_PORTA	0x81
#define REG_PORTB	0x82
#define REG_PORTC	0x83
#define REG_POWERON	0x85
#define REG_PWM		0x86
#define REG_ADDR_L	0x8c
#define REG_ADDR_H	0x8d
#define REG_WRITE_DATA_H	0x90
#define REG_WRITE_DATA_L	0x91

#define PA_LCD_DITHB		BIT(0)
#define PA_LCD_MODE		BIT(1)
#define PA_LCD_LR		BIT(2)
#define PA_LCD_UD		BIT(3)

#define PB_BRIDGE_PWRDNX_N	BIT(0)
#define PB_LCD_VCC_N		BIT(1)
#define PB_LCD_MAIN		BIT(7)

#define PC_LED_EN		BIT(0)
#define PC_RST_TP_N		BIT(1)
#define PC_RST_LCD_N		BIT(2)
#define PC_RST_BRIDGE_N		BIT(3)

#define DEFAULT_BRIGHTNESS	0xFF

DECLARE_GLOBAL_DATA_PTR;

struct attiny_regulator_priv {
};

static int attiny_regulator_ofdata_to_platdata(struct udevice *dev)
{
	return 0;
}

static int attiny_i2c_write(struct udevice *dev, uint8_t buf, uint8_t reg)
{
	struct dm_i2c_chip *chip = dev_get_parent_platdata(dev);
	int ret;

	ret = dm_i2c_write(dev, reg, &buf, 1);
	if (ret)
		printf("attiny_i2c_write Failed Reg: %x", reg);
	else
		udelay(5000);

	return ret;
}

static int attiny_i2c_read(struct udevice *dev, uint8_t *buf, uint8_t reg)
{
	struct dm_i2c_chip *chip = dev_get_parent_platdata(dev);
	uint8_t addr_buf[1] = { reg };
	uint8_t data_buf[1] = { 0, };
	struct i2c_msg msgs[1];
	int ret;

	/* Write register address */
	msgs[0].addr = chip->chip_addr;
	msgs[0].flags = 0;
	msgs[0].len = ARRAY_SIZE(addr_buf);
	msgs[0].buf = addr_buf;

	ret = dm_i2c_xfer(dev, msgs, ARRAY_SIZE(msgs));
	if (ret)
		return ret;

	udelay(5000);

	/* Read data from register */
	msgs[0].addr = chip->chip_addr;
	msgs[0].flags = I2C_M_RD;
	msgs[0].len = 1;
	msgs[0].buf = data_buf;

	ret = dm_i2c_xfer(dev, msgs, ARRAY_SIZE(msgs));
	*buf = data_buf[0];

	return ret;
}

static int attiny_regulator_set_enable(struct udevice *dev, bool enable)
{
	int ret, i;

	ret = attiny_i2c_write(dev, 0, REG_PORTC);
	if (ret) {
		return ret;
	}
	mdelay(10);

	attiny_i2c_write(dev, PA_LCD_LR, REG_PORTA);
	mdelay(10);
	attiny_i2c_write(dev, PB_LCD_MAIN, REG_PORTB);
	mdelay(10);
	attiny_i2c_write(dev, PC_LED_EN, REG_PORTC);
	mdelay(80);

	for (i = 0; i < 10; i++) {
		attiny_i2c_write(dev, DEFAULT_BRIGHTNESS, REG_PWM);
	}

	return 0;
}

static int attiny_regulator_probe(struct udevice *dev)
{
	uint8_t data, wdata;
	int ret, i;

	ret = attiny_i2c_read(dev, &data, REG_ID);
	if (ret) {
		printf("Regulator I2C read failed = %d\n", ret);
		return ret;
	}

	switch (data) {
	case 0xde: /* ver 1 */
	case 0xc3: /* ver 2 */
		break;
	default:
		printf("Unknown Atmel firmware revision: 0x%02x\n", data);
		return -ENODEV;
	}

	attiny_i2c_write(dev, 0, REG_POWERON);
	mdelay(30);
	attiny_i2c_write(dev, 0, REG_PWM);

	return 0;
}

static const struct dm_regulator_ops attiny_regulator_ops = {
	.set_enable = attiny_regulator_set_enable,
};

static const struct udevice_id attiny_regulator_ids[] = {
	{ .compatible = "raspberrypi,7inch-touchscreen-panel-regulator" },
	{ }
};

U_BOOT_DRIVER(attiny_regulator) = {
	.name	= "attiny_regulator",
	.id	= UCLASS_REGULATOR,
	.of_match = attiny_regulator_ids,
	.ops	= &attiny_regulator_ops,
	.ofdata_to_platdata = &attiny_regulator_ofdata_to_platdata,
	.probe	= attiny_regulator_probe,
	.priv_auto_alloc_size = sizeof(struct attiny_regulator_priv),
};
