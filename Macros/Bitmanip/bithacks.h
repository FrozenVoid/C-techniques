// reduce x to 0 if y!=0 (x*(y==0))
// y>0:==0 -> 0:1 -> -0:-1 =>0:0xffff.. => x&0==0:x&0xffff..
#define red0(x,y) (x&(-(!y)))
