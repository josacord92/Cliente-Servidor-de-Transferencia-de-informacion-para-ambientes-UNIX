#include "fttp.h"
#include <pthread.h>

struct parametrosHiloServidor{
char urlDirectorioLocal;
char urlDirectorioRemoto;
char userNameLocal;
char userPasswordLocal;
char ipAdressRemota;
};

int exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "rb")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

int esDirectorio(const char *dirname){

DIR *directorio;
directorio = opendir(dirname);
if(directorio){
closedir(directorio);
return 1;
}
else{
return 0;
}

}
 struct fileInfo_t listarDirectoriox(char* dirAddress){
fileInfo_t listaDirectorio[400];
 DIR *d;
	struct dirent *dirEntry;
        localCount = 0;
	strcpy(directory,dirAddress);
	d = opendir(dirAddress);
	if(d){		
		localCount = 0; //inicia en 0
		while(NULL != (dirEntry = readdir(d))){
			if((strcmp(dirEntry->d_name,".")==0)
				||(strcmp(dirEntry->d_name,"..")==0)
				||(strcmp(dirEntry->d_name,".ldregister")==0))
			{
				continue;
			}
			else{
				fileInfo_t file;
				struct stat fileData;
				char *path = malloc(sizeof(dirAddress)+sizeof(dirEntry->d_name));
				strcpy(path,directory);
				strcat(path, dirEntry->d_name);
				strcpy(file.filename, dirEntry->d_name);
				strcpy(file.path, path);
				if (lstat (path, &fileData) == -1) //Verifica que el archivo exista y pueda abrirse
					error(strcat("Ha sido imposible encontrar el archivo %s\n",path));
				else {
					file.lastModification=fileData.st_mtime;							
					file.fileSize=fileData.st_size;
					file.flag=3;					
					listaDirectorio[localCount] = file;//Guarda los datos en la lista files
					localCount++;
				}		
			}
		}
		printf("Cantidad de files dentro del directorio:  %d\n\n", localCount);
		closedir(d);
	}
	else{
		error("ERROR: No se ha logrado acceder al directorio especificado\n");
	}
return *listaDirectorio;
}

void listarDirectorio(char* dirAddress){
        memset(&filesInDirectory,0,sizeof(filesInDirectory));
        DIR *d;
	struct dirent *dirEntry;
        int contador = 0;
	strcpy(directory,dirAddress);
	d = opendir(dirAddress);
	if(d){		
		localCount = 0; //inicia en 0
		while(NULL != (dirEntry = readdir(d))){
			if((strcmp(dirEntry->d_name,".")==0)
				||(strcmp(dirEntry->d_name,"..")==0)
				||(strcmp(dirEntry->d_name,".ldregister")==0))
			{
				continue;
			}
			else{
				fileInfo_t file;
				struct stat fileData;
				char *path = malloc(sizeof(dirAddress)+sizeof(dirEntry->d_name));
				strcpy(path,directory);
				strcat(path, dirEntry->d_name);
				strcpy(file.filename, dirEntry->d_name);
				strcpy(file.path, path);
				if (lstat (path, &fileData) == -1) //Verifica que el archivo exista y pueda abrirse
					error(strcat("Ha sido imposible encontrar el archivo %s\n",path));
				else {
					file.lastModification=fileData.st_mtime;							
					file.fileSize=fileData.st_size;
					file.flag=3;					
					filesInDirectory[contador] = file;//Guarda los datos en la lista files
					contador++;
				}		
			}
		}
		printf("Cantidad de files dentro del directorio:  %d\n\n", contador);
		closedir(d);
	}
	else{
		error("ERROR: No se ha logrado acceder al directorio especificado\n");
	}
}

int borrarDirectorio(char* dirAddres){
//statusBorrado = remove(DirectorioDeElementoASerBorrado);
DIR *directorio;
struct dirent *dirEntry;
char DirCompleta[3000];

directorio = opendir(dirAddres);
if(directorio){
while(NULL != (dirEntry = readdir(directorio))){
memset(DirCompleta,'\0',sizeof(DirCompleta));
strcpy(DirCompleta,dirAddres);
strcat(DirCompleta,dirEntry->d_name);



if((strcmp(dirEntry->d_name,".")==0)
				||(strcmp(dirEntry->d_name,"..")==0)
				)
			{
				continue;
			}
			else{
//printf("%s",DirCompleta);
//printf("\n");
struct stat datosFichero;
lstat(DirCompleta,&datosFichero);

if(S_ISDIR(datosFichero.st_mode)){ //es una carpeta
//printf("entro");
strcat(DirCompleta,caracterFSlash);
borrarDirectorio(DirCompleta);
}

//if(exists(DirCompleta)==1)
else{//es un archivo remuevalo
remove(DirCompleta);
}

}

}
rmdir(dirAddres);
}

else{
return 0;
}

return 1;
}

void chargeDirectory(char* dirAddress){	
	DIR *d;
	struct dirent *dirEntry;

	strcpy(directory,dirAddress);
	d = opendir(dirAddress);
	if(d){		
		localCount = 0; //inicia en 0
		while(NULL != (dirEntry = readdir(d))){
			if((strcmp(dirEntry->d_name,".")==0)
				||(strcmp(dirEntry->d_name,"..")==0)
				||(strcmp(dirEntry->d_name,".ldregister")==0))
			{
				continue;
			}
			else{
				fileInfo_t file;
				struct stat fileData;
				char *path = malloc(sizeof(dirAddress)+sizeof(dirEntry->d_name));
				strcpy(path,directory);
				strcat(path, dirEntry->d_name);
				strcpy(file.filename, dirEntry->d_name);
				strcpy(file.path, path);
				if (lstat (path, &fileData) == -1) //Verifica que el archivo exista y pueda abrirse
					error(strcat("Ha sido imposible encontrar el archivo %s\n",path));
				else {
					file.lastModification=fileData.st_mtime;							
					file.fileSize=fileData.st_size;
					file.flag=3;					
					filesInDirectory[localCount] = file;//Guarda los datos en la lista files
					localCount++;
				}		
			}
		}
		printf("Cantidad de files dentro del directorio:  %d\n\n", localCount);
		closedir(d);
	}
	else{
		error("ERROR: No se ha logrado acceder al directorio especificado\n");
	}
}

//Imprime la info del struct file
void printFileInfo(fileInfo_t* file, int size){
	int i=0;
	printf("Listado Maximo de archivos n %i\n",size);
        printf("Nombre archivo/ruta\n");
	while(i<size){
		if(!strcmp("",file[i].filename))
			break;
                printf("%i",i);
		printf("->%s",file[i].filename);
                printf("--%s\n",file[i].path);
               // printf("--%d\n",file[i].fileSize);
		i++;
	}

}

//Funcion encargada de escribir el archivo que contiene la informacion de los archivos contenidos en el directorio local
int  writeSyncronizedFile(char* path, int size){
	int i=0;
	FILE* syncronized;
	char* direccion = malloc(200*sizeof(char));
	sprintf(direccion, "%s%s",path,".ldregister");
	syncronized = fopen (direccion, "wb+");
	fwrite (&size, sizeof(int), 1, syncronized);
	while(i<size){
		fwrite (&filesInDirectory[i], sizeof(fileInfo_t), 1, syncronized);
		i++;
	}
	fclose(syncronized);
	return 1;
}

int readSyncronizedFile(char* filename){
	
	if(exists(filename)){
		FILE* syncronized;
		syncronized= fopen(filename, "rb+");
		int i=0;
		int size=0;
		fread(&size,sizeof(int),1,syncronized);
		while(i<size){
			fread(&filesInSincronizedFile[i],sizeof(fileInfo_t),1, syncronized);
			i++;
		}
		return 1;	
	}
	else{
		return 0;
	}
	
	
}

int searchNewFiles(){
	int i=0;
	localCount=0;
	while(strcmp(filesInDirectory[i].filename,"")){
		int j=0;
		int seeFlag=0;
		while(strcmp(filesInSincronizedFile[j].filename,"")){
			if(!strcmp(filesInDirectory[i].filename,filesInSincronizedFile[j].filename)
				&& filesInDirectory[i].lastModification == filesInSincronizedFile[j].lastModification){
				seeFlag=1;
				break;
			}
			j++;
		}
		if(!seeFlag){
			files[localCount]=filesInDirectory[i];
			localCount++;
		}
		i++;
	}
	return 1;
}

