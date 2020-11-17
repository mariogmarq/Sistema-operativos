#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pidhijos[] = {0, 0, 0, 0, 0};
  int numHijos = 5;

  for (int i = 0; i < numHijos; i++) {
    pid_t pid;
    if ((pid = fork()) < 1) {
      printf("Soy el hijo %d\n", getpid());
      return 0;
    }
    pidhijos[i] = pid;
  }
  while (numHijos) {
    printf("Ha acabado mi hijo con PID %d\n", wait(NULL));
    printf("Quedan %d hijos\n", --numHijos);
  }
}
