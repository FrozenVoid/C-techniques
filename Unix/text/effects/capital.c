#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
//capitalization animation ver(marquee+upper )
//see https://www.w3docs.com/learn-html/html-marquee-tag.html
int main(int argc,char**argv){
if(argc<2){printf("Syntax:capital \"text message\"\n");return 1;}

int maxlen=strlen(argv[1]),c=0;
for(;;){printf("%.*s%c%s\r",c,argv[1],toupper(argv[1][c]),&argv[1][c+1]);c=c>=maxlen-1?0:c+1;fflush(stdout);usleep(104166);}
}
