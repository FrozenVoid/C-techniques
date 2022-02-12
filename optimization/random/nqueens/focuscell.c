#include "Util/void.h"//https://github.com/FrozenVoid/C-headers

//fast N Queens "focus cell" solver
#define mstime() ((clock())/(CLOCKS_PER_SEC/1000))
#define QDEBUG 1//print swaps/intersect count each INTERSECT_DISP seconds
#define INTERSECT_DISP 1//1 seconds
#define MS_CLOCK (CLOCKS_PER_SEC/1000)
#define MIN_SIDE 4//minimal board width
size_t last=0,fst=0;//focus column(last intersect)
int* diag;
i64 swapt=0;//valid swaps total(set if QDEBUG enabled)
u64 calls=0,rndtime=0,cti;
clock_t nxt=0;


void printboard(int*q,size_t N){print("\n");for(int i=0;i<N;i++)printf("%d,",q[i]+1);}
size_t diags(int*board,size_t len){//optimization metric
size_t sum=0;
for(size_t i=0;i<len;i++){size_t cur=board[i],zc=0;
 for(size_t z=i+1;z<len&&zc<2;z++){
  size_t zqueen=board[z];
 if(((z-i)==(zqueen-cur))||((z-i)==(cur-zqueen))){fst=i;last=z;zc++;sum++; };   }  }
return sum;}

uint64_t log2index(size_t X){return ((unsigned) (63 - __builtin_clzll((X)) ))      ;}


size_t fstcols(int* board,size_t len){
for(size_t i=0;i<len;i++){diag[i]=0;}
for(size_t i=0;i<len;i++){
int r=board[i]-i;//rowcol
diag[r<0?r+len:r]++;}
for(size_t i=0;i<len;i++){
if(diag[i]>1)return i;}

for(size_t i=0;i<len;i++){;diag[i]=0;}
for(size_t i=0;i<len;i++){
int r=board[i]-(len-i-1);//rowcol
diag[r<0?r+len:r]++;}

for(size_t i=0;i<len;i++){
if(diag[i]>1)return i;}

return len;
}

