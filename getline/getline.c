#include <stdio.h>
#include <stdlib.h>

#define LIMIT 72

ssize_t getline_from_consloe(char *line)
{
    int i = 0;
    char c;
    while ( i < LIMIT -1 & (c = getchar()) != '\n' & c != EOF )
        line[i++] = c;
    line[i] = '\0';
    return i;
}

void main(void)
{
    char *line = malloc(LIMIT);
    int numOfchar = getline_from_consloe(line);
    printf("Get a line with %d character%s:\n%s\n", numOfchar,
            numOfchar==1?"":"s", line);
}
