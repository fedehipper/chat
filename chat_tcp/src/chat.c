#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]) {

	int sockfd, portno;
	struct sockaddr_in serv_addr;
	char buffer[256];

	if(!strcmp(argv[1], "servidor")) {
		// ./char servidor puerto

		int newsockfd, clilen;
		struct sockaddr_in cli_addr;

		sockfd = socket(AF_INET, SOCK_STREAM, 0);

		bzero((char *) &serv_addr, sizeof(serv_addr));

		portno = atoi(argv[2]);

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);

		bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr));

		listen(sockfd,5);
		clilen = sizeof(cli_addr);

		newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, ( socklen_t *)&clilen);

		bzero(buffer,256);

		read(newsockfd,buffer,255);

		printf("Here is the message: %s\n",buffer);

		write(newsockfd,"I got your message",18);

	} else if(!strcmp(argv[1], "cliente")) {
		// ./chat cliente localhost puerto

		struct hostent *server;
		portno = atoi(argv[3]);

		sockfd = socket(AF_INET, SOCK_STREAM, 0);

		server = gethostbyname(argv[2]);

		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;

		bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

		serv_addr.sin_port = htons(portno);

		connect(sockfd, (const struct sockaddr *)&serv_addr,sizeof(serv_addr));

		printf("Please enter the message: ");
		bzero(buffer,256);
		fgets(buffer,255,stdin);
		write(sockfd,buffer,strlen(buffer));

		bzero(buffer,256);

		read(sockfd,buffer,255);

		printf("%s\n",buffer);

	} else
		printf("no se selecciono modo cliente o servidor");

	return EXIT_SUCCESS;
}
