/*
 * nivel_read_archivo_configuracion.c
 *
 *  Created on: 18/04/2013
 *      Author: utnso
 */


#include "nivel_library.h"

/*NAME: read_nivel_archivo_configuracion
PARAM: char* path -> direccion del archivo de configuracion
RETURN: t_nivel * -> un nivel creado en base a un archivo de configuracion
DESC: instancia un t_config (struct de commons/config.h) tomando valores del archivo de configuracion y devuelve 
	un nivel creado en base a este t_config
	*/

t_nivel *read_nivel_archivo_configuracion(char* path){

	t_nivel *nivel;
	t_config * n;

	n = config_create(path);

	nivel = create_nivel(n);

	printf("nivel creado\n\n");

	return nivel;
}

/*NAME: create_nivel
PARAM: t_config *n -> una instancia de t_config con los valores de un archivo de ocnfiguracion
RETURN: t_nivel * -> el nivel creado
DESC: con las funciones de commons/config.h va tomando los valores del t_config dependiendo de la key pasada
	como parametro a cada función
	*/

t_nivel *create_nivel(t_config *n){

	t_nivel *nivel;
	nivel = (t_nivel*)malloc(sizeof(t_nivel));
	t_list *list_personajes = list_create();

	nivel->nivel_items = create_lista_cajas(n);

	nivel->nivel_orquestador = config_get_string_value(n, "orquestador");

	nivel->nivel_tiempo_deadlock = config_get_double_value(n, "tiempoChequeoDeadlock");

	nivel->nivel_recovery = config_get_int_value(n, "recovery");

	nivel->personajes_en_nivel = list_personajes;

	return nivel;
}

/*NAME: create_lista_cajas
PARAM: t_config *n -> una instancia de t_config con los valores de un archivo de configuracion
RETURN: ITEM_NIVEL * -> una instancia de ITEM_NIVEL * (so-nivel-gui-library-master/nivel-gui/nivel.h) como una lista nueva
DESC: crea una lista de ITEM_NIVEL con sus respectivos atributos
	*/

ITEM_NIVEL *create_lista_cajas(t_config *n){

	ITEM_NIVEL *ListaItems = NULL;

	char buffer_caja[8];
	char buffer_num[5];
	char buffer_caja_num[8];
	int i = 1;

	strcpy(buffer_caja, "caja");
	sprintf(buffer_num, "%d", i);
	strcpy(buffer_caja_num, (strcat(buffer_caja, buffer_num)));

	while(config_has_property(n, buffer_caja_num)){

		ListItems_add_caja(n, buffer_caja_num, &ListaItems);

		i++;

		strcpy(buffer_num, "");
		strcpy(buffer_caja, "");
		strcpy(buffer_caja_num, "");

		strcpy(buffer_caja, "caja");
		sprintf(buffer_num, "%d", i);
		strcpy(buffer_caja_num, (strcat(buffer_caja, buffer_num)));
	}

	return ListaItems;
}

/*NAME: create_caja
PARAM: t_config *n, char *buffer_caja_num -> una instancia de t_config y el key de una caja ("caja1", "caja2", etc..)
RETURN: ITEM_NIVEL * -> devuelve una instancia de ITEM_NIVEL * con los valores tomados del t_config utilizando la key
pasada como argumento
DESC: crea una nueva instancia de ITEM_NIVEL * utilizando las funciones de commons/config.h para tomar los valores
	de t_config *n.
EXPLICACION: el arch viene en formato "x,y,z,w", para poder tomar cada valor por separado, hay que convertirlo 
	a formato ["x","y","z","w"], utilizando las funciones de commons/string.h  string_from_format\2 y 
	string_get_string_as_array\1
	*/

void ListItems_add_caja(t_config *n, char *buffer_caja_num, ITEM_NIVEL **list){
	ITEM_NIVEL *new = malloc(sizeof(ITEM_NIVEL));
	
	char* aux_string = string_from_format("[%s]", config_get_string_value(n, buffer_caja_num));

	char **aux = string_get_string_as_array(aux_string);

	new->id = aux[1][0];

	new->quantity = atoi(aux[2]);
	
	new->item_type = RECURSO_ITEM_TYPE;

	new->posx = atoi(aux[3]);

	new->posy = atoi(aux[4]);	

	new->next = *list;
	
	*list = new;
}


/*-----------------------------FUNCIONES DE USO PARA DIBUJAR NIVEL----------------------------------------*/
/*
ITEM_NIVEL *crear_lista_items(t_list *cajas, t_list *personajes){
	
	ITEM_NIVEL *ListaItems = NULL;
	int i = 0;
	int j = 0;
	t_nivel_caja *caja;
	t_personaje_en_nivel *personaje;

	while(i < (list_size(cajas))){
		caja = list_get(cajas, i);
		add_caja_item_nivel(caja, &ListaItems, RECURSO_ITEM_TYPE),		
		i++;
	}
	
	while(j < (list_size(personajes))){
		personaje = list_get(personajes, i);
		add_personaje_item_nivel(personaje, &ListaItems, PERSONAJE_ITEM_TYPE),		
		j++;
	}	
	return ListaItems,
}

void add_caja_item_nivel(t_nivel_caja *caja, ITEM_NIVEL **list, char tipo){
	    ITEM_NIVEL * temp;
        temp = malloc(sizeof(ITEM_NIVEL));

        temp->id = caja->caja_simbolo;
        temp->posx = caja->caja_pos_x;
        temp->posy = caja->caja_pos_y;
        temp->item_type = tipo;
        temp->quantity = caja->caja_instancias;
        temp->next = *list;
        *list = temp;
}

void add_personaje_item_nivel(t_personaje_en_nivel *personaje, ITEM_NIVEL **list, char tipo){
	    ITEM_NIVEL * temp;
        temp = malloc(sizeof(ITEM_NIVEL));

        temp->id = personaje->personaje_simbolo;
        temp->posx = personaje->personaje_pos_x;
        temp->posy = personaje->personaje_pos_y;
        temp->item_type = tipo;
        temp->quantity = 0;
        temp->next = *list;
        *list = temp;
}

void BorrarItem(ITEM_NIVEL** ListaItems, char id) {
        ITEM_NIVEL * temp = *ListaItems;
        ITEM_NIVEL * oldtemp;

        if ((temp != NULL) && (temp->id == id)) {
                *ListaItems = (*ListaItems)->next;
		free(temp);
        } else {
                while((temp != NULL) && (temp->id != id)) {
                        oldtemp = temp;
                        temp = temp->next;
                }
                if ((temp != NULL) && (temp->id == id)) {
                        oldtemp->next = temp->next;
			free(temp);
                }
        }
}

void MoverPersonaje(ITEM_NIVEL* ListaItems, char id, int x, int y) {

        ITEM_NIVEL * temp;
        temp = ListaItems;

        while ((temp != NULL) && (temp->id != id)) {
                temp = temp->next;
        }
        if ((temp != NULL) && (temp->id == id)) {
                temp->posx = x;
                temp->posy = y;
        }
}
	
	
	*/
