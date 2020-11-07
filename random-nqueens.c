//solve 8 queens puzzle using random optimization algorithms
/* compile with gcc -Ofast  queens.c -oqueens
syntax: queens boardsize   [minintersect]
minintersect minimal intersections for which the program will halt and print board(0==default)
(The program isn't that optimized, searching for boardsizes >10000 not reccomended)
the optimizer will often get stuck at 1-3 intersections, this is normal due randomness


*/
#include "Util/void.h"//https://github.com/FrozenVoid/C-headers

void printboard(int* b,size_t len){puts("");
for(size_t i=0;i<len;i++){ for(size_t z=0;z<len;z++){ printf("%s",(z==b[i])?"Q":"⚹"); }puts(""); }}

size_t intersections(int*board,size_t len){//optimization metric
size_t sum=0;
for(size_t i=0;i<len;i++){int cur=board[i];
 for(size_t z=i+1;z<len;z++){int zqueen=board[z];
sum+=(cur==zqueen);sum+=((z-i)==tabs(zqueen-cur));   }  }
return sum;}

//4- cell optimization++++++++++++++++++++++++++++++++++++++++++++
uint64_t log2index(size_t X){return ((unsigned) (63 - __builtin_clzll((X)) ))      ;}

void optimize(int*board,size_t len,size_t mininter){
size_t metric=intersections(board,len),curmetric=-1;
const int maxcols=tmin(log2index(metric),len/2);
const int maxiter=1+(128/maxcols);// int maxcols=tmin(tmax(index,8),len);int maxiter=1+(128/maxcols);//tmin(maxcols,1+metric);
size_t rndcol[maxcols];int optimal[maxcols];size_t trial[maxcols];
uniquesetrand(rndcol,maxcols,0,len);//create unique random cols
for(size_t i=0;i<maxcols;i++)optimal[i]=board[rndcol[i]];
for(size_t i=0;i<maxiter;i++){
uniquesetrand(trial,maxcols,0,len);//unique valss
for(size_t i=0;i<maxcols;i++)board[rndcol[i]]=trial[i];//copy  trial to board[rndcol]
curmetric=intersections(board,len);
if(curmetric<metric){metric=curmetric; //new metric
for(size_t i=0;i<maxcols;i++)optimal[i]=board[rndcol[i]];
dbgprint("\nClock:",clock(),"Intersections:" ,metric,"Active Cols:",maxcols);
if(metric<mininter)break;
 }
}
for(size_t i=0;i<maxcols;i++)board[rndcol[i]]=optimal[i];//copy  optimals to board[rndcol]
}


int main(int argc,char ** argv){
size_t maxqueens=(argc>1)?numberof(argv[1]):8;
size_t minintersect=(argc>2)?numberof(argv[2]):0;
if(maxqueens<4){dbgprint("\nError:Boardsize <4 not supported\n");return 2;}

int* b=malloc(sizeof(int)*maxqueens);
for(size_t i=0;i<maxqueens;i++)b[i]=rrange(0,maxqueens);//set row=column
while(intersections(b,maxqueens)>minintersect)optimize(b,maxqueens,minintersect);
if(minintersect){dbgprint("\nReached",minintersect, "intersections of (diag|line) minimum");} else printboard(b,maxqueens);return 0;}
