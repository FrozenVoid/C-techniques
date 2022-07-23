#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//vertical slide marquee ver(marquee shifted diag)
//see https://www.w3docs.com/learn-html/html-marquee-tag.html
int main(int argc,char**argv){
if(argc<2){printf("Syntax:slide \"text message\"\n");return 1;}

int maxlen=strlen(argv[1]),c=0;
for(;;){printf("%s %.*s\v\r",&argv[1][c],c,argv[1]);c=c>=maxlen?0:c+1;fflush(stdout);usleep(104166);}
}
