// productorFIFO.c
// Productor que usa mecanismo de comunicacion FIFO
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define ARCHIVO_FIFO "ComunicacionFIFO"
int main(int argc, char *argv[]) {
  int fd;
  // Comprobar el uso correcto del programa
  if (argc != 2) {
    printf("\nproductorFIFO: faltan argumentos (mensaje)");
    printf(
        "\nPruebe: productorFIFO <mensaje>, donde <mensaje> es una cadena de "
        "caracteres.\n");
    exit(-1);
  }
  // Intentar abrir para escritura el cauce FIFO
  if ((fd = open(ARCHIVO_FIFO, O_WRONLY)) < 0) {
    perror("\nError en open");
    exit(-1);
  }
  // Escribir en el cauce FIFO el mensaje introducido como argumento
  if ((write(fd, argv[1], strlen(argv[1]) + 1)) != strlen(argv[1]) + 1) {
    perror("\nError al escribir en el FIFO");
    exit(-1);
  }
  close(fd);
  return 0;
}

