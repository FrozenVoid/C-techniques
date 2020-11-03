#include "Util/print.h"
#include "Util/argmanip.h"
int global=4,local=50;
void func(char* scope){print(scope,global,local);}
//gcc extension
#define exprstate(scope) ({print(scope,global,local);})

void outerfunc(char*scope){ print(scope,global,local);}
void func2(char* scope){
int global=2000,local=6000; //override global vars.
void func3(char* scope){//inner function GCC extension
print(scope,global,local);}
func3(scope);//2000,6000
atype func_ptr=outerfunc;
func_ptr("\nGlobals again:");//function pointer inherits global scope
exprstate("\nContext scope again:");//macros apply to local context


}
// argmanip.h includes: with(args) converts to local block 
//#define with(args...) {opapply(;,args);} 
int main(int argc,char**argv){
int global=5;int local=100;
exprstate("\nContext scope:");//macros inherit outer scope
with(int global=1,int local=2,//uses do loop as {} 
print("\nLocal scope:",global,local));

print("\nOuter scope:",global,local);
func("\nGlobal scope:");
func2("\nDynamic scope:");
do{//do loop local context, introduces a block,(often used in macros)
int global=-1,local=-400;
print("\ndo loop context:",global,local);
}while(0);
//inline block context {}
{ int global=-44,local=-233;
print("\nBlock scope:",global,local);
 {//but theres more
  int global=-20000,local=5055;
 print("\nNext layer of block scope:",global,local);
   { //even more
    int global=-201,local=654654;
    print("\nNesting of block scope:",global,local);
   }
  print("\nNext layer of block scope returns:",global,local);
 }
 print("\nBlock scope returns:",global,local);
}
//the above block ended
print("\nback to main context:",global,local);


}
