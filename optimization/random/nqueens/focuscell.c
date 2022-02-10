#include "Util/void.h"//https://github.com/FrozenVoid/C-headers

//fast N Queens "focus cell" solver

#define QDEBUG 1//print intersect count each INTERSECT_DISP seconds
#define PRINT_RESULT_MAX 5000//don't print result row positions if Board is above PRINT_RESULT_MAX
#define INTERSECT_DISP 5//1 seconds
#define MS_CLOCK (CLOCKS_PER_SEC/1000)
size_t last=0,fst=0;//focus column(last intersect)
clock_t startt,startt2;
size_t diags(int*board,size_t len){//optimization metric
size_t sum=0;
for(size_t i=0;i<len;i++){size_t cur=board[i],zc=0;
 for(size_t z=i+1;z<len&&zc<2;z++){size_t zqueen=board[z];
 if(((z-i)==(zqueen-cur))||((z-i)==(cur-zqueen))){fst=i;last=z;zc++;sum++; };   }  }
return sum;}

uint64_t log2index(size_t X){return ((unsigned) (63 - __builtin_clzll((X)) ))      ;}

size_t firstq1(int*board,size_t len){//first intersect
size_t i,z;
for( i=0;i<len;i++){
 size_t cur=board[i];
 for( z=i+1;z<len;z++){
 size_t zqueen=board[z];
  if(((z-i)==(zqueen-cur))||((z-i)==(cur-zqueen))){
 fst=i;
 last=z;
 return i; };   }  }
return len;}

//presolve positions
void psolve(int* q,int N){int temp;
#define swapq(x,y) temp=x;x=y;y=temp;
u64 limlq=N*16;//1280/log2index(N);
u64 cur,lastq=0, A,B;
while(firstq1(q,N)<N && lastq<limlq){
B=randuint64()&1?last:fst;//force focus cell to swap queens
if(N<64)B=randuint64()%N;
do{A=randuint64()%N;
}while(A==B );
swapq(q[A],q[B]);

cur=fst;
;//count diagonal intersects
if(firstq1(q,N)<cur){lastq++; //revert if worse
swapq(q[A],q[B]);
continue;  }
lastq=0;
//new record
#if QDEBUG
clock_t curt=clock(); //display first filled column
  if(curt-startt2> INTERSECT_DISP*CLOCKS_PER_SEC){
  print("Time(s):",(curt-startt)/CLOCKS_PER_SEC,"Partial:",fst,"/",N,"\n");startt2=curt;}
#else
fflush(stdout);//fix low priority;
#endif

} //end loop


}



void solve(int* q,int N){int temp;
#define swapq(x,y) temp=x;x=y;y=temp;

psolve(q,N);

u64 cur=diags(q,N),best=cur, A,B;
#if QDEBUG
if(cur){print(N," is partially solved to:",cur," intersections\n");}
#endif
while(cur){
B=randuint64()&1?last:fst;
do{A=randuint64()%N;}while(A==B);


swapq(q[A],q[B]);
cur=diags(q,N);//count diagonal intersects
if(cur>best){ //revert if worse
swapq(q[A],q[B]);continue;  }
best=cur;
//new record
#if QDEBUG
clock_t curt=clock();
  if(curt-startt2> INTERSECT_DISP*CLOCKS_PER_SEC){
  print("Time(s):",(curt-startt)/CLOCKS_PER_SEC,"Intersections:",cur,"\n");startt2=curt;}
#else
fflush(stdout);//fix low priority;
#endif

} //end loop
}


int main(int argc,char**argv){startt=clock();startt2=startt;
if(argc!=2){syntax:;puts("Syntax:nq N\n N=Board size(4+)");exit(1);}
int N=atoi(argv[1]);if(N<4)goto syntax;
int* q=malloc(sizeof(int)*N);//queen row/cols(2^31-1 max)
if(!q){perror("Queen array size too large");exit(2);}
for(int i=0;i<N;i++)q[i]=i;//unique rows/cols to swap.
;solve(q,N);startt2=clock();
if(PRINT_RESULT_MAX>N){for(int i=0;i<N;i++)printf("%d,",q[i]+1);}
print("\nSolution found in:",(startt2-startt)/MS_CLOCK," milliseconds\n");

return 0;}
