#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
  mkfifo("pipe1", 0644);
  mkfifo("pipe2", 0644);

  int fd1 = open("pipe1", O_RDONLY);
  int fd2 = open("pipe2", O_WRONLY);

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