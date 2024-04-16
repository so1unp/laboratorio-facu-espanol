#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h> // times()
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>

int busywork(void)
{
    struct tms buf;
    for (;;)
    {
        times(&buf);
    }
}

void sighandler()
{
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    id_t pid = (id_t)getpid();
    printf("Child %d (nice %2d):\t%3li\n", pid, getpriority(PRIO_PROCESS, pid), usage.ru_stime.tv_sec + usage.ru_utime.tv_sec);
    exit(EXIT_SUCCESS);
}

void sighandlerparent()
{
}

int main(int argc, char *argv[])
{
    int i;
    int j;
    int id = 1;
    int canthijos = atoi(argv[1]);
    int segejecucion = atoi(argv[2]);
    int prioridad = atoi(argv[3]);
    int hijos[canthijos];

    if (argc != 4)
    {
        perror("Cantidad de argumentos invalido. \n");
    }

    struct sigaction act;
    act.sa_handler = sighandler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    for (i = 0; i < canthijos; i++)
    {
        id = fork();
        if (id == 0)    //cuando es el hijo
        {
            if (prioridad == 1) //si se quiere bajar la prioridad
            {
                setpriority(PRIO_PROCESS, (id_t)getpid(), i);
            }
            sigaction(SIGTERM, &act, NULL);
            sigaction(SIGINT, &act, NULL);
            busywork();
        }
        else
        {
            hijos[i] = id;
        }
    }

    if (segejecucion > 0)
    {
        sleep((unsigned int)segejecucion);
        //mata a todos los hijos
        for (j = 0; j < i; j++)
        {
            kill(hijos[j], SIGTERM);
        }
    }
    else
    {
        //si se quiere ejecutar hasta que se presione ctrl+c
        struct sigaction act_parent;
        act_parent.sa_handler = sighandlerparent;
        sigemptyset(&act_parent.sa_mask);
        act_parent.sa_flags = 0;
        sigaction(SIGINT, &act_parent, NULL);
        pause();
    }
    exit(EXIT_SUCCESS);
