#include <signal.h>
#include <stdio.h>
int main() {
  sigset_t new_mask;
  /* inicializar la nueva mascara de señales */
  sigemptyset(&new_mask);
  for (int i = 0; i < 19; i++) {
    if (i != SIGUSR1) sigaddset(&new_mask, i);
  }
  /*esperar a SIGUSR1 */
  sigsuspend(&new_mask);
}
