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
#include <reset.h>
#include <sdhci.h>
#include <clk.h>
#include "dwcmshc_sdhci.h"

static void dwcmshc_reset_phy(struct sdhci_host *host, int rst)
{
	volatile u16 valw;

	valw = sdhci_readw(host, PHY_CNFG_REG);
	valw &= ~PHY_RSTN;
	valw |= rst;
	sdhci_writew(host, valw, PHY_CNFG_REG);
}

static void dwcmshc_reset_device(struct sdhci_host *host)
{
	u32 offset, val;

	offset = sdhci_readl(host, SDHCI_P_VENDOR_SPECIFIC_AREA);
	offset &= SDHCI_P_VENDOR_SPECIFIC_AREA_MASK;
	offset += SDHCI_EMMC_CTRL_OFFSET;
	val = sdhci_readl(host, offset);
	val |= CARD_IS_EMMC;
	val |= EMMC_RST_N_OE;
	val &= ~EMMC_RST_N;
	sdhci_writel(host, val, offset);
	mdelay(1);
	val = sdhci_readl(host, offset);
	val |= EMMC_RST_N;
	sdhci_writel(host, val, offset);
	mdelay(1);
	val = sdhci_readl(host, offset);
}

static void dwcmshc_reset_host(struct dwcmshc_sdhci_plat *plat)
{
	reset_assert_bulk(&plat->reset_ctl);
	mdelay(1);
	reset_deassert_bulk(&plat->reset_ctl);
}

static void dwcmshc_setup_phy_datapath(struct sdhci_host *host)
{
	u8 valb;

	valb = sdhci_readb(host, PHY_COMMDL_CNFG_REG);
	valb &= ~DLSTEP_SEL;
	valb &= ~DLOUT_EN;
	sdhci_writeb(host, valb, PHY_COMMDL_CNFG_REG);

	valb = sdhci_readb(host, PHY_SDCLKDL_CNFG_REG);
	valb &= ~EXTDLY_EN;
	valb &= ~BYPASS_EN;
	valb &= ~UPDATE_DC;
	valb &= ~INPSEL_CNFG_MSK;
	sdhci_writeb(host, valb, PHY_SDCLKDL_CNFG_REG);

	valb = sdhci_readb(host, PHY_SMPLDL_CNFG_REG);
	valb &= ~SEXTDLY_EN;
	valb &= ~SBYPASS_EN;
	valb &= ~SINPSEL_OVERRIDE;
	valb &= ~SINPSEL_CNFG_MSK;
	valb |= (3 << SINPSEL_CNFG_SFT);
	sdhci_writeb(host, valb, PHY_SMPLDL_CNFG_REG);

	valb = sdhci_readb(host, PHY_ATDL_CNFG_REG);
	valb &= ~AEXTDLY_EN;
	valb &= ~ABYPASS_EN;
	valb &= ~AINPSEL_CNFG_MSK;
	valb |= (3 << AINPSEL_CNFG_SFT);
	sdhci_writeb(host, valb, PHY_ATDL_CNFG_REG);
}

static void dwcmshc_setup_phy_delayline(struct sdhci_host *host, u8 delay)
{
	u8 valb;

	valb = sdhci_readb(host, PHY_SDCLKDL_CNFG_REG);
	valb |= UPDATE_DC;
	sdhci_writeb(host, valb, PHY_SDCLKDL_CNFG_REG);

	valb = sdhci_readb(host, PHY_SDCLKDL_DC_REG);
	valb &= ~CCKDL_DC_MSK;
	valb |= delay << CCKDL_DC_SFT;
	sdhci_writeb(host, valb, PHY_SDCLKDL_DC_REG);

	valb = sdhci_readb(host, PHY_SDCLKDL_CNFG_REG);
	valb &= ~UPDATE_DC;
	sdhci_writeb(host, valb, PHY_SDCLKDL_CNFG_REG);
}