int *fExisteRegistro(char* registro){
//registro compuesto por user*pass

     FILE *archivo;
     char caracter;
     char caracteres[100];
     char* base64DecodeOutput;
     int index = 0;
      memset(caracteres,'\0',100);
     archivo = fopen(".passwords","r");
     
     if(archivo == NULL){
       printf("\nError de apertura del archivo\n");
       return 0;
     }
     else{
     
       while(feof(archivo)==0){
          caracter = fgetc(archivo);
          if(caracter == '\n'){
            index = 0;
            Base64Decode(caracteres, &base64DecodeOutput);
            if(!strcmp(registro,base64DecodeOutput)){
             fclose(archivo);
             return 1;
             }
            
            memset(caracteres,'\0',100);
           }
else{
      caracteres[index] = caracter;
      index = index + 1;}
        } 
    }
    fclose(archivo);
    return 0;
}

void *funcionCliente(){
    iniciodehilocliente:
    printf("\npresione tecla enter para intentar conectar cliente\n");
    char tecla[10];
    fgets(tecla,10,stdin);
    __fpurge(stdin);

    printf("Iniciando cliente\n");
    int sockfd, n;
    int EnvioMensaje;
    int ReciboMensaje;
    int CodigoMensajeEnviado;
    int CodigoMensajeRecibido;
    int AceptadoPorCliente = 0;
    int FalloDeConexion = 0;
    struct sockaddr_in serv_addrx;
    struct hostent *server;
        //printf("flag 1 - client\n");
	
        sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0){ 
        //error("ERROR: No se ha logrado crear el socket de conexion");
        printf("Error: No se logro crear el socket de conexion\n");
        FalloDeConexion = 1;
        }
	//printf("flag 2 - client\n");
	

        if(FalloDeConexion == 0){ //check 1
        server = gethostbyname(direccionIp);
	if (server == NULL) {
        //fprintf(stderr,"ERROR: No se ha logrado encontrar el servidor dentro de la red\n");
        //exit(0);
        //printf("Error: No se ha logrado encontrar el servidor dentro de la red\n");
        FalloDeConexion = 1;
        }

        if(FalloDeConexion ==0){ //check 2
          //   printf("flag 3 - client\n");
    //Inicializa los valores del buffer serv_addr en cero
	bzero((char *) &serv_addrx, sizeof(serv_addrx));
	  //   printf("flag 4 - client\n");
	 serv_addrx.sin_family = AF_INET;							
         bcopy((char *)server->h_addr, 
         (char *)&serv_addrx.sin_addr.s_addr,
         server->h_length);									
    serv_addrx.sin_port = htons(PORT2);						
      //printf("flag 5 - client\n");
    
    if (connect(sockfd,(struct sockaddr *) &serv_addrx,sizeof(serv_addrx)) < 0) {
        //error("ERROR: No se ha logrado la conexion con el servidor\n");
       //printf("flag 6 - client\n");
       printf("Error: No se ha logrado la conexion con el servidor\n");
       FalloDeConexion = 1;
       }
       if(FalloDeConexion ==0){ //check 3
       printf("\nCliente Conectado con el servidor\n");
       printf("\nIntentando autenticar\n");
       //   printf("flag 7 - client\n");
     //se empieza la comunicacion con el servidor primero se verifica que la contraseña sea valida

     char concatenadouserpass[4097];
     memset(concatenadouserpass,'\0',sizeof(concatenadouserpass));
     strcat(concatenadouserpass,usuario);
     strcat(concatenadouserpass,caracterAsterix);
     strcat(concatenadouserpass,contrasena);
//printf("flag 8 - client\n");

//***************************VERIFICACION USER - PASS************************************
     CodigoMensajeEnviado = 1;//verificacion contraseña
     EnvioMensaje = send(sockfd,&CodigoMensajeEnviado,sizeof(int),0);
//printf("flag 9 - client\n");
     EnvioMensaje = send(sockfd,&concatenadouserpass,sizeof(concatenadouserpass),0);
//printf("flag 10 - client\n");
     ReciboMensaje = recv(sockfd,&CodigoMensajeRecibido,sizeof(int),MSG_WAITALL);
//printf("flag 11 - client\n");
     if(CodigoMensajeRecibido == 1){//user pass correcto
         printf("\nCliente: user - pass fueron aceptados por el servidor\n");
         AceptadoPorCliente = 1;
         }
     if(CodigoMensajeRecibido == 0){//user pass incorrecto
         printf("\nCliente: user - pass no fueron aceptados por el servidor\n");
         printf("Terminando Cliente-Server Local\n");
         exit(0);
         }
//***************************************************************************************
          }//fin check fallo de conexion 3
         }//fin check fallo de conexion 2
}//fin check fallo de conexion 1

FalloDeConexion = 0;
int frenoDeCliente = 0;

