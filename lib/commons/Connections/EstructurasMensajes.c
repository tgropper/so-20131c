/*
 * EstructurasMensajes.c
 *
 *  Created on: 25/05/2013
 *      Author: utnso
 */
#ifndef ESTRUCTURASMENSAJES_H_
#define ESTRUCTURASMENSAJES_H_

#include "EstructurasMensajes.h"

Posicion Pos (int x, int y){
	Posicion aux;
	aux.POS_X  = x;
	aux.POS_Y = y;
	return(aux);
}


int obtenerPosX(Posicion pos){
	int aux = pos.POS_X;
	return(aux);
}

int obtenerPosY(Posicion pos){
	int aux = pos.POS_Y;
	return(aux);
}

int tomarPuerto(char* direct){
	char** direct_sep = string_split(direct, ":");
	int puerto = atoi(direct_sep[1]);
	return puerto;
}

char* tomarIP(char* direct){
	char** direct_sep = string_split(direct, ":");
	char *IP = direct_sep[0];
	return IP;
}

#endif
