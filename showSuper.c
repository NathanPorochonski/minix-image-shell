#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "minix_fs.h"

//Prints info of the superblock to the screen.
void showSuper(int fd) {

  char *superbuf[128];
  struct minix_super_block *p = (struct minix_super_block *) superbuf;

  lseek(fd, 1024, SEEK_SET);
  read (fd, superbuf, 1024);
  
  printf("\nnumber of inodes: \t %d\n", p -> s_ninodes);
  printf("number of zones: \t %d\n", p -> s_nzones);
  printf("number of imap_blocks: \t %d\n", p -> s_imap_blocks);
  printf("number of zmap_blocks: \t %d\n", p -> s_zmap_blocks);
  printf("first data zone: \t %d\n", p -> s_firstdatazone);
  printf("log zone size: \t %d\n", p -> s_log_zone_size);
  printf("max size: \t %d\n", p -> s_max_size);
  printf("magic: \t %d\n", p -> s_magic);
  printf("state: \t %d\n", p -> s_state);
  printf("zones: \t %d\n", p -> s_zones);

}
