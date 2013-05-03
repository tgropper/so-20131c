#include "Proceso Server.h"

int main(void){

	t_queue* mensajesQueue;
	mensajesQueue = queue_create();
	t_list* conexionesList;
	conexionesList = list_create();

	initServer(5000);
	////ESPERO MENSAJES O CONEXIONES
	while(1){
		//SI HAY MENSAJES
		if(mensajes(mensajesQueue, conexionesList)){
			Mensaje* miMensaje;
			miMensaje = queue_pop(mensajesQueue);
			char*msg = (char*) miMensaje->data;
			printf("%s",msg);
			fflush(stdout);
			//printf("Mensaje Recibido: %c", miMensaje->type);
			free(miMensaje->data);
			free(miMensaje);
		}
	}
	return 0;



}