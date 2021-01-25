/**
 * La manera de la que se ha enfocado el programa esta escrita en comentarios a
 * lo largo del codigo. Aun asi el enfoque ha sido el de abrir el directorio de
 * trabajo ( "." ) y leer archivos de el
 */
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define ARCHIVO_FIFO "archivo.fifo"

int main() {
  // Creamos el archivo fifo
  // Ponemos umask a 0 para poder crear bien el archivo fifo
  umask(0);
  int fifo;
  int pid;
  mknod(ARCHIVO_FIFO, S_IFIFO | 0666, 0);
  if ((fifo = open(ARCHIVO_FIFO, O_RDWR)) < 0) {
    printf("Error en archivo fifo\n");
    return 1;
  }

  // Redirigimos stdin
  dup2(fifo, STDIN_FILENO);

  // Creamos el hijo
  if ((pid = fork()) == 0) {
    // Ahora ejecutamos el programa
    // doy por hecho que esta compilado con el nombre a.out
    execl("a.out", "a.out", "1", NULL);
  }

  // Generamos el numero aleatorio
  // Nota: no hemos inicializado la semilla asi que es muy probable de que
  // siempre genere el mismo numero
  int random = (rand() % 10) + 1;

  // Abrimos el directorio de trabajo
  DIR *directory = opendir(".");
  struct dirent *file;
  int encauce;
  char filename[257];

  // Lo leemos hasta que se acabe o hasta que superemos las entradas aleatorias
  while (random-- != 0) {
    file = readdir(directory);
    if (file == NULL)
      break;

    // Agregamos \n al final de nuestro nombre
    sprintf(filename, "%s\n", file->d_name);

    // Escribimos en el cauce
    write(fifo, filename, strlen(filename) + 1);

    sleep(1);
  }

  // Finalmente escribimos la cadena vacia
  write(fifo, "\n", 2);
  close(fifo);
}
