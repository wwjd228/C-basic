#include <stdio.h>

void sqeeze(char *s1, char *s2)
{
    int i = 0, k = 0, j;
    while ( s1[i] != '\0' ) {
        j = 0;
        while ( s2[j] != '\0' && s1[i] != s2[j] )
            j++;
        if ( s2[j] == '\0' )
            s1[k++] = s1[i];
        i++;
    }

    s1[k] = '\0';
}

void main(void)
{
    char s1_before[12] = "Hello World!";
    char s1[12] = "Hello World!";
    char s2[15] = "Damn it! World!";
    sqeeze(s1, s2);
    printf("\"%s\" After squeeze with \"%s\":\n%s\n", s1_before, s2, s1);
}
