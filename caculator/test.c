#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "getline.h"
#include "postfix.h"

extern int top;

int main(void)
{
    // input test getline.

    // the initial value of auto variable is gabage.
    printf("Please type \"(1+2)*3\"\n");
    char line[LIMIT];
    ssize_t numOfChar = getline_from_consloe(line);
    assert(!strcmp(line, "(1+2)*3"));

    // test stack
    // test push
    struct stack stack_t;
    stack_t.top = 0;
    char *input_str = "one";
    push(&stack_t, input_str, &stack_t.top);
    assert(stack_t.top == 1);

    // test pop
    char *element = pop(&stack_t, &stack_t.top);
    assert(!strcmp(element, "one") && stack_t.top == 0);

    // test postfix
    struct stack postfixOpt;
    postfixOpt.top = 0;
    int start = 0;
    int endOfline = postfix(line, start, &postfixOpt);
    print_stack(postfixOpt);
    assert(postfixOpt.top == 5);

    // test boundary atof
    double f = atof(" vhhjgjhg +  8.3+");
    printf("test boundary atof \"jhfjhgjh +     8.3\": %lf\n", f);

    printf("Test Passed!\n");
    return 0;
}