while(frenoDeCliente == 0){
char entradaComandosCliente[300];
memset(entradaComandosCliente,'\0',sizeof(entradaComandosCliente));
//printf("Bienvenido Client Listo para tareas \n");
printf("\n(Client Console)Introducir comandos->: ");
fgets(entradaComandosCliente,sizeof(entradaComandosCliente),stdin);
entradaComandosCliente[strlen(entradaComandosCliente)-1]='\0';
if(AceptadoPorCliente==1){//*****************Cliente en confianza con servidor*************************************
__fpurge(stdin); //se limpia el buffer de entrada principal


//*****************************************QUIT
if(!strcmp(entradaComandosCliente,"quit") ){ //se pide la salida total del programa
puts("\nSalida el programa\n");
puts("\nCierre de la conexion actual\n");
CodigoMensajeEnviado = 2;//Cerrar conexion actual para que el servidor no siga esperando respuesta
EnvioMensaje = send(sockfd,&CodigoMensajeEnviado,sizeof(int),0);
exit(0);
}

//****************************************CLOSE
if(!strcmp(entradaComandosCliente,"close")){ //se pide que se cierre la conexion actual con el servidor
puts("\nCierre de la conexion actual\n");
CodigoMensajeEnviado = 2;//Cerrar conexion actual
EnvioMensaje = send(sockfd,&CodigoMensajeEnviado,sizeof(int),0);
AceptadoPorCliente = 0; //Se cierran la acreditacion por parte de un servidor
}

//****************************************LCD
if(!strcmp(entradaComandosCliente,"lcd")){ //se pide que se cambie el directorio local actual
puts("Introducir nuevo directorio local-> :");
__fpurge(stdin); //se limpia el buffer de entrada principal
fgets(entradaComandosCliente,sizeof(entradaComandosCliente),stdin); //se obtiene el nuevo directorio local
//eliminacion de enter del nuevo directorio local para evitar contaminar el parametro
entradaComandosCliente[strlen(entradaComandosCliente)-1]='\0';
__fpurge(stdin); //se limpia el buffer de entrada principal
memset(urlLocal,'\0',sizeof(urlLocal));
strcpy(urlLocal,entradaComandosCliente);
printf("%s",urlLocal);
}

//****************************************LS lista los archivos que se encuentran en el directorio remoto
if(!strcmp(entradaComandosCliente,"ls")){//se listan los archivos
CodigoMensajeEnviado = 5; //enviame un listado del directorio remoto
EnvioMensaje = send(sockfd,&CodigoMensajeEnviado,sizeof(int),0);
//envio la url remota que se desea solicitar listar al server
EnvioMensaje = send(sockfd,&urlRuta,sizeof(urlRuta),0);
fileInfo_t filesInDirectoryInput[400];
ReciboMensaje = recv(sockfd,&filesInDirectoryInput,sizeof(filesInDirectoryInput),MSG_WAITALL);
printFileInfo(filesInDirectoryInput, 400);
__fpurge(stdin); //se limpia el buffer de entrada principal
}


//****************************************PWD pide demostrar el directorio activo remoto actual
if(!strcmp(entradaComandosCliente,"pwd")){//se pide mostrar el directorio activo remoto
puts("Show -> Directorio activo remoto ");
puts(urlRuta);
__fpurge(stdin); //se limpia el buffer de entrada principal
}

//****************mdelete
if(!strcmp(entradaComandosCliente,"mput")){
puts("Introducir patron de busqueda a enviar ->: use ([[:alnum:]])* en vez de *");
memset(entradaComandosCliente,'\0',sizeof(entradaComandosCliente));
fgets(entradaComandosCliente,sizeof(entradaComandosCliente),stdin); //se obtiene el nombre de archivo a recuperar
//eliminacion de enter del nombre de archivo a recuperar para evitar contaminar el parametro
entradaComandosCliente[strlen(entradaComandosCliente)-1]='\0';
int r;


char DirExactaArchivoEnLocal[2350]; //se guardara aca la direccion exacta del archivo

//se verifica que el actual directorio local exista
DIR *dir;
dir = opendir(urlLocal);
if(dir){ //existe el directorio local actual
strcpy(DirExactaArchivoEnLocal,urlLocal);
//strcat(DirExactaArchivoEnLocal,entradaComandosCliente);
//closedir(dir);
}
else{ //no existe el directorio local actual - se usa el por defecto donde se ubica el servidor
printf("\nNo existe el directorio local actual en el cliente - se usara la ubicacion def\n");
getcwd(DirExactaArchivoEnLocal,sizeof(DirExactaArchivoEnLocal));
strcat(DirExactaArchivoEnLocal,caracterFSlash);
//strcat(DirExactaArchivoEnLocal,entradaComandosCliente);
}


DIR *directorio;
struct dirent *dirEntry;
char DirCompleta[3000];
char dirAddres[2350];
strcpy(dirAddres,DirExactaArchivoEnLocal);

directorio = opendir(dirAddres);
if(directorio){
while(NULL != (dirEntry = readdir(directorio))){
memset(DirCompleta,'\0',sizeof(DirCompleta));
strcpy(DirCompleta,dirAddres);
strcat(DirCompleta,dirEntry->d_name);



if((strcmp(dirEntry->d_name,".")==0)
				||(strcmp(dirEntry->d_name,"..")==0)
				)
			{
				continue;
			}
			else{

struct stat datosFichero;
lstat(DirCompleta,&datosFichero);

if(S_ISDIR(datosFichero.st_mode)){ //es una carpeta

}

else{//es un archivo envielo


//r = cumpleRegEx(entradaComandosCliente,"hola.txt");
r = cumpleRegEx(entradaComandosCliente,dirEntry->d_name);
if(r==1){
printf("*");
/*
memset(DirExactaArchivoEnLocal,'\0',sizeof(DirExactaArchivoEnLocal));
strcpy(DirExactaArchivoEnLocal,DirCompleta);
//*****************************************************************************************
CodigoMensajeEnviado = 4; //enviar archivo al servidor
EnvioMensaje = send(sockfd,&CodigoMensajeEnviado,sizeof(int),0);//se envia mensaje al servidor que se quiere enviar un archivo


//se envia el nombre del archivo
EnvioMensaje = send(sockfd,&dirEntry->d_name,sizeof(dirEntry->d_name),0);


char miRutaRemota[2048];
memset(miRutaRemota,'\0',sizeof(miRutaRemota));
strcpy(miRutaRemota,urlRuta);
printf("%s",miRutaRemota);
//se le pregunta al servidor si la url remota existe en el
EnvioMensaje = send(sockfd,&miRutaRemota,sizeof(miRutaRemota),0); //pregunta al servidor si dicha ruta remota existe en el



//ENVIO EL TAMANO DE ARCHIVO A SER ENVIADO
float tamanoArchivo;
FILE *archivoAMedir;
archivoAMedir=fopen(DirExactaArchivoEnLocal,"r");
fseek(archivoAMedir,0L,SEEK_END);
tamanoArchivo = ftell(archivoAMedir);
fclose(archivoAMedir);
EnvioMensaje = send(sockfd,&tamanoArchivo,sizeof(float),0); //envio el tamaño de archivo a ser enviado


//empiezo a enviar el archivo
FILE *archivoSolicitado2;
int bytesleidos2=0;
archivoSolicitado2 = fopen(DirExactaArchivoEnLocal,"rb");
fileBlock_t paqueteArchivo2;
while((bytesleidos2 = fread(paqueteArchivo2.buffer,1,10240,archivoSolicitado2))){
 paqueteArchivo2.tamanoBloque=bytesleidos2;
 send(sockfd,(void*)&paqueteArchivo2,sizeof(paqueteArchivo2),0);
}
fclose(archivoSolicitado2);

//*****************************************************************************************
*/

//DirExactaArchivoEnLocal
CodigoMensajeEnviado = 10; //enviar archivo al servidor
EnvioMensaje = send(sockfd,&CodigoMensajeEnviado,sizeof(int),0);//se envia mensaje al servidor que se quiere enviar un archivo


//dirEntry->d_name
//se envia el nombre del archivo

//300];
//[2048];
//2350];

char nombre[300];
strcpy(nombre,dirEntry->d_name);

EnvioMensaje = send(sockfd,&nombre,sizeof(nombre),0);

EnvioMensaje = send(sockfd,&urlRuta,sizeof(urlRuta),0); //pregunta al servidor si dicha ruta remota existe en el

//ENVIO EL TAMANO DE ARCHIVO A SER ENVIADO
float tamanoArchivo;
FILE *archivoAMedir;
archivoAMedir=fopen(DirCompleta,"r");
fseek(archivoAMedir,0L,SEEK_END);
tamanoArchivo = ftell(archivoAMedir);
fclose(archivoAMedir);
EnvioMensaje = send(sockfd,&tamanoArchivo,sizeof(float),0); //envio el tamaño de archivo a ser enviado

//empiezo a enviar el archivo
FILE *archivoSolicitado2;
int bytesleidos2=0;
archivoSolicitado2 = fopen(DirExactaArchivoEnLocal,"rb");
fileBlock_t paqueteArchivo2;
while((bytesleidos2 = fread(paqueteArchivo2.buffer,1,10240,archivoSolicitado2))){
 paqueteArchivo2.tamanoBloque=bytesleidos2;
 send(sockfd,(void*)&paqueteArchivo2,sizeof(paqueteArchivo2),0);
}
fclose(archivoSolicitado2);
ReciboMensaje = recv(sockfd,&CodigoMensajeRecibido,sizeof(int),MSG_WAITALL);

}
else
{

}

//remove(DirCompleta);
} //fin es un archivo

}

}
//rmdir(dirAddres);
}


 //fin while




}//fin mput

//***************************************DELETE se borra archivo del lado del servidor
if(!strcmp(entradaComandosCliente,"delete")){//se pide borrar un archivo en la maquina remota

puts("Introducir nombre de archivo a borrar ->: ");
__fpurge(stdin); //se limpia el buffer de entrada principal
memset(entradaComandosCliente,'\0',sizeof(entradaComandosCliente));
fgets(entradaComandosCliente,sizeof(entradaComandosCliente),stdin); //se obtiene el nombre de archivo a recuperar
//eliminacion de enter del nombre de archivo a recuperar para evitar contaminar el parametro
entradaComandosCliente[strlen(entradaComandosCliente)-1]='\0';


CodigoMensajeEnviado = 6; //Quiero borrar un archivo del lado del servidor
EnvioMensaje = send(sockfd,&CodigoMensajeEnviado,sizeof(int),0);

//envio la url remota que se desea usar para borrar de ahi lo referente al server
EnvioMensaje = send(sockfd,&urlRuta,sizeof(urlRuta),0);
__fpurge(stdin); //se limpia el buffer de entrada principal

//envio el nombre de archivo que deseo borrar
EnvioMensaje = send(sockfd,&entradaComandosCliente,sizeof(entradaComandosCliente),0);

//se espera respuesta a ver que es lo que paso
ReciboMensaje = recv(sockfd,&CodigoMensajeRecibido,sizeof(int),MSG_WAITALL); //se recibe respuesta por parte del servidor
if(CodigoMensajeRecibido == 0){ // No existe el archivo que se solicito borrar
puts("\nNo existe el archivo que se solicito borrar\n");
__fpurge(stdin); //se limpia el buffer de entrada principal
}
if(CodigoMensajeRecibido == 1){ // Se borro con exito el archivo
puts("\nSe borro con exito el archivo\n");
__fpurge(stdin); //se limpia el buffer de entrada principal
}
if(CodigoMensajeRecibido == 2){ // No se logro borrar el archivo
puts("\n\No se logro borrar el archivo\n");
__fpurge(stdin); //se limpia el buffer de entrada principal
}

}//Fin delete

//**************************************RENAME se renombra archivo del lado del servidor**************************
if(!strcmp(entradaComandosCliente,"rename")){ // se piensa renombrar un archivo en el servidor
CodigoMensajeEnviado = 7; //Quiero renombrar un archivo del lado del servidor
EnvioMensaje = send(sockfd,&CodigoMensajeEnviado,sizeof(int),0);


EnvioMensaje = send(sockfd,&urlRuta,sizeof(urlRuta),0);
char nombreActualArchivo[300];
char nombreNuevoArchivo[300];
puts("Introducir nombre de archivo a ser renombrado ->: ");
__fpurge(stdin); //se limpia el buffer de entrada principal
memset(entradaComandosCliente,'\0',sizeof(entradaComandosCliente));
fgets(entradaComandosCliente,sizeof(entradaComandosCliente),stdin); //se obtiene el nombre de archivo a renombrar
//eliminacion de enter del nombre de archivo a recuperar para evitar contaminar el parametro
entradaComandosCliente[strlen(entradaComandosCliente)-1]='\0';

strcpy(nombreActualArchivo,entradaComandosCliente);
__fpurge(stdin); //se limpia el buffer de entrada principal
EnvioMensaje = send(sockfd,&nombreActualArchivo,sizeof(nombreActualArchivo),0);

puts("\n");
puts("Introducir nuevo nombre de archivo->: ");
memset(entradaComandosCliente,'\0',sizeof(entradaComandosCliente));
fgets(entradaComandosCliente,sizeof(entradaComandosCliente),stdin); //se obtiene el nuevo nombre de archivo
//eliminacion de enter del nombre de archivo a recuperar para evitar contaminar el parametro
entradaComandosCliente[strlen(entradaComandosCliente)-1]='\0';

strcpy(nombreNuevoArchivo,entradaComandosCliente);
__fpurge(stdin); //se limpia el buffer de entrada principal
EnvioMensaje = send(sockfd,&nombreNuevoArchivo,sizeof(nombreNuevoArchivo),0);

//se espera respuesta a ver que es lo que paso
ReciboMensaje = recv(sockfd,&CodigoMensajeRecibido,sizeof(int),MSG_WAITALL); //se recibe respuesta por parte del servidor
if(CodigoMensajeRecibido == 0){ // No existe el archivo que se solicito borrar
puts("\nNo existe el archivo que se solicito renombrar\n");
__fpurge(stdin); //se limpia el buffer de entrada principal
}
if(CodigoMensajeRecibido == 1){ // Se borro con exito el archivo
puts("\nSe renombro con exito el archivo\n");
__fpurge(stdin); //se limpia el buffer de entrada principal
}
if(CodigoMensajeRecibido == 2){ // No se logro borrar el archivo
puts("\n\No se logro renombrar el archivo \n");
__fpurge(stdin); //se limpia el buffer de entrada principal
}


} //Fin rename

//********************************************************RMDIR
if(!strcmp(entradaComandosCliente,"rmdir")){ //borrar un directorio del lado del servidor 
CodigoMensajeEnviado = 8; //Quiero borrar un directorio remoto
EnvioMensaje = send(sockfd,&CodigoMensajeEnviado,sizeof(int),0);


char directorioASerBorrado[2048];

puts("Introducir direccion del directorio a ser borrado ->: ");
__fpurge(stdin); //se limpia el buffer de entrada principal
memset(directorioASerBorrado,'\0',sizeof(directorioASerBorrado));
fgets(directorioASerBorrado,sizeof(directorioASerBorrado),stdin); //se obtiene el nombre de archivo a renombrar
//eliminacion de enter del nombre de archivo a recuperar para evitar contaminar el parametro
directorioASerBorrado[strlen(directorioASerBorrado)-1]='\0';

EnvioMensaje = send(sockfd,&directorioASerBorrado,sizeof(directorioASerBorrado),0);

ReciboMensaje = recv(sockfd,&CodigoMensajeRecibido,sizeof(int),MSG_WAITALL);
if(CodigoMensajeRecibido == 0){
puts("\nNo existe el directorio que esta intentando borrar\n");
}
if(CodigoMensajeRecibido == 1){
puts("\nSe borro con exito dicho directorio\n");
}
if(CodigoMensajeRecibido == 2){
puts("\nExistio un error a la hora de borrar el directorio\n");
}
if(CodigoMensajeRecibido == 3){
puts("\nEsta intentando borrar el servidor - acceso denegado\n");
}
__fpurge(stdin); //se limpia el buffer de entrada principal
} //fin RMDIR


//********************************************************MKDIR se crea un directorio en la maquina remota
if(!strcmp(entradaComandosCliente,"mkdir")){ //crear un directorio del lado del servidor
CodigoMensajeEnviado = 9; //Quiero crear un directorio remoto
EnvioMensaje = send(sockfd,&CodigoMensajeEnviado,sizeof(int),0);

char directorioASerCreado[2048];

puts("Introducir direccion del directorio a ser creado ->: ");
__fpurge(stdin); //se limpia el buffer de entrada principal
memset(directorioASerCreado,'\0',sizeof(directorioASerCreado));
fgets(directorioASerCreado,sizeof(directorioASerCreado),stdin); //se obtiene el nombre de archivo a renombrar
//eliminacion de enter del nombre de archivo a recuperar para evitar contaminar el parametro
directorioASerCreado[strlen(directorioASerCreado)-1]='\0';

EnvioMensaje = send(sockfd,&directorioASerCreado,sizeof(directorioASerCreado),0);

if(CodigoMensajeRecibido == 1){
puts("\nSe creo con exito dicho directorio\n");
}
if(CodigoMensajeRecibido == 2){
puts("\nNo se pudo crear el directorio\n");
}
if(CodigoMensajeRecibido == 3){
puts("\nEl directorio ya existe\n");
}
__fpurge(stdin); //se limpia el buffer de entrada principal


}//fin MKDIR

//********************************************************PUT SE ENVIA ARCHIVO AL SERVIDOR REMOTO****************
if(!strcmp(entradaComandosCliente,"put")){
puts("Introducir nombre de archivo a ser enviado ->: ");
__fpurge(stdin); //se limpia el buffer de entrada principal
memset(entradaComandosCliente,'\0',sizeof(entradaComandosCliente));
fgets(entradaComandosCliente,sizeof(entradaComandosCliente),stdin); //se obtiene el nombre de archivo a enviar
//eliminacion de enter del nombre de archivo a recuperar para evitar contaminar el parametro
entradaComandosCliente[strlen(entradaComandosCliente)-1]='\0';
__fpurge(stdin); //se limpia el buffer de entrada principal
char DirExactaArchivoEnLocal[2350]; //se guardara aca la direccion exacta del archivo

//se verifica que el actual directorio local exista
DIR *dir;
dir = opendir(urlLocal);
if(dir){ //existe el directorio local actual
strcpy(DirExactaArchivoEnLocal,urlLocal);
strcat(DirExactaArchivoEnLocal,entradaComandosCliente);
closedir(dir);
}
else{ //no existe el directorio local actual - se usa el por defecto donde se ubica el servidor
printf("\nNo existe el directorio local actual en el cliente - se usara la ubicacion def\n");
getcwd(DirExactaArchivoEnLocal,sizeof(DirExactaArchivoEnLocal));
strcat(DirExactaArchivoEnLocal,caracterFSlash);
strcat(DirExactaArchivoEnLocal,entradaComandosCliente);
}


if(exists(DirExactaArchivoEnLocal)==1){
CodigoMensajeEnviado = 4; //enviar archivo al servidor
EnvioMensaje = send(sockfd,&CodigoMensajeEnviado,sizeof(int),0);//se envia mensaje al servidor que se quiere enviar un archivo

//se envia el nombre del archivo
EnvioMensaje = send(sockfd,&entradaComandosCliente,sizeof(entradaComandosCliente),0);


char miRutaRemota[2048];
strcpy(miRutaRemota,urlRuta);
//se le pregunta al servidor si la url remota existe en el
EnvioMensaje = send(sockfd,&miRutaRemota,sizeof(miRutaRemota),0); //pregunta al servidor si dicha ruta remota existe en el



//ENVIO EL TAMANO DE ARCHIVO A SER ENVIADO
float tamanoArchivo;
FILE *archivoAMedir;
archivoAMedir=fopen(DirExactaArchivoEnLocal,"r");
fseek(archivoAMedir,0L,SEEK_END);
tamanoArchivo = ftell(archivoAMedir);
fclose(archivoAMedir);
EnvioMensaje = send(sockfd,&tamanoArchivo,sizeof(float),0); //envio el tamaño de archivo a ser enviado


//empiezo a enviar el archivo
FILE *archivoSolicitado2;
int bytesleidos2=0;
archivoSolicitado2 = fopen(DirExactaArchivoEnLocal,"rb");
fileBlock_t paqueteArchivo2;
while((bytesleidos2 = fread(paqueteArchivo2.buffer,1,10240,archivoSolicitado2))){
 paqueteArchivo2.tamanoBloque=bytesleidos2;
 send(sockfd,(void*)&paqueteArchivo2,sizeof(paqueteArchivo2),0);
}
fclose(archivoSolicitado2);
 
}
else{
printf("\nEl archivo que se quiere enviar no existe en el directorio local o el directorio local esta errado (la ruta siempre debe terminar con /)\n");
}

} //*******FIN PUT

//********************************************************GET SE OBTIENE ARCHIVO DEL SERVIDOR REMOTO***********************
if(!strcmp(entradaComandosCliente,"get")){ //se recupera un archivo del directorio remoto
puts("Introducir nombre de archivo a recuperar ->: ");
__fpurge(stdin); //se limpia el buffer de entrada principal
memset(entradaComandosCliente,'\0',sizeof(entradaComandosCliente));
fgets(entradaComandosCliente,sizeof(entradaComandosCliente),stdin); //se obtiene el nombre de archivo a recuperar
//eliminacion de enter del nombre de archivo a recuperar para evitar contaminar el parametro
entradaComandosCliente[strlen(entradaComandosCliente)-1]='\0';
__fpurge(stdin); //se limpia el buffer de entrada principal
CodigoMensajeEnviado = 3; //recuperar archivo del servidor
EnvioMensaje = send(sockfd,&CodigoMensajeEnviado,sizeof(int),0);
char DirExactaArchivo[2350];
strcpy(DirExactaArchivo,urlRuta);
strcat(DirExactaArchivo,entradaComandosCliente);
EnvioMensaje = send(sockfd,&DirExactaArchivo,sizeof(DirExactaArchivo),0); //pregunta al servidor si dicho archivo existe

ReciboMensaje = recv(sockfd,&CodigoMensajeRecibido,sizeof(int),MSG_WAITALL); //se recibe respuesta por parte del servidor

if(CodigoMensajeRecibido == 1){ //si existe el archivo
printf("\nInicio de recuperacion de archivo\n");
float tamanoarchivoaserrecibido;
int bytesrecibidos=0;
ReciboMensaje = recv(sockfd,&tamanoarchivoaserrecibido,sizeof(float),MSG_WAITALL); //Se recibe el tamaño de archivo a ser recibido

//se determina si el directorio local existe o no
DIR *d;
d = opendir(urlLocal);
char DirExactaASerCopiado[2350];
if(d){ //existe el directorio local actual

strcpy(DirExactaASerCopiado,urlLocal);
strcat(DirExactaASerCopiado,entradaComandosCliente);
closedir(d);
}
else{ //no existe el directorio local actual - se usa el por defecto donde se ubica el servidor
printf("\nNo existe el directorio local actual en el cliente - se usara la ubicacion def\n");
getcwd(DirExactaASerCopiado,sizeof(DirExactaASerCopiado));
strcat(DirExactaASerCopiado,caracterFSlash);
strcat(DirExactaASerCopiado,entradaComandosCliente);
}

printf("aca se get el archivo -> %s",DirExactaASerCopiado);

                        //empiezo a recibir el archivo 
                        FILE *newFile;
			newFile = fopen(DirExactaASerCopiado, "wb+"); 
			fileBlock_t fb;
			while(bytesrecibidos<tamanoarchivoaserrecibido){
					recv(sockfd,(void*)&fb, sizeof(fb), MSG_WAITALL);
					bytesrecibidos = bytesrecibidos + fb.tamanoBloque;
					fwrite(fb.buffer, 1, fb.tamanoBloque, newFile);
			}
			fclose(newFile);


}
if(CodigoMensajeRecibido == 0){ //no existe el archivo
 printf("\nno existe el archivo o el directorio esta errado\n");
}

}
//****************FIN DE GET

if(!strcmp(entradaComandosCliente,"cd")){ //se pide que se cambie el directorio remoto actual
puts("Introducir nuevo directorio remoto (la ruta siempre debe terminar con /)-> :");
__fpurge(stdin); //se limpia el buffer de entrada principal
fgets(entradaComandosCliente,sizeof(entradaComandosCliente),stdin); //se obtiene el nuevo directorio local
//eliminacion de enter del nuevo directorio remoto para evitar contaminar el parametro
entradaComandosCliente[strlen(entradaComandosCliente)-1]='\0';
__fpurge(stdin); //se limpia el buffer de entrada principal
memset(urlRuta,'\0',sizeof(urlRuta));
strcpy(urlRuta,entradaComandosCliente);
printf("%s",urlRuta);
}

if(!strcmp(entradaComandosCliente,"lcd")){ //se pide que se cambie el directorio local actual
puts("Introducir nuevo directorio local (la ruta siempre debe terminar con /)-> :");
__fpurge(stdin); //se limpia el buffer de entrada principal
fgets(entradaComandosCliente,sizeof(entradaComandosCliente),stdin); //se obtiene el nuevo directorio local
//eliminacion de enter del nuevo directorio local para evitar contaminar el parametro
entradaComandosCliente[strlen(entradaComandosCliente)-1]='\0';
__fpurge(stdin); //se limpia el buffer de entrada principal
memset(urlLocal,'\0',sizeof(urlLocal));
strcpy(urlLocal,entradaComandosCliente);
printf("%s",urlLocal);
}





} // end Cliente en confianza con servidor

if(AceptadoPorCliente == 0){ //**********Cliente no esta relacionado con ningun servidor********

if(!strcmp(entradaComandosCliente,"quit")){ //se pide la salida total del programa
puts("\nSalida el programa\n");
exit(0);
}

if(!strcmp(entradaComandosCliente,"open")){ //se pide que se logre una nueva conexion con una nueva ip
puts("Introducir nueva direccion ip-> :");
__fpurge(stdin); //se limpia el buffer de entrada principal
fgets(entradaComandosCliente,sizeof(entradaComandosCliente),stdin); //se obtiene la nueva direccion ip
//eliminacion de enter de la ip para evitar contaminar el parametro
entradaComandosCliente[strlen(entradaComandosCliente)-1]='\0';
//printf("%s",entradaComandosCliente);
__fpurge(stdin); //se limpia el buffer de entrada principal
memset(direccionIp,'\0',sizeof(direccionIp));
strcpy(direccionIp,entradaComandosCliente);
printf("%s",direccionIp);
goto iniciodehilocliente;
}

if(!strcmp(entradaComandosCliente,"lcd")){ //se pide que se cambie el directorio local actual
puts("Introducir nuevo directorio local-> :");
__fpurge(stdin); //se limpia el buffer de entrada principal
fgets(entradaComandosCliente,sizeof(entradaComandosCliente),stdin); //se obtiene el nuevo directorio local
//eliminacion de enter del nuevo directorio local para evitar contaminar el parametro
entradaComandosCliente[strlen(entradaComandosCliente)-1]='\0';
__fpurge(stdin); //se limpia el buffer de entrada principal
memset(urlLocal,'\0',sizeof(urlLocal));
strcpy(urlLocal,entradaComandosCliente);
printf("%s",urlLocal);
}

}//end Cliente no esta relacionado con ningun servidor
__fpurge(stdin); //se limpia el buffer de entrada principal
}//end del while


}

