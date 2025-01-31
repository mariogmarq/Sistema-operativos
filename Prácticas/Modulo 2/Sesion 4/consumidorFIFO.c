// consumidorFIFO.c
// Consumidor que usa mecanismo de comunicacion FIFO
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define ARCHIVO_FIFO "ComunicacionFIFO"
int main(void) {
  int fd;
  char buffer[80];  // Almacenamiento del mensaje del cliente
  int leidos;
  // Crear el cauce con nombre (FIFO) si no existe
  umask(0);
  mknod(ARCHIVO_FIFO, S_IFIFO | 0666, 0);
  // también vale: mkfifo(ARCHIVO_FIFO,0666);
  // Abrir el cauce para lectura-escritura
  if ((fd = open(ARCHIVO_FIFO, O_RDWR)) < 0) {
    perror("open");
    exit(-1);
  }
  // Aceptar datos a consumir hasta que se envíe la cadena fin
  while (1) {
    leidos = read(fd, buffer, 80);
    if (strcmp(buffer, "fin") == 0) {
      close(fd);
      return 0;
    }
    printf("\nMensaje recibido: %s\n", buffer);
  }
  return 0;
}
