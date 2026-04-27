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
#include <div64.h>
#include <dm.h>
#include <pwm.h>
#include <clk.h>
#include <regmap.h>
#include <syscon.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

#define OSC_24MHZ			24000000
#define NSEC_PER_SEC			1000000000L

#define BERLIN_PWM_EN			0x0
#define  BERLIN_PWM_ENABLE		BIT(0)
#define BERLIN_PWM_CONTROL		0x4
/*
 * The prescaler claims to support 8 different moduli, configured using the
 * low three bits of PWM_CONTROL. (Sequentially, they are 1, 4, 8, 16, 64,
 * 256, 1024, and 4096.)  However, the moduli from 4 to 1024 appear to be
 * implemented by internally shifting TCNT left without adding additional
 * bits. So, the max TCNT that actually works for a modulus of 4 is 0x3fff;
 * for 8, 0x1fff; and so on. This means that those moduli are entirely
 * useless, as we could just do the shift ourselves. The 4096 modulus is
 * implemented with a real prescaler, so we do use that, but we treat it
 * as a flag instead of pretending the modulus is actually configurable.
 */
#define BERLIN_PWM_PRESCALE_4096	0x7
#define  BERLIN_PWM_INVERT_POLARITY	BIT(3)
#define BERLIN_PWM_DUTY			0x8
#define BERLIN_PWM_TCNT			0xc
#define BERLIN_PWM_MAX_TCNT		65535

struct berlin_pwm_priv {
#if CONFIG_IS_ENABLED(CLK)
	struct clk clk;
#endif
	void  __iomem *regs;
	bool invert;
};

static int berlin_pwm_set_invert(struct udevice *dev, uint channel,
				 bool polarity)
{
	struct berlin_pwm_priv *priv = dev_get_priv(dev);
	u32 value = 0;

	value = readl_relaxed(priv->regs + channel * 0x10 + BERLIN_PWM_CONTROL);

	if (!polarity)
		value &= ~BERLIN_PWM_INVERT_POLARITY;
	else
		value |= BERLIN_PWM_INVERT_POLARITY;

	writel_relaxed(value, priv->regs + channel * 0x10 + BERLIN_PWM_CONTROL);

	return 0;
}

static int berlin_pwm_set_config(struct udevice *dev, uint channel,
				 uint period_ns, uint duty_ns)
{
	struct berlin_pwm_priv *priv = dev_get_priv(dev);
	bool prescale_4096 = false;
	u32 value, duty, period;
	u64 cycles;

#if CONFIG_IS_ENABLED(CLK)
	cycles = clk_get_rate(&priv->clk);
#else
	cycles = 1000000U;
#endif
	cycles *= period_ns;
	do_div(cycles, NSEC_PER_SEC);
	if (cycles > BERLIN_PWM_MAX_TCNT) {
		prescale_4096 = true;
		cycles >>= 12; // Prescaled by 4096
		if (cycles > BERLIN_PWM_MAX_TCNT)
			return -ERANGE;
	}

	period = cycles;
	cycles *= duty_ns;
	do_div(cycles, period_ns);
	duty = cycles;

	value = readl_relaxed(priv->regs + channel * 0x10 + BERLIN_PWM_CONTROL);
	if (prescale_4096)
		value |= BERLIN_PWM_PRESCALE_4096;
	else
		value &= ~BERLIN_PWM_PRESCALE_4096;
	writel_relaxed(value, priv->regs + channel * 0x10 + BERLIN_PWM_CONTROL);

	writel_relaxed(duty, priv->regs + channel * 0x10 + BERLIN_PWM_DUTY);
	writel_relaxed(period, priv->regs + channel * 0x10 + BERLIN_PWM_TCNT);

	debug("%s: prescaler: %d, period: %d, duty: %d\n",
	      __func__, prescale_4096, period, duty);

	return 0;
}

static int berlin_pwm_set_enable(struct udevice *dev, uint channel, bool enable)
{
	struct berlin_pwm_priv *priv = dev_get_priv(dev);
	u32 value = 0;

	value = readl_relaxed(priv->regs + channel * 0x10 + BERLIN_PWM_EN);
	if (!enable)
		value &= ~BERLIN_PWM_ENABLE;
	else
		value |= BERLIN_PWM_ENABLE;

	writel_relaxed(value, priv->regs + channel * 0x10 + BERLIN_PWM_EN);

	return 0;
}

static int berlin_pwm_ofdata_to_platdata(struct udevice *dev)
{
	struct berlin_pwm_priv *priv = dev_get_priv(dev);

	priv->regs = (void __iomem *)devfdt_get_addr(dev);

	return 0;
}

static int berlin_pwm_probe(struct udevice *dev)
{
	struct berlin_pwm_priv *priv = dev_get_priv(dev);
	int ret;

#if CONFIG_IS_ENABLED(CLK)
	ret = clk_get_by_index(dev, 0, &priv->clk);
	if (ret) {
		printf("%s: failed to get clock\n", __func__);
		return ret;
	}
	ret = clk_enable(&priv->clk);
	if (ret && ret != -ENOSYS && ret != -ENOTSUPP) {
		clk_free(&priv->clk);
		printf("%s: failed to enable clock\n", __func__);
		return ret;
	}
#endif
	return 0;
}

static const struct pwm_ops berlin_pwm_ops = {
	.set_invert	= berlin_pwm_set_invert,
	.set_config	= berlin_pwm_set_config,
	.set_enable	= berlin_pwm_set_enable,
};

static const struct udevice_id berlin_pwm_ids[] = {
	{ .compatible = "syna,berlin-pwm" },
	{ }
};

U_BOOT_DRIVER(berlin_pwm) = {
	.name	= "berlin_pwm",
	.id	= UCLASS_PWM,
	.of_match = berlin_pwm_ids,
	.ops	= &berlin_pwm_ops,
	.ofdata_to_platdata	= berlin_pwm_ofdata_to_platdata,
	.probe		= berlin_pwm_probe,
	.priv_auto_alloc_size	= sizeof(struct berlin_pwm_priv),
};
