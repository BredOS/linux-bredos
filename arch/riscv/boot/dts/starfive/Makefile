# SPDX-License-Identifier: GPL-2.0
# Enables support for device-tree overlays
DTC_FLAGS_jh7100-beaglev-starlight := -@
DTC_FLAGS_jh7100-starfive-visionfive-v1 := -@
DTC_FLAGS_jh7110-starfive-visionfive-2-v1.2a := -@
DTC_FLAGS_jh7110-starfive-visionfive-2-v1.3b := -@
DTC_FLAGS_jh7110-evb := -@

dtb-$(CONFIG_ARCH_STARFIVE) += jh7100-beaglev-starlight.dtb
dtb-$(CONFIG_ARCH_STARFIVE) += jh7100-starfive-visionfive-v1.dtb

dtb-$(CONFIG_ARCH_STARFIVE) += jh7110-milkv-mars.dtb
dtb-$(CONFIG_ARCH_STARFIVE) += jh7110-pine64-star64.dtb
dtb-$(CONFIG_ARCH_STARFIVE) += jh7110-orangepi-rv.dtb

subdir-y += vf2-overlay
dtb-$(CONFIG_ARCH_STARFIVE) += jh7110-starfive-visionfive-2-v1.2a.dtb
dtb-$(CONFIG_ARCH_STARFIVE) += jh7110-starfive-visionfive-2-v1.3b.dtb	\
			       jh7110-starfive-visionfive-2-ac108.dtb	\
			       jh7110-starfive-visionfive-2-amp.dtb	\
			       jh7110-starfive-visionfive-2-tdm.dtb	\
			       jh7110-starfive-visionfive-2-wm8960.dtb