static void dwcmshc_setup_phy_tuning(struct sdhci_host *host)
{
	u32 offset, val;

	offset = sdhci_readl(host, SDHCI_P_VENDOR_SPECIFIC_AREA);
	offset &= SDHCI_P_VENDOR_SPECIFIC_AREA_MASK;
	offset += PHY_AT_CTRL_R_REG_OFFSET;

	val = sdhci_readl(host, offset);
	val &= ~TUNE_CLK_STOP_EN;
	val &= ~POST_CHANGE_DLY_MSK;
	val &= ~PRE_CHANGE_DLY_MSK;
	val |= TUNE_CLK_STOP_EN | (3 << POST_CHANGE_DLY_SFT) | (3 << PRE_CHANGE_DLY_SFT);
	sdhci_writel(host, val, offset);
}

static int dwcmshc_setup_phy_configure(struct sdhci_host *host)
{
	struct dwcmshc_sdhci_plat *plat = dev_get_platdata(host->mmc->dev);
	struct phy_gen_setting *gen_setting = &gen_setting_1v8;
	struct phy_pad_setting *pad_setting = pad_setting_1v8;

	int i;
	volatile u16 valw;
	volatile u32 val;
	int timeout = 100;

	if (host->mmc->signal_voltage == MMC_SIGNAL_VOLTAGE_330) {
		gen_setting = &gen_setting_3v3;
		pad_setting = pad_setting_3v3;
	}

	val = sdhci_readl(host, gen_setting->reg);
	val &= ~(gen_setting->mask);
	val |= gen_setting->setting;
	if (plat->pad_sp) {
		val &= ~(0xf << 16);
		val |= (plat->pad_sp & 0xFF) << 16;
	}
	if (plat->pad_sn) {
		val &= ~(0xf << 20);
		val |= (plat->pad_sn & 0xFF) << 20;
	}
	sdhci_writel(host, val, gen_setting->reg);

	for (i = 0; i < PHY_PAD_SETTING_NUM; i++) {
		valw = sdhci_readw(host, pad_setting[i].reg);
		valw &= ~(pad_setting[i].mask);
		valw |= pad_setting[i].setting;
		sdhci_writew(host, valw, pad_setting[i].reg);
	}

	do {
		mdelay(1);
		val = sdhci_readl(host, PHY_CNFG_REG);

		if (!timeout) {
			printf("EMMC PHY's PowerGood status is not ready !\n");
			return -1;
		}
	} while (!(val & PHY_PWRGOOD) && timeout--);

	plat->phy_voltage = host->mmc->signal_voltage;

	return 0;
}

static int dwcmshc_setup_hs400_phy_dll(struct sdhci_host *host)
{
	struct dwcmshc_sdhci_plat *plat = dev_get_platdata(host->mmc->dev);
	u32 delay_step, delay_code;
	u32 mstlkdc, slvlkdc;
	u16 valw;
	u8 valb;
	char *ep = NULL;

	/* prepare DLL configuration */
	valw = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	valw &= ~SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, valw, SDHCI_CLOCK_CONTROL);

	sdhci_writew(host, 0x8000, PHY_DLLLBT_CNFG_REG);

	valb = sdhci_readb(host, PHY_DLL_CNFG1_REG);
	valb &= ~WAITCYCLE_MSK;
	valb |= (3 << WAITCYCLE_SFT);
	valb &= ~SLVDLY_MSK;
	valb |= (3 << SLVDLY_SFT);
	sdhci_writeb(host, valb, PHY_DLL_CNFG1_REG);

	sdhci_writeb(host, 0xa, PHY_DLL_CNFG2_REG);

	valb = sdhci_readb(host, PHY_DLLDL_CNFG_REG);
	valb &= ~SLV_INPSEL_MSK;
	valb = 0;
	valb |= (3 << SLV_INPSEL_SFT);
	sdhci_writeb(host, valb, PHY_DLLDL_CNFG_REG);

	valw = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	valw |= SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, valw, SDHCI_CLOCK_CONTROL);

	/* start DLL lock */
	valb = sdhci_readb(host, PHY_DLL_CTRL_REG);
	valb &= ~DLL_EN;
	sdhci_writeb(host, valb, PHY_DLL_CTRL_REG);
	valb |= DLL_EN;
	sdhci_writeb(host, valb, PHY_DLL_CTRL_REG);

	do {
		valb = sdhci_readb(host, PHY_DLL_STATUS_REG);
	} while (!(valb & LOCK_STS));

	if (valb & ERROR_STS) {
		printf("%s failed\n", __func__);
		return -1;
	}

	/* calibrate DLL */
	valb = sdhci_readb(host, PHY_DLLDBG_MLKDC_REG);
	mstlkdc = valb & 0x7F;
	valb = sdhci_readb(host, PHY_DLLDBG_SLKDC_REG);
	slvlkdc = valb & 0x7F;

	if (mstlkdc / slvlkdc == 4)
		delay_step = 5000 / mstlkdc;
	else if (mstlkdc / slvlkdc == 2)
		delay_step = 5000 / (2 * mstlkdc);
	else
		delay_step = 5000 / (4 * slvlkdc);

	ep = env_get("sdhci_dll_delay_offset");
	if (ep)
		plat->dll_delay_offset = (u32)simple_strtol(ep, NULL, 10);

	delay_code = plat->dll_delay_offset / delay_step;
	delay_code += 1;

	return delay_code;
}

