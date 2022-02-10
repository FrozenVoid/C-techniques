#include "Util/void.h"//https://github.com/FrozenVoid/C-headers

//fast N Queens "focus cell" solver

#define QDEBUG 1//print swaps/intersect count each INTERSECT_DISP seconds
#define PRINT_RESULT_MAX 5000//don't print result row positions if Board is above PRINT_RESULT_MAX
#define INTERSECT_DISP 5//1 seconds
#define MS_CLOCK (CLOCKS_PER_SEC/1000)
#define MIN_SIDE 8//minimal board width
size_t last=0,fst=0;//focus column(last intersect)

i64 swapt=0;//valid swaps total(set if QDEBUG enabled)

clock_t startt,startt2;
size_t diags(int*board,size_t len){//optimization metric
size_t sum=0;
for(size_t i=0;i<len;i++){size_t cur=board[i],zc=0;
 for(size_t z=i+1;z<len&&zc<2;z++){
  size_t zqueen=board[z];
 if(((z-i)==(zqueen-cur))||((z-i)==(cur-zqueen))){fst=i;last=z;zc++;sum++; };   }  }
return sum;}

uint64_t log2index(size_t X){return ((unsigned) (63 - __builtin_clzll((X)) ))      ;}

size_t firstq1(int*board,size_t len){//first intersect
for(size_t i=0;i<len;i++){
 size_t cur=board[i];
 for(size_t z=i+1;
 z!=len;
 z++){
  if(((z-i)^(board[z]-cur))&& (z-i)^(cur-board[z])  )continue;
 fst=i; last=z; return i; ;   }  }
return len;}

//partially solve by 1st intersect(firstq1)
void psolve(int* q,int N){int temp;
#define swapq(x,y) temp=x;x=y;y=temp;
u64 limlq=N;//lower limit for queen swap fails
u64 cur,lastq=0, A,B,edge=N/256;
while(firstq1(q,N)<N && lastq<limlq){
B=(last<fst+edge)?fst:last;//force focus cell to swap queens(fst,last update from firstq1())
if(MIN_SIDE<8 && N<8)B=randuint64()%N;//fix small boards intersect
do{A=randuint64()%N;
}while(A==B );
#if QDEBUG
swapt++;//valid swaps total
#endif
swapq(q[A],q[B]);//swap random with focused cell
cur=fst;//store fst(i) in cur, overwritten by firstq1
;//find first intersect source, check if below fst(i)
if(firstq1(q,N)<cur){lastq++; //revert if worse
swapq(q[A],q[B]);
#if QDEBUG
swapt--;//valid swaps revert
#endif
continue;  }
lastq=0;//reset count of #last failed queen swaps.
//new record
#if QDEBUG
clock_t curt=clock(); //display first filled column
  if(curt-startt2> INTERSECT_DISP*CLOCKS_PER_SEC){
  print("Time(s):",(curt-startt)/CLOCKS_PER_SEC,"Partial:(",fst,",",last,")/",N," VSwaps:",swapt,"\n");startt2=curt;}
#else
fflush(stdout);//fix low priority assigned if no output
#endif

} //end loop


}



void solve(int* q,int N){int temp;
#define swapq(x,y) temp=x;x=y;y=temp;
u64 A,B;

if(N>2000){//scrambke diagonal for large boards
for(size_t i=0;i<(N);i+=1){swapq(q[i],q[randuint64()%N]);}
}
psolve(q,N);

u64 cur=diags(q,N),best=cur;
#if QDEBUG
if(cur){print(N," is partially solved to:",cur," intersections and ",swapt,"swaps\n");}
#endif
while(cur){
B=randuint64()&1?last:fst;
do{A=randuint64()%N;}while(A==B);
swapq(q[A],q[B]);
#if QDEBUG
swapt++;//valid swaps total
#endif
cur=diags(q,N);//count diagonal intersects
if(cur>best){ //revert if worse
#if QDEBUG
 swapt--;//valid swaps revert
#endif
swapq(q[A],q[B]);continue;  }
best=cur;
//new record
#if QDEBUG
clock_t curt=clock();
  if(curt-startt2> INTERSECT_DISP*CLOCKS_PER_SEC){
  print("Time(s):",(curt-startt)/CLOCKS_PER_SEC,"Intersections:",cur,"VSwaps:",swapt,"\n");startt2=curt;}
#else
fflush(stdout);//fix low priority;
#endif

} //end loop
}


int main(int argc,char**argv){startt=clock();startt2=startt;
if(argc!=2){syntax:;puts("Syntax:nq N\n N=Board size min=" stringify(MIN_SIDE) " >3");exit(1);}
int N=atoi(argv[1]);if(N<MIN_SIDE||N<4)goto syntax;
int* q=calloc(sizeof(int),N);//queen row/cols(2^31-1 max)
if(!q){perror("Queen array size too large");exit(2);}
for(int i=0;i<N;i++)q[i]=i;//unique rows/cols to swap.
;solve(q,N);startt2=clock();
if(PRINT_RESULT_MAX>N){for(int i=0;i<N;i++)printf("%d,",q[i]+1);}
print("\nSolution found in:",(startt2-startt)/MS_CLOCK," milliseconds",swapt,"swaps\n");

return 0;}
