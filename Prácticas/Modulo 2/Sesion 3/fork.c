#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int nargs, char** vargs) {
  if (nargs != 2) return 1;
  int num = atoi(vargs[1]);
  pid_t pid = fork();
  if (pid < 0) return 2;
  if (pid == 0) printf("Es par: %d\n", num % 2 == 0);
  if (pid > 0) printf("Divisible entre 4: %d\n", num % 4 == 0);
}
