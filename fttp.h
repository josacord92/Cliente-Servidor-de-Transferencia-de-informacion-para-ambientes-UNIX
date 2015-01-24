#ifndef FTTP_H
#define	FTTP_H
#include <dirent.h> 
//#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>
#include <regex.h>

#define PORT 8889			/* El puerto que será abierto */
#define PORT2 8889
#define BACKLOG 5			/* El número de conexiones permitidas */
#define DELAY_SHARE_DATES 2 /* Retraso en compartir las fechas de los sistemas */


typedef struct fileInfo_t {
	char filename[2048];
	char path[2048];
	float fileSize;	
	long lastModification;
	int flag;//1 el archivo en el servidor se debe modificar
			//2 el archivo es una copia vieja
	int halt;
	struct fileInfo_t* next;
} fileInfo_t;

typedef struct {
	char buffer[10240];
	int tamanoBloque;
} fileBlock_t;

int encendidoServidor = 1;
int encendidoCliente = 1;

char parametroEntrada[2048];
char caracterDosPuntos[] = ":";
char caracterArroba[] = "@";
char caracterFSlash[] = "/";
char caracterNum[] = "#";
char caracterAsterix[] = "*";

char bufferW[2048];
char bufferW2[2048];
char bufferW3[2048];
char bufferW4[2048];

char usuario[2048];
char contrasena[2048];
char direccionIp[2048];
char urlRuta[2048];
char urlLocal[2048];


fileInfo_t filesInDirectory[400]; //ligante a funcion chargeDirectory
fileInfo_t filesInSincronizedFile[200]; //ligante al archivo .ldregister
fileInfo_t files[200]; //ligante a search new files

char directory[2048]; //ligante a funcion cargar directorio;

int localCount=0; //Conteo local de archivos en directorio - ligante a funcion chargeDirectory

void *funciondelhilo(void *);
void *ImprimirEncabezado();
int *ObtenerSubCadenaHasta(char cadenaEntrada[], char puntoDeFinalizacion[]);
int *CortarSubCadenaHasta(char cadenaEntrada[], char puntoDeFinalizacion[]);
int ExisteEnLaCadena(char cadenaEntrada[], char caracter[]);

//**Funciones importantes para el servidor
//**paso uno se hace carga de directorio

void chargeDirectory(char* dirAddress);
#endif	/* FTTP_H */
