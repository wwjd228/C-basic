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

    int *nums = mycalloc(3, 4);
    printf("%d, %d, %d\n", nums[0], nums[1], nums[2]);

    myfree(str);
    myfree(nums);

    return 0;
}
