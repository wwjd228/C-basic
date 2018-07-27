#include <stdio.h>
#include "mylib.h"

int main(void)
{
    char *str = mymalloc(6);
    str[0] = 'H';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    str[5] = '\0';

    printf("%s\n", str);
    myfree(str);

    return 0;
}
