#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//see https://en.wikipedia.org/wiki/Blink_element
int main(int argc,char**argv){
if(argc<2){printf("Syntax:blink \"text message\" [delay ms]\n");return 1;}
int delayval=104166;
if(argc==3){delayval=atoi(argv[2])*1000;}
int maxlen=strlen(argv[1]),c=0;
char empty[maxlen+1];
empty[maxlen]=0;
memset(empty,' ',maxlen);
for(;;){
printf("\r%s",c++&1?argv[1]:empty);
fflush(stdout);usleep(delayval);}
}
