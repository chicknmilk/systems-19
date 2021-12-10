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

int main() {
  mkfifo("pipe1", 0644);
  mkfifo("pipe2", 0644);

  int fd1 = open("pipe1", O_WRONLY);
  int fd2 = open("pipe2", O_RDONLY);

  while (1) {
      
    char buffer[1024];
    printf("Send something to child process: ");
    fgets(buffer, 1024, stdin);

    write(fd1, buffer, strlen(buffer));
    read(fd2, buffer, 1024);

    printf("Child process returned: %s\n", buffer);
  }

  return 0;
}