//solve 8 queens puzzle using random optimization algorithms
/* compile with gcc -Ofast  queens.c -oqueens
syntax: queens boardsize   [minintersect]
minintersect minimal intersections for which the program will halt and print board(0==default)
(The program isn't that optimized, searching for boardsizes >10000 not reccomended)
the optimizer will often get stuck at 1-3 intersections, this is normal due randomness
*The idea is that optimize function knows nothing about the problem itself.


*/
#include "Util/void.h"//https://github.com/FrozenVoid/C-headers

void printboard(int* b,size_t len){puts("");
for(size_t i=0;i<len;i++){
 for(size_t z=0;z<len;z++){ printf("%s",(z==b[i])?"Q":"⚹"); }puts(""); }}


void intersections2(int*board,size_t len,size_t* diagsum,size_t* linesum){//optimization metric
//check equal rows,diagonal
size_t diag=0,line=0;
for(size_t i=0;i<len;i++){int cur=board[i];
 for(size_t z=i+1;z<len;z++){int zqueen=board[z];
line+=(cur==zqueen);
diag+=((z-i)==tabs(zqueen-cur));   }  }
*diagsum=diag;*linesum=line;
;}


size_t intersections(int*board,size_t len){//optimization metric
size_t sum=0,diagsum=0,linesum=0;;
//check equal rows,diagonal
for(size_t i=0;i<len;i++){int cur=board[i];
 for(size_t z=i+1;z<len;z++){int zqueen=board[z];
linesum+=(cur==zqueen);
diagsum+=((z-i)==tabs(zqueen-cur));
   }  }
sum=tmax(linesum,diagsum);

return sum;}

//4- cell optimization++++++++++++++++++++++++++++++++++++++++++++
#define intersectionssum(b,len) ({size_t diagsum=0,linesum=0;\
intersections2(b,len,&diagsum,&linesum);\
diagsum+linesum;})
#define MINCOLS 4
uint64_t log2index(size_t X){return ((unsigned) (63 - __builtin_clzll((X)) ))      ;}

#define METRIC intersectionssum
void optimize(int*board,size_t len,size_t mininter){

size_t metric=intersections(board,len),curmetric=-1;
size_t total=intersectionssum(board,len);
int index=log2index(metric);size_t diagsum,linesum;
const int maxcols=tmin(index,len/2);
//tmin(tmin(8,len),total)
const int maxiter=1+(128/maxcols);// int maxcols=tmin(tmax(index,8),len);int maxiter=1+(128/maxcols);//tmin(maxcols,1+metric);
size_t rndcol[maxcols];int optimal[maxcols];size_t trial[maxcols];
uniquesetrand(rndcol,maxcols,0,len);//create unique random cols
for(size_t i=0;i<maxcols;i++)optimal[i]=board[rndcol[i]];
for(size_t i=0;i<maxiter;i++){
uniquesetrand(trial,maxcols,0,len);//unique valss
for(size_t i=0;i<maxcols;i++)board[rndcol[i]]=trial[i];//copy  trial to board[rndcol]
//intersections2(board,len,&diagsum,&linesum);
curmetric=intersections(board,len);
//curmetric=tmax(diagsum,linesum);//check max metric diag/line
//found new record
if(curmetric<metric){metric=curmetric; //new metric
for(size_t i=0;i<maxcols;i++)optimal[i]=board[rndcol[i]];
intersections2(board,len,&diagsum,&linesum);
char choice=diagsum>linesum;
dbgprint("\nClock:",clock(),"Diagonals:",choice?"[":" ",diagsum,choice?"]":" ","Lines:",!choice?"[":" ",linesum,!choice?"]":" ","Active Cols:",maxcols);
if((diagsum+linesum)<mininter)break;
 }
}
for(size_t i=0;i<maxcols;i++)board[rndcol[i]]=optimal[i];//copy  optimals to board[rndcol]
}


int main(int argc,char ** argv){
size_t maxqueens=(argc>1)?numberof(argv[1]):8;
size_t minintersect=(argc>2)?numberof(argv[2]):0;
if(maxqueens<MINCOLS){dbgprint("\nError:Boardsize <",MINCOLS," not supported\n");return 2;}

int* b=malloc(sizeof(int)*maxqueens);
for(size_t i=0;i<maxqueens;i++)b[i]=rrange(0,maxqueens);//set row=column
while(intersectionssum(b,maxqueens)>minintersect)optimize(b,maxqueens,minintersect);
if(minintersect){dbgprint("\nReached",minintersect, "intersections of (diag|line) minimum");} else printboard(b,maxqueens);return 0;}