void *funcionInstanciaServidorAtiendeCliente(void *arg){
printf("\nSe inicia un hilo en el servidor para atender conexiones\n");
int socket;
int n;
socket = (int *)arg;

int EnvioMensaje;
int ReciboMensaje;
int CodigoMensajeEnviado;
int CodigoMensajeRecibido;
int ModoEnvio = 0;
int ModoRecibido = 1;

while(encendidoServidor == 1){

char concatenadouserpass[4097];
ReciboMensaje = recv(socket,&CodigoMensajeRecibido,sizeof(int), MSG_WAITALL);


//*******************************CODIGO PROTOCOLO 1: Verificacion del user pass********************
if(CodigoMensajeRecibido == 1){ //Verificacion de user pass
ReciboMensaje = recv(socket,&concatenadouserpass,sizeof(concatenadouserpass),MSG_WAITALL);
//printf("verificar user pass-> %s",concatenadouserpass);
if(fExisteRegistro(concatenadouserpass) == 1){ //Existe el password y username
//printf("\nsi existe el user name y password\n");
CodigoMensajeEnviado = 1;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}
else{ //No Existe el password y username
//printf("\nNo existe el user name y password\n");
printf("\nSe expulsa conexion no autenticada\n");
CodigoMensajeEnviado = 0;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
pthread_exit(NULL);
}
}//fin Verificacion de user pass

//*****************************CODIGO PROTOCOLO 2: Cierre de conexion por parte del cliente*********
if(CodigoMensajeRecibido == 2){ //Cierre de conexion enviado por parte del cliente
printf("\nSe desconecto conexion\n");
pthread_exit(NULL);
} //fin Cierre de conexion enviado por parte del cliente

//*****************************CODIGO PROTOCOLO 3: El cliente quierer recuperar un archivo**********
if(CodigoMensajeRecibido == 3){//El cliente solicita que quiere recuperar un archivo
char DirExactaArchivo[2350];
ReciboMensaje = recv(socket,&DirExactaArchivo,sizeof(DirExactaArchivo),MSG_WAITALL); //Mandan la urlRemota desde el server
__fpurge(stdin); //se limpia el buffer de entrada principal
puts(DirExactaArchivo);
__fpurge(stdin); //se limpia el buffer de entrada principal
if(exists(DirExactaArchivo)==1){
CodigoMensajeEnviado = 1; // si existe el archivo
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);

//mido el tamaño en bytes del archivo
float tamanoArchivo;
FILE *archivoAMedir;
archivoAMedir=fopen(DirExactaArchivo,"r");
fseek(archivoAMedir,0L,SEEK_END);
tamanoArchivo = ftell(archivoAMedir);
fclose(archivoAMedir);
EnvioMensaje = send(socket,&tamanoArchivo,sizeof(float),0); //envio el tamaño de archivo a ser enviado

//Apertura de archivo a ser enviado
FILE *archivoSolicitado;
int bytesleidos=0;
archivoSolicitado = fopen(DirExactaArchivo,"rb");
fileBlock_t paqueteArchivo;
//Envio de paquetes hasta lograr transferir por completo el archivo
while((bytesleidos = fread(paqueteArchivo.buffer,1,10240,archivoSolicitado))){
 paqueteArchivo.tamanoBloque=bytesleidos;
 send(socket,(void*)&paqueteArchivo,sizeof(paqueteArchivo),0);
}
fclose(archivoSolicitado);
}
else{
CodigoMensajeEnviado = 0; // no existe el archivo
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}
                       
}//fin Cliente solicita que quiere recuperar un archivo

//*************************************CODIGO PROTOCOLO: 4 El cliente quiere guardar un archivo en el servidor*************
if(CodigoMensajeRecibido == 4){ //El cliente solicita que quiere enviar un archivo al servidor
//Recibo nombre del archivo
char nombreArchivoAGrabar[300];
ReciboMensaje = recv(socket,&nombreArchivoAGrabar,sizeof(nombreArchivoAGrabar),MSG_WAITALL);

//Recibo la ruta remota desde el cliente
char rutaURLRemotaDelCliente[2048];
ReciboMensaje = recv(socket,&rutaURLRemotaDelCliente,sizeof(rutaURLRemotaDelCliente),MSG_WAITALL);

//determino si la ruta sugerida por el cliente es valida sino se usa la de por defecto
DIR *directorium;
directorium = opendir(rutaURLRemotaDelCliente);

char DirExactaASerGrabado[2350];
if(directorium){ //existe el directorio local actual <- Se guardara en la ruta que solicita el cliente
strcpy(DirExactaASerGrabado,rutaURLRemotaDelCliente);
strcat(DirExactaASerGrabado,nombreArchivoAGrabar);
closedir(directorium);
}
else{ //no existe el directorio remoto enviado por el cliente - se usa el por defecto donde se ubica el servidor <- Se guardara en la ruta actual donde esta el server
 
//***************************************************************************************
 getcwd(DirExactaASerGrabado,sizeof(DirExactaASerGrabado));
 strcat(DirExactaASerGrabado,caracterFSlash);
 strcat(DirExactaASerGrabado,nombreArchivoAGrabar);
}
printf("%s",DirExactaASerGrabado);

float tamanoarchivoaserrecibido;
int bytesrecibidos=0;
ReciboMensaje = recv(socket,&tamanoarchivoaserrecibido,sizeof(float),MSG_WAITALL); //Se recibe el tamaño de archivo a ser recibido


                        //se empieza a recibir el archivo
                        FILE *newFile;
			newFile = fopen(DirExactaASerGrabado, "wb+"); 
			fileBlock_t fb;
			while(bytesrecibidos<tamanoarchivoaserrecibido){
					recv(socket,(void*)&fb, sizeof(fb), MSG_WAITALL);
					bytesrecibidos = bytesrecibidos + fb.tamanoBloque;
					fwrite(fb.buffer, 1, fb.tamanoBloque, newFile);
			}
			fclose(newFile);


}//fin Cliente solicita que quiere enviar un archivo al servidor
//##################################################
if(CodigoMensajeRecibido == 10){ //El cliente solicita que quiere enviar un archivo al servidor
//Recibo nombre del archivo
char nombreArchivoAGrabar[300];
ReciboMensaje = recv(socket,&nombreArchivoAGrabar,sizeof(nombreArchivoAGrabar),MSG_WAITALL);

//Recibo la ruta remota desde el cliente
char rutaURLRemotaDelCliente[2048];
ReciboMensaje = recv(socket,&rutaURLRemotaDelCliente,sizeof(rutaURLRemotaDelCliente),MSG_WAITALL);

//determino si la ruta sugerida por el cliente es valida sino se usa la de por defecto
DIR *directorium;
directorium = opendir(rutaURLRemotaDelCliente);

char DirExactaASerGrabado[2350];
if(directorium){ //existe el directorio local actual <- Se guardara en la ruta que solicita el cliente
strcpy(DirExactaASerGrabado,rutaURLRemotaDelCliente);
strcat(DirExactaASerGrabado,nombreArchivoAGrabar);
closedir(directorium);
}
else{ //no existe el directorio remoto enviado por el cliente - se usa el por defecto donde se ubica el servidor <- Se guardara en la ruta actual donde esta el server
 
//***************************************************************************************
 getcwd(DirExactaASerGrabado,sizeof(DirExactaASerGrabado));
 strcat(DirExactaASerGrabado,caracterFSlash);
 strcat(DirExactaASerGrabado,nombreArchivoAGrabar);
}
printf("%s",DirExactaASerGrabado);

float tamanoarchivoaserrecibido;
int bytesrecibidos=0;
ReciboMensaje = recv(socket,&tamanoarchivoaserrecibido,sizeof(float),MSG_WAITALL); //Se recibe el tamaño de archivo a ser recibido


                        //se empieza a recibir el archivo
                        FILE *newFile;
			newFile = fopen(DirExactaASerGrabado, "wb+"); 
			fileBlock_t fb;
			while(bytesrecibidos<tamanoarchivoaserrecibido){
					recv(socket,(void*)&fb, sizeof(fb), MSG_WAITALL);
					bytesrecibidos = bytesrecibidos + fb.tamanoBloque;
					fwrite(fb.buffer, 1, fb.tamanoBloque, newFile);
			}
			fclose(newFile);

CodigoMensajeEnviado = 1;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}//fin Cliente solicita que quiere enviar un archivo al servidor
//########################

//***************************CODIGO PROTOCOLO: 5 - El cliente solicita un listado del directorio remoto del cliente
if(CodigoMensajeRecibido == 5){// Se solicita un listado del directorio remoto del cliente
char urlRemEnServ[2048];
ReciboMensaje = recv(socket,&urlRemEnServ,sizeof(urlRemEnServ),MSG_WAITALL); //se recibe la ruta que el cliente quiere que sea listada

//se determina si dicha ruta existe caso contrario se devuelve el listado de la ruta standard
DIR *dirz;
dirz = opendir(urlRemEnServ);

char DirectorioASerListado[2048];
if(dirz){ //existe el directorio local actual
strcpy(DirectorioASerListado,urlRemEnServ);
closedir(dirz);
}
else{ //no existe el directorio local actual - se usa el por defecto donde se ubica el servidor
//printf("\nNo existe el directorio local actual en el cliente - se usara la ubicacion def\n");
getcwd(DirectorioASerListado,sizeof(DirectorioASerListado));
strcat(DirectorioASerListado,caracterFSlash);
}
//struct fileInfo_t listadoDeArchivos[400];
//*listadoDeArchivos = listarDirectoriox(DirectorioASerListado);

listarDirectorio(DirectorioASerListado);
//filesInDirectory en lugar de DirectorioASerListado
EnvioMensaje = send(socket,&filesInDirectory,sizeof(filesInDirectory),0);

//free((fileInfo_t*)filesInDirectory);
//EnvioMensaje = send(socket,&listadoDeArchivos,sizeof(listadoDeArchivos),0);
}//fin Se solicita un listado del directorio remoto del cliente

//************************CODIGO PROTOCOLO: 6 - El cliente solicita borrar un archivo en el servidor
if(CodigoMensajeRecibido == 6){
char urlRemEnServ2[2048];
ReciboMensaje = recv(socket,&urlRemEnServ2,sizeof(urlRemEnServ2),MSG_WAITALL); //se recibe la ruta que el cliente quiere para que el archivo sea borrado

char nombreArchivoASerBorrado[300];
ReciboMensaje = recv(socket,&nombreArchivoASerBorrado,sizeof(nombreArchivoASerBorrado),MSG_WAITALL);

//se determina si dicha ruta existe caso contrario devuelve el listado de la ruta standard
DIR *dirz2;
dirz2 = opendir(urlRemEnServ2);
char DirectorioDeElementoASerBorrado[2350];
if(dirz2){ //existe el directorio
strcpy(DirectorioDeElementoASerBorrado,urlRemEnServ2);
closedir(dirz2);
}
else{ //no existe el directio - se usa el por defecto donde se ubica el servidor
getcwd(DirectorioDeElementoASerBorrado,sizeof(DirectorioDeElementoASerBorrado));
strcat(DirectorioDeElementoASerBorrado,caracterFSlash);
}

//pego la url con el nombre del archivo
strcat(DirectorioDeElementoASerBorrado,nombreArchivoASerBorrado);

//determino si existe o no el archivo
if(exists(DirectorioDeElementoASerBorrado) == 1){ //si existe el archivo por lo tanto se borro con exito
int statusBorrado;
statusBorrado = remove(DirectorioDeElementoASerBorrado);

if(statusBorrado == 0){ //borrado con exito
CodigoMensajeEnviado = 1;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0); 
}
else{ // no se pudo borrar el archivo
CodigoMensajeEnviado = 2;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}

}
else{ //no existe el archivo por lo tanto no se borro
CodigoMensajeEnviado = 0; // no existe el archivo
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}

} //fin El cliente solicita borrar un archivo en el servidor

