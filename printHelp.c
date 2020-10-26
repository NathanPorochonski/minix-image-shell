#include <stdio.h>

//Prints available commands and their actions to the screen
void printHelp() {
  printf("\nminimount argument: mount a local minix disk, where 'argument' is a minix image file, e.g., imagefile.img\n");
  printf("miniumount: umount the mounted minix disk\n");
  printf("showsuper: list the information of the super block\n");
  printf("traverse [-l]: list the content in the root directory (When switch -l is turned on, all detailed information is shown)\n");
  printf("showzone [zone number]: show the ASCII content of the specified zone number\n");
  printf("showfile [filename]: show the content of the target file (in the hex dump) located in the root directory\n");
  printf("quit: quit the minix shell\n");
}