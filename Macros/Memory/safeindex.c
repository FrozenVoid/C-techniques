#include <stdio.h>
#define safeindex(x,max) ({size_t y=x;y*(y<max);})
int main(int argc,char**argv){
int buffer[10]={0/*index 0, sentinel value*/,111,2222,3333,44444,55555,66666,7777777,888,9999};
puts("int buffer[10]={0/*index 0, sentinel value*/,111,2222,3333,44444,55555,66666,7777777,888,9999};");
loop:;
int access;
printf("\nEnter the buffer cell:");
scanf("%d",&access);
printf("\nvalue is=%d",buffer[safeindex(access,10)]);
goto loop;;
}
