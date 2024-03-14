#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Agregar código aquí.
	int suma=0;
	int i;
	for (i=1;i<argc;i++){
	suma+=atoi(argv[i]);
	}
	printf("%d\n",suma);
    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}
