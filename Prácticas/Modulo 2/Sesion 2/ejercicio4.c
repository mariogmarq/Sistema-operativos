#include <dirent.h>
#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int tam = 0;
int trabajar(const char* path, const struct stat* statbuf, int typeflag,
             struct FTW* ftwbuf) {
  DIR* directory = opendir(path);
  if (directory == NULL) return 0;
  struct dirent* file;
  struct stat atributo;
  while (1) {
    file = readdir(directory);
    if (file == NULL) break;
    if (file->d_name[0] == '.' &&
        (file->d_name[1] == '\0' || file->d_name[1] == '.'))
      continue;
    stat(file->d_name, &atributo);
    printf("%s %lu\n", file->d_name, atributo.st_ino);
    tam += file->d_reclen;
  }
  return 0;
}

int main(int nargs, const char** vargs) {
  if (nargs < 2) exit(1);
  const char* pathname = vargs[1];
  if (nftw(pathname, trabajar, 10, FTW_D) != 0) exit(1);
  printf("Tamaño de %d", tam);
}
