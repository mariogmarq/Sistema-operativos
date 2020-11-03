#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main(int nargs, char** vargs) {
  int fd;
  int wf;
  int rd = 0;
  int contador = 1;
  char bloque[20];
  char buff[80];
  if (nargs > 1) {
    if ((fd = open(vargs[1], S_IRUSR)) < 0) {
      printf("Error opening. Error code %d", fd);
      exit(EXIT_FAILURE);
    }
  } else {
    fd = STDIN_FILENO;
  }
  if ((wf = open("salida.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)) < 0) {
    exit(EXIT_FAILURE);
  }

  while ((rd = read(fd, buff, 80)) > 0) {
    sprintf(bloque, "Bloque %d\n", contador);
    write(wf, bloque, 20);
    write(wf, buff, 80);
    write(wf, "\n", 1);
    contador++;
  }
  if (lseek(wf, 0, SEEK_SET) < 0) {
    printf("F");
  }
  sprintf(bloque, "Hay %d Bloques\n", contador);
  write(wf, bloque, 20);
}
