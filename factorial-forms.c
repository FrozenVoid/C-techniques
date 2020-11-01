#include "Util/print.h"
#include <stdlib.h>
//beauty of form: the recursive call 
uint64_t elegantfactorial(uint64_t n) {
return n == 0 ? 1 : n * elegantfactorial(n - 1);
}
//beauty of function: the optimized loop
uint64_t uglyfactorial(uint64_t n) {
uint64_t i=1; while(n)i*=n--; return i;
}
// tail call:recursion without stack cost
void tailcall(uint64_t* result,uint64_t n){
if(n==0)return;
*result=(*result) *n;
return nonrec(result,n-1);
}

int main(int argc,char**argv){
uint64_t x=atoll(argv[1]);
uint64_t a=elegantfactorial(x);
uint64_t b=uglyfactorial(x);
uint64_t c=1;tailcall(&c,x);
print(a,b,c);

}
