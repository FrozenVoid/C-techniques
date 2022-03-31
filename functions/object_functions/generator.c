#include "Util/void.h"

/*
function generating struct,
similar to python generators
example
*/
typedef struct pair{int a;int b;} Pair;
Pair generator(size_t rset){
static size_t count=0;if(rset!=0)count=rset;
Pair r={.a=count,.b=count*count};count++;
return r;
}



int main(int argc,char**argv){
Pair a1=generator(0);
Pair a2=generator(0);
Pair c1=generator(19);
// 0 0 1 1 19 361
print(a1.a,a1.b,a2.a,a2.b,c1.a,c1.b);
return 0;
}
