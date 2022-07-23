#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//see https://www.w3docs.com/learn-html/html-marquee-tag.html
int main(int argc,char**argv){
if(argc<2){printf("Syntax:marque \"text message\" [delay ms]\n");return 1;}
int delayval=104166;
if(argc==3){delayval=atoi(argv[2])*1000;}
int maxlen=strlen(argv[1]),c=0;
for(;;){

printf("%s %.*s\r",&argv[1][c],c,argv[1]);c=c>=maxlen?0:c+1;

fflush(stdout);usleep(delayval);}
}
