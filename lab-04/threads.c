#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int cantSegundosMax;

void *sleep_thread(void *p)
{
    long id = (long)p;
    int dormir = rand() % (cantSegundosMax + 1);
    printf("Hilo %ld: dormire %d\n", id, dormir);
    sleep(dormir);
    pthread_exit((void *)(intptr_t) dormir);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Error en la cantidad de argumentos\n");
        exit(EXIT_FAILURE);
    }
    int cantHilos = atoi(argv[1]);
    long i;
    cantSegundosMax = atoi(argv[2]);
    pthread_t hilos[cantHilos];
    for (i = 0; i < cantHilos; i++)
    {
        pthread_t h;
        pthread_create(&h, NULL, sleep_thread, (void *)i);
        hilos[i] = h;
    }

    for (i = 0; i < cantHilos; i++)
    {
        void *durmio;
        pthread_join(hilos[i], &durmio);

        printf("Hilo %ld: termino: %ld\n", i, (long)durmio);
        //printf("Hilo %ld: termino\n", hilos[i]);
    }
    //pthread_exit(0);
    //return 0;
    exit(EXIT_SUCCESS);
}
