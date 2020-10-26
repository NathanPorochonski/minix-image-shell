#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include "printPerms.h"
#include "minix_fs.h"

/*Prints the content of the root directory to the screen. If flag "-f" is provided,
all detailed information is shown, including the file type, 9 permission bits, user ID, file size (in bytes), last modified date (with year), and the file name.*/
void traverse(int fd, char *flag) {

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

  //If flag is not provided.
  if (flag == NULL || flag[0] == '\0') {
  
    for (int i = 0; i < 32; i++) {

      char *filebuf[128];

      //Reads file info into a buffer.
      lseek(fd, rootZoneStart + i*32, SEEK_SET);
      struct minix_dir_entry *filep = (struct minix_dir_entry *) filebuf;
      read (fd, filebuf, 32);
      
      //Excludes "." and ".." and prints each filename.
      if (filep -> inode != 0 && filep -> inode != 1) {
        printf("\n%s", filep -> name);
      }
    }
    printf("\n");
  }

  //If flag "-l" is provided.
  else if (strcmp(flag, "-l") == 0) {

    printf("\n");
    for (int i = 0; i < 32; i++) {

      char *filebuf[128];
      char *inodebuf[32];
      char *datebuf[128];
      struct minix_dir_entry *filep = (struct minix_dir_entry *) filebuf;
      struct minix_inode *inodep = (struct minix_inode *) inodebuf;

      //Reads file info into a buffer.
      lseek(fd, rootZoneStart + i*32, SEEK_SET);
      read (fd, filebuf, 32);

      int inode = filep -> inode;

      //Reads inode info into a buffer
      lseek(fd, inodeStart + (inode-1)*32, SEEK_SET);
      read (fd, inodebuf, 32);

      //Gets date info of the file.
      time_t sec = inodep -> i_time;
      char *time = (char *) malloc(24);
      time = ctime(&sec);

      char *year = (char *) malloc(4);
      char *date = (char *) malloc(6);
      year = &time[20];

      for (int i = 4; i < 10; i++) {
        date[i-4] = time[i];
      }
      time[strlen(time)-1]='\0';

      //Prints each filename and its details to the screen.
      if (filep -> inode != 0 && filep -> inode != 1) {
        printPerms(inodep -> i_mode);
        printf("%i %i %s %s %s\n", inodep -> i_uid, inodep -> i_size, date, year, filep -> name);
      }
    }
  }

  else {
    printf("\nError: Incorrect flag specified.\n");
  }
}
