#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef FUNCT_INLINE
#define INLINE __attribute__((always_inline))
#else
#define INLINE
#endif

#if 0
static INLINE int barrier(int x)
{
    asm volatile ("" : "+r"(x));
    return x;
}
#endif

#if 1
static INLINE void barrier_order(void)
{
    asm volatile (""::: "memory");
}
#endif

static int do_some_thing(int *j) {
    *j = *j + 100;
    return 0x55AA55AA;
}

int main(void)
{
    int i = 0xAA55AA55, j = 0;

#if 0
    i = barrier(i);
#endif

#if 1
    barrier_order();
#endif

    i = do_some_thing(&j);
    if (0x55AA55AA != i) exit(1);
    printf("%d\n", j);
    return 0;
}
