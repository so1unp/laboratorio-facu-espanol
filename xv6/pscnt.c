#include "types.h"
#include "user.h"
#include "date.h"

int main(void)
{
    printf(1, "Cantidad de procesos en ejecucion antes de crear hijos: %d \n", pscnt());
    int i = 0;
    const int CANT_NUEVOS_PROC = 2;
    for (i=0; i<CANT_NUEVOS_PROC; i++ )
    {
        if (fork() == 0)
        {
            exit();
        }
    }

    printf(1, "Cantidad de procesos en ejecucion luego de crear %d hijos: %d \n", CANT_NUEVOS_PROC, pscnt());
    for (i = 0; i < CANT_NUEVOS_PROC; i++)
    {
        wait();
    }

    exit();
}