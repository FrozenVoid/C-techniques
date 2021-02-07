/* every type has a fixed length string literal
that is equivalent to a number.
Usually used with integers, with result dependent on endianess of
 the system:
char c='a';
 uint16_t d='bb';
 uint32_t e='cccc';

*/
#include "Util/void.h"
int main(int argc,char**argv){
char lit1='a';
float lit2='aaaa';
int32_t lit3='aaaa';
double lit4='aaaaaaaa';
uint16_t lit5='aa';
__int128 lit6='aaaaaaaaaaaaaaaa';
void* lit7='aaaaaaaa';
int64_t lit8='aa';

print(lit1,lit2,lit3,lit4,lit5,lit7,lit8);
arbpr(lit6);
return 0;
}
