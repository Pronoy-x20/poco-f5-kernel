# SPDX-License-Identifier: GPL-2.0
dtstree	:= $(srctree)/$(src)

vendor  := $(dtstree)/vendor
ifeq "$(wildcard $(vendor)/Makefile)" ""
# subdir-y += actions
# subdir-y += allwinner
# subdir-y += altera
# subdir-y += amazon
# subdir-y += amd
# subdir-y += amlogic
# subdir-y += apm
# subdir-y += arm
# subdir-y += bitmain
# subdir-y += broadcom
# subdir-y += cavium
# subdir-y += exynos
# subdir-y += freescale
# subdir-y += hisilicon
# subdir-y += intel
# subdir-y += lg
# subdir-y += marvell
# subdir-y += mediatek
# subdir-y += microchip
# subdir-y += nvidia
subdir-y += qcom
# subdir-y += realtek
# subdir-y += renesas
# subdir-y += rockchip
# subdir-y += socionext
# subdir-y += sprd
# subdir-y += synaptics
# subdir-y += ti
# subdir-y += toshiba
# subdir-y += xilinx
# subdir-y += zte


else
	subdir-y += vendor
endif
