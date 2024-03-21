#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char entrada;
	while(1){
		entrada=getchar(); 
		if (entrada==' '){
			printf("\n");
		}
		else
		{
			printf("%c", entrada);
		}
	}
    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}