//*******************************CODIGO PROTOCOLO 7 El cliente desea renombrar un archivo
if(CodigoMensajeRecibido == 7){

char urlRemEnServ3[2048];
ReciboMensaje = recv(socket,&urlRemEnServ3,sizeof(urlRemEnServ3),MSG_WAITALL); //se recibe la ruta que el cliente quiere para que el archivo sea borrado

char nombreArchivoASerRenombrado[300];
ReciboMensaje = recv(socket,&nombreArchivoASerRenombrado,sizeof(nombreArchivoASerRenombrado),MSG_WAITALL);

char nuevoNombreParaArchivo[300];
ReciboMensaje = recv(socket,&nuevoNombreParaArchivo,sizeof(nuevoNombreParaArchivo),MSG_WAITALL);

//se determina si dicha ruta existe caso contrario devuelve el listado de la ruta standard
DIR *dirz3;
dirz3 = opendir(urlRemEnServ3);
char DirectorioDeArchivoASerRenombrado[2350];
char DirectorioDeArchivoASerRenombradoAuxiliar[2350]; // se usa para concatenar al nuevo nombre y poder convertir con la misma ruta
if(dirz3){ //existe el directorio
strcpy(DirectorioDeArchivoASerRenombrado,urlRemEnServ3);
closedir(dirz3);
}
else{ //no existe el directio - se usa el por defecto donde se ubica el servidor
getcwd(DirectorioDeArchivoASerRenombrado,sizeof(DirectorioDeArchivoASerRenombrado));
strcat(DirectorioDeArchivoASerRenombrado,caracterFSlash);
}

strcpy( DirectorioDeArchivoASerRenombradoAuxiliar,DirectorioDeArchivoASerRenombrado);
//se determina si existe el archivo a ser renombrado
strcat(DirectorioDeArchivoASerRenombrado,nombreArchivoASerRenombrado);
strcat(DirectorioDeArchivoASerRenombradoAuxiliar,nuevoNombreParaArchivo);
if(exists(DirectorioDeArchivoASerRenombrado)==1){//existe el archivo a ser renombrado
int estadoRenombrar;

estadoRenombrar = rename(DirectorioDeArchivoASerRenombrado,DirectorioDeArchivoASerRenombradoAuxiliar);

if(estadoRenombrar == 0){ //se logro renombrar con exito el archivo
CodigoMensajeEnviado = 1;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}
else{ // no se logro renombrar el archivo
CodigoMensajeEnviado = 2;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}

}
else{ // no existe el archivo que esta deseando renombrar
CodigoMensajeEnviado = 0;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}


} //fin protocolo 7 renombrar

