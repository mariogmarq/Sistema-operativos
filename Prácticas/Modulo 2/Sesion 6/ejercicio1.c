#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** args) {
  if (argc != 4) {
    exit(1);
  }

  int direccion;
  if (args[2][0] == '<')
    direccion = 0;
  else if (args[2][0] == '>')
    direccion = 1;
  else
    exit(1);

  int fd = open(args[1], O_RDWR | O_CREAT);
  if (direccion) {
    char bufer[256];
    int leido = read(fd, bufer, 256);
    write(0, bufer, leido);
    execlp(args[3], "", NULL);
  } else {
    close(STDOUT_FILENO);
    if (fcntl(fd, F_DUPFD, 1) == -1) exit(1);
    if (execlp(args[3], "", NULL) < 0) {
      perror("El execl peta");
    }
  }
}
