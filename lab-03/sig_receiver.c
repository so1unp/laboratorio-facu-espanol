#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void sighandler(int signum)
{
<<<<<<< HEAD
    printf("Señal: %d, Descripcion: %s \n", signum, strsignal(signum));
=======
    printf("Senial: %d, Descripcion: %s \n", signum, strsignal(signum));
>>>>>>> a574e75885be2b172c320eea9925a8755c613775
}

int main(void)
{
    struct sigaction act;
    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    printf("PID num %d \n", getpid());
    int i;
    for (i = 0; i < _NSIG; i++)
    {
        sigaction(i, &act, NULL);
    }
    while (1)
    {
        pause();
    }
    exit(EXIT_SUCCESS);
}
