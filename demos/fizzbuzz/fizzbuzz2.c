#define buzz(bzz,bees) ({fizzbuzz=fizzbuzz?:1000000000;\
do{putchar(bees);}while(fizzbuzz/=bzz);putchar('\x0a');})
#define buzzing(bee) buzz(256,fizzbuzz)
#define twin(bee) buzz(10,'0'+(bee/fizzbuzz)%10)

#define fris(bee) ({unsigned long long  fizzbuzz=8825495348169042246;\
if(bee%5)fizzbuzz=(int)fizzbuzz;\
if(bee%3)fizzbuzz>>=32;\
fizzbuzz?buzzing(bee):twin(bee);-~bee;})
main(bee){while(bee=fris(bee));}
