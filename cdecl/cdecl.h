#define MAX_TOKEN_LEN 100
#define MAX_TOKENS 64

typedef struct token {
    char type;
    char string[MAX_TOKEN_LEN];
} token_t;

typedef enum token_type {
    TYPE = 0,
    QUALIFIER,
    IDENTIFIER
} token_type_t;


/* save previous tokens */
token_t stack[MAX_TOKENS];

/* save current token */
token_t this_token;

token_type_t classify_string(void);
void get_token(void);
void read_to_first_identifier(void);

/* deal with arg of function */
void deal_with_function_args(void);

/* deal with array */
void deal_with_arrays(void);

/* deal with pointer */
void deal_with_pointers(void);

/* deal with declarator */
void deal_with_declarator(void);
