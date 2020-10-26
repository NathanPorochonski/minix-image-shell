#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "minix_fs.h"

/*Prints the content of the target file (in the hex dump) located in the 
root directory to the screen.*/
void showFile(int fd, char *filename){

  //Reads info from the superblock.
  char *superbuf[128];
  struct minix_super_block *superp = (struct minix_super_block *) superbuf;

  lseek(fd, 1024, SEEK_SET);
  read (fd, superbuf, 1024);

  int imapBlocks = superp -> s_imap_blocks;
  int zmapBlocks = superp -> s_zmap_blocks;
  int firstDataZone = superp -> s_firstdatazone;
  int rootZoneStart = 1024 * firstDataZone;
  int inodeStart = 2048 + 1024*(imapBlocks + zmapBlocks);

  int blockOffset = 0;
  int fileBlocks = 0;
  char found = '0';

  //Searches for the filename in the root directory
  for (int i = 0; i < 32 && found == '0'; i++) {

    char *filebuf[128];
    char *inodebuf[32];
    struct minix_dir_entry *filep = (struct minix_dir_entry *) filebuf;
    struct minix_inode *inodep = (struct minix_inode *) inodebuf;

    //Reads file info into a buffer.
    lseek(fd, rootZoneStart + i*32, SEEK_SET);
    read (fd, filebuf, 32);

    int inode = filep -> inode;

    //Reads inode info into a buffer.
    lseek(fd, inodeStart + (inode-1)*32, SEEK_SET);
    read (fd, inodebuf, 32);

    if (i > 1) {
      fileBlocks = (inodep -> i_size) / 512 + 1;
    }
    else {
      fileBlocks = 1;
    }

    if (strcmp(filename, filep -> name) == 0) {
      found = '1';
    }
    else {
      blockOffset = blockOffset + fileBlocks;
    }
  }

  //Prints the content of the file or an error if not found
  if (found != '1') {
    printf("\nError: file not in root directory\n");
  }
  else {

    char *content = (char *) malloc(fileBlocks*512);
    lseek(fd, rootZoneStart + blockOffset*512, SEEK_SET);
    read(fd, content, fileBlocks*512);

    for (int i = 0; i < fileBlocks*512 / 16; i++) {
      printf("\n");
      for (int j = 0; j < 16; j++) {
        printf("%x\t", content[i*16+j]);
      }
    }
    printf("\n");
  }
}
