#include "include/token.h"
#include <stdlib.h>
#include <string.h>

Token* create_token(char* value, int type) {
    Token* token = calloc(1, sizeof(struct TOKEN));
    token->value = value;
    token->type = type;

    return token;
}

char* token_type_to_str(int type) {
    switch (type) {
    case TOKT_IDENTIFIER:
        return "IDENTIFER";
    case TOKT_EQUALS:
        return "EQUALS";
    case TOKT_LPAREN:
        return "LEFT_PARENTHESIS";
    case TOKT_RPAREN:
        return "RIGHT_PARENTHESIS";
    case TOKT_LBRACE:
        return "LEFT_BRACE";
    case TOKT_RBRACE:
        return "RIGHT_BRACE";
    case TOKT_COLON:
        return "COLON";
    case TOKT_COMMA:
        return "COMMA";
    case TOKT_LT:
        return "LESS_ARROW";
    case TOKT_GT:
        return "GREATER_ARROW";
    case TOKT_INT:
        return "INT";
    case TOKT_SEMI:
        return "SEMICOLON";
    case TOKT_PLUS:
        return "PLUS";
    case TOKT_MINUS:
        return "MINUS";
    case TOKT_STAR:
        return "STAR";
    case TOKT_SLASH:
        return "SLASH";
    case TOKT_EOFL:
        return "END_OF_FILE";
    default:
        break;
    }

    return "???";
}

char* token_to_str(Token* token) {
    const char* type_str = token_type_to_str(token->type);
    const char* template = "[type=\"%s\", int_type=%d, value=\"%s\"]";

    char* str = calloc(strlen(type_str) + strlen(template) + 8, sizeof(char));
    sprintf(str, template, type_str, token->type, token->value);

    return str;
}