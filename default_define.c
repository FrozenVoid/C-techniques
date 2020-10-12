/* dual pass compilation:
gcc code.c -E -CC|gcc -xc -
demonstates that C preprocessor is capable(with some tricks)
of create a default_define macro, just like lisp.
This is obviously never used in serious code.
the comments -CC ensure the newline preserved.
*/
#include "print.h"
#include "arguments.h"
#define D #define
#define IFND #ifndef
#define ENDF #endif
#define proxy1(x) x
#define default_define(macro_name,argument_tuple,body...) IFND macro_name /* 
*/ D proxy1(macro_name)(id argument_tuple) body  /*
*/ ENDF

//uncomment to change printed result.
//#define abc(x) x+124
default_define(abc,(a),a+100)
int main(){
print(abc(1));}
