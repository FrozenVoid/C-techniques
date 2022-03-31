#include "Util/void.h"

/*
function with static variables,
can use such variable storage
to emulate object-data.
example
*/
int accumulate(int add){
static int sum=0;
sum+=add;
return sum;
}


int main(int argc,char**argv){
//1,6,19
print(accumulate(1),accumulate(5),accumulate(13));
return 0;
}
