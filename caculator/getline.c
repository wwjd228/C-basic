#include <stdio.h>
#include "getline.h"

ssize_t getline_from_consloe(char *line)
{
    int i = 0;
    char c;
    while ( i < LIMIT -1 & (c = getchar()) != '\n' & c != EOF )
        line[i++] = c;
    line[i] = '\0';
    return i;
}

