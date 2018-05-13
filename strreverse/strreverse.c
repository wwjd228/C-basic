#include <stdio.h>
#include <stdlib.h>

void *strreverse( char *src )
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

void main(void)
{
    // pointer string cannot be modified.
    // string function like strcpy() won't to allocate memory space.
    char str[11] = "Hello World";
    strreverse(str);
    printf("%s\n", str);
}
