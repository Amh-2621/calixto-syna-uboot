ifdef CONFIG_VIDEO_SYNA

PLATFORM_CPPFLAGS += -DCONFIG_FASTLOGO
PLATFORM_CPPFLAGS += -DCONFIG_TRUSTZONE
PLATFORM_CPPFLAGS += -DCONFIG_MV_AMP_TEE_ENABLE
PLATFORM_CPPFLAGS += -DVPP_ENABLE_TZ_MALLOC_MEM_ALLOCATION

PLATFORM_CPPFLAGS += -DVPP_SUS_RES -DPE_3D_FMT_CONVERT -DPE_3D_BD
PLATFORM_CPPFLAGS += -DBERLIN -DVPP_IN_TRUST_ZONE
PLATFORM_CPPFLAGS += -DHDMI_HW_EDDC_SUPPORT

PLATFORM_CPPFLAGS += -DVPP_ENABLE_INTERNAL_MEM_MGR

PLATFORM_CPPFLAGS += -DVPP_ENABLE_FLUSH_CACHE

PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/include
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/vpp_ca/include
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/vpp_ca/thinvpp_ca
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/vpp_ca/thinvpp_ca/include
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/vpp_ca/thinvpp_ca/osal/include
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/vpp_ca/thinvpp_ca/common/include
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/vpp_ca/thinvpp_ca/ca/include
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/vpp_ca/avpll/
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/tz
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/utils
PLATFORM_CPPFLAGS += -I$(srctree)/include/linux
PLATFORM_CPPFLAGS += -I$(srctree)/../../common/inc
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/lcdc/include
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/dhub/
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/dhub/myna2/
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/dsi
PLATFORM_CPPFLAGS += -I$(srctree)/drivers/video
PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/bridge/

PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/panel/$(CONFIG_PANEL_CFG)/

ifneq ($(filter y, $(CONFIG_TARGET_DOLPHIN) $(CONFIG_TARGET_PLATYPUS)), )
    PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/vsxxx
    PLATFORM_CPPFLAGS += -DLOGO_SRC_FMT=0
    PLATFORM_CPPFLAGS += -DCONFIG_OPTEE -DCONFIG_GENX_ENABLE

    #source files specific to TA
    obj-y += vpp_ca/thinvpp_ca/ca/source/vpp_api_tz.o
    obj-y += vpp_ca/thinvpp_ca/ca/source/tee_ca_vpp_optee.o
    obj-y += vpp_ca/thinvpp_ca/vbuf.o
    obj-y += vpp_ca/thinvpp_ca/vpp_cfg.o
    obj-y += vpp_ca/avpll/avpll.o
    obj-y += vsxxx/vpp_display.o
    obj-y += hal_vpp_tz.o
endif

ifdef CONFIG_TARGET_DOLPHIN
    PLATFORM_CPPFLAGS += -I$(srctree)/../common/inc/chip/dolphin/A0
    PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/vpp_ca/avpll/dolphin/
    obj-y += vpp_ca/avpll/dolphin/diag_pll.o
endif

ifdef CONFIG_TARGET_PLATYPUS
    PLATFORM_CPPFLAGS += -I$(srctree)/../common/inc/chip/platypus/A0
    PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/vpp_ca/avpll/platypus/
    obj-y += vpp_ca/avpll/platypus/diag_pll.o
endif

ifdef CONFIG_TARGET_MYNA2
    PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/vpp_ca/avpll/myna2/
    PLATFORM_CPPFLAGS += -I$(srctree)/arch/arm/mach-synaptics/drivers/video/asxxx
    PLATFORM_CPPFLAGS += -I$(srctree)/../common/inc/chip/myna2/A0
    B_CHIP_CFLAGS += -DGEN_3
    PLATFORM_CPPFLAGS += -DCONFIG_GENX_ENABLE
    PLATFORM_CPPFLAGS += -DLOGO_SRC_FMT=3

    obj-y += lcdc/source/syna_lcdc_dev.o
    obj-y += lcdc/source/syna_lcdc_dlr.o
    obj-y += dhub/bcmbuf.o
    obj-y += dhub/hal_dhub.o
    obj-y += dhub/myna2/avio_dhub_cfg.o
    obj-y += vpp_ca/avpll/myna2/avpll.o
    obj-y += dsi/dsih_api.o
    obj-y += dsi/dsih_core.o
    obj-y += dsi/dsih_dphy.o
    obj-y += dsi/dsih_hal.o
    obj-y += dsi/dphy_wrap.o
    obj-y += dsi/dsih_displays.o
    obj-y += vpp_ca/avpll/myna2/diag_pll.o
    obj-y += asxxx/lcdc_display.o
    obj-y += hal_vpp_ntz.o
    obj-$(CONFIG_SYNA_DRM_BRIDGE_LT9611) += bridge/lt9611.o
endif

PLATFORM_CPPFLAGS += $(B_CHIP_CFLAGS)

obj-y += vpp_ca/thinvpp_ca/osal/source/OSAL_api.o
obj-y += hal_vpp_wrap.o
obj-y += load_logo.o
obj-y += vpp_api.o
obj-y += fb.o
obj-$(CONFIG_SYNA_WSPANEL_1080P) += panel/waveshare/panel-waveshare-dsi.o

endif