static int dwcmshc_setup_phy(struct sdhci_host *host)
{
	struct dwcmshc_sdhci_plat *plat = dev_get_platdata(host->mmc->dev);

	dwcmshc_setup_phy_datapath(host);
	dwcmshc_setup_phy_delayline(host, plat->mmc_type == SD_VERSION_SD ? phy_delay[SD_LEGACY] : phy_delay[MMC_LEGACY]);
	dwcmshc_setup_phy_tuning(host);
	dwcmshc_setup_phy_configure(host);

	return 0;
}

static void dwcmshc_sdhci_set_control_reg(struct sdhci_host *host)
{
	sdhci_set_control_reg(host);
}

static int dwcmshc_sdhci_set_ios_post(struct sdhci_host *host)
{
	struct dwcmshc_sdhci_plat *plat = dev_get_platdata(host->mmc->dev);
	int delay = 0;
	char *ep = NULL;

	if (plat->phy_voltage != host->mmc->signal_voltage && !plat->fixed_voltage) {
		dwcmshc_reset_phy(host, 0);
		dwcmshc_setup_phy(host);
		dwcmshc_reset_phy(host, 1);
	}

	if (host->mmc->selected_mode == MMC_HS_400) {
		delay = dwcmshc_setup_hs400_phy_dll(host);
		if (delay > 0) {
			dwcmshc_setup_phy_delayline(host, (u8)delay);
			return 0;
		}

		printf("%s MMC_HS_400 PHY_DLL_CAL failed\n", __func__);

		ep = env_get("sdhci_sdclkdl_dc");
		if (ep)
			plat->sdclkdl_dc = (u32)simple_strtol(ep, NULL, 10);

		if (plat->sdclkdl_dc) {
			dwcmshc_setup_phy_delayline(host, plat->sdclkdl_dc);
			return 0;
		}
	}

	if (host->mmc->selected_mode == UHS_SDR104) {
		ep = env_get("sdhci_sdclkdl_dc");
		if (ep)
			plat->sdclkdl_dc = (u32)simple_strtol(ep, NULL, 10);

		if (plat->sdclkdl_dc) {
			dwcmshc_setup_phy_delayline(host, plat->sdclkdl_dc);
			return 0;
		}
	}

	if (host->mmc->selected_mode == MMC_LEGACY) {
		dwcmshc_setup_phy_delayline(host, plat->mmc_type == SD_VERSION_SD ? phy_delay[SD_LEGACY] : phy_delay[MMC_LEGACY]);
		return 0;
	}

	if (host->mmc->selected_mode < MMC_MODES_END && phy_delay[host->mmc->selected_mode])
		dwcmshc_setup_phy_delayline(host, phy_delay[host->mmc->selected_mode]);

	return 0;
}

