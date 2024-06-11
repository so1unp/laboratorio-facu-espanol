// notify-mq.c 
// 
// Recibe mensajes en un thread asincrónico
// (no espera mensajes)
//
// Usando notify sobre la cola de mensajes POSIX
// 
// Recibe como parámetros:
//    - El nombre de la cola a inspeccionar (debe tener una / al principio. P.e. /M1)
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


mqd_t cola;   	  	 	//descriptor de la cola
struct sigevent noti;		//evento notificación

static void                     /* Thread de receive */
tnoti(union sigval sv)
{
    struct mq_attr attr;
    char mess[1024+10]="";

    /* extrae atributos de la cola */
    if (mq_getattr(cola, &attr) == -1) {
        perror("mq_getattr");
        exit(EXIT_FAILURE);
    }

    /* recibe el mensaje */
    mq_receive(cola, mess, sizeof(mess)+10, 0);
    printf("Recibió [%s]. quedan %i mensajes en la cola\n", mess,attr.mq_curmsgs-1);

    if (mq_notify(cola, &noti) == -1) {
        perror("Error al establecer notificacion");
        return;
    }
    return;
}


int main (int argc, char *argv[ ])
{

   // Controla parámetros de entrada
   if (argc<2)
   {   perror("uso: notify-mq <nombre-cola> \n"); exit(1); }
   
   printf ("Espera eventos en la cola %s\n",argv[1]);

   /* Abre la cola de mensajes */
   if ((cola = mq_open (argv[1],  O_RDONLY)) == -1) 
   {   perror("No se puede acceder a la cola de mensajes"); exit(1); }


   /* Programa evento de notificación en otro thread */
   noti.sigev_notify = SIGEV_THREAD;
   noti.sigev_notify_function = tnoti;
   noti.sigev_notify_attributes = NULL;
   if (mq_notify(cola, &noti) == -1) {
        perror("Error al establecer notificacion");
        exit(EXIT_FAILURE);
   }

   printf("Comienza a hacer la tarea que tenga que hacer .....\n");
   //pause();
   while(1==1){
    printf("Sigo trabajando ...\n");
    sleep(5);
   }
   exit(0);
}

