 #ifdef WIN32
 #include <malloc.h>
 #define memsize(x) _msize((void*)x)
  #else
  #ifdef __APPLE__
  #include <malloc/malloc.h>
  #define memsize(x) malloc_size((const void*)x)
  #else//assume Linux-compatible
  #include <malloc.h>
  #define memsize(x) malloc_usable_size((void*)x)
  #endif
 #endif
