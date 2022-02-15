#include "Util/void.h"//https://github.com/FrozenVoid/C-headers
//linear ~O(N) NQueens  solver
#define NCYCLES 8 //report each NCYCLES
#define mstime() ((clock())/(CLOCKS_PER_SEC/1000))
#define tsctime(c) ((__rdtsc()-c)>>30)
#define SCRAMBLE 2//scramble iters 0-N
#define QDEBUG 1//print debug/iteration data
size_t N;
int* board;
int* diagL;i64 sumL=0;
int* diagR;i64 sumR=0;
i64 swapt=0,swaps=0;//valid swaps total(set if QDEBUG enabled)
size_t fail=0,tfail=0;
uint64_t log2index(size_t X){return ((unsigned) (63 - __builtin_clzll((X)) ))      ;}
#define swapq(x,y) ({int temp=x;x=y;y=temp;})
inline void swapc(size_t x,size_t y){
i64  clx,crx,cly,cry;


//update sums/first/last
#if QDEBUG
swaps++;//valid swaps total
#endif
clx=diagL[board[x]+x]--;//current X pos Left
cly=diagL[board[y]+y]--;//current y pos Left
crx=diagR[board[x]+(N-x)]--;
cry=diagR[board[y]+(N-y)]--;
//reduce sums,first,last
//if clx==1 0 clx>1=1
sumL-=(clx>1);//reduce sum if old collision
sumL-=cly>1;
sumR-=crx>1;
sumR-=cry>1;
//swap
swapq(board[x],board[y]);
//updates sums
clx=(++diagL[board[x]+x]);
cly=(++diagL[board[y]+y]);;
crx=(++diagR[board[x]+(N-x)]);
cry=(++diagR[board[y]+(N-y)]);

sumL+=(clx>1);//reduce sum if old collision
sumL+=cly>1;
sumR+=crx>1;
sumR+=cry>1;}

//queen collisons at position: 2=none,2+=collision
inline i32 qccount(int* q,size_t P){
//cannot be zero due being set from q[]
return ((diagL[q[P]+P]))+((diagR[q[P]+(N-P)]))-2;}



//--------------------------
void printboard(int*q,size_t N){print("\n");for(size_t i=0;i<N;i++)printf("%d\n",q[i]+1);}
//https://lemire.me/blog/2016/06/27/a-fast-alternative-to-the-modulo-reduction/

inline uint32_t modreduce(uint32_t x, uint32_t N) {
  return ((uint64_t) x * (uint64_t) N) >> 32 ;
}
uint32_t rndcell(){return modreduce(randuint32(),N);}
//-----------linear collission count----------
#define countudiag() (sumL+sumR)
//--------------------------------------------
void linearsolve(int* q,int N){
u64 A=0,B=0;int Aflag=0;
u64 cend=__rdtsc();
u64 cur=countudiag(),best=cur,lcur=cur;

loop:;u64 valr=randuint64();
A=modreduce((valr>>32),N);
B=modreduce(valr&0xffffffff,N);
if( (qccount(q,B)+qccount(q,A)<1)||A==B )goto loop;

swap_loc:;
swapc(A,B);//test swap
cur=countudiag();//count diagonal intersects
if(cur>best){swapc(A,B);fail++;goto loop;}
if(cur==best){goto loop;}

#if QDEBUG
  if(tsctime(cend)>NCYCLES ){
  clock_t Ntime=mstime();
  print("\n cols=",cur,"A=",A,"valid/fail:",(((swaps>>1)-fail)),"/",(fail),"\nswap/ms:",1.0*swapt/Ntime,"fail/ms:",1.0*tfail/Ntime);
  print("\nT:",Ntime,"ms Col%",100.0*(N-cur)/N,"Swapt",swapt,"Valid%",100.0-(200.0*tfail/swapt));cend=__rdtsc();}
#endif

tfail+=fail;swapt+=swaps;
fail=0;;swaps=0;best=cur;Aflag=1;



if(cur>0)goto loop; //end loop
#if QDEBUG
 print("\nSolved N=",N," at:",mstime(),"ms Swaps:",swapt,"Fails:",tfail,"\n");
#endif
}


//===================Solver===========================
void solve(void){
size_t len=N;int*q=board;
u64 A,B;
//fill queen location counts
for(size_t i=0;i<N;i++){diagL[board[i]+i]++;}
for(size_t i=0;i<N;i++){diagR[board[i]+(N-i)]++;}
//calculate Sums of collisions

for(size_t i=0;i<N*2;i++){sumL+=(diagL[i]-1)*(diagL[i]>1);}
for(size_t i=0;i<N*2;i++){sumR+=(diagR[i]-1)*(diagR[i]>1);}
linearsolve(q,N);}

int main(int argc,char**argv){
if(argc<2){syntax:;puts("Syntax:nq N [p]\n N=Board size min=8 \n p=printboard");exit(1);}
 N=atoi(argv[1]);if(N<8)goto syntax;
board=malloc(sizeof(int)*N);//queen row/cols(2^31-1 max)
int* q=board;
if(!board){perror("Queen array size too large for malloc");exit(2);}
diagL=malloc(sizeof(int)*(N+2)*2);
diagR=malloc(sizeof(int)*(N+2)*2);
if(!diagR||!diagL){perror("Diag arrays size too large for malloc");exit(3);}
for(size_t i=0;i<N;i++)q[i]=i;//unique rows/cols to swap.
#if SCRAMBLE
u64 timeseed=1111;
u64 oldA,B;
setrseed(timeseed,1-~timeseed,timeseed-~timeseed,~timeseed+timeseed);
for(int z=0;z<SCRAMBLE;z++){
for(size_t i=0;i<N;i++){
u64 valr=randuint64();
oldA=(valr>>32);B=valr&0xffffffff;
oldA=modreduce(oldA,N);B=modreduce(B,N);
swapq(q[oldA],q[B]);
}}
#endif
solve();
//verify no collisions (diagonals contain x=1)
size_t verify=0;
for(size_t i=0;i<N;i++){
verify+=(diagL[board[i]+i])!=1;
verify+=(diagR[board[i]+(N-i)])!=1;
}

if(verify){print("Invalid solution to N=",N);char tt=getchar();}
if((argc==3 && (argv[2][0]=='p'))){printboard(q,N);}
return 0;}
