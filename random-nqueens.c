//solve 8 queens puzzle using random optimization algorithms
/* compile with gcc -Ofast  queens.c -oqueens
syntax: queens boardsize  
(The program isn't that optimized, searching for boardsize>1000 not reccomended)
the optimizer will often get stuck at 1-3 intersections, this is normal due randomness
*/
#include "Util/void.h"//https://github.com/FrozenVoid/C-headers


void printboard(int* b,size_t len){puts("");
for(size_t i=0;i<len;i++){
 for(size_t z=0;z<len;z++){ printf("%s",(z==b[i])?"Q":"X"); }puts(""); }}


size_t intersections(int*board,size_t len){//optimization metric
size_t sum=0;
//check equal rows,diagonal
for(size_t i=0;i<len;i++){int cur=board[i];
 for(size_t z=i+1;z<len;z++){
sum+=(cur==board[z]);
sum+=(abs(z-i)==abs(board[z]-cur));   }  }
return sum;}

//4- cell optimization++++++++++++++++++++++++++++++++++++++++++++

uint64_t log2index(size_t X){return ((unsigned) (8*sizeof (unsigned long long) - __builtin_clzll((X)) ))      ;}

#define tmin(x,y) ({typeof(x) tminx=x,tminy=y,res=tminy<tminx?tminy:tminx;      ;res;})
#define tmax(x,y) ({typeof(x) tminx=x,tminy=y,res=tminy>tminx?tminy:tminx;      ;res;})
void optimize(int*board,size_t len){

size_t metric=intersections(board,len),curmetric=1e9;
if(!metric)return;//already solved board

int maxcols=tmax(log2index(metric),len<4?len:4);
//if(defcols<8)defcols=len<8?len/2:8;

/* queens 640  @16->to 3000 intersections:

*/


size_t rndcol[maxcols];int optimal[maxcols];size_t trial[maxcols];


uniquesetrand(rndcol,maxcols,0,len);//create unique random cols
for(size_t i=0;i<maxcols;i++)optimal[i]=board[rndcol[i]];

for(size_t i=0;i<len;i++){
if(!metric)return;//already solved


uniquesetrand(trial,maxcols,0,len);//unique valss
for(size_t i=0;i<maxcols;i++)board[rndcol[i]]=trial[i];//copy  trial to board[rndcol]
curmetric=intersections(board,len);//check metric

if(curmetric<metric){metric=curmetric; //new metric
for(size_t i=0;i<maxcols;i++)optimal[i]=board[rndcol[i]];

dbgprint("\nIntersections:",metric," Maxcols:",maxcols);
if(!metric)return;

 }
}
for(size_t i=0;i<maxcols;i++)board[rndcol[i]]=optimal[i];//copy  optimals to board[rndcol]


}


int main(int argc,char ** argv){
size_t maxqueens=(argc>1)?numberof(argv[1]):8;
int* b=calloc(sizeof(int)*maxqueens,1);
for(size_t i=0;i<maxqueens;i++)b[i]=i;//set row=column
notoptimized:
for(size_t i=0;i<10000;i++) optimize(b,maxqueens);
if(intersections(b,maxqueens))goto notoptimized;

printboard(b,maxqueens);
}
