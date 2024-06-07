#include <stdio.h>
#include <stdlib.h>

#define PAGINA 4

#define VIRTUAL (64 / PAGINA) // 64/4
#define FISICA (16 / PAGINA)
#define SWAP (64 / PAGINA)
#define MAXIMO_PROCESOS 100

struct frame
{
    int pid;
    int pagina;
};

typedef struct frame frame_t;

struct pagina_virtual
{
    int pid;
    int ubicacion_swap;
    int ubicacion;
    char ram;
    //int lru_index se usa para ver cual es el menos recientemente usado. se aumenta y se le asigna sucesivamente a lo que se carga
};

typedef struct pagina_virtual pagina_t;

struct proceso
{
    int pid;
    pagina_t paginas[VIRTUAL];
};

typedef struct proceso proceso_t;

void usage(char *argv[])
{
    fprintf(stderr, "Uso: %s comando parametro\n", argv[0]);
    fprintf(stderr, "Comandos:\n");
    fprintf(stderr, "\t-f Algoritmo FIFO\n");
    fprintf(stderr, "\t-l Algoritmo LRU\n");
}
frame_t fisica[FISICA];
frame_t swap[SWAP];
proceso_t procesos[MAXIMO_PROCESOS];
int fifo_index = 0;
int swap_index = 0;

// falta eliminar de la swap si vuelve a la ram
void fifo(int proceso_id, int pagina)
{
    if (procesos[proceso_id].pid == -1)
    {
        procesos[proceso_id].pid = proceso_id;
    }
    if (procesos[proceso_id].paginas[pagina].ubicacion != -1 && procesos[proceso_id].paginas[pagina].ram == 'r')
    {
        return;
    }
    if (fisica[fifo_index].pid != -1)
    {
        if (swap_index > SWAP)
        {
            printf("Memoria secundaria llena");
            exit(EXIT_SUCCESS);
        }
        int old_pid = fisica[fifo_index].pid;
        int old_pagina = fisica[fifo_index].pagina;

        swap[swap_index].pid = old_pid;
        swap[swap_index].pagina = old_pagina;
        procesos[old_pid].paginas[old_pagina].ubicacion_swap = swap_index;
        procesos[old_pid].paginas[old_pagina].ram = 's';
        swap_index++;
    }
    procesos[proceso_id].paginas[pagina].ram = 'r';
    fisica[fifo_index].pid = proceso_id;
    fisica[fifo_index].pagina = pagina;
    procesos[proceso_id].paginas[pagina].ubicacion = fifo_index;
    fifo_index = (fifo_index + 1) % FISICA;
}

void lru(int proceso_id, int pagina)
{
    if (procesos[proceso_id].pid == -1)
    {
        procesos[proceso_id].pid = proceso_id;
    }
    if (procesos[proceso_id].paginas[pagina].ubicacion != -1 && procesos[proceso_id].paginas[pagina].ram == 'r')
    {
        return;
    }
    if (fisica[fifo_index].pid != -1)
    {
        if (swap_index > SWAP)
        {
            printf("Memoria secundaria llena");
            exit(EXIT_SUCCESS);
        }
        int old_pid = fisica[fifo_index].pid;
        int old_pagina = fisica[fifo_index].pagina;

        swap[swap_index].pid = old_pid;
        swap[swap_index].pagina = old_pagina;
        procesos[old_pid].paginas[old_pagina].ubicacion_swap = swap_index;
        procesos[old_pid].paginas[old_pagina].ram = 's';
        swap_index++;
    }
    procesos[proceso_id].paginas[pagina].ram = 'r';
    fisica[fifo_index].pid = proceso_id;
    fisica[fifo_index].pagina = pagina;

    procesos[proceso_id].paginas[pagina].ubicacion = fifo_index;
    fifo_index = (fifo_index + 1) % FISICA;
}

int main(int argc, char *argv[])
{

    if (argv[1][0] != '-')
    {
        usage(argv);
        exit(EXIT_FAILURE);
    }

    int i, j;

    for (i = 0; i < FISICA; i++)
    {
        fisica[i].pid = -1;
        fisica[i].pagina = -1;
    }

    for (i = 0; i < SWAP; i++)
    {
        swap[i].pid = -1;
        swap[i].pagina = -1;
    }

    for (i = 0; i < MAXIMO_PROCESOS; i++)
    {
        procesos[i].pid = -1;
        for (j = 0; j < VIRTUAL; j++)
        {
            procesos[i].paginas[j].ubicacion_swap = -1;
            procesos[i].paginas[j].ubicacion = -1;
            procesos[i].paginas[j].pid = -1;
        }
    }

    int proceso_id, pagina;
    char option = argv[1][1];

    switch (option)
    {
    case 'f':
        while (scanf("%d\n%d", &proceso_id, &pagina) != EOF)
        {
            fifo(proceso_id, pagina);
        }
        break;
    case 'l':
        while (scanf("%d\n%d", &proceso_id, &pagina) != EOF)
        {
            lru(proceso_id, pagina);
        }
        break;
    default:
        fprintf(stderr, "Comando desconocido\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < MAXIMO_PROCESOS; i++)
    {
        if (procesos[i].pid != -1)
        {
            printf("Proceso %d: ", procesos[i].pid);
            for (j = 0; j < VIRTUAL; j++)
            {
                if (procesos[i].paginas[j].ubicacion != -1)
                {
                    printf("%c%d, ", procesos[i].paginas[j].ram, procesos[i].paginas[j].ubicacion);
                }
                else
                {
                    printf("- ");
                }
            }
            printf("\n");
        }
    }

    printf("Memoria física: ");
    for (i = 0; i < FISICA; i++)
    {
        if (fisica[i].pid != -1)
        {
            printf("%d.%d ", fisica[i].pid, fisica[i].pagina);
        }
        else
        {
            printf("- ");
        }
    }
    printf("\nMemoria secundaria: ");
    for (i = 0; i < VIRTUAL; i++)
    {
        if (swap[i].pid != -1)
        {
            printf("%d.%d ", swap[i].pid, swap[i].pagina);
        }
        else
        {
            printf("- ");
        }
    }
    printf("\n");
    exit(EXIT_SUCCESS);
}
