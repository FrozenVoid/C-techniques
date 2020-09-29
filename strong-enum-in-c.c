#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
//uses GCC empty structure extension
//(can be any struct/union of course:e.g. union{unsigned char val;}})
#define enumc(name,...) typedef union{}name;name __VA_ARGS__;
#define atype __auto_type
#define istype(x,type) (_Generic((x),type:1,default:0))

int main(int argc,char**argv){
enumc(Colors,Red,Blue,Yellow,Green);
Colors Purple=Red;
atype Black=Blue;
#define isblue(x) (&Blue==&x)
#define isgreen(x) (&Green==&x)
#define ispurple(x) (&Purple==&x)
#define isred(x)  (&Red==&x)
#define iseq(x,y) (x==y) 
int iscolorx(Colors* x,Colors*y){return  x==y;}

printf("Red:%p;Black:%p ;%d:%d\n",
&Red,&Black,iseq(&Red,&Black),iscolorx(&Red,&Black));

printf("%d:%d,%d:%d \n%d:%d,%d:%d,",
istype(Purple,Colors),istype(Black,int),isblue(Blue),isblue(Red),
isblue(Black),isred(Purple),isgreen(Green),isgreen(Green));
}
