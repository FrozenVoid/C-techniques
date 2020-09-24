#include <unistd.h>
/* A pointer can be passed directly as literal object.
  This is usually used with strings.

*/
// ssize_t write(int fd, const void *buf, size_t count);
int main(){write(1,"Hello World",11);}
