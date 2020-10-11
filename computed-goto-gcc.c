#include <stdio.h>

int main(){


#define sum(i,acc) acc+=i

#define sumprinti(i,acc) acc+=i;printf("%d,",i);


#define loop(x,y,acc,func) ({ __label__ loop1,end1;int i=0;\

static void *gotoarray[] = {&&loop1,&&end1};\

 loop1:\

func(i,acc); i++; goto *gotoarray[i>y];end1:; acc;})

#define sumloop(x,y,func) ({int acc=0;loop(x,y,acc,func);})


sumloop(1,10,sumprinti);printf("\n%d",sumloop(1,10,sum));

}

