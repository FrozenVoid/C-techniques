#include "stdio.h"
    //FizzBuzz without variables,printf,separate strings,if/ternary/branches(except loop) or modulus/division/multiply use
    int main(){

    char
           //0  1 2 3 4 5 6
     num[]={48,48,0,1,1,1,58,'F','i','z','z',0,'B','u','z','z',0,0,0,'F','i','z','z','B','u','z','z',0};
    for( ;num[0]<num[6];num[3]++,num[5]++){
    num[3]>>=((num[3]==3)<<3);
    num[5]>>=((num[5]==5)<<3);
    num[1]++;
    num[0]+=(num[1]==num[6]);
    num[1]>>=((num[1]==num[6]))<<3;
    num[1]+=(((!num[1])<<6)-((!num[1])<<4));
    puts(num+(((!num[3])<<3)-!num[3])+((!num[5]<<2)+((!num[5])<<3)));

    ;}}
