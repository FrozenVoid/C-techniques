#include "Util/void.h"//https://github.com/FrozenVoid/C-headers

//fast N Queens "focus cell" solver

#define QDEBUG 1//print intersect count each INTERSECT_DISP seconds
#define INTERSECT_DISP 1//1 seconds
#define MS_CLOCK (CLOCKS_PER_SEC/1000)
size_t last=0;//focus column(last intersect)
clock_t startt,startt2,curt;
size_t diags(int*board,size_t len){//optimization metric
size_t sum=0;
for(size_t i=0;i<len;i++){int cur=board[i];
 for(size_t z=i+1;z<len;z++){int zqueen=board[z];
 if(((z-i)==tabs(zqueen-cur))){last=z;sum++;break;};   }  }
return sum;}


void solve(int* q,int N){int temp;
#define swapq(x,y) temp=x;x=y;y=temp;
u64 cur=diags(q,N),best=cur;int lswap=0;size_t A=4,B=3,C=1,D=2;
while(cur){lswap=cur>N/8;//low intersect switch off
B=last;//force focus cell to swap queens
do{A=randuint64()%N;}while(!(B^A));
if(lswap){
do{C=randuint64()%N;}while(!((C^A)|(C^B)));
 do{ D=randuint64()%N;}while(!((D^A)|(D^B)|(D^C)));
 swapq(q[C],q[D]);//swap next cols
}
swapq(q[A],q[B]);

cur=diags(q,N);//count diagonal intersects

if(cur>best){ //revert if worse
swapq(q[A],q[B]);
if(lswap){swapq(q[C],q[D]);}
continue;  }

best=cur;
  if(QDEBUG && (clock()-startt2> INTERSECT_DISP*CLOCKS_PER_SEC)){print("Time(s):",(clock()-startt)/CLOCKS_PER_SEC,"Intersections:",cur,"\n");startt2=clock();}
} //end loop
}

int main(int argc,char**argv){startt=clock();startt2=clock();
if(argc!=2){syntax:;puts("Syntax:nq N\n N=Board size(4+)");exit(1);}
int N=atoi(argv[1]);if(N<4)goto syntax;
int* q=malloc(sizeof(int)*N);//queen row/cols(2^31-1 max)
if(!q){perror("Queen array size too large");exit(2);}
for(int i=0;i<N;i++)q[i]=i;//unique rows/cols to swap.
solve(q,N);
for(int i=0;i<N;i++)printf("%d,",q[i]+1);
print("\nSolution found in:",(clock()-startt)/MS_CLOCK," milliseconds\n");

return 0;}
