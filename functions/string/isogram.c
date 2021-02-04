#include "Util/void.h"
int main(int argc,char**argv){
if(argc<2){print("syntax:",argv[0]," text");return 1;}
char isotest[256]={0};
for(int i=0;argv[1][i];i++)isotest[argv[1][i]]++;
for(int i=0;i<256;i++){if(isotest[i]>1){print("not an isogram");return 2;}}
print("this is an isogram");return 0;}