size_t mostcols2(int* board,size_t len){
size_t sum=0,maxi=0;//most collided col.
for(size_t i=0;i<len;i++){diag[i]=0;}
for(size_t i=0;i<len;i++){
int r=board[i]-i;//rowcol
diag[r<0?r+len:r]++;}

for(size_t i=0;i<len;i++){
if(diag[i]>sum){sum=diag[i];maxi=i;};}

for(size_t i=0;i<len;i++){diag[i]=0;}
for(size_t i=0;i<len;i++){
int r=board[i]-(len-i-1);//rowcol
diag[r<0?r+len:r]++;;}
for(size_t i=0;i<len;i++){
if(diag[i]>sum){sum=diag[i];maxi=i;}
;;}
return maxi;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

size_t countudiag(int* board,size_t len){
//const i64 expect=(len*(len-1))/2;//all row sum

i64 sum=0;//count double occupied diagonals
//all q sum to (len*(len-1))/2;
//0 1 2 3 4 5 = 15= 6*5/2
for(size_t i=0;i<len;i++){diag[i]=0;}
for(size_t i=0;i<len;i++){
int left=board[i]-i;
left=(left<0)?left+len:left;
diag[left]++;}//row down
for(size_t i=0;i<len;i++){
sum+=diag[i]==0;}

for(size_t i=0;i<len;i++){diag[i]=0;}
for(size_t i=0;i<len;i++){
int left=board[i]-(len-i-1);
left=(left<0)?left+len:left;
diag[left]++;}//row down
for(size_t i=0;i<len;i++){
sum+=diag[i]==0;}


return sum;
}
size_t firstq2(int*board,size_t len){//first intersect
#if QDEBUG
calls++;
#endif//don't alter focus
for(size_t i=0;i<len;i++){
 size_t cur=board[i];
 for(size_t z=i+1; z<len; z++){
  if(((z-i)^(board[z]-cur))&& (z-i)^(cur-board[z])  )continue;
  return i; ;   }  }
return len;}


size_t firstq1(int*board,size_t len){//first intersect
#if QDEBUG
calls++;// cti=__rdtsc();
#endif
for(size_t i=0;i<len;i++){
 size_t cur=board[i];
 for(size_t z=i+1; z<len; z++){
  if(((z-i)^(board[z]-cur))&& (z-i)^(cur-board[z])  )continue;
 fst=i; last=z; return i; ;   }  }
return len;}

//partially solve by 1st intersect(firstq1)
void psolve(int* q,int N){int temp;
#define swapq(x,y) temp=x;x=y;y=temp;
u64 limlq=N;//lower limit for queen swap fails
u64 cur,lastq=0, A,B,edge=N/256;
#if QDEBUG
u64 pinit=firstq1(q,N);
print("Starting partial solver;",mstime(),"ms \n","Partial:(",fst,",",last,")/",N," VSwaps:",swapt,"QCalls:",calls,"\n");
#endif
while(firstq1(q,N)<N ){//rndtime+=__rdtsc()-cti;
B=((last-fst)>edge)?last:fst;//force focus cell to swap queens(fst,last update from firstq1())
early:;
if(MIN_SIDE<8 && N<8)B=randuint64()%N;//fix small boards intersect

do{A=randuint64()%N;}while(A==B );

#if QDEBUG
swapt++;//valid swaps total
#endif
swapq(q[A],q[B]);//swap random with focused cell
//find first intersect source, check if below fst(i)
size_t res=firstq2(q,N);
if(res<fst){
swapq(q[A],q[B]);//revert if worse
if(lastq++>limlq)break;
#if QDEBUG
swapt--;//valid swaps revert
#endif
goto early;  }
lastq=0;//reset count of #last failed queen swaps.
//new record
#if QDEBUG

  if(clock()-nxt>INTERSECT_DISP*CLOCKS_PER_SEC){
  print("psolve:",mstime(),"ms Partial:(",res,",",last,")/",N," VSwaps:",swapt,"QCalls:",calls,"\n");nxt=clock();;}
#else
fflush(stdout);//fix low priority assigned if no output
#endif

} //end loop


}
//=======================

void dsolve(int* q,int N){int temp;
#define swapq(x,y) temp=x;x=y;y=temp;
u64 A,B;size_t fail=0;
u64 limf=N*16+12000;size_t tdiag;
u64 cur=countudiag(q,N),best=cur,udiag=0,ucur=0;
#if QDEBUG
//printboard(q,N);
 tdiag=diags(q,N);
print("Starting diagonal solver:",mstime()," ms",cur,"intersections\n");
#endif
while(cur){//fst=firstq1(q,N);

if(cur==best)B=mostcols2(q,N);
else{B=fstcols(q,N);}
//if(cur<5){firstq1(q,N);B=randuint64()&1?last:fst;}
A=randuint64()%N;while(A==B)A=randuint64()%N;

//if(cur!=udiag )B=mostcols(q,N);//stuck
//do{A=randuint64()%N;}while(A==B);

swapq(q[A],q[B]);
//for(int i=0;i<N;i++)printf("%d,",q[i]+1);print("\n");
#if QDEBUG
swapt++;//valid swaps total
#endif
cur=countudiag(q,N);//count diagonal intersects
if(cur>best){if(fail++>limf)break;//revert if worse
if(1){swapq(q[A],q[B]);
#if QDEBUG
 swapt--;//valid swaps revert
#endif
}
continue; }
fail=0;best=cur;

#if QDEBUG
 //tdiag=diags(q,N);
  if(clock()-nxt>INTERSECT_DISP*CLOCKS_PER_SEC ){
  print("dsolve:",mstime(),"ms Intersections:",best,"VSwaps:",swapt,"\n");nxt=clock();}
#else
fflush(stdout);//fix low priority;
#endif

} //end loop

 print("dsolve:",mstime(),"ms Intersections:",cur,"VSwaps:",swapt,"fails",fail,"\n");
}
//===================Solver===========================
void solve(int* q,int N){int temp;
#define swapq(x,y) temp=x;x=y;y=temp;
u64 A,B;

if(N>2000){//scrambke diagonal for large boards
for(int z=0;z<4;z++){
for(size_t i=0;i<(N);i+=1){size_t sB=randuint64()%N;
swapq(q[i],q[sB]);}}

}

#if QDEBUG

print("Start solving at:",mstime()," ms\n");
#endif
if(N>1024)dsolve(q,N);
if(N<1025)psolve(q,N);



u64 cur=diags(q,N),best=cur,udiag=0,ucur=0;
#if QDEBUG
if(cur){print(N," is partially solved to:",cur," intersections and ",swapt,"swaps;",mstime(),"ms\n");}
#endif
while(cur){
u64 rnd1=randuint64();
firstq1(q,N);
B=rnd1&1?last:fst;


A=randuint64()%N;
while(A==B)A=randuint64()%N;
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

//new record
#if QDEBUG

  if(clock()-nxt>INTERSECT_DISP*CLOCKS_PER_SEC){
  print("solve:",mstime(),"ms Intersections:",cur,"VSwaps:",swapt,"\n");
nxt=clock();
  }


#else
fflush(stdout);//fix low priority;
#endif
best=cur;
} //end loop
}

int main(int argc,char**argv){
if(argc<2){syntax:;puts("Syntax:nq N [p]\n N=Board size min=" stringify(MIN_SIDE) " \n p=printboard");exit(1);}
int N=atoi(argv[1]);if(N<MIN_SIDE||N<4)goto syntax;
int* q=calloc(sizeof(int),N);//queen row/cols(2^31-1 max)
if(!q){perror("Queen array size too large");exit(2);}
; diag=calloc(sizeof(int),N);//diag row/cols(2^31-1 max)
if(!diag){perror("Diag array size too large");exit(3);}
for(int i=0;i<N;i++)q[i]=i;//unique rows/cols to swap.

;solve(q,N);
if(argc==3 && argv[2][0]=='p'){printboard(q,N);}
print("\nSolution found in:",mstime()," milliseconds",swapt,"swaps\n");

return 0;}
