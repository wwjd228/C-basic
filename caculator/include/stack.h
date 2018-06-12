// the initial value extern(global) and static variable is 0.
#define MAX_DIGITAL 8
#define MAX_SIZE 72
struct stack {
    char element[MAX_DIGITAL][MAX_SIZE];
    int top;
};

char *pop(struct stack *s, int *top);
void push(struct stack *s, char *element, int *top);
void print_stack(struct stack s);
