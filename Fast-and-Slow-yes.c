/* yes is a Unix utility that outputs 'y' or its argument
in an infinite loop.
Here are two example of yes;
slowyes() this function is slower, yet doesn't use resources.
fastyes() a much faster function, wins benchmarks but practically useless
 and uses far more resources than slowyes.
the slowyes is 'worse is better' approach to software
the fastyes is the 'right thing' but its domain(speed) doesn't have application in actual user demand(repeat user keystrokes)

*/
//---slowyes
#include <stdio.h>//yes.c Output first arg or ("y")
int main(int argc,char**argv){
for(;;){puts(argc>1?argv[1]:"y");}}
//---fastyes
#include <stdio.h>//yes.c Output first arg or ("y")
#include <string.h>
#include <stdlib.h>

#define YSIZE (65535-1)
int main(int argc,char**argv){
char buf[(YSIZE)+1]={0};size_t i;
char* yes=buf;
if(argc>1){size_t st=strlen(argv[1])+1;
if(st>YSIZE){yes=argv[1];goto end;}
//small string
for(i=0;i<YSIZE;i+=st){
memcpy(&buf[i],argv[1],st-1);
buf[i+st-1]='\n';}
goto end;}
//no arguments
for(i=0;i<YSIZE;i+=2){buf[i]='y';buf[i+1]='\n';}

end:;
for(;;)fwrite_unlocked(yes,YSIZE+1,1,stdout);
}
