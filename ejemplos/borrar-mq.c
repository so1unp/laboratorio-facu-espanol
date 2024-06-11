// borrar-mq.c 
// Elimina una cola de mensajes POSIX
// 
// Recibe como parámetros:
//    - El nombre de la cola a eliminar
//
// Autor: CB - UNPSJB 
// 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_PERMISSIONS 0644
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main (int argc, char *argv[ ])
{
   mqd_t cola;   		//descriptor de la cola
   struct mq_attr attr;   	//atributos de la cola

   // Controla parámetros de entrada
   if (argc<2)
   {   perror("uso: borrar-mq <nombre-cola> \n"); exit(1); }
   

   /* elimina la cola de mensajes */
   mq_unlink(argv[1]);

   printf ("Se ha eliminado la cola %s\n",argv[1]);


   exit(0);
}

