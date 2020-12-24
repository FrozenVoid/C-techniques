//earlier USEDEBUG has to be defined to toggle on debug print
#ifndef USEDEBUG
#define DEBUGPRINT(...) 
#else
#define DEBUGPRINT(...) fprintf(stderr,__VA_ARGS__)
#endif
