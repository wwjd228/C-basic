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

/* status "initialize": read to first indentifier */
void initialize(void);

/* status "get_lparen": deal with '(' */
void get_lparen(void);

/* status "get_param": deal with arg of function */
void get_param(void);

/* status "get_array" deal with array */
void get_array(void);

/* status "get_ptr_part": deal with pointer */
void get_ptr_part(void);

/* status "get_type": deal with the token in stack */
void get_type(void);
