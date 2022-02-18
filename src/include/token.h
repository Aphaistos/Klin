#ifndef KLIN_TOKEN_H
#define KLIN_TOKEN_H
#include <stdlib.h>
#include <stdio.h>

typedef struct TOKEN {
    char* value;
    enum TOKEN_TYPE {
        TOKT_IDENTIFIER,
        TOKT_EQUALS,
        TOKT_LPAREN,
        TOKT_RPAREN,
        TOKT_LBRACE,
        TOKT_RBRACE,
        TOKT_COLON,
        TOKT_COMMA,
        TOKT_LT,
        TOKT_GT,
        TOKT_INT,
        TOKT_SEMI,
        TOKT_PLUS,
        TOKT_MINUS,
        TOKT_STAR,
        TOKT_SLASH,
        TOKT_EOFL // End Of File ('\0') the character that is present at the end of a string
    } type;
} Token;

Token* create_token(char* value, int type);

char* token_type_to_str(int type);
char* token_to_str(Token*);

#endif