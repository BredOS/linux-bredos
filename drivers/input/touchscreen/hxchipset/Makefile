obj-$(CONFIG_TOUCHSCREEN_HIMAX_COMMON) += himax_tp.o

subdir-ccflags-y += -Wno-unused-label -Wno-unused-variable -Wno-unused-function

himax_tp-y := himax_common.o himax_platform.o 
himax_tp-$(CONFIG_TOUCHSCREEN_HIMAX_INCELL) += himax_ic_incell_core.o
himax_tp-$(CONFIG_TOUCHSCREEN_HIMAX_IC_HX83121) += himax_ic_HX83121.o
himax_tp-$(CONFIG_TOUCHSCREEN_HIMAX_INSPECT) += himax_inspection.o
himax_tp-$(CONFIG_TOUCHSCREEN_HIMAX_DEBUG) += himax_debug.o
#obj-y	+= himax_inspection.o
#obj-y	+= himax_ic_HX83121.o
#obj-y	+= himax_platform.o
#obj-y	+= himax_debug.o
#obj-y	+= himax_ic_incell_core.o
#obj-y	+= himax_common.o
