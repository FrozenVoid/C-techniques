#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
//long long to ascii( integer, base(2<>36))
char* lltoa(int64_t inp,int base){
const char bases_str[]="0123456789abcdefghijklmnopqrstuvwxyz";
size_t i=127;
static char buf[128]={0};
char sgn=(inp<0)?inp=-inp,'-':' ';
do{buf[i--]=bases_str[inp%base];
inp/=base;}while(inp);
buf[i]=sgn;
return &buf[i];}

int main(int argc,char**argv){
//Example:convert arguments to ascii in base 36
// atoll converts arguments to int64
// lltoa converts int64 to base36 string representation of number
for(int i=1;i<argc;i++){printf("%s\n\n",lltoa(atoll(argv[i]),36));}
return 0;}
