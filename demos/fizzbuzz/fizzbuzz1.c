#define fris(bee) ({long long  fizzbuzz=8825495348169042246;\
if(bee%3)fizzbuzz>>=64>>!(bee%5);\
if(bee%5)fizzbuzz=(int)fizzbuzz;\
puts((fizzbuzz?:sprintf(&fizzbuzz,"%d\0",bee),&fizzbuzz));-~bee;})
main(bee){while(bee=fris(bee));}

