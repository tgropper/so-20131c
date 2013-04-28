/*
 * Client.c
 *
 *  Created on: 27/04/2013
 *      Author: utnso
 */
#include "Client.h"



/*
 * @NAME: connectServer
 * @DESC: Conecta a un  servidor. Recibe ip en formato string (ej "127.101
 * 		  type: codigo de mensaje, lenght: size of (variable que se adjunta),
 * 		  data: dirección de la variable a adjuntar.
 */
int connectServer(char *IP, int PORT){
	int sockfd; 					// Escuchar sobre sock_fd, nuevas conexiones sobre new_fd
	struct sockaddr_in their_addr; 	// Información sobre mi dirección
	struct hostent *server; 		// Información sobre el server


	////OBTENER INFORMACIÓN DEL SERVER
		if ((server = gethostbyname(IP)) == NULL) { // obtener información de máquina
		perror("gethostbyname");
		exit(1);
		}

		////SETEO CONFIGURACIONES DE IP + PUERTO
		their_addr.sin_family = AF_INET;  // Ordenación de bytes de la máquina
		their_addr.sin_port = htons(PORT); // short, Ordenación de bytes de la	red
		their_addr.sin_addr = *((struct in_addr *)server->h_addr);
		memset(&(their_addr.sin_zero), '\0', 8); // Poner a cero el resto de la estructura


		////PIDO EL SOCKET
		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket");
			exit(1);
		}


	////INTENTO CONECTAR
		if (connect(sockfd, (struct sockaddr *)&their_addr,	sizeof(struct sockaddr)) == -1) {
			perror("connect");
			exit(1);
		}
		printf("Conectado con host \n");

		//HAGO EL SOCKET NO BLOQUEANTE
		if (make_socket_non_blocking (sockfd) == -1) abort ();

		////ASOCIO EL FD DE LA NUEVA CONEXION
		event.data.fd = sockfd;
		event.events = EPOLLIN | EPOLLET;

		//AGREGO LA NUEVA CONEXION A LA INSTANCIA EPOLL
		if ((epoll_ctl (instancia_epoll, EPOLL_CTL_ADD, sockfd, &event)) == -1){
		  perror ("epoll_ctl");
		  exit(1);
		}
	return sockfd;

}


