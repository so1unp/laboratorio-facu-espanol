#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Agregar código aquí.
	const int MAX=10;
	int cant[MAX];
	int contador=0;
	int i;
	for (i=0;i<MAX; i++){
		cant[i]=0;	
	}
	char entrada;
	while ((entrada=getchar())!=EOF){
		if ((entrada!=' ') && (entrada!='\n')){
			contador++;
		} else{
			cant[contador]++;
			contador=0;
		}
	}
	int j;
	for (i=1; i<MAX; i++){
		printf("%d",i);
		for (j=0; j<cant[i]; j++){
			printf("*");
		} 
		printf("\n");
	}
    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}
