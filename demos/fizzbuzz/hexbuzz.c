putchar(c);
#define buzzing(bee) ({do{putchar(fizzbuzz);}while(fizzbuzz>>=8);putchar('\x0a');})
#define twin(bee) ({fizzbuzz=bee;do{\
putchar("0123456789ABCDEF"[fizzbuzz>>60]);}while(fizzbuzz<<=4);\
bee&15?:putchar('0');putchar('\x0a');})
#define fris(bee) ({unsigned long long  fizzbuzz=8825495348169042246;\
if(bee%3)fizzbuzz>>=64>>!(bee%5);\
if(bee%5)fizzbuzz=(int)fizzbuzz;\
fizzbuzz?buzzing(bee):twin(bee);-~bee;})
main(bee){while(bee=fris(bee));}
