#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int MAX=2000000; //MAX-1 es el maximo tamaño del histograma
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
	int maximo=MAX;
	int encontrado=0;
	for (i=MAX-1 ;i>=1 && encontrado!=1; i--){
		if(cant[i]==0){
			maximo=i;
		}
		else{
			encontrado=1;
		}
	}
	int j;
	for (i=1; i<maximo; i++){
		printf("%d",i);
		for (j=0; j<cant[i]; j++){
			printf("*");
		} 
		printf("\n");
	}
    // Termina la ejecución del programa.
    exit(EXIT_SUCCESS);
}