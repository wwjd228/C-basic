#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "cdecl.h"
#include "j_string.h"

int top = -1;
#define POP stack[top--]
#define PUSH(s) (stack[++top] = s)

token_type_t classify_string(void)
{
    char *s = this_token.string;

    if (!j_strcmp(s, "const")) {
        j_strcpy(s, "read-only");
        return QUALIFIER;
    }

    if (!j_strcmp(s, "volatile")) return QUALIFIER;
    if (!j_strcmp(s, "void")) return TYPE;
    if (!j_strcmp(s, "char")) return TYPE;
    if (!j_strcmp(s, "signed")) return TYPE;
    if (!j_strcmp(s, "unsigned")) return TYPE;
    if (!j_strcmp(s, "short")) return TYPE;
    if (!j_strcmp(s, "int")) return TYPE;
    if (!j_strcmp(s, "long")) return TYPE;
    if (!j_strcmp(s, "float")) return TYPE;
    if (!j_strcmp(s, "double")) return TYPE;
    if (!j_strcmp(s, "struct")) return TYPE;
    if (!j_strcmp(s, "enum")) return TYPE;
    if (!j_strcmp(s, "union")) return TYPE;
    return IDENTIFIER;
}

void get_token(void)
{
    char *p = this_token.string;

    /* skip spaces */
    while ((*p = getchar()) == ' ');

    if (isalnum(*p)) {
        while (isalnum(*++p = getchar()));
        ungetc(*p, stdin);
        *p = '\0';
        this_token.type = classify_string();
    }
    else if ('*' == *p) {
        j_strcpy(this_token.string, "pointer to");
        this_token.type = '*';
    }
    else {
        this_token.string[1] = '\0';
        this_token.type = *p;
    }

    return;
}

void read_to_first_identifier(void) {
    get_token();
    while(IDENTIFIER != this_token.type) {
        PUSH(this_token);
        get_token();
    }

    printf("%s is ", this_token.string);
    get_token();
}

/* deal with arg of function */
void deal_with_function_args(void)
{
    while (')' != this_token.type)
        get_token();
    get_token();
    printf("function returning ");
}

/* deal with array */
void deal_with_arrays(void)
{
    while ('[' == this_token.type) {
        printf("array ");
        get_token();
        if (isdigit(this_token.string[0])) {
            printf("0..%d ", atoi(this_token.string));
            get_token(); /* read ']' */
        }

        get_token();
        printf("of ");
    }
}

/* deal with pointer */
void deal_with_pointers(void)
{
    while ('*' == stack[top].type)
        printf("%s ", POP.string);
}

/* deal with declarator */
void deal_with_declarator(void)
{
    /* deal with array/function */
    switch(this_token.type) {
        case '[': /* array */
            deal_with_arrays();
            break;
        case '(': /* function */
            deal_with_function_args();
            break;
        default:
            break;
    }

    deal_with_pointers;

    /* deal with stack before identifier */
    while (0 <= top) {
        if ('(' == stack[top].type) {
            POP;
            get_token();
            deal_with_declarator();
        }
        else
            printf("%s ", POP.string);
    }
}

int main(void)
{
    /* push the tokens into stack until identifier */
    read_to_first_identifier();
    deal_with_declarator();
    printf("\n");
    return 0;
}
