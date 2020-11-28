#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int nargs, char** vargs) {
  if (nargs != 3) exit(1);
  int inicio = atoi(vargs[1]), final = atoi(vargs[2]);
  int mitad = (final + inicio) / 2;
  int fd[2];
  int fd2[2];
  int pid1, pid2;
  int divisible;

  // Creamos primer pipe
  pipe(fd);

  // Primero hijo
  if ((pid1 = fork()) == 0) {
    // Cerramos lectura
    close(fd[0]);

    close(fd2[0]);
    close(fd2[1]);  //!! son del otro hijo

    // bucle
    for (int i = inicio; i < mitad; i++) {
      divisible = 0;
      for (int j = 2; j <= sqrt(i); j++) {
        if (!divisible)
          if (i % j == 0) {
            divisible = 1;
            break;
          }
      }
      if (!divisible) {
        write(fd[1], &i, sizeof(int));  // Escribimos sin formatear
      }
    }
    return 0;
  }

  close(fd[1]);
  // Creamos segundo pipe
  pipe(fd2);

  // Segundo hijo
  if ((pid2 = fork()) == 0) {
    // Cerramos todo el primer pipe
    close(fd[0]);
    close(fd[1]);  //!!
    // Repetimos hijo 1
    close(fd2[0]);

    // bucle
    for (int i = mitad; i <= final; i++) {
      divisible = 0;
      for (int j = 2; j <= sqrt(i); j++) {
        if (!divisible)
          if (i % j == 0) {
            divisible = 1;
            break;
          }
      }
      if (divisible == 0) {
        write(fd2[1], &i, sizeof(int));
      }
    }
    return 0;
  }
  close(fd2[1]);

  // Padre

  int primo;  // !!

  while (1) {
    long num;
    num = read(fd[0], &primo, sizeof(int));
    if (num == 0) break;
    printf("%d  ", primo);
  }

  while (1) {
    long num;
    num = read(fd2[0], &primo, sizeof(int));
    if (num == 0) break;
    printf("%d  ", primo);
  }
}
