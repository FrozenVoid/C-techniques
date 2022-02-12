#include "Util/void.h"//https://github.com/FrozenVoid/C-headers

//fast N Queens "focus cell" solver
#define mstime() ((clock())/(CLOCKS_PER_SEC/1000))
#define QDEBUG 1//print swaps/intersect count each INTERSECT_DISP seconds
#define INTERSECT_DISP 3//1 seconds
#define MS_CLOCK (CLOCKS_PER_SEC/1000)
#define MIN_SIDE 4//minimal board width
size_t last=0,fst=0;//focus column(last intersect)
int* diag;
i64 swapt=0;//valid swaps total(set if QDEBUG enabled)
u64 calls=0,rndtime=0,cti;
clock_t nxt=0;


void printboard(int*q,size_t N){print("\n");for(int i=0;i<N;i++)printf("%d,",q[i]+1);}
size_t diags(int*board,size_t len,size_t early){//optimization metric
size_t sum=0;

if(early&& len>64){//skip >early sum overflow
for(size_t i=0;i<len;i++){size_t cur=board[i],zc=0;if(sum>early)return sum;
 for(size_t z=i+1;z<len&&zc<2;z++){
  size_t zqueen=board[z];
 if(((z-i)==(zqueen-cur))||((z-i)==(cur-zqueen))){fst=i;last=z;zc++;sum++; };   }  }
}else{
for(size_t i=0;i<len;i++){size_t cur=board[i];
 for(size_t z=i+1;z<len;z++){
  size_t zqueen=board[z];
 if(((z-i)==(zqueen-cur))||((z-i)==(cur-zqueen))){fst=i;last=z;sum++; };   }  }}
return sum;}

uint64_t log2index(size_t X){return ((unsigned) (63 - __builtin_clzll((X)) ))      ;}


size_t fstcols(int* board,size_t len){
size_t leftret=len,rightret=len;
for(size_t i=0;i<len;i++){diag[i]=0;}
for(size_t i=0;i<len;i++){
int r=board[i]-i;//rowcol
r=r<0?r+len-1:r;
diag[r]++;if(diag[r]>1){leftret=i;break;}}

for(size_t i=0;i<len;i++){;diag[i]=0;}
for(size_t i=0;i<len;i++){
int r=board[i]-(len-i-1);//rowcol
r=r<0?r+len-1:r;
diag[r]++;if(diag[r]>1){rightret=i;break;}}



return rightret>leftret?leftret:rightret;
}

size_t lstcols(int* board,size_t len){
//last d intersect
size_t leftret=len,rightret=len;
for(size_t i=0;i<len;i++){diag[i]=0;}
for(size_t i=0;i<len;i++){
int r=board[i]-i;//rowcol
r=r<0?r+len-1:r;
diag[r]++;if(diag[r]>1 ){leftret=i;;}}

for(size_t i=0;i<len;i++){;diag[i]=0;}
for(size_t i=0;i<len;i++){
int r=board[i]-(len-i-1);//rowcol
r=r<0?r+len-1:r;
diag[r]++;if(diag[r]>1 ){rightret=i;}}
if(rightret==len)return leftret;
return rightret<leftret?leftret:rightret;
}



size_t mostcols2(int* board,size_t len){
size_t sum=0,maxi=0;//most collided col.
for(size_t i=0;i<len;i++){diag[i]=0;}
for(size_t i=0;i<len;i++){
int r=board[i]-i;//rowcol
diag[r<0?r+len-1:r]++;}

for(size_t i=0;i<len;i++){
if(diag[i]>sum){sum=diag[i];maxi=i;};}

for(size_t i=0;i<len;i++){diag[i]=0;}
for(size_t i=0;i<len;i++){
int r=board[i]-(len-i-1);//rowcol
diag[r<0?r+len-1:r]++;;}
for(size_t i=0;i<len;i++){
if(diag[i]>sum){sum=diag[i];maxi=i;}
;;}
return maxi;
}

size_t countudiag(int* board,size_t len){
//each collision leaves +zero in diag array.
i64 sum=0;//count double occupied diagonals
//all q sum to (len*(len-1))/2;
//0 1 2 3 4 5 = 15= 6*5/2
for(size_t i=0;i<len;i++){diag[i]=0;}
for(size_t i=0;i<len;i++){
int left=board[i]-i;
left=(left<0)?left+len-1:left;
diag[left]++;}//row down
for(size_t i=0;i<len;i++){
sum+=diag[i]==0;}

for(size_t i=0;i<len;i++){diag[i]=0;}
for(size_t i=0;i<len;i++){
int left=board[i]-(len-i-1);
left=(left<0)?left+len-1:left;
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
// O(N) > complexity < O(N^2)
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
  print("psolve:",mstime(),"ms Solved%:",res*100.0/N," VSwaps:",swapt,"QCalls:",calls,"\n");nxt=clock();;}
#else
fflush(stdout);//fix low priority assigned if no output
#endif

} //end loop


}


