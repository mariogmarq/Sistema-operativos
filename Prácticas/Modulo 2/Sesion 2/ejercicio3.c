#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int tam = 0;
void trabajar(const char* path) {
  struct dirent* file;
  struct stat atributo;
  DIR* directory = opendir(path);
  if (directory == NULL) exit(1);
  while (1) {
    file = readdir(directory);
    if (file == NULL) break;
    if (file->d_name[0] == '.' &&
        (file->d_name[1] == '\0' || file->d_name[1] == '.'))
      continue;
    char* newpath = malloc(1000 * sizeof(char));
    newpath[0] = '\0';
    strcat(newpath, path);
    strcat(newpath, "/");
    strcat(newpath, file->d_name);
    stat(newpath, &atributo);
    printf("%s %lu\n", newpath, atributo.st_ino);
    if (file->d_type == DT_DIR)
      trabajar(newpath);
    else {
      tam += file->d_reclen;
    }
    free(newpath);
  }
}

int main(int nargs, const char** vargs) {
  if (nargs < 2) exit(1);
  const char* pathname = vargs[1];
  trabajar(pathname);
  printf("Tamaño de %d", tam);
}
