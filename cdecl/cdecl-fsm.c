#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "cdecl-fsm.h"
#include "j_string.h"

static void (*next_status)(void);

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

/* status "initialize": read to first indentifier */
void initialize(void)
{
    get_token();
    while (IDENTIFIER != this_token.type) {
        PUSH(this_token);
        get_token();
    }

    printf("%s is ", this_token.string);
    get_token();
    next_status = get_array;
}

/* status "get_lparen": deal with '(' */
void get_lparen(void)
{
    next_status = get_ptr_part;
    if (0 <= top) {
        if ('(' == stack[top].type) {
            POP;
            get_token();
            next_status = get_array;
        }
    }
}

/* status "get_param": deal with arg of function */
void get_param(void)
{
    next_status = get_lparen;
    if ('(' == this_token.type) {
        while (')' != this_token.type) get_token();
        get_token();
        printf("function returning ");
    }
}

/* status "get_array" deal with array */
void get_array(void)
{
    next_status = get_param;
    while ('[' == this_token.type) {
        printf("array ");
        get_token();
        if (isdigit(this_token.string[0])) {
            printf("0...%d ", atoi(this_token.string) - 1);
            get_token(); /* read ']' */
        }

        get_token();
        printf("of ");
        next_status = get_lparen;
    }
}

/* status "get_ptr_part": deal with pointer */
void get_ptr_part(void)
{
    next_status = get_type;
    if ('*' == stack[top].type) {
        printf("pointer to");
        POP;
        next_status = get_lparen;
    }
    else if (QUALIFIER == stack[top].type) {
        printf("%s ", POP.string);
        next_status = get_lparen;
    }
}

/* status "get_type": deal with the token in stack */
void get_type(void)
{
    next_status = NULL;
    while (0 <= top) printf("%s ", POP.string);
    printf("\n");
}

int main(void)
{
    next_status = initialize;

    while (NULL != next_status) next_status();
    return 0;
}
