#include "Util/print.h"
#include "Util/timing.h"
#include <stdlib.h>
//beauty of form: the recursive call 
uint64_t elegantfactorial(uint64_t n) {
return n == 0 ? 1 : n * elegantfactorial(n - 1);
}
//beauty of function: the optimized loop
uint64_t uglyfactorial(uint64_t n) {
uint64_t i=1; while(n)i*=n--; return i;
}
/* tail call:recursion without stack cost( GCC "tail call elimination"
also works for simple functions like elegantfactorial above, the compiler also
turns them to tail-recursive form, but due the structure somewhat less efficient. if elegantfactorial was more complex, more advantage comes from tail-call structure function.
*/
void tailcall(uint64_t* result,uint64_t n){
if(n==0)return;
*result=(*result) *n;
return tailcall(result,n-1);
}

//static return
void staticret(uint64_t* result,uint64_t n){
static uint64_t res=1;
if(n==0){*result=res;return;}
res*=n--;
staticret(result,n);
}

//tailcallv2
void tail2(uint64_t* result,uint64_t n){
if(n!=0){
*result=(*result) *n;
return tail2(result,n-1);}
}
//static return v2;
void staticret2(uint64_t* n){
static uint64_t res=1;
if(*n==0){*n=res;return;}
res*=(*n);*n=(*n)-1;
return staticret2(n);

}


int main(int argc,char**argv){
uint64_t x=strtoull(argv[1],NULL,10),a=1,b=1,c=1,d=1,e=1,g=x;
uint64_t resa=timing(a=elegantfactorial(x));
uint64_t resb=timing(b=uglyfactorial(x));

uint64_t resc=timing(tailcall(&c,x));
uint64_t resd=timing(staticret(&d,x));
uint64_t rese=timing(tail2(&e,x));
uint64_t resg=timing(staticret2(&g));
print("\ntiming ugly     :",resb,b,\
"\ntiming tail     :",resc,c,"\ntiming elegant  :",resa,a,"\ntiming staticret:",resd,d,"\ntiming tail2    :",rese,e,"\ntiming staticre2:",resg,g);

}
