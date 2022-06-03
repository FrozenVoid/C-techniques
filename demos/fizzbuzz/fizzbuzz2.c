putchar(c);
#define buzzing(bee) ({do{putchar(fizzbuzz);}while(fizzbuzz>>=8);putchar('\x0a');})
#define twin(bee) ({fizzbuzz=1000000000;do{\
putchar("0123456789 "[(bee/fizzbuzz)?(bee/fizzbuzz)%10:10]);}while(fizzbuzz/=10);putchar('\x0a');})
#define fris(bee) ({unsigned long long  fizzbuzz=8825495348169042246;\
if(bee%3)fizzbuzz>>=64>>!(bee%5);\
if(bee%5)fizzbuzz=(int)fizzbuzz;\
fizzbuzz?buzzing(bee):twin(bee);-~bee;})
main(bee){while(bee=fris(bee));}
