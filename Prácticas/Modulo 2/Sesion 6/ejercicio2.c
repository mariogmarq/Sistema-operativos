#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** args) {
  if (argc != 4) {
    exit(1);
  }

  if (args[2][0] != '|') exit(1);

  close(STDIN_FILENO);
  fcntl(STDOUT_FILENO, F_DUPFD, STDIN_FILENO);
  execlp(args[1], "", NULL);
  execlp(args[3], "", NULL);
}
