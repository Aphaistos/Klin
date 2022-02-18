#ifndef KLIN_LEXER_H
#define KLIN_LEXER_H
#include "token.h"


typedef struct LEXER {
    char* src;
    size_t src_size;
    char curr_c;
    unsigned int position;
} Lexer;

Lexer* create_lexer(char* src);

void lxr_advance(Lexer* lexer);
char lxr_peek(Lexer*, int offset);
void lxr_skip_whitespace(Lexer* lexer);

Token* lxr_advance_with(Lexer*, Token* token);
Token* lxr_advance_current(Lexer*, int type);

Token* lxr_parse_id(Lexer* lexer);
Token* lxr_parse_number(Lexer* lexer);

Token* lxr_next_token(Lexer* lexer);

#endif