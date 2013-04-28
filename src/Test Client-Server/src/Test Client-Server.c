/*
 ============================================================================
 Name        : Test.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <Connections/Client.h>
#include <Connections/Server.h>
#include <Connections/Mensajes.h>
#include <collections/queue.h>

int main(void) {
	//INICIALIZO LA COLA DE MENSAJES
	t_queue* mensajesQueue;
	mensajesQueue = queue_create();
	int socketCliente;
	Mensaje* miMensaje;

	//INICIALIZO EL SERVIDOR EN EL PUERTO 5000
	initServer(5000);

	//INICIALIZO EL CLIENTE EN EL SOCKETCLIENTE
	socketCliente = connectServer("localhost",5000);

	//MANDO MENSAJE DEL CLIENTE AL SERVIDOR
	mandarMensaje(socketCliente,'a',sizeof("Mensaje de Cliente a Server\n"),"Mensaje de Cliente a Server\n");

	//LEVANTO EL MENSAJE DEL CLIENTE
	while(!mensajes(mensajesQueue));


				miMensaje = queue_pop(mensajesQueue);
				char*msg = (char*) miMensaje->data;
				printf("%s",msg);
				fflush(stdout);

				//ENVIO UNA RESPUESTA DEL SERVER AL CLIENTE
				mandarMensaje(miMensaje->from,'b',sizeof("Mensaje de Server a Cliente\n"),"Mensaje de Server a Cliente\n");

				//BORRO EL MENSAJE
				borrarMensaje(miMensaje);


	//LEVANTO EL MENSAJE DEL SERVIDOR (LLEGAN A LA MISMA COLA, QUE ES UNICA DEL PROCESO)
	while(!mensajes(mensajesQueue));


				miMensaje = queue_pop(mensajesQueue);
				msg = (char*) miMensaje->data;
				printf("%s",msg);
				fflush(stdout);


				//BORRO EL MENSAJE
				borrarMensaje(miMensaje);



	//CIERRO EL SOCKET DEL CLIENTE
	close(socketCliente);

	return EXIT_SUCCESS;
}
