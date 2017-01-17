/*
 * libSocket.h
 *
 *  Created on: 16/1/2017
 *      Author: utnso
 */

#ifndef LIBSOCKET_H_
#define LIBSOCKET_H_


void socket_close(int socket);
void client_init(int * cliSocket, char *ip, char *puerto);
void server_init(int *svrSocket, char *puerto);
void server_acept(int serverSocket, int *clientSocket);


#endif /* LIBSOCKET_H_ */
