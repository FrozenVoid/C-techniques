#include "Util/void.h"
int main(int argc,char**argv){
if(argc<2){print("syntax:",argv[0]," string");return 1;}
typedef struct charcount{char c;int count;} charcount;
charcount rle={argv[1][0],1} ;
//rle output of string
#define prle(s) print("(",s.c,":",s.count,")")
print("[");
for(int i=1;argv[1][i];i++){
if(rle.c==argv[1][i]){rle.count++;}
else{prle(rle);print(",");
rle.c=argv[1][i];rle.count=1;}
}
prle(rle);print("]");

return 0;
}
