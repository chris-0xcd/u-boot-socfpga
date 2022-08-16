/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2017, Intel Corporation
 */
#ifndef __CONFIG_TERASIC_DE10_H__
#define __CONFIG_TERASIC_DE10_H__

#include <asm/arch/base_addr_ac5.h>

/* Memory configurations */
#define PHYS_SDRAM_1_SIZE		0x40000000	/* 1GiB */

/* Booting Linux */
#define CONFIG_BOOTFILE		"fitImage"
#define CONFIG_BOOTARGS		"console=ttyS0," __stringify(CONFIG_BAUDRATE) " $v loop.max_part=8 mem=511M memmap=513M$511M"
#define CONFIG_BOOTCOMMAND	"mw 0xff709004 0x800; run mmcload; run mmcboot"

/* Extra Environment */
#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=" __stringify(CONFIG_SYS_LOAD_ADDR) "\0" \
	"bootimage=/linux/zImage_dtb\0" \
	"fdt_addr=100\0" \
	"fpgadata=0x02000000\0" \
	"core=menu.rbf\0" \
	"fpgacheck=if mt 0x1FFFFF08 0xBEEFB001;then mw 0x1FFFFF08 0;if mt 0x1FFFF000 0x87654321;then mw 0x1FFFF000 0;env import -t 0x1FFFF004;run fpgaload;fi;else run fpgaload;fi\0" \
	"fpgaload=load mmc 0:$mmc_boot $fpgadata $core;fpga load 0 $fpgadata $filesize;bridge enable;mw 0x1FFFF000 0;mw 0xFFD05054 0\0" \
	"scrtest=if test -e mmc 0:$mmc_boot /linux/u-boot.txt;then load mmc 0:$mmc_boot $loadaddr /linux/u-boot.txt;env import -t $loadaddr;fi\0" \
	"bootm $loadaddr - $fdt_addr\0" \
	"mmc_boot=" __stringify(CONFIG_SYS_MMCSD_FS_BOOT_PARTITION) "\0" \
	"mmcroot=/dev/mmcblk0p" __stringify(CONFIG_SYS_MMCSD_FS_BOOT_PARTITION) "\0" \
	"v=loglevel=4\0" \
	"mmcboot=setenv bootargs " CONFIG_BOOTARGS " root=$mmcroot loop=linux/linux.img ro rootwait;" "bootz $loadaddr - $fdt_addr\0" \
	"mmcload=mmc rescan;" \
		"run fpgacheck;" \
		"run scrtest;" \
		"load mmc 0:$mmc_boot $loadaddr $bootimage;" \
		"setexpr.l fdt_addr $loadaddr + 0x2C;" \
		"setexpr.l fdt_addr *$fdt_addr + $loadaddr\0"

/* The rest of the configuration is shared */
#include <configs/socfpga_common.h>

#endif	/* __CONFIG_TERASIC_DE10_H__ */
