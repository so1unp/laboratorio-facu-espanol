#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define QUEUE_PERMISSIONS 0622
#define USERNAME_MAXSIZE 15 // Máximo tamaño en caracteres del nombre del remitente.
#define TXT_SIZE 100        // Máximo tamaño del texto del mensaje.

/**
 * Estructura del mensaje:
 * - sender: nombre del usuario que envió el mensaje.
 * - text: texto del mensaje.
 */
struct msg
{
    char sender[USERNAME_MAXSIZE];
    char text[TXT_SIZE];
};

typedef struct msg msg_t;

/**
 * Imprime información acerca del uso del programa.
 */
void usage(char *argv[])
{
    fprintf(stderr, "Uso: %s comando parametro\n", argv[0]);
    fprintf(stderr, "Comandos:\n");
    fprintf(stderr, "\t-s queue mensaje: escribe el mensaje en queue.\n");
    fprintf(stderr, "\t-r queue: imprime el primer mensaje en queue.\n");
    fprintf(stderr, "\t-a queue: imprime todos los mensaje en queue.\n");
    fprintf(stderr, "\t-l queue: vigila por mensajes en queue.\n");
    fprintf(stderr, "\t-c queue: crea una cola de mensaje queue.\n");
    fprintf(stderr, "\t-d queue: elimina la cola de mensajes queue.\n");
    fprintf(stderr, "\t-h imprime este mensaje.\n");
}

// el tamanio del mensaje tiene que ser igual al tamano de la estructura de datos

int main(int argc, char *argv[])
{
    msg_t mensaje;
    mqd_t cola;          // descriptor de la cola
    struct mq_attr attr; // atributos de la cola

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(msg_t);

    if (argc < 2)
    {
        usage(argv);
        exit(EXIT_FAILURE);
    }

    if (argv[1][0] != '-')
    {
        usage(argv);
        exit(EXIT_FAILURE);
    }

    char option = argv[1][1];
    switch (option)
    {
    case 's':
        printf("Enviar %s a la cola %s\n", argv[3], argv[2]);
        if ((cola = mq_open(argv[2], O_WRONLY)) == -1)
        {
            perror("No se puede abrir la cola de mensajes");
            exit(1);
        }

        strncpy(mensaje.text, argv[3], strlen(argv[3]) + 1);
        getlogin_r(mensaje.sender, sizeof(mensaje.sender));
        mq_send(cola, (char *)&mensaje, sizeof(msg_t), (unsigned int)1);
        break;
    case 'r':
        printf("Recibe el primer mensaje en %s\n", argv[2]);
        if ((cola = mq_open(argv[2], O_RDONLY | O_NONBLOCK)) == -1)
        {
            perror("No se puede abrir la cola de mensajes");
            exit(1);
        }
        if (mq_receive(cola, (char *)&mensaje, sizeof(msg_t), NULL) == -1)
        {
            printf("No hay mensajes en la cola");
        }
        else
        {
            printf("Remitente: %s\nMensaje: %s\n", mensaje.sender, mensaje.text);
        }
        break;
    case 'a':
        printf("Imprimir todos los mensajes en %s\n", argv[2]);
        if ((cola = mq_open(argv[2], O_RDONLY | O_NONBLOCK)) == -1)
        {
            perror("No se puede abrir la cola de mensajes");
            exit(1);
        }
        while (mq_receive(cola, (char *)&mensaje, sizeof(msg_t), NULL) != -1)
        {
            printf("Remitente: %s\nMensaje: %s\n", mensaje.sender, mensaje.text);
        }

        break;
    case 'l':
        printf("Escucha indefinidamente por mensajes\n");
        if ((cola = mq_open(argv[2], O_RDONLY)) == -1)
        {
            perror("No se puede abrir la cola de mensajes");
            exit(1);
        }
        while (mq_receive(cola, (char *)&mensaje, sizeof(msg_t), NULL) != -1)
        {
            printf("Remitente: %s\nMensaje: %s\n", mensaje.sender, mensaje.text);
        }
        break;
    case 'c':
        umask(0000);
        if ((cola = mq_open(argv[2], O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
        {
            perror("No se puede crear la cola de mensajes");
            exit(1);
        }
        printf("Crea la cola de mensajes %s\n", argv[2]);
        break;
    case 'd':
        printf("Borra la cola de mensajes %s\n", argv[2]);
        if (mq_unlink(argv[2]) == -1)
        {
            perror("No se puede borrar la cola de mensajes");
            exit(1);
        }
        break;
    case 'h':
        usage(argv);
        break;
    default:
        fprintf(stderr, "Comando desconocido: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
