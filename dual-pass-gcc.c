//dual pass example:
//compile: gcc code.c -E|gcc -xc -
#include "print.h"
#include "arguments.h"
#define D #define
#define DEFMACRO(name,tup,body...) D name(id tup) body
DEFMACRO(quack,(a,b,c),a+b+c)
int main(){  
int x=quack(1,2,3);
print(x);//6
}