static int dwcmshc_sdhci_execute_tuning(struct mmc *mmc, u8 opcode)
{
	struct mmc_cmd cmd;
	struct mmc_data data;
	struct sdhci_host *host = dev_get_priv(mmc->dev);
	struct dwcmshc_sdhci_plat *plat = dev_get_platdata(mmc->dev);
	char tuning_loop_counter = SDHCI_TUNING_LOOP_COUNT;
	u32 timeout = 100;
	u32 offset, val;
	u16 valw;
	int delay = 0;

	if (opcode == MMC_CMD_SEND_TUNING_BLOCK_HS200) {
		delay = dwcmshc_setup_hs400_phy_dll(host);
		if (delay > 0)
			dwcmshc_setup_phy_delayline(host, (u8)delay);
	}

	/* prepare tuning */
	valw = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	valw &= ~SDHCI_CTRL_TUNED_CLK;
	valw &= ~SDHCI_CTRL_EXEC_TUNING;
	sdhci_writew(host, valw, SDHCI_HOST_CONTROL2);

	offset = sdhci_readl(host, SDHCI_P_VENDOR_SPECIFIC_AREA);
	offset &= SDHCI_P_VENDOR_SPECIFIC_AREA_MASK;
	offset += PHY_AT_CTRL_R_REG_OFFSET;

	val = sdhci_readl(host, offset);
	val &= ~(RPT_TUNE_ERR | SWIN_TH_EN | AT_EN);
	if (plat->mmc_type == MMC_VERSION_MMC)
		val |= AT_EN;
	val |= TUNE_CLK_STOP_EN;
	val |= 0x3 << PRE_CHANGE_DLY_SFT;
	val |= 0x3 << POST_CHANGE_DLY_SFT;
	sdhci_writel(host, val, offset);

	/* reset DAT and CMD */
	sdhci_writeb(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA, SDHCI_SOFTWARE_RESET);
	while (sdhci_readb(host, SDHCI_SOFTWARE_RESET) & (SDHCI_RESET_CMD | SDHCI_RESET_DATA)) {
		if (timeout == 0) {
			printf("%s: Reset 0x%x never completed.\n",
			       __func__, (int)(SDHCI_RESET_CMD | SDHCI_RESET_DATA));
			return -1;
		}
		timeout--;
		udelay(1000);
	}

	/* start tuning */
	valw = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	valw |= SDHCI_CTRL_EXEC_TUNING;
	sdhci_writew(host, valw, SDHCI_HOST_CONTROL2);

	do {
		cmd.cmdidx = opcode;
		cmd.resp_type = MMC_RSP_R1;
		cmd.cmdarg = 0;

		data.blocksize = 64;
		data.blocks = 1;
		data.flags = MMC_DATA_READ;

		if (tuning_loop_counter-- == 0)
			break;

		if (cmd.cmdidx == MMC_CMD_SEND_TUNING_BLOCK_HS200 &&
		    mmc->bus_width == 8)
			data.blocksize = 128;

		sdhci_writew(host, SDHCI_MAKE_BLKSZ(SDHCI_DEFAULT_BOUNDARY_ARG,
						    data.blocksize),
			     SDHCI_BLOCK_SIZE);
		sdhci_writew(host, data.blocks, SDHCI_BLOCK_COUNT);
		sdhci_writew(host, SDHCI_TRNS_READ, SDHCI_TRANSFER_MODE);

		mmc_send_cmd(mmc, &cmd, NULL);
		valw = sdhci_readw(host, SDHCI_HOST_CONTROL2);

		if (cmd.cmdidx == MMC_CMD_SEND_TUNING_BLOCK)
			udelay(1);
	} while (valw & SDHCI_CTRL_EXEC_TUNING);

	if (tuning_loop_counter < 0) {
		valw &= ~SDHCI_CTRL_TUNED_CLK;
		sdhci_writew(host, valw, SDHCI_HOST_CONTROL2);
	}

	if (!(valw & SDHCI_CTRL_TUNED_CLK)) {
		printf("%s:Tuning failed\n", __func__);
		return -1;
	}

	return 0;
}

const struct sdhci_ops dwcmshc_ops = {
	.set_control_reg = &dwcmshc_sdhci_set_control_reg,
	.set_ios_post = &dwcmshc_sdhci_set_ios_post,
	.platform_execute_tuning = &dwcmshc_sdhci_execute_tuning,
};

