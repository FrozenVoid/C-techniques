#include "Util/void.h"
//random valid ASCII string with default len=5
char rndchar(uint64_t a){
const char * valid=" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
return valid[a%95];
;}

int main(int argc,char**argv){
uint64_t rndttime=__rdtsc();
randomize(rndttime);
int maxlen=5;
if(argc>1)maxlen=atoi(argv[1]);
char res[maxlen+1];res[maxlen]=0;
for(int i=0;i<maxlen;i++){randomize(rndttime);
res[i]=rndchar(rndttime);}
print(res);

return 0;
}
