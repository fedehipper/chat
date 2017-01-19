#include "libSocket.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define PACKAGESIZE 30

int socket_servidor;
int socket_cliente;

void recibir(void) {
	char package[PACKAGESIZE];
	int status = 1;
	while (status != 0) {
		status = recv(socket_servidor, (void*)package, PACKAGESIZE, 0);
		if (status) printf("%s",package);
	}
}

void responder(void) {
	char message[PACKAGESIZE];
	int enviar = 1;
	while(enviar) {
		fgets(message, PACKAGESIZE, stdin);
		if (!strcmp(message, "exit\n")) enviar = 0;
		if (enviar) send(socket_servidor, message, strlen(message) + 1, 0);
	}
}


int main(int argc, char **argv) {
	printf("\n%s\n", argv[1]);

	if(!strcmp(argv[1], "servidor")) {
		printf("\nse seleciono modo servidor\n");
		//funciones de servidor
		//Inicia el socket para escuchar
			server_init(&socket_servidor, "4143");
			printf("servidor listo...\n");
		//inicia el socket para atender al cliente
			server_acept(socket_servidor, &socket_servidor);
			printf("cliente aceptado...\n");

			pthread_t hilo_recibir;
			pthread_create(&hilo_recibir, NULL, (void*)recibir, NULL);

		//pasaje de mensaje
			int enviar = 1;
			char message[PACKAGESIZE];

			while(enviar){
				fgets(message, PACKAGESIZE, stdin);
				if (!strcmp(message, "exit\n")) enviar = 0;
				if (enviar) send(socket_servidor, message, strlen(message) + 1, 0);
			}

			close(socket_servidor);
			close(socket_servidor);

	} else 	if(!strcmp(argv[1], "cliente")) {
		printf("\nse selecciono modo cliente\n");
		//funciones de cliente
		//inicia el socket para conectarse con el servidor

			client_init(&socket_servidor, "127.0.0.1", "4143");
			printf("conectado al servidor...\n");

		//pasaje de mensaje
			pthread_t hilo_enviar;
			pthread_create(&hilo_enviar, NULL, (void*)responder, NULL);

			char package[PACKAGESIZE];
			int status = 1;

			while (status != 0) {
				status = recv(socket_servidor, (void*) package, PACKAGESIZE, 0);
				if (status) printf("%s",package);
			}

			printf("servidor cerrado...\n");
			close(socket_servidor);
	} else
		printf("\nno se selecciono modo\n");

	return EXIT_SUCCESS;
}
