#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define abs( x ) (x < 0 ? (x * -1) : (x))

void strreverse( char *src )
{
    int end = 0;
    int beg = 0;
    while (src[end] != '\0')
        end++;

    // skip null-terminated string
    end--;

    while (beg < end) {
        src[beg] ^= src[end];
        src[end] ^= src[beg];
        src[beg++] ^= src[end--];
    }
}

void itob(int src, char dest[], int base)
{
    /*
     * The type of base must be "int".
     * Or the mod in negative case will be wrong.
     * Keep the operation in same type.
     */
    int sign = src;
    int remain = 0, i = 0;
    do {
        /*
         * Using abs to avoid the case of -2^31.
         * Because the the range of int [-2^31, 2^31 - 1]
         */
        remain = abs(src % base);
        dest[i++] = ((remain > 9) ? (remain - 10 + 'a') : (remain + '0'));
    } while ( (src /= base) );

    if ( sign < 0 ) dest[i++] = '-';
    dest[i] = '\0';
    strreverse(dest);
}

void main(void)
{
    int n = -6, b = 10;
    int q = n / b;
    int r = n % b;
    printf("The mod function in C:\n-6 = 10 * %d + %d\n", q, r);
    char *s1 = malloc(sizeof(char) * 5);
    itob(1005, s1, 10);
    assert(!strcmp(s1, "1005"));
    char *s2 = malloc(sizeof(char) * 6);
    itob(-5050, s2, 10);
    assert(!strcmp(s2, "-5050"));
    char *s3 = malloc(sizeof(char) * 5);
    itob(15, s3, 2);
    assert(!strcmp(s3, "1111"));
    char *s4 = malloc(sizeof(char) * 3);
    itob(255, s4, 16);
    assert(!strcmp(s4, "ff"));
    char *s5 = malloc(sizeof(char) * 12);
    itob(-2147483648, s5, 10);
    assert(!strcmp(s5, "-2147483648"));
    printf("Testing Success!\n");

    // clean memory
    free(s1);
    free(s2);
    free(s3);
    free(s4);
    free(s5);
}
