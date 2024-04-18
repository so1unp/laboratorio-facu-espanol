#include "types.h"
#include "user.h"
#include "date.h"

int main(void)
{
    printf(1, "Mi PID es %d \n", getpid());
    int pid = fork();
    if (pid == 0)
    {
        printf(1, "Soy el hijo, el PID de mi padre es %d \n", getppid());
    }
    if (pid != 0)
    {
        wait();
    }
    exit();
}