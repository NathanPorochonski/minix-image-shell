#include <stdio.h>
#include <stdlib.h> 
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "printHelp.h"
#include "showSuper.h"
#include "traverse.h"
#include "showZone.h"
#include "showFile.h"

/*This program allows users to open a minix imagefile
and extract info from it using various commands.*/
int main () {

  char mount = '0';
  char quit = '0';
  int fd;

  while (quit != '1') {

    char *input = (char *) malloc(100);
    char *arg1 = (char *) malloc(100);
    char *arg2[100];

    //Prompts user to enter command
    if (mount == '1') {
      printf("\n$minix: ");
    } 
    else {
      printf("\n$ ");
    }
    scanf(" %99[^\n]", input);
      
    //Processes input  
    strcpy(arg1, input);
    for (int i = 0; input[i] != '\0'; i++) {
      if (input[i] == ' ') {
        *arg2 = &input[i+1];
        for (int j = 0; j < i; j++) {
          arg1[j] = input[j];
        }
        arg1[i] = '\0';
      }
    }
    
    if (strcmp(arg1, "help") == 0) {
      printHelp();
    }

    else if (strcmp(arg1, "miniumount") == 0) {
      if (mount == '1') {
        fd = close(fd);
        mount = '0';
      }
      else {
        printf("\nError: no image mounted\n");
      }
    }

    else if (strcmp(arg1, "minimount") == 0) {
      if (mount == '1') {
        printf("\nError: image already mounted\n");
      }
      else if (arg2[0] == '\0') {
        printf("\nError: Please enter an imagefile name\n");
      }
      else {
        fd = open(*arg2, O_RDONLY);
        if (fd == -1) {
          printf("\nError: Unable to mount %s\n", *arg2);
        }
        else {
          mount = '1';
        }
      }
    }

    else if (strcmp(arg1, "showsuper") == 0) {
      if (mount == '1') {
        showSuper(fd);
      }
      else {
        printf("\nError: image file must be mounted first\n");
      }
    }

    else if (strcmp(arg1, "traverse") == 0) {
      traverse(fd, *arg2);
    }

    else if (strcmp(arg1, "showzone") == 0) {
      if (mount == '1') {
        if (arg2[0] == '\0') {
          printf("\nError: Please enter a zone number\n");
        }
        else {
          showZone(fd, atoi(*arg2));
        }
      }
      else {
        printf("\nError: image file must be mounted first\n");
      }
    }

    else if (strcmp(arg1, "showfile") == 0) {
      if (mount == '1') {
        if (arg2[0] == '\0') {
          printf("\nError: Please enter a filename\n");
        }
        else {
          showFile(fd, *arg2);
        }
      }
      else {
        printf("\nError: image file must be mounted first\n");
      }
    }

    else if (strcmp(arg1, "quit") == 0) {
      quit = '1';
      fd = close(fd);
    }
    else {
      printf("\nError: incorrect command. Type 'help' to view list of commands\n");
    }

    //Resets arg2 buffer for next command
    memset(arg2,0,sizeof(arg2));
  }

}
