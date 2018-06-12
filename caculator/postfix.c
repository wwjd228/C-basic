#include <string.h>
#include <stdio.h>
#include "postfix.h"

static inline int whiteSpace(char ch)
{
    return (ch == ' ' | ch == '\t' | ch == '\0' | ch == '\n');
}

static inline int skipWhiteSpace(char *str, int beg) {
    while (whiteSpace(str[beg++]));
    return beg - 1;
}

static inline int isOperator(char ch) {
    return (ch == '+' | ch == '-' | ch == '*' | ch == '/'
         | ch == '|' | ch == '&' | ch == '^' | ch == '%');
}

static inline int isSign(char ch) {
    return ( ch == '(' || ch == ')' );
}

static inline int getPriority(char *op) {
    if (!strcmp(op, "|")) return 0;
    else if (!strcmp(op, "^")) return 1;
    else if (!strcmp(op, "&")) return 2;
    else if (!strcmp(op, "<<")) return 3;
    else if (!strcmp(op, ">>")) return 3;
    else if (!strcmp(op, "+")) return 4;
    else if (!strcmp(op, "-")) return 4;
    else if (!strcmp(op, "*")) return 5;
    else if (!strcmp(op, "/")) return 5;
    else if (!strcmp(op, "%")) return 5;
    else return -1;
}

int postfix(char *infix, int position, struct stack *opt)
{
    int numOfOperation = 0;
    int previousOpt = 0;
    struct stack tmp;
    tmp.top = 0;

    while (infix[position] != '\0' && infix[position] != '\n') {
        int i = 0;
        position = skipWhiteSpace(infix, position);
        while (!whiteSpace(infix[position])) {
            char operation[MAX_DIGITAL];
            char operator[2];
            if (infix[position] == ')') {
                return position + 1;
            }

            // push expression in ()
            else if (infix[position] == '(') {
                position++;
                position = postfix(infix, position, opt);
                numOfOperation++;
            }

            // process operator
            else if (isOperator(infix[position])) {
                do {
                    operator[i++] = infix[position++];
                } while (isOperator(infix[position]));
                operator[i] = '\0';
            }

            // push operation
            else {
                do {
                    operation[i++] = infix[position++];
                } while (!isOperator(infix[position]) && !whiteSpace(infix[position]) && !isSign(infix[position]));
                operation[i] = '\0';
                numOfOperation++;
                push(opt, operation, &((*opt).top));
            }

            i = 0;
            if (numOfOperation == 2) {
                if ( previousOpt != 0 && getPriority(operator) > getPriority((*opt).element[previousOpt - 1])) {
                    // Need temp stack to save poped element.
                    // Poped until previous opt
                    while ((*opt).top >= previousOpt) {
                        char *element = pop(opt, &((*opt).top));
                        push(&tmp, element, &tmp.top);
                    }

                    // Push all element back
                    char *low_priorityOp = pop(&tmp, &tmp.top);
                    while (tmp.top > 0) {
                        char *element = pop(&tmp, &tmp.top);
                        push(opt, element, &((*opt).top));
                    }
                    push(opt, operator, &((*opt).top));
                    push(opt, low_priorityOp, &((*opt).top));
                }
                else
                    push(opt, operator, &((*opt).top));
                previousOpt = (*opt).top;
                numOfOperation = 1;
            }
        }
    }
    return position;
}
