#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int nargs, const char** vargs) {
  if (nargs < 3) exit(1);
  const char* pathname = vargs[1];
  long int num = strtol(vargs[2], NULL, 8);
  printf("%lo\n", num);
  num = num & 0777;
  printf("%lo", num);

  DIR* myDir = opendir(pathname);
  if (myDir == NULL) exit(1);

  int reading = 1;

  struct stat atributos;
  struct stat oldstat;
  char* filename = malloc(1000 * sizeof(char));
  do {
    struct dirent* file = readdir(myDir);
    if (file != NULL) {
      filename[0] = '\0';
      strcat(filename, pathname);
      strcat(filename, "/");
      strcat(filename, file->d_name);
      if (stat(filename, &oldstat) >= 0) {
        if (chmod(filename, num) >= 0) {
          stat(filename, &atributos);
          printf("%s : %o %o\n", file->d_name, oldstat.st_mode,
                 atributos.st_mode);
        } else {
          printf("error %s: %d %o", file->d_name, chmod(filename, num),
                 atributos.st_mode);
        }
      }
    } else {
      reading = 0;
    }
  } while (reading);
  free(filename);
}
