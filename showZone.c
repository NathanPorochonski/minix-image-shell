#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include "minix_fs.h"

//Prints one 16 byte row of the zone.
void printRow(char *zonebuf, int i) {

  for (int j = 0; j < 16; j++) {

    if (isprint(zonebuf[i*16+j]) != 0) {
      printf("\t%c", zonebuf[i*16+j]);
    }
    else {
      printf("\t");
    }
  }
  printf("\n");
}

//Prints the ASCII content of the specified zone number to the screen.
void showZone(int fd, int zone) {

  //Reads info from the superblock.
  char *superbuf[128];
  struct minix_super_block *superp = (struct minix_super_block *) superbuf;

  lseek(fd, 1024, SEEK_SET);
  read (fd, superbuf, 1024);
  
  int firstDataZone = superp -> s_firstdatazone;
  int maxZone = superp -> s_nzones + firstDataZone - 1;

  if (zone < firstDataZone || zone > maxZone) {
    printf("\nError: Please enter a correct zone number\n");
  }

  else {

    //Prints column and row headings and ASCII content.
    char *zonebuf = (char *) malloc(1024);

    lseek(fd, 1024 * zone, SEEK_SET);
    read (fd, zonebuf, 1024);

    printf("\n");
    for (int i = 0; i < 10; i++) {
      printf("\t%i", i);
    }
    printf("\ta\tb\tc\td\te\tf\n\n");

    int n = 0;

    for (int i = 0; i < 64; i++) {
      
      int row = n * 10;

      if (row % 100 != 0 || row < 100) {
        printf("%i", row);
        printRow(zonebuf, i);
        n++;
      }
      else {
        if (row > 100) {
          printf("%ia0", row / 100 - 1);
          printRow(zonebuf, i);
          i++;
          printf("%ib0", row / 100 - 1);
          printRow(zonebuf, i);
          i++;
          printf("%ic0", row / 100 - 1);
          printRow(zonebuf, i);
          i++;;
          printf("%id0", row / 100 - 1);
          printRow(zonebuf, i);
          i++;
          printf("%ie0", row / 100 - 1);
          printRow(zonebuf, i);
          i++;
          printf("%if0", row / 100 - 1);
          printRow(zonebuf, i);
        }
        else {
          printf("a0");
          printRow(zonebuf, i);
          i++;
          printf("b0");
          printRow(zonebuf, i);
          i++;
          printf("c0");
          printRow(zonebuf, i);
          i++;
          printf("d0");
          printRow(zonebuf, i);
          i++;
          printf("e0");
          printRow(zonebuf, i);
          i++;
          printf("f0");
          printRow(zonebuf, i);
        }
        if (row < 400) {
          i++;
          printf("%i", row);
          printRow(zonebuf, i);
          n++;
        }
      }
    }
  }
}
