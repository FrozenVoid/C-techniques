#include "Util/void.h"
int main(int argc,char**argv){
if(argc<2){print("syntax:",argv[0]," string");return 1;}
//largestword in string;
char* word=strtok(argv[1]," ");
char* longest=word;size_t maxlen=0;
while(word){size_t curlen=strlen(word);
if(curlen>maxlen)maxlen=curlen,longest=word;
word=strtok(NULL," ");//continue on last pointer
}
print(longest?longest:"No words detected");
return 0;
}
