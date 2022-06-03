puts(char*);putchar(c);
#define twin(bee) ({fizzbuzz=bee;do{\
putchar("0123456789ABCDEF"[fizzbuzz>>60]);}while(fizzbuzz<<=4);\
putchar(bee&15?' ':'0');putchar('\x0a');})
#define fris(bee) ({unsigned long long  fizzbuzz=8825495348169042246;\
if(bee%3)fizzbuzz>>=64>>!(bee%5);\
if(bee%5)fizzbuzz=(int)fizzbuzz;\
fizzbuzz?puts(&fizzbuzz):twin(bee);-~bee;})
main(bee){while(bee=fris(bee));}