//*******************************CODIGO PROTOCOLO 8 El cliente desea borrar un directorio
if(CodigoMensajeRecibido == 8){
char urlRemEnServ4[2048];
ReciboMensaje = recv(socket,&urlRemEnServ4,sizeof(urlRemEnServ4),MSG_WAITALL); //se recibe la ruta que el cliente quiere borrar

//se determina si dicha ruta existe caso contrario devuelve el listado de la ruta standard
DIR *dirz4;
dirz4 = opendir(urlRemEnServ4);
char DirectorioDeServidor[2348];

if(dirz4){ //existe el directorio
closedir(dirz4);
getcwd(DirectorioDeServidor,sizeof(DirectorioDeServidor)); //quiero saber donde se encuentra el servidor en este momento
strcat(DirectorioDeServidor,caracterFSlash);

if(!strcmp(urlRemEnServ4,DirectorioDeServidor)){ // si son iguales no se permite el borrado pues se esta intentando borrar el servidor
CodigoMensajeEnviado = 3;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}//fin si son iguales no se permite borrado
else{ //se intenta borrar
int resultado = 0;
resultado = borrarDirectorio(urlRemEnServ4);

if(resultado == 1){//se borro con exito
CodigoMensajeEnviado = 1;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}
else{ //no se pudo borrar
CodigoMensajeEnviado = 2;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}

} //fin se intenta borrar
}//fin existe el directorio

else{ //no existe el directorio solicitado
CodigoMensajeEnviado = 0;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}



}//fin protocolo 8 borrar directorio en el lado del servidor


//*******************************CODIGO PROTOCOLO 9 El cliente desea crear un directorio
if(CodigoMensajeRecibido == 9){

char urlRemEnServ5[2048];
ReciboMensaje = recv(socket,&urlRemEnServ5,sizeof(urlRemEnServ5),MSG_WAITALL); //se recibe la ruta que el cliente quiere borrar

//se determina si dicha ruta existe caso contrario devuelve el listado de la ruta standard
DIR *dirz5;
dirz5 = opendir(urlRemEnServ5);
char DirectorioDeServidor[2348];

if(dirz5){ //existe el directorio
closedir(dirz5);
CodigoMensajeEnviado = 3; // se le comunica al cliente que la carpeta ya existe
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}
else{
int status = 0;
status = mkdir(urlRemEnServ5,00777);

if(status == 0){
CodigoMensajeEnviado = 1;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}
if(status == -1){
CodigoMensajeEnviado = 2;
EnvioMensaje = send(socket,&CodigoMensajeEnviado,sizeof(int),0);
}

}

}//fin protocolo 9 crear un directorio mkdir


}


}

void *funcionServidor(){
//Se ponen en funcionamiento todas las estructuras de registro del respectivo servidor
                        printf("**Encendiendo server**\n");
			printf("Esperando conexion de cliente...\n\n");

//Se monta socket 
	int sockfd, newsockfd;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;	
	int n;
	//printf("flag1\n");
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd < 0)
		error("ERROR: No se ha logrado crear el socket de conexion");
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;							
	serv_addr.sin_addr.s_addr = INADDR_ANY;					
	serv_addr.sin_port = htons(PORT);					
	
	//printf("flag2\n");
	int yes = 1;
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (yes)) == -1) {
		perror("setsockopt");
		exit(1);
	}
        //printf("flag3\n");
	//Enlaza la dirección con el puerto respectivo
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(struct sockaddr)) < 0){ 
		error("ERROR: No se ha logrado enlazar la direccion con el puerto especificado");
	}

        // printf("flag4\n");
        pthread_t idHiloCliente;
        pthread_create(&idHiloCliente,NULL,funcionCliente,NULL);
        //pthread_join(idHiloCliente,NULL);

       while(1==1){

         // printf("flag5\n");
	//Llamada a listen() que permite escuchar conexiones por socket
 	if (listen(sockfd, BACKLOG) == -1) {
        printf("Error en Listen()\n");
        exit(-1);
    }

        // printf("flag6\n");
        //Llamada a accept() que permite bloquear el proceso hasta recibir conexion
	clilen = sizeof(cli_addr);
        //printf("esperando cliente");
        // printf("flag7\n");
	newsockfd =	accept(sockfd, (struct sockaddr *) &cli_addr,&clilen);
        //  printf("flag8\n");
	if (newsockfd < 0){
		error("ERROR: Ha ocurrido un error al aceptar la conexion con el cliente");}
         else{
        //  printf("flag9\n");
         printf("\nNueva conexion entrante");

         pthread_t h1;
         pthread_create(&h1,NULL,funcionInstanciaServidorAtiendeCliente,newsockfd);
        // pthread_join(h1,NULL);
            }
        }
        
}


