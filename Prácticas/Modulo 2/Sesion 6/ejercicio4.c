#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  struct flock cerrojo;
  int fd;
  cerrojo.l_len = 0;
  cerrojo.l_start = 0;
  cerrojo.l_type = F_WRLCK;
  cerrojo.l_whence = SEEK_SET;
  // Ponemos el cerrojo en el archivo
  printf("procedo a cerrar\n");
  fd = open(argv[1], O_CREAT | O_RDWR);
  printf("FD: %d\n", fd);
  if (fcntl(fd, F_SETLK, &cerrojo) == -1) {
    printf("ta ocupado");
    return 1;
  } else {
    printf("toy dentro");
  }
  sleep(10);
  return 0;
}
