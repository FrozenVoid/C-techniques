#define buzzing(bee) ({buzz=1000000000;\
do{putchar('0'+(bee/buzz)%10);\
}while(buzz/=10);putchar('\x0a');})
#define twin(bee) puts(fizz?&fizz:&buzz)
#define fris(bee) ({int fizz=('zziF'*!(bee%3)),\
buzz=('zzuB'*!(bee%5));\
fizz+buzz?twin(bee):buzzing(bee);-~bee;})
main(bee){while(bee=fris(bee));}
