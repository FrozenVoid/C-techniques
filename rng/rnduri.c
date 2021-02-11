#include "Util/void.h"
const char* uri[]={"%20","!","%22","%23","%24","%25","%26","'","(",")","*","%2B","%2C","-",".","%2F","0","1","2","3","4","5","6","7","8","9","%3A","%3B","%3C","%3D","%3E","%3F","%40","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","%5B","%5C","%5D","%5E","_","%60","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","%7B","%7C","%7D","~"};

char* rndchar(uint64_t a){
return uri[a%95];//valid URI component characters
;}


int main(int argc,char**argv){
uint64_t rndttime=__rdtsc();
randomize(rndttime);
int maxlen=5;
if(argc>1)maxlen=atoi(argv[1]);
for(int i=0;i<maxlen;i++){randomize(rndttime);
printf("%s",rndchar(rndttime));}
return 0;
}
