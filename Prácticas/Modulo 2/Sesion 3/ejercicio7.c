// Bugged para mas de 2 argumentos

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int nargs, char** vargs) {
  pid_t pid;
  int estado;
  int bg = 0;
  if (nargs == 1) return 1;
  if (strcmp(vargs[nargs - 1], "bg") == 0) bg = 1;

  if ((pid = fork()) == 0) {
    int length = nargs - 1;
    char** args;
    args = malloc(length * sizeof(char*));
    args[length - 1] = NULL;
    for (int i = 1; i < nargs; i++) {
      args[i - 1] = vargs[i];
    }
    if (bg) {
      args[length - 2] = NULL;
      char* x = malloc(100 * sizeof(char));
      x[0] = '\0';
      strcat(x, "bg ");
      strcat(x, vargs[1]);
      execvp(x, args);
      free(x);
    } else {
      execvp(vargs[1], args);
    }
    free(args);
  }
  wait(&estado);
  printf("Proceso terminado con estado %d\n", estado);
}
