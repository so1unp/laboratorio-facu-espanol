#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Número de parámetros inválido");
        exit(EXIT_FAILURE);
    }
    int signum = atoi(argv[1]);
    int pid = atoi(argv[2]);
    kill(pid, signum);
    exit(EXIT_SUCCESS);
}