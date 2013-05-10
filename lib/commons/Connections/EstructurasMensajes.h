#define HANDSHAKE 1
#define REQUEST_DATA_NIVEL 2
#define REQUEST_POS_RECURSO 3
#define POSICION_RECURSO 4
#define REQUEST_RECURSO 5
#define CONFIRMAR_RECURSO 6
#define TERMINE_NIVEL 7
#define RECURSOS_LIBERADOS 8
#define REQUEST_INTERBLOQUEO 10
#define REQUEST_MOVIMIENTO 11
#define PERSONAJE_BLOQUEADO 12
#define TERMINE_TURNO 13
#define MORISTE_PERSONAJE 14
#define DATANIVEL 16
#define MOVIMIENTO_PERMITIDO 17
#define RECURSOS_REASIGNADOS 18

typedef struct  c{
	char ID[3]; //es un string, para usar strcpy
	char IP[20];
	int PORT;
	int FD;
} Nivel;

typedef struct  b{
	char ID[3]; //es un string, para usar strcpy
	char IP[20];
	int PORT;
	int FD
} Planificador;

typedef struct a {
	char ID[3]; //es un string, para usar strcpy
	char IP[20];
	int PORT;
	int FD;
} Personaje;

typedef struct {
	int POS_X;
	int POS_Y;
}Posicion;

typedef struct {
	Nivel miNivel;
	Planificador miPlanificador;
}Data_Nivel;


typedef struct {
	int cant_flor;
	int cant_hongo;
	int cant_moneda;
}Recursos;

Recursos CantRecursos (int flores,int hongos,int monedas){
	Recursos aux;
	aux.cant_flor = flores;
	aux.cant_hongo = hongos;
	aux.cant_moneda = monedas;
	return(aux);

}


Posicion Pos (int x, int y){
	Posicion aux;
	aux.POS_X  = x;
	aux.POS_Y = y;
	return(aux);
}

