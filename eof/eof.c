#include <stdio.h>

int main(void)
{
    printf("value of EOF = %d\n", EOF);
    return getchar() != EOF;
}
