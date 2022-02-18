#include "include/lexer.h"
#include "include/utils.h"
#include <string.h>
#include <ctype.h>

Lexer* create_lexer(char* src) {
    Lexer* lexer = calloc(1, sizeof(struct LEXER));
    lexer->src = src;
    lexer->src_size = strlen(src);
    lexer->i = 0;
    lexer->curr_c = src[lexer->i];

    return lexer;
}

void lxr_advance(Lexer* lexer) {
    if(lexer->i < lexer->src_size && lexer->curr_c != '0') {
        lexer->i += 1;
        lexer->curr_c = lexer->src[lexer->i];
    }
}
char lxr_peek(Lexer* lexer, int offset) {
    return lexer->src[MIN(lexer->i + offset, lexer->src_size)];
}
void lxr_skip_whitespace(Lexer* lexer) {
    while(lexer->curr_c == 13 || lexer->curr_c == 10 || lexer->curr_c == ' ' || lexer->curr_c == '\t') {
        lxr_advance(lexer);
    }
}

Token* lxr_advance_with(Lexer* lexer, Token* token) {
    lxr_advance(lexer);
    return token;
}
Token* lxr_advance_current(Lexer* lexer, int type) {
    char* value = calloc(2, sizeof(char));
    value[0] = lexer->curr_c;
    value[1] = '\0';

    Token* token = create_token(value, type);
    lxr_advance(lexer);
    return token;
}

Token* lxr_parse_id(Lexer* lexer) {
    char* value = calloc(1, sizeof(char));
    while(isalpha(lexer->curr_c)) {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]) {lexer->curr_c, 0});
        lxr_advance(lexer);
    }

    return create_token(value, TOKT_IDENTIFIER);
}
Token* lxr_parse_number(Lexer* lexer) {
    char* value = calloc(1, sizeof(char));

    while(isdigit(lexer->curr_c) || lexer->curr_c == '0') {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]) {lexer->curr_c, 0});
        lxr_advance(lexer);
    }

    return create_token(value, TOKT_INT);
}

Token* lxr_next_token(Lexer* lexer) {
    while (lexer->curr_c != '\0') {
        lxr_skip_whitespace(lexer);

        if(isalpha(lexer->curr_c)) // Check if character is alphanumeric
            return lxr_parse_id(lexer); // Parse identifier
        if(isdigit(lexer->curr_c) || lexer->curr_c == '0')
            return lxr_parse_number(lexer);
            
        switch (lexer->curr_c) {
            case '=': return lxr_advance_current(lexer, TOKT_EQUALS);
            case '(': return lxr_advance_current(lexer, TOKT_LPAREN);
            case ')': return lxr_advance_current(lexer, TOKT_RPAREN);
            case '{': return lxr_advance_current(lexer, TOKT_LBRACE);
            case '}': return lxr_advance_current(lexer, TOKT_RBRACE);
            case ':': return lxr_advance_current(lexer, TOKT_COLON);
            case ',': return lxr_advance_current(lexer, TOKT_COMMA);
            case '<': return lxr_advance_current(lexer, TOKT_LT);
            case '>': return lxr_advance_current(lexer, TOKT_GT);
            case ';': return lxr_advance_current(lexer, TOKT_SEMI);
            case '+': return lxr_advance_current(lexer, TOKT_PLUS);
            case '-': return lxr_advance_current(lexer, TOKT_MINUS);
            case '*': return lxr_advance_current(lexer, TOKT_STAR);
            case '/': return lxr_advance_current(lexer, TOKT_SLASH);
            case '\0': break;
            default: printf("[Lexer]: Unexpected character '%c'.\n", lexer->curr_c); exit(1); break;
        }
    }

    return create_token(0, TOKT_EOFL);
}