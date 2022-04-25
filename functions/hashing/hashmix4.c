static inline u64 rotate64(u64 x,u32 bits){return (x>>bits)|(x<<(64-bits));}

u64 hashaddrt2(const u8* data,const size_t len){
//add with rotate2
u64 res=0x1234567812345178;
const u64* data8=(u64*)data;
const size_t data8len=len/8;
for(size_t i=0;i<data8len;i++){res+=rotate64(data8[i],res&63);}
u64 rest[1]={0};
memcpy(&rest[0],&data[(data8len)<<3],len-((data8len)<<3));
res+=rotate64(rest[0],res&63);
return res;}

u64 hashaddrt(const u8* data,const size_t len){
//add with rotate
u64 res=0;u64 last=0x1234567812345678;
const u64* data8=(u64*)data;
for(size_t i=0;i<(len/8);i++){
res+=last;res+=rotate64(data8[i],res&63);last=~data8[i];}
u64 rest[1]={0};
memcpy(&rest[0],&data[(len/8)<<3],len-((len/8)<<3));
res+=last;res+=rotate64(rest[0],res&63);
return res;}


u64 hashxoraddrt(const u8* data,const size_t len){
//xor add with rotate
u64 res=0;u64 last=0x1234567812345678;
const u64* data8=(u64*)data;
for(size_t i=0;i<(len/8);i++){
res+=last;res^=data8[i];last= rotate64(data8[i],res&31);}
for(size_t i=(len/8)<<3;i<len;i++){
res-=last;res^=data[i];last=data[i];}
return res;}


u64 hashxoradd(const u8* data,const size_t len){
//faster xor-add 
u64 res=0;u64 last=0x1234567812345678;
const u64* data8=(u64*)data;
for(size_t i=0;i<(len/8);i++){
res^=data8[i];res+=last;last=~data8[i];}
for(size_t i=(len/8)<<3;i<len;i++){
res^=data[i];res+=last;last=~data[i];}
return res;}

u64 hashmix4(const u8* data,const size_t len){
//quick xor-add hash, untested
u64 res=0;u64 mix[4]={0x1234567812345678,0x2345678123456781,0x3456781234567812,0x4567812345678123};
const u64* data8=(u64*)data;
for(size_t i=0;i<(len/8);i++){
res^=data8[i];res+=mix[i&3];mix[i&3]=data8[i];}
for(size_t i=(len/8)<<3;i<len;i++){
res^=data[i];res+=mix[i&3];mix[i&3]=data[i];}
return res;}
