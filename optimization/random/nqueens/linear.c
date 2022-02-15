#include "Util/void.h"//https://github.com/FrozenVoid/C-headers
//linear ~O(N) NQueens  solver
//moved: https://github.com/FrozenVoid/NQ.c
#define NCYCLES 8 //report each NCYCLES
#define mstime() ((clock())/(CLOCKS_PER_SEC/1000))
#define tsctime(c) ((__rdtsc()-c)>>30)
#define SCRAMBLE 8//scramble iters 0-N
#define QDEBUG 1//print debug/iteration data
#define NONLINEAR 1//ending search if (cols<log(N))
#define val_t u32
#define rotate(num,bits) ({ typeof(num) x=num;\
x=(x>>bits)|(x<<((sizeof(x)*8)-bits));x;})
#define rndgen64 randuint64
#define rndgen32 msws

//from https://arxiv.org/abs/1704.00358
static uint32_t msws() {
static uint64_t x = 0, w = 0, s = 0xb5ad4eceda1ce2a9;
   x *= x; x += (w += s); return x = (x>>32) | (x<<32);}
static u64 tseedw=0;




val_t N,A,B;
val_t * board;
val_t * diagL;i64 sumL=0;
val_t * diagR;i64 sumR=0;
i64 swapt=0,swaps=0;//valid swaps total(set if QDEBUG enabled)
size_t loops=0,fail=0,tfail=0,dir=1,tswaps=0,cend,valr,cur,best;
uint64_t log2index(size_t X){return ((unsigned) (63 - __builtin_clzll((X)) ))      ;}
#define swapq(x,y) ({val_t temp=x;x=y;y=temp;})

 void swapc(val_t x,val_t y){
val_t  clx,crx,cly,cry;
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
 val_t qccount(u32 P){
//cannot be zero due being set from q[]
val_t s=board[P];
return ((diagL[s+P]))+((diagR[s+(N-P)]))-2;}

 val_t qccount2(u32 P,u32 P2){
//cannot be zero due being set from q[]
val_t s=board[P],s2=board[P2];
return ((diagL[s+P]))+((diagR[s+(N-P)]))+ ((diagL[s2+P2]))+((diagR[s2+(N-P2)]))-4;}

val_t fstcols(){
for(size_t i=0;i<N;i++){if(qccount(i))return i;};return N;}

//--------------------------
void printboard(){print("\n");for(size_t i=0;i<N;i++)print(board[i]+1,"\n");}
//https://lemire.me/blog/2016/06/27/a-fast-alternative-to-the-modulo-reduction/

 val_t modreduce(uint32_t x, uint32_t N) {
  return ((uint64_t) x * (uint64_t) N) >> 32 ;
}
val_t rndcell(){return modreduce(randuint32(),N);}
//-----------linear collission count----------
#define countudiag() (sumL+sumR)
//------------------------
 void info(){
  if(tsctime(cend)>NCYCLES ){
  clock_t Ntime=mstime();
  print("\n cols=",cur,"A=",A,"valid/fail:",swaps,"/",(fail),"\nswap:",1.0*swapt/Ntime,"fail:",1.0*tfail/Ntime,"loops:",1.0*loops/Ntime);
  print("\nT:",Ntime,"ms Col%",100.0*(N-cur)/N,"Swapt",swapt,"Valid%",100.0*swapt/tswaps);cend=__rdtsc();}}
//--------------------------------------------
void linearsolve(){
 A=0,B=0,valr=0;
 //large board speedup
 val_t minsearch=N>200000?log2index(N)/3:0;
cend=__rdtsc();u64 lc=0,lcmax=N;
 cur=countudiag(),best=cur;
#if QDEBUG
print("\nT:",mstime()," ms Collisions:",cur," SearchLim:",minsearch);
#endif
//--------Main loop-------------
loop:;
#if QDEBUG
loops++;
#endif
do{A=modreduce(rndgen32(),N);}while(!qccount(A));
duploc:;lc=0;do{B=modreduce(rndgen32(),N); lc++;}while( !qccount(B) && (lc<lcmax) );
if(A==B)goto duploc;
#if QDEBUG
dir=1;
#endif
swapc(A,B);cur=countudiag();//count diagonal intersects
//----bad swap-----
if(cur>best){
#if QDEBUG
dir=-1;fail++;
#endif
swapc(A,B);
goto loop;}
 if(cur==best){;goto loop;}
//-----good swap------
#if QDEBUG
tfail+=fail;swapt+=swaps;
info();//new iteration update
fail=0;;swaps=0;
#endif
best=cur;
//=================Search at ending========================
#if NONLINEAR
if( best<minsearch ){//ending speedup for N>1024
#if QDEBUG
print("\nEnd search:",mstime()," ms Collisions:",best);
#endif
innerloop:;
B=fstcols();
innerloop2:;lc=0,lcmax=1023;
do{A=modreduce(rndgen32(),N);lc++;}while(!qccount(A) && lc<lcmax );
if(A==B)goto innerloop2;

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
#endif

if(cur>0){goto loop;;}
//-----------Success-----
endl:; //end loop
#if QDEBUG
 print("\nSolved N=",N," at:",mstime(),"ms Swaps:",swapt,"Fails:",tfail,"\n",tseedw," calls\n");
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
board=malloc(sizeof(val_t)*N);//queen row/cols(2^31-1 max)

if(!board){perror("Queen array size too large for malloc");exit(2);}
diagL=malloc(sizeof(val_t)*(N+2)*2);
diagR=malloc(sizeof(val_t)*(N+2)*2);
if(!diagR||!diagL){perror("Diag arrays size too large for malloc");exit(3);}
for(size_t i=0;i<N;i++)board[i]=i;//unique rows/cols to swap.
#if SCRAMBLE //speedup board solutions
u64 timeseed=1111;
setrseed(timeseed,1-~timeseed,timeseed-~timeseed,~timeseed+timeseed);
for(val_t z=0;z<SCRAMBLE;z++){
for(val_t i=0;i<N;i++){
u64 valr=randuint64();
A=(valr>>32);B=valr&0xffffffff;
A=modreduce(A,N);B=modreduce(B,N);
swapq(board[A],board[B]);
}}
#endif
solve();
//verify no collisions (diagonals contain x=1)
size_t verify=0;
for(size_t i=0;i<N;i++){
verify+=(diagL[board[i]+i])!=1;
verify+=(diagR[board[i]+(N-i)])!=1;
}
//halt on error(stops nqtest.sh) (fix:disable NONLINEAR search
if(verify){print("Invalid solution to N=",N,"Collisions:",verify);char tt=getchar();}
if((argc==3 && (argv[2][0]=='p'))){printboard();}
return 0;}
