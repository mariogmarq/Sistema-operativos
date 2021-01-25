/*
 * Para la realizacion de este ejercicio usaremos la funcion nftw que ejecutara
 * la funcion data por nosotros de forma recursiva, asi toda la logica queda en
 * la funcion trabajar y el main se reduce en la llamada a esta funcion
 */

#include <dirent.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int tam = 0;
int trabajar(const char *path, const struct stat *statbuf, int typeflag,
             struct FTW *ftwbuf) {
  // Comprobamos que es un archivo regular
  if (typeflag == FTW_F) {
    // Comprobamos el tamanio
    if (statbuf->st_size >= tam) {
      printf("Archivo: %s con propietario: %d\n", path, statbuf->st_uid);
    }
  }
  return 0;
}

int main(int nargs, const char **vargs) {
  // Parseamos argumentos
  if (nargs < 2)
    exit(1);
  tam = atoi(vargs[1]);

  const char *pathname = ".";
  if (nftw(pathname, trabajar, 10, FTW_D) != 0)
    exit(1);
}
