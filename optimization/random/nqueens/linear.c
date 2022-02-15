#include "Util/void.h"//https://github.com/FrozenVoid/C-headers
//linear ~O(N) NQueens  solver
#define NCYCLES 8 //report each NCYCLES
#define mstime() ((clock())/(CLOCKS_PER_SEC/1000))
#define tsctime(c) ((__rdtsc()-c)>>30)
#define SCRAMBLE 8//scramble iters 0-N
#define QDEBUG 1//print debug/iteration data
size_t N;
int * board;
int * diagL;i64 sumL=0;
int * diagR;i64 sumR=0;
i64 swapt=0,swaps=0;//valid swaps total(set if QDEBUG enabled)
size_t fail=0,tfail=0,dir=1,tswaps=0,cend,A,B,valr,cur,best;
uint64_t log2index(size_t X){return ((unsigned) (63 - __builtin_clzll((X)) ))      ;}
#define swapq(x,y) ({int temp=x;x=y;y=temp;})

 void swapc(size_t x,size_t y){
i64  clx,crx,cly,cry;
#if QDEBUG
tswaps++;swaps+=dir;//valid swaps total
#endif
clx=diagL[board[x]+x]--;//current X pos Left
cly=diagL[board[y]+y]--;//current y pos Left
crx=diagR[board[x]+(N-x)]--;
cry=diagR[board[y]+(N-y)]--;
//reduce sums,first,last
//if clx==1 0 clx>1=1  (clx-1)=0
sumL-=!!(clx-1);//reduce sum if old collision
sumL-=!!(cly-1);
sumR-=!!(crx-1);
sumR-=!!(cry-1);
//swap
swapq(board[x],board[y]);
//updates sums
clx=(++diagL[board[x]+x]);
cly=(++diagL[board[y]+y]);;
crx=(++diagR[board[x]+(N-x)]);
cry=(++diagR[board[y]+(N-y)]);

sumL+=!!(clx-1);//reduce sum if old collision
sumL+=!!(cly-1);
sumR+=!!(crx-1);
sumR+=!!(cry-1);

}


//queen collisons at position: 2=none,2+=collision
 i32 qccount(size_t P){
//cannot be zero due being set from q[]
return ((diagL[board[P]+P]))+((diagR[board[P]+(N-P)]))-2;}

size_t fstcols(){
for(size_t i=0;i<N;i++){if(qccount(i))return i;};return N;}

//--------------------------
void printboard(){print("\n");for(size_t i=0;i<N;i++)printf("%d\n",board[i]+1);}
//https://lemire.me/blog/2016/06/27/a-fast-alternative-to-the-modulo-reduction/

 uint32_t modreduce(uint32_t x, uint32_t N) {
  return ((uint64_t) x * (uint64_t) N) >> 32 ;
}
uint32_t rndcell(){return modreduce(randuint32(),N);}
//-----------linear collission count----------
#define countudiag() (sumL+sumR)
//------------------------
 void info(){
  if(tsctime(cend)>NCYCLES ){
  clock_t Ntime=mstime();
  print("\n cols=",cur,"A=",A,"valid/fail:",swaps,"/",(fail),"\nswap/ms:",1.0*swapt/Ntime,"fail/ms:",1.0*tfail/Ntime);
  print("\nT:",Ntime,"ms Col%",100.0*(N-cur)/N,"Swapt",swapt,"Valid%",100.0*swapt/tswaps);cend=__rdtsc();}}
//--------------------------------------------
void linearsolve(){
 A=0,B=0,valr=0;int minsearch=N>1024?log2index(N):0;
cend=__rdtsc();
 cur=countudiag(),best=cur;
#if QDEBUG
print("\nT:",mstime()," ms Collisions:",cur," SearchLim:",minsearch);
#endif
loop:;valr=randuint64();
A=modreduce((valr>>32),N);
B=modreduce(valr&0xffffffff,N);
if( (qccount(B)+qccount(A)<1)||A==B )goto loop;

swap_loc:;
#if QDEBUG
dir=1;
#endif
swapc(A,B);cur=countudiag();//count diagonal intersects
if(cur>best){
#if QDEBUG
dir=-1;fail++;
#endif
swapc(A,B);
goto loop;}else if(cur==best){;goto loop;}

#if QDEBUG
tfail+=fail;swapt+=swaps;
info();//new iteration update
fail=0;;swaps=0;
#endif



best=cur;
if(best<minsearch ){//ending speedup for N>1024
#if QDEBUG
print("\nEnd search:",mstime()," ms Collisions:",best);
#endif
innerloop:;
B=fstcols();
innerloop2:;
valr=randuint64();A=modreduce((valr>>32),N);

#if QDEBUG
dir=1;
#endif
swapc(A,B);cur=countudiag();
if(cur==0){goto endl;}
if(cur<=best){
#if QDEBUG
fail=0;if(cur<best)info();
#endif
best=cur;goto innerloop;}
#if QDEBUG
dir=-1;fail++;
#endif
swapc(A,B);goto innerloop2;

}


if(cur>0){goto loop;;}
endl:; //end loop
#if QDEBUG
 print("\nSolved N=",N," at:",mstime(),"ms Swaps:",swapt,"Fails:",tfail,"\n");
#endif
}


//===================Solver===========================
void solve(void){
u64 A,B;
//fill queen location counts
for(size_t i=0;i<N;i++){diagL[board[i]+i]++;}
for(size_t i=0;i<N;i++){diagR[board[i]+(N-i)]++;}
//calculate Sums of collisions

for(size_t i=0;i<N*2;i++){sumL+=(diagL[i]-1)*(diagL[i]>1);}
for(size_t i=0;i<N*2;i++){sumR+=(diagR[i]-1)*(diagR[i]>1);}
linearsolve();}

int main(int argc,char**argv){
if(argc<2){syntax:;puts("Syntax:nq N [p]\n N=Board size min=8 \n p=printboard");exit(1);}
 N=atoi(argv[1]);if(N<8)goto syntax;
board=malloc(sizeof(int)*N);//queen row/cols(2^31-1 max)

if(!board){perror("Queen array size too large for malloc");exit(2);}
diagL=malloc(sizeof(int)*(N+2)*2);
diagR=malloc(sizeof(int)*(N+2)*2);
if(!diagR||!diagL){perror("Diag arrays size too large for malloc");exit(3);}
for(size_t i=0;i<N;i++)board[i]=i;//unique rows/cols to swap.
#if SCRAMBLE //speedup board solutions
u64 timeseed=1111;
u64 oldA,B;
setrseed(timeseed,1-~timeseed,timeseed-~timeseed,~timeseed+timeseed);
for(int z=0;z<SCRAMBLE;z++){
for(size_t i=0;i<N;i++){
u64 valr=randuint64();
oldA=(valr>>32);B=valr&0xffffffff;
oldA=modreduce(oldA,N);B=modreduce(B,N);
swapq(board[oldA],board[B]);
}}
#endif
solve();
//verify no collisions (diagonals contain x=1)
size_t verify=0;
for(size_t i=0;i<N;i++){
verify+=(diagL[board[i]+i])!=1;
verify+=(diagR[board[i]+(N-i)])!=1;
}
//halt on error(stops nqtest.sh)
if(verify){print("Invalid solution to N=",N);char tt=getchar();}
if((argc==3 && (argv[2][0]=='p'))){printboard();}
return 0;}
