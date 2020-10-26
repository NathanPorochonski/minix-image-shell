#include <stdio.h>

/*Takes an inode mode field and checks whether it is a file or directory
and checks its permissions for the owner, group, and others. Prints
the information to the screen*/
void printPerms(int mode) {

  if ((mode & 0040000) != 0) {
    printf("d");
  }
  else {
    printf("-");
  }

  if ((mode & 00400) != 0) {
    printf("r");
  }
  else {
    printf("-");
  }

  if ((mode & 00200) != 0) {
    printf("w");
  }
  else {
    printf("-");
  }

  if ((mode & 00100) != 0) {
    printf("x");
  }
  else {
    printf("-");
  }

  if ((mode & 00040) != 0) {
    printf("r");
  }
  else {
    printf("-");
  }

  if ((mode & 00020) != 0) {
    printf("w");
  }
  else {
    printf("-");
  }

  if ((mode & 00010) != 0) {
    printf("x");
  }
  else {
    printf("-");
  }

  if ((mode & 00004) != 0) {
    printf("r");
  }
  else {
    printf("-");
  }

  if ((mode & 00002) != 0) {
    printf("w");
  }
  else {
    printf("-");
  }

  if ((mode & 00001) != 0) {
    printf("x ");
  }
  else {
    printf("- ");
  }
}