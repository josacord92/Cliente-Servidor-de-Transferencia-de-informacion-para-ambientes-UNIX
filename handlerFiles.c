#include <stdio.h>
#include <stdlib.h>

int main(){
     FILE *archivo;
     char caracter;
     char caracteres[1000];
     char* base64EncodeOutput;
     char* base64DeccodeOutput;
     int index = 0;

     archivo = fopen("p.txt","r");
     
     if(archivo == NULL){
       printf("\nError de apertura del archivo\n");
     }
     else{
       printf("\nEl contenido es\n");
       while(feof(archivo)==0){
          caracter = fgetc(archivo);
          if(caracter == '\n'){
             caracteres[index] = '#';
                  index = 0;
            printf("%s",caracteres);
           }
      caracteres[index] = caracter;
      index = index + 1;
        } 
    }
    fclose(archivo);
    return 0; 
           
 
}
