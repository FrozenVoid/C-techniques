int bingap32_dc(u32 N){// a faster pure C bingap using GCC intrinsics
int maxGap=0,gap=0;
do{
N>>=__builtin_ctz(N);//strip trailing zeros
N>>=__builtin_ctz(~N);//strip trailing ones
maxGap=gap>maxGap?gap:maxGap;//if N has bits set maxGap(initial iteration does nothing)
gap=__builtin_ctz(N);//count trailing zeros 
}while(N);

return maxGap;	
}                      
