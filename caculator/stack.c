#include <string.h>
#include <stdio.h>
#include "stack.h"

char *pop(struct stack *s, int *top)
{
    return (*s).element[--(*top)];
}

void push(struct stack *s, char *element, int *top)
{
    strcpy((*s).element[(*top)++], element);
}

void print_stack(struct stack s)
{
    int i = 0;
    while ( i < s.top )
        printf("%s", s.element[i++]);
    printf("\n");
}
