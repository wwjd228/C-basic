#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void j_strreverse( char *src )
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

void j_strcat(char *dest, char *src)
{
    // strcat asume dest has enough space to be copied.
    int i = 0;
    while (dest[i++] != '\0')
        ;
    i--;
    while ((dest[i++] = *src++) != '\0')
        ;
    dest[i] = '\0';
}

int j_strcmp(char *str1, char *str2)
{
    while (*str1 == *str2++) {
        if (*str1++ == '\0')
            return 0;
    }

    return -1;
}

size_t j_strlen(char *str)
{
    size_t s = 0;
    while (str[s++] != '\0')
        ;
    return s - 1;
}

void *j_strcpy(char *dest, char *src)
{
    int i = 0;
    while((dest[i++] = *src++) != '\0')
        ;
    dest[i] = '\0';
}

void main(void)
{
    char *strp = "Hello World";
    printf("size of pointer string \"Hello World\" = %lu\n", sizeof(strp) / sizeof(strp[0]));
    // pointer string cannot be modified.
    // string function like strcpy() won't to allocate memory space.
    char str[11] = "Hello World";
    j_strreverse(str);
    assert(j_strcmp(str, "dlroW olleH") == strcmp(str, "dlroW olleH"));

    // test j_strcat
    char str_to_concate[16] = "test ";
    j_strcat(str_to_concate, str);
    assert(j_strcmp(str_to_concate, "test dlroW olleH") ==
        strcmp(str_to_concate, "test dlroW olleH"));

    // test j_strlen
    assert(strlen(str) == j_strlen(str));

    // test j_strcpy
    j_strcpy(str, "Hello World");
    assert(!j_strcmp(str, "Hello World"));

    printf("Pass Test\n");
}
