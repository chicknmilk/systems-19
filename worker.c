#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>

int toupper(int c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 'A';
  }
  return c;
}

int main() {

  int fd1 = open("pipe1", O_WRONLY);
  int fd2 = open("pipe2", O_RDONLY);

  while (1) {

    char buffer[1024];
    read(fd1, buffer, 1024);
    int i = 0;

    while (buffer[i]) {
      if (buffer[i] == '\n') {
        buffer[i] = '\0';
        break;
      }

      buffer[i] = toupper(buffer[i]);
      i++;
    }

    printf("returning processed string to parent process\n");
    write(fd2, buffer, strlen(buffer));
  }

  return 0;
}