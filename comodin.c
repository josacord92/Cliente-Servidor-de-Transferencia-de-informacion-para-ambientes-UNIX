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

int cumpleRegEx(char* expre, char* hile){
regex_t regex;
int reti;

char *hileron;

//reti = regcomp(&regex,"hola([[:alnum:]])+mundo",REG_EXTENDED);

reti = regcomp(&regex,expre,REG_EXTENDED);
if(reti){return 0;}

reti = regexec(&regex,hile,0,NULL,REG_EXTENDED);
if(!reti){
return 1;
}
else if(reti == REG_NOMATCH){
return 0;
}else{
return 0;
}

}


/*
int main(){
regex_t regex;
int reti;
char msgbuf[100];
char *hileron;
//hileron = cambiarformato("*.txt");
//printf("%s",hileron);
reti = regcomp(&regex,"hola([[:alnum:]])+mundo",REG_EXTENDED);
if(reti){fprintf(stderr,"no se compilo");exit(1);}

reti = regexec(&regex,"holamuyomundo",0,NULL,REG_EXTENDED);
if(!reti){
puts("son");
}
else if(reti == REG_NOMATCH){
puts("no son");
}else{
puts("error");
}

return 1;
}
*/
