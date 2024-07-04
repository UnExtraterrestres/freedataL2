/* 
 * l'option -D_DEFAULT_SOURCE est nécessaire avec l'option -std=c99 (man 7 feature_test_macros )
 * 
 * gcc -Wall -std=c99 -D_DEFAULT_SOURCE

 * ou #define _DEFAULT_SOURCE // avant l'inclusion des fichiers d'entête système
 */

#define _DEFAULT_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc,char *argv[]) {
  sigset_t ens1;
  /* Construction de l'ensemble ens1 = {SIGINT, SIGQUIT, SIGUSR1} */
  sigemptyset(&ens1);
  sigaddset(&ens1, SIGINT);
  sigaddset(&ens1, SIGQUIT);
  sigaddset(&ens1, SIGUSR1);
  /* Installation du masque ens1 */
  sigprocmask(SIG_SETMASK, &ens1, NULL);
  
  /* Le processus s'envoie 2 fois le signal SIGINT et une fois SIGUSR1 */
  raise(SIGINT);
  kill(getpid(), SIGINT);
  kill(getpid(), SIGUSR1);
  /* Extraction des signaux pendants masqués */
  sigset_t ens2;
  sigpending(&ens2);
  /* Impression de la liste des signaux pendants masqués */
  fprintf(stderr,"Signaux pendants masqués : ");
  for (int sig = 1; sig <= SIGRTMAX; ++sig){
    if (sigismember(&ens2, sig))
      fprintf(stderr,"%d ", sig);
  }
  fprintf(stderr, "\n");
  sleep(5);
  sigemptyset(&ens1);
  printf("Deblocage de tous les signaux\n");
  sigprocmask(SIG_SETMASK, &ens1, NULL);
  printf("Fin du processus\n"); //ne s'exécute pas car un signal qui termine le processus est délivré
  return EXIT_SUCCESS;
}

/*
Exécution : 
$ ./signaux_pendants
Signaux pendants masqués : 2 10
^C^C^C^C^\^\^\Deblocage de tous les signaux

$ echo $?
130
$

*/

