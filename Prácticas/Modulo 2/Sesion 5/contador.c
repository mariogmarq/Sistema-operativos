#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int contadores[19];

static void sig_USR_hdlr(int sigNum) {
  printf("Señal del tipo %d recibida %d veces\n", sigNum, ++contadores[sigNum]);
}

int main() {
  int sig = 0;
  for (int i = 0; i < 19; i++) {
    contadores[i] = 0;
  }
  struct sigaction sig_USR;
  sig_USR.sa_handler = sig_USR_hdlr;
  sigemptyset(&sig_USR.sa_mask);
  sig_USR.sa_flags = SA_RESTART;
  for (int i = 0; i < 19; i++) {
    if ((sig = sigaction(i, &sig_USR, NULL)) == -1)
      printf("La señal %d no se puede manejar\n", i);
  }
  for (;;) {
  }
}
