#ifndef KLIN_PARSER_H
#define KLIN_PARSER_H
#include "lexer.h"
#include "ast.h"

typedef struct PARSER {
    Lexer* lexer;
    Token* token;
} Parser;

Parser* create_parser(Lexer* lexer);

Token* prsr_eat(Parser* parser, int type);

AbstractTree* prsr_parse(Parser* parser);
AbstractTree* prsr_parse_id(Parser* parser);
AbstractTree* prsr_parse_block(Parser* parser);
AbstractTree* prsr_parse_list(Parser* parser);
AbstractTree* prsr_parse_int(Parser* parser);
AbstractTree* prsr_parse_expr(Parser* parser);
AbstractTree* prsr_parse_compound(Parser* parser);

#endif