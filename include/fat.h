/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * R/O (V)FAT 12/16/32 filesystem implementation by Marcus Sundberg
 *
 * 2002-07-28 - rjones@nexus-tech.net - ported to ppcboot v1.1.6
 * 2003-03-10 - kharris@nexus-tech.net - ported to u-boot
 */

#ifndef _FAT_H_
#define _FAT_H_

#include <fs.h>
#include <asm/byteorder.h>
#include <asm/cache.h>

struct disk_partition;

int file_fat_detectfs(void);
int fat_exists(const char *filename);
int fat_size(const char *filename, loff_t *size);
int file_fat_read_at(const char *filename, loff_t pos, void *buffer,
		     loff_t maxsize, loff_t *actread);
int file_fat_read(const char *filename, void *buffer, int maxsize);
int fat_set_blk_dev(struct blk_desc *rbdd, struct disk_partition *info);
int fat_register_device(struct blk_desc *dev_desc, int part_no);

int file_fat_write(const char *filename, void *buf, loff_t offset, loff_t len,
		   loff_t *actwrite);
int fat_read_file(const char *filename, void *buf, loff_t offset, loff_t len,
		  loff_t *actread);
int fat_opendir(const char *filename, struct fs_dir_stream **dirsp);
int fat_readdir(struct fs_dir_stream *dirs, struct fs_dirent **dentp);
void fat_closedir(struct fs_dir_stream *dirs);
int fat_unlink(const char *filename);
int fat_mkdir(const char *dirname);
void fat_close(void);

/**
 * fat_uuid() - get FAT volume ID
 *
 * The FAT volume ID returned in @uuid_str as hexadecimal number in XXXX-XXXX
 * format.
 *
 * @uuid_str:	caller allocated buffer of at least 10 bytes for the volume ID
 * Return:	0 on success
 */
int fat_uuid(char *uuid_str);

#endif /* _FAT_H_ */
