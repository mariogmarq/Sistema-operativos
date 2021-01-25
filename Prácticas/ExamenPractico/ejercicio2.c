/**
 * Para este ejercicio leeremos de la entrada estandar sin formato con read, la
 * manera que se le pasara la informacion al hijo sera mediante el buffer ya que
 * al hacer fork el hijo obtendra una copia de este y como no hace falta mas
 * comunicacion no habra falta de un pipe.
 *
 * El padre leera hasta que solo lea '\n' que sera el string vacio, con ellos
 * esperara a los hijos a acabar
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  // Empezamos a leer
  char buffer[257];
  int leidos;
  int hijos_vivos = 0;
  int pid;

  while (1) {
    // Limpiamos el buffer, hago esto porque he tenido problemas de cadenas que
    // se concatenan
    for (int i = 0; i < 257; i++)
      buffer[i] = '\0';

    leidos = read(STDIN_FILENO, buffer, 257);
    // Comprobamos que la cadena no es vacia
    if (leidos <= 1) {
      break;
    }

    // No tenemos una cadena vacia
    // Quitamos el caracter de salto de linea
    buffer[strlen(buffer) - 1] = '\0';
    // Creamos un hijo, que tiene en buffer el nombre del archivo
    if ((pid = fork()) == 0) {
      // Estamos en el hijo
      // Abrimos el archivo
      int fd;
      int espacios_blancos = 0;
      char bufferhijo[1];
      fd = open(buffer, O_RDONLY);
      if (fd < 0) {
        // El archivo no existe
        printf("El archivo %s no se puede abrir\n", buffer);
        return 0;
      }
      // Leemos
      while ((leidos = read(fd, bufferhijo, 1)) != 0) {
        if (bufferhijo[0] == ' ')
          espacios_blancos++;
      }
      // Se acaba el hijo
      printf("el archivo %s tiene %d espacios\n", buffer, espacios_blancos);
      return 0;
    } else {
      // Estamos en el padre
      ++hijos_vivos;
    }
  }

  // Hemos leido la cadena vacia, procedemos a esperar a los hijos
  while (hijos_vivos) {
    wait(NULL);
    --hijos_vivos;
  }
}
