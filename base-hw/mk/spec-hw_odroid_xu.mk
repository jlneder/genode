#
# \brief  Offer build configurations that are specific to base-hw and Odroid XU
# \author Stefan Kalkowski
# \date   2013-11-25
#

# denote wich specs are also fullfilled by this spec
SPECS += hw platform_odroid_xu

# add repository relative paths
REP_INC_DIR += include/exynos5_uart

# set address where to link the text segment at
LD_TEXT_ADDR ?= 0x80000000

# include implied specs
include $(call select_from_repositories,mk/spec-hw.mk)
include $(call select_from_repositories,mk/spec-platform_odroid_xu.mk)
