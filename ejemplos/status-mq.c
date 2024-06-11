// status-mq.c 
// Muestra el estado de una cola de mensajes POSIX
// 
// Recibe como parámetros:
//    - El nombre de la cola a analizar
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
   {   perror("uso: status-mq <nombre-cola> \n"); exit(1); }
   
   printf ("Estado de la cola %s\n",argv[1]);

   /* Crea la cola de mensajes */
   if ((cola = mq_open (argv[1],  O_RDONLY)) == -1) 
   {   perror("No se puede acceder a la cola de mensajes"); exit(1); }


   /* recupera los atributos de la cola */
   mq_getattr(cola, &attr);


   printf("La cola %s tiene los siguientes atributos:\n",argv[1]);
   printf("	flags %i \n", attr.mq_flags);
   printf("	maxmsg %i \n", attr.mq_maxmsg);
   printf("	msgsize %i \n", attr.mq_msgsize);
   printf("	curmsgs %i \n", attr.mq_curmsgs);

   mq_close(cola);

   exit(0);
}