void *funciondelhilo(void *parametro){
printf("\nSoy un hilo posix\n");
//printf("%s",urlRuta);

}


void *ImprimirEncabezado(){
printf("\nInstituto Tecnologico De Costa Rica\n");
printf("Principios de Sistemas Operativos\n");
printf("Prof. Ing. Armando Arce\n");
printf("Proyecto 3 12/11/2014\n");
printf("Estudiantes:Jose Carlos Alvarez Umana\n");
printf("Christian Matarrita\n");
}


int *ObtenerSubCadenaHasta(char cadenaEntrada[], char puntoDeFinalizacion[]){
  int longitudCadenaEntrada = strlen(cadenaEntrada);
  longitudCadenaEntrada = longitudCadenaEntrada - 1;
  int index = 0;
  
  char *puntero;
  char *puntero2;
  puntero = cadenaEntrada;
  puntero2 = puntoDeFinalizacion;

  while(index <= longitudCadenaEntrada){
  if(*puntero == *puntero2){
  return 1;
  }
  bufferW2[index] = *puntero;
  puntero = puntero + 1;
  index = index + 1;
  } 
  return 1;
  
}

int *CortarSubCadenaHasta(char cadenaEntrada[], char puntoDeFinalizacion[]){
 int longitudCadenaEntrada = strlen(cadenaEntrada);
 longitudCadenaEntrada = longitudCadenaEntrada - 1;
 int index = 0;
 
 char *puntero;
 puntero = cadenaEntrada;
 int readyToCopy = 0;
 int indexCopy = 0;
 while(index <= longitudCadenaEntrada){ 
  if(readyToCopy == 1){
  bufferW3[indexCopy] = *puntero;
  indexCopy = indexCopy + 1;
  }
 
 if((*puntero == *puntoDeFinalizacion) &&(readyToCopy == 0)){
  readyToCopy = 1;
  }

  puntero = puntero + 1;
  index = index + 1;
 }
 return 1;

}

int ExisteEnLaCadena(char cadenaEntrada[], char caracter[]){
 int longitudCadenaEntrada = strlen(cadenaEntrada);
 longitudCadenaEntrada = longitudCadenaEntrada - 1;
 int index = 0;
 char resultado[2048];
 char *puntero;
 
 puntero = cadenaEntrada;
 while(index <= longitudCadenaEntrada){
 if(*puntero == *caracter){
 return 1;
 }
 puntero = puntero + 1;
 index = index + 1;
 }
 return 0;

}

int main (int argc, char **argv)
{

 int todosLosParametrosValidos = 0;

 if(argc == 1){
  ImprimirEncabezado();
  printf("\n Atencion: No fueron introducidos paramestros\n");
  return 0;
  }
 if(argc == 2){
 
 char comando[1000];
 strcpy(comando,argv[1]);
 char *esComando;
 //esComando = strchr(comando,'v');

 //if(esComando != NULL){
if(!strcmp(comando,"v")){
ImprimirEncabezado();
 printf("Comando introducido-> ");
 printf("%s",argv[1]);
    FILE *archivo;
     char caracter;
     char caracteres[100];
     char* base64DecodeOutput;
     int index = 0;
      memset(caracteres,'\0',100);
     archivo = fopen(".passwords","r");
     
     if(archivo == NULL){
       printf("\nError de apertura del archivo\n");
       return 0;
     }
     else{
       printf("\nUsername*Password:\n");
       printf("\n******************\n");
       while(feof(archivo)==0){
          caracter = fgetc(archivo);
          if(caracter == '\n'){
            index = 0;
            Base64Decode(caracteres, &base64DecodeOutput);
            printf("%s",base64DecodeOutput);
            printf("\n");
            memset(caracteres,'\0',100);
           }
else{
      caracteres[index] = caracter;
      index = index + 1;}
        } 
    }
    fclose(archivo);
    return 0;
  }

 }

 if(argc == 4){
 ImprimirEncabezado();
 printf("Comando de registro -> ");
 printf("%s",argv[1]);
 char comando[1000];
 strcpy(comando,argv[1]);
 //char *esComando;
 //esComando = strchr(comando,'r');
 //if(esComando != NULL){
 if(!strcmp(comando,"r")){
 char nombreUsuario[1024];
 char contrasena[1024];
 char concatenacion[2049];
 printf("\nSe esta registrando su usuario y contraseña\n");
 strcpy(nombreUsuario,argv[2]);
 strcpy(contrasena,argv[3]);
 printf("Nombre usuario -> %s",nombreUsuario);
 printf("\n");
 printf("Contrasena -> %s",contrasena);
 printf("\n");
 strcat(concatenacion,nombreUsuario);
 
 char tokenizador[] = "*";
 char finalDeLinea[] = "\n";
 strcat(concatenacion,tokenizador);
 strcat(concatenacion,contrasena);
 printf("\n");
 printf("convirtiendo en un registro -> %s",concatenacion);
 printf("\n Con codificacion BASE64\n");

 //Trabajo con archivos
 FILE *archivoPasswords;
 
 archivoPasswords = fopen(".passwords","a");
 if(archivoPasswords==NULL){ printf("Error en archivo .passwords no se pudo registrar"); fclose(archivoPasswords); return 0;}
 //aplicacion de cifrado BASE64
 char* base64EncodeOutput;
 Base64Encode(concatenacion, &base64EncodeOutput);
 fputs(base64EncodeOutput,archivoPasswords);
 fputs(finalDeLinea,archivoPasswords);
 fclose(archivoPasswords);
 printf("\nregistro con exito en archivo .passwords\n");
 return 0;
 }
 printf("comando desconocido");
return 0;
 }

//Recibimiento de la linea principal de parametros
 if(argc == 2){
  ImprimirEncabezado();
  strcpy(parametroEntrada, argv[1]);
  strcpy(bufferW,argv[1]);
  char numeral[] = "#";
  strcat(bufferW,numeral);
  if(ExisteEnLaCadena(bufferW,caracterDosPuntos)){
   ObtenerSubCadenaHasta(bufferW,caracterDosPuntos);
   strcpy(usuario,bufferW2);
   memset(bufferW2,'\0',sizeof(bufferW2));
   printf("\n Nombre de Usuario-> %s",usuario);
   CortarSubCadenaHasta(bufferW,caracterDosPuntos);
   strcpy(bufferW,bufferW3);
   memset(bufferW3,'\0',sizeof(bufferW3));
     if(ExisteEnLaCadena(bufferW,caracterArroba)){
       ObtenerSubCadenaHasta(bufferW,caracterArroba);
       strcpy(contrasena,bufferW2);
       memset(bufferW2,'\0',sizeof(bufferW2));
       printf("\n Constrasena-> %s",contrasena);
       CortarSubCadenaHasta(bufferW,caracterArroba);
       strcpy(bufferW,bufferW3);
       memset(bufferW3,'\0',sizeof(bufferW3));    
             if(ExisteEnLaCadena(bufferW,caracterFSlash)){
             ObtenerSubCadenaHasta(bufferW,caracterFSlash);
             strcpy(direccionIp,bufferW2);
             memset(bufferW2,'\0',sizeof(bufferW2));
             printf("\n Direccion IP-> %s",direccionIp);
             CortarSubCadenaHasta(bufferW,caracterFSlash);
             strcpy(bufferW,bufferW3);
             memset(bufferW3,'\0',sizeof(bufferW3));
                  if(ExisteEnLaCadena(bufferW,caracterNum)){
                    ObtenerSubCadenaHasta(bufferW,caracterNum);
                    char urlRutaTemp[2048];
                    strcpy(urlRutaTemp,caracterFSlash);
                    strcat(urlRutaTemp,bufferW2);
                    memset(bufferW2,'\0',sizeof(bufferW2));
                    strcpy(urlRuta,urlRutaTemp);
                    todosLosParametrosValidos = 1;
                    printf("\n URL Remota Objetivo-> %s",urlRuta);
                    printf("\n");
                  }
             }
       }

     
   }
  

   if(todosLosParametrosValidos == 0){
    printf("\n Atencion: no todos los parametros fueron  \n");
    }
   //se obtuvieron los 4 parametros que se solicitan siempre al principio
   else{

   getcwd(urlLocal,sizeof(urlLocal));
   strcat(urlLocal,caracterFSlash);
   printf(" Directorio Local -> %s",urlLocal);
   printf("\n");
   pthread_t idHiloServidor;
   pthread_create(&idHiloServidor,NULL,funcionServidor,NULL);
   pthread_join(idHiloServidor,NULL);

   }


  }

 
}
