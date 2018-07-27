#include <stddef.h>

#define NALLOC 1024

typedef long _align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    _align x;
};

typedef union header _header_t;

void *mymalloc(unsigned nbytes);
void myfree(void *ap);