//=======================
//diagonal count solver ~O(N) but weak vs ending
void dsolve(int* q,int N){int temp;
#define swapq(x,y) temp=x;x=y;y=temp;
u64 A,B;size_t fail=0;
u64 limf=N*16;
u64 limf2=N/4;
u64 limf3=N/16;
size_t tdiag;
u64 cur=countudiag(q,N),best=cur,udiag=0,ucur=0;

#if QDEBUG
//printboard(q,N);
 //tdiag=diags(q,N);
print("Starting diagonal solver:",mstime()," ms",cur,"intersections\n");
#endif
while(cur){fst=fstcols(q,N);

if(fail>limf2){B=mostcols2(q,N);
}else{B=fst;}
//if(cur!=best)B=randuint64()%N;else{B=fstcols(q,N);}
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
if(cur>best){
swapq(q[A],q[B]);
#if QDEBUG
 swapt--;//valid swaps revert
#endif
if(fail++>limf)break;//revert if worse
continue; }


#if QDEBUG
 //tdiag=diags(q,N);
  if(clock()-nxt>INTERSECT_DISP*CLOCKS_PER_SEC ){
  print("\n best=",best,"cur=",cur,"fst=",fst,"A=",A,"B=",B,"fail=",fail,"/",limf2);
  print("\ndsolve:",mstime(),"ms Intersections:",best,"VSwaps:",swapt);nxt=clock();}
#else
fflush(stdout);//fix low priority;
#endif
fail=0;best=cur;
} //end loop

 print("dsolve:",mstime(),"ms Intersections:",cur,"VSwaps:",swapt,"fails",fail,"\n");
}

//=======================
//first diagonal count solver ~O(N)
void fdsolve(int* q,int N){int temp;
#define swapq(x,y) temp=x;x=y;y=temp;
u64 A,B;size_t fail=0,dupcur=0;
u64 limf=N*16;
u64 limf2=N/4;
u64 limf3=N/16;
size_t lindex=log2index(N);
size_t scramble=512/lindex;
u64 limf4=2+N/512;
#if QDEBUG
//printboard(q,N);
 //tdiag=diags(q,N);
print("Scramble*=",scramble,"\n");
#endif
//scramble diagonals
for(int z=0;z<scramble;z++){
for(size_t i=0;i<N;i++){
size_t rcol=randuint64()%N;
swapq(q[i],q[rcol]);
}}
u64 cur=fstcols(q,N),best=cur,udiag=0,ucur=0;

#if QDEBUG
//printboard(q,N);
 //tdiag=diags(q,N);
print("Starting fdsolve solver:",mstime()," ms",N-cur,"intersections\n");
#endif
while(best<N  ){//fst=firstq1(q,N);
fst=fstcols(q,N);
B=fst;
//if(dupcur>lindex)B=mostcols2(q,N);
//limit search range B <>N (Bmax+1==N)N-Bmax-1=0
if(cur!=best){
A=fst+randuint64()%(N-fst-1);
while(A==B)A=fst+randuint64()%(N-fst-1);
}else{
A=randuint64()%(N);
while(A==B)A=randuint64()%(N);
}

//if(cur!=udiag )B=mostcols(q,N);//stuck
//do{A=randuint64()%N;}while(A==B);

swapq(q[A],q[B]);
//for(int i=0;i<N;i++)printf("%d,",q[i]+1);print("\n");
#if QDEBUG
swapt++;//valid swaps total
#endif
cur=fstcols(q,N);//count diagonal intersects
if(cur<=fst){
if(cur<fst){swapq(q[A],q[B]);}

#if QDEBUG
 swapt--;//valid swaps revert
#endif
if(fail++>(N-best)*limf4)break;//revert if worse
continue; }


#if QDEBUG


 //tdiag=diags(q,N);
  if(clock()-nxt>INTERSECT_DISP*CLOCKS_PER_SEC ){
  print("\n best=",best,"cur=",cur,"fst=",fst,"A=",A,"B=",B,"fail=",fail,"/",(N-best)*limf4);
  print("\nfdsolve:",mstime(),"ms Solved%:",((best*100.0)/N),"VSwaps:",swapt);nxt=clock();}


#else
fflush(stdout);//fix low priority;
#endif
//if(best==cur)dupcur++;else{dupcur=0;}
fail=0;best=cur;
} //end loop

 print("fdsolve:",mstime(),"ms Distance:",N-best,"VSwaps:",swapt,"fails",fail,"\n");
}

//===================Solver===========================
void solve(int* q,int N){int temp;
//step-by-step solver ~O(N^2)
#define swapq(x,y) temp=x;x=y;y=temp;
u64 A,B;


#if QDEBUG

print("Start solving at:",mstime()," ms\n");
#endif
if(N>1024){fdsolve(q,N);dsolve(q,N);}
if(N<1025)psolve(q,N);


size_t fail=0; const int smallboard=N<9;
if(smallboard)psolve(q,N);
//u64 cur=countudiag(q,N);
u64 cur=diags(q,N,0);
u64 best=cur,udiag=0,ucur=0;
#if QDEBUG
if(cur){print(N," is partially solved to:",cur," intersections and ",swapt,"swaps;",mstime(),"ms\n");}
#endif
while(cur){
u64 rnd1=randuint64();
firstq1(q,N);
//size_t bcol=mostcols2(q,N);
B=rnd1&1?last:rnd1%N;


A=randuint64()%N;
while(A==B)A=randuint64()%N;
swapq(q[A],q[B]);



#if QDEBUG
swapt++;//valid swaps total
#endif
//cur=countudiag(q,N);
cur=diags(q,N,best);//count diagonal intersects

if(cur>best){ //revert if worse

if(cur>best){
#if QDEBUG
 swapt--;//valid swaps revert
#endif
fail++;
swapq(q[A],q[B]);}
continue;  }

//new record
#if QDEBUG

  if(clock()-nxt>INTERSECT_DISP*CLOCKS_PER_SEC){
  print("solve:",mstime(),"ms Intersections:",cur,"/",N,"VSwaps:",swapt,"Fail:",fail,"\n");if(N<64)printboard(q,N);puts("");
nxt=clock();
  }


#else
fflush(stdout);//fix low priority;
#endif
best=cur;fail=0;
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
