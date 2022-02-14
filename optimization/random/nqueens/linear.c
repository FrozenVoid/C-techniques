#include "Util/void.h"//https://github.com/FrozenVoid/C-headers

//linear O(N) NQueens  solver
#define mstime() ((clock())/(CLOCKS_PER_SEC/1000))
#define QDEBUG 1//print swaps/intersect count each INTERSECT_DISP seconds
#define INTERSECT_DISP 3//1 seconds
#define MS_CLOCK (CLOCKS_PER_SEC/1000)
size_t N;
int* board;
int* diagL;i64 sumL=0;
int* diagR;i64 sumR=0;
i64 swapt=0;//valid swaps total(set if QDEBUG enabled)

clock_t nxt=0;
#define swapq(x,y) ({int temp=x;x=y;y=temp;})
void swapc(size_t x,size_t y){
i64  clx,crx,cly,cry;
if(x==y)return;//no action
//update sums/first/last
#if QDEBUG
swapt++;//valid swaps total
#endif
clx=diagL[board[x]+x]--;//current X pos Left
cly=diagL[board[y]+y]--;//current y pos Left
crx=diagR[board[x]+(N-x)]--;
cry=diagR[board[y]+(N-y)]--;


//cannot see counts of columns
if(!clx || !cly || !crx || !cry){print("\nInvalid diagonal data:x,y,clx,crx,cly,cry:\n",x,y,clx,crx,cly,cry);exit(22);}
//reduce sums,first,last
sumL-=clx>1;//reduce sum if old collision
sumR-=crx>1;
sumL-=cly>1;
sumR-=cry>1;
//swap
swapq(board[x],board[y]);
//updates sums
sumL+=++diagL[board[x]+x]>1;
sumL+=++diagL[board[y]+y]>1;;
sumR+=++diagR[board[x]+(N-x)]>1;
sumR+=++diagR[board[y]+(N-y)]>1;


}


void printboard(int*q,size_t N){print("\n");for(size_t i=0;i<N;i++)printf("%d,",q[i]+1);}
//https://lemire.me/blog/2016/06/27/a-fast-alternative-to-the-modulo-reduction/

uint32_t modreduce(uint32_t x, uint32_t N) {
  return ((uint64_t) x * (uint64_t) N) >> 32 ;
}
uint32_t rndcell(){return modreduce(randuint32(),N);}
//-----------linear collission count----------
#define countudiag() (sumL+sumR)
//--------------------------------------------
void linearsolve(int* q,int N){
u64 A,B;size_t fail=0,tfail=0;
u64 cur=countudiag(),best=cur;
#if QDEBUG
print("Starting linear solver:",mstime()," ms",cur,"intersections\n");
#endif
while(cur){
u64 valr=randuint64();
A=(valr>>32);B=valr&0xffffffff;
A=modreduce(A,N);B=modreduce(B,N);

swapc(A,B);cur=countudiag();//count diagonal intersects
if(cur>=best){if(cur>best){swapc(A,B);fail++;}
continue;}
#if QDEBUG
  if(clock()-nxt>INTERSECT_DISP*CLOCKS_PER_SEC ){
  print("\n best=",best,"cur=",cur,"A=",A,"B=",B," fail=",fail);
  print("\n",mstime(),"ms Cols:",cur,"Swaps:",swapt,"Fails:",tfail);nxt=clock();}
#else
fflush(stdout);//fix low priority;
#endif
tfail+=fail;fail=0;best=cur;
} //end loop

 print("\nSolved at:",mstime(),"ms Collisions:",cur,"Swaps:",swapt,"Fails:",tfail,"\n");
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
solve();

if(argc==3 && argv[2][0]=='p'){printboard(q,N);}
print("\nSolution found in:",mstime()," milliseconds",swapt,"swaps","\n");

return 0;}
