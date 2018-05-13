#include <stdio.h>

#define BITSOFINT sizeof(unsigned) * 8

void testUnsignedShift(unsigned x)
{
    printf("Before shift right %x\n", x);
    printf("Unsigned shift right 1 bit is ");
    x >> 1 < 0?printf("arithmetical.\n"):printf("logical.\n");
    printf("After shift right %x\n", x >> 1);
}

void testSignedShift(int x)
{
    printf("Before shift right %x\n", x);
    printf("Signed shift right 1 bit is ");
    x >> 1 < 0?printf("arithmetical.\n"):printf("logical.\n");
    printf("After shift right %x\n", x >> 1);
}

unsigned getBits( unsigned x, int position, int n )
{
    return (x >> (position + 1 - n)) & ~(~0 << n);
}

unsigned cleanBits32_t(unsigned x, int position, int n)
{
    return n == 0 ? x : (x & ~(~(~0 << n) << (position + 1 - n)));
}

unsigned setBits32_t(unsigned x, int position, int n)
{
    return n == 0 ? x : (x | (~(~0 << n) << (position + 1 - n)));
}

unsigned invertBits32_t(unsigned x, int position, int n)
{
    return n == 0 ? x : (x ^ (~(~0 << n) << (position + 1 - n)));
}

unsigned rightror(unsigned x, int n)
{
    return n == 0 ? x : (x >> (BITSOFINT - n)) | (x << n);
}

void main(void)
{
    unsigned i = -1;
    int j = -1;
    printf("Environment: %lu bits\n", BITSOFINT);
    testUnsignedShift(i);
    testSignedShift(j);

    // n == 0 will cause overflow (if shift 32 bits).
    printf("------------------ Bit operations -------------------------\n");
    printf("Get 0xff form bit 7 offset 4 bits: 0x%x\n", getBits(0xff, 7, 4));
    printf("Clean 0xff form bit 3 offset 4 bits: 0x%x\n", cleanBits32_t(0xff, 3, 4));
    printf("Set 0x0f form bit 7 offset 4 bits: 0x%x\n", setBits32_t(0x0f, 7, 4));
    printf("Invert 0x80ff form bit 15 offset 1 bits: 0x%x\n", invertBits32_t(0x80ff, 15, 1));
    printf("Rotate 0x0fffffff offset 4 bits: 0x%x\n", rightror(0x0fffffff, 4));
}