static int dwcmshc_probe(struct udevice *dev)
{
	struct dwcmshc_sdhci_plat *plat = dev_get_platdata(dev);
	struct mmc_uclass_priv *upriv = dev_get_uclass_priv(dev);
	struct sdhci_host *host = dev_get_priv(dev);
	int ret = 0;
	struct clk clk;
	unsigned long clock;

	dwcmshc_reset_host(plat);

	ret = clk_get_by_index(dev, 0, &clk);
	if (ret < 0) {
		dev_err(dev, "failed to get clock\n");
		return ret;
	}

	clock = clk_get_rate(&clk);
	if (IS_ERR_VALUE(clock)) {
		dev_err(dev, "failed to get rate\n");
		return clock;
	}

	host->max_clk = clock;
	host->mmc = &plat->mmc;
	host->mmc->dev = dev;
	host->mmc->signal_voltage = MMC_SIGNAL_VOLTAGE_180;

	if (dev_read_bool(dev, "3_3v-signalling"))
		host->mmc->signal_voltage = MMC_SIGNAL_VOLTAGE_330;

	if (dev_read_bool(dev, "fixed-voltage"))
		plat->fixed_voltage = 1;

	if (dev_read_bool(dev, "sdhci-sdio"))
		plat->mmc_type = SD_VERSION_SD;
	else
		plat->mmc_type = MMC_VERSION_MMC;

	plat->sdclkdl_dc = dev_read_u32_default(dev, "sdclkdl-dc", 0);
	plat->pad_sn = dev_read_u32_default(dev, "pad_sn", 0);
	plat->pad_sp = dev_read_u32_default(dev, "pad_sp", 0);
	plat->dll_delay_offset = dev_read_u32_default(dev, "dll-delay-offset", 1000);

	ret = sdhci_setup_cfg(&plat->cfg, host, plat->cfg.f_max, 0);
	if (ret)
		return ret;

	upriv->mmc = host->mmc;
	host->mmc->priv = host;

	ret = sdhci_probe(dev);
	if (ret)
		return ret;

	dwcmshc_reset_device(host);
	dwcmshc_reset_phy(host, 0);
	dwcmshc_setup_phy(host);
	dwcmshc_reset_phy(host, 1);

	return ret;
}

static int dwcmshc_ofdata_to_platdata(struct udevice *dev)
{
	struct dwcmshc_sdhci_plat *plat = dev_get_platdata(dev);
	struct sdhci_host *host = dev_get_priv(dev);
	struct mmc_config *cfg = &plat->cfg;
	int ret;

	if (reset_get_bulk(dev, &plat->reset_ctl)) {
		printf("%s: can't get reset index for xenon_sdhci\n", __func__);
		return -ENODEV;
	}
	host->name = dev->name;
	host->ioaddr = (void *)dev_read_addr(dev);

	ret = mmc_of_parse(dev, cfg);
	if (ret)
		return ret;

	host->ops = &dwcmshc_ops;

	return 0;
}

static int dwcmshc_bind(struct udevice *dev)
{
	struct dwcmshc_sdhci_plat *plat = dev_get_platdata(dev);
	int ret;

	ret = sdhci_bind(dev, &plat->mmc, &plat->cfg);
	if (ret)
		return ret;

	return 0;
}

static const struct udevice_id dwcmshc_sdhci_ids[] = {
	{ .compatible = "snps,dwcmshc-sdhci" },
	{ }
};

U_BOOT_DRIVER(dwcmshc_sdhci) = {
	.name	= "dwcmshc-sdhci",
	.id	= UCLASS_MMC,
	.of_match = dwcmshc_sdhci_ids,
	.ofdata_to_platdata = dwcmshc_ofdata_to_platdata,
	.ops	= &sdhci_ops,
	.bind	= dwcmshc_bind,
	.probe	= dwcmshc_probe,
	.priv_auto_alloc_size = sizeof(struct sdhci_host),
	.platdata_auto_alloc_size = sizeof(struct dwcmshc_sdhci_plat),
};
