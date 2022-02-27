#include "include/parser.h"
#include "include/types.h"
#include <stdlib.h>
#include <string.h>

Parser* create_parser(Lexer* lexer) {
    Parser* parser = calloc(1, sizeof(struct PARSER));
    parser->lexer = lexer;
    parser->token = lxr_next_token(lexer);

    return parser;
}

Token* prsr_eat(Parser* parser, int type) {
    if(parser->token->type != type) {
        printf("[Parser]: Unexpected token: \"%s\", was expecting: \"%s\"\n", token_to_str(parser->token), token_type_to_str(type));
        exit(1);
    }

    parser->token = lxr_next_token(parser->lexer);
    return parser->token;
}

void print_ast(AbstractTree* ast, int isList) {
    switch (ast->type) {
    case AST_COMPOUND:
        printf((isList == 0) ? "Compound\n" : "List\n");
        break;
    case AST_FUNCTION:
        printf("Function(Name=%s,DataType=%d)\n", ast->name, ast->dtype);
        break;
    case AST_CALL:
        printf("Call(Name=%s)\n", ast->name);
        break;
    case AST_ASSIGNMENT:
        printf("Assignment(Name=%s)\n", ast->name);
        break;
    case AST_DEFINITION_TYPE:
        printf("DefinitionType\n");
        break;
    case AST_VARIABLE:
        printf("Variable(Name=%s,DataType=%d)\n", ast->name, ast->dtype);
        break;
    case AST_INT:
        printf("Integer(IntValue=%d)\n", ast->int_value);
        break;
    case AST_BINOP:
        printf("BinaryOperation\n");
        break;
    case AST_NOOP:
        printf("NoOperation\n");
        break;
    }
}

AbstractTree* prsr_parse(Parser* parser) {
    return prsr_parse_compound(parser);
}
AbstractTree* prsr_parse_id(Parser* parser) {
    char* value = calloc(strlen(parser->token->value) + 1, sizeof(char));
    strcpy(value, parser->token->value);
    prsr_eat(parser, TOKT_IDENTIFIER);
    
    AbstractTree* ast = create_ast(AST_VARIABLE);
    ast->name = value;

    if(parser->token->type == TOKT_LT) {
        prsr_eat(parser, TOKT_LT);
        strcat(value, parser->token->value);
        prsr_eat(parser, TOKT_IDENTIFIER);
        prsr_eat(parser, TOKT_GT);
    }
    if(parser->token->type == TOKT_IDENTIFIER) {
        ast->name = parser->token->value;
        ast->dtype += typename_to_int(value);
        prsr_eat(parser, TOKT_IDENTIFIER);

        if(parser->token->type == TOKT_EQUALS) {
            printf("%s %s\n", value, ast->name);
            prsr_eat(parser, TOKT_EQUALS);
            AbstractTree* assignment = create_ast(AST_ASSIGNMENT); 
            assignment->name = ast->name;
            assignment->value = prsr_parse_expr(parser);
            print_ast(assignment, 0);
            return assignment;
        }
        if(parser->token->type == TOKT_LPAREN) {
            AbstractTree* function = create_ast(AST_FUNCTION); 
            function->name = ast->name;
            function->dtype = ast->dtype;
            print_ast(function, 0);
            prsr_parse_list(parser);
            function->value = prsr_parse_compound(parser);
            return function;
        }
        print_ast(ast, 0);
    } 
    if(parser->token->type == TOKT_LPAREN) {
        ast->type = AST_CALL;
        print_ast(ast, 0);
        ast->value = prsr_parse_list(parser);
        return ast;
    }

    return ast;
}
AbstractTree* prsr_parse_block(Parser* parser) {
    prsr_eat(parser, TOKT_LBRACE);
    AbstractTree* ast = create_ast(AST_COMPOUND);

    while(parser->token->type != TOKT_RBRACE) {
        list_push(ast->children, prsr_parse_expr(parser));
    }

    prsr_eat(parser, TOKT_RBRACE);

    print_ast(ast, 0);
    return ast;
}
AbstractTree* prsr_parse_list(Parser* parser) {
    prsr_eat(parser, TOKT_LPAREN);

    AbstractTree* ast = create_ast(AST_COMPOUND);
    print_ast(ast, 1);

    if(parser->token->type == TOKT_RPAREN) {
        prsr_eat(parser, TOKT_RPAREN);
    }
    list_push(ast->children, prsr_parse_expr(parser));

    while(parser->token->type == TOKT_COMMA) {
        prsr_eat(parser, TOKT_COMMA);
        list_push(ast->children, prsr_parse_expr(parser));
    }
    
    prsr_eat(parser, TOKT_RPAREN);
    return ast;
}
AbstractTree* prsr_parse_int(Parser* parser) {
    int int_value = atoi(parser->token->value);
    prsr_eat(parser, TOKT_INT);

    AbstractTree* ast = create_ast(AST_INT);
    ast->int_value = int_value;

    print_ast(ast, 0);
    return ast;
}
AbstractTree* prsr_parse_expr(Parser* parser) {
    switch(parser->token->type) {
        case TOKT_IDENTIFIER: return prsr_parse_id(parser);
        case TOKT_LPAREN: return prsr_parse_list(parser);
        case TOKT_INT: return prsr_parse_int(parser);
        default: { printf("[Parser]: Unexpected token \"%s\"\n", token_to_str(parser->token)); exit(1); break; }
    }
}
AbstractTree* prsr_parse_compound(Parser* parser) {
    unsigned int should_close = 0;
    if(parser->token->type == TOKT_LBRACE) {
        prsr_eat(parser, TOKT_LBRACE);
        should_close = 1;
    }
    AbstractTree* compound = create_ast(AST_COMPOUND);
    print_ast(compound, 0);

    while(parser->token->type != TOKT_EOFL && parser->token->type != TOKT_RBRACE) {
        list_push(compound->children, prsr_parse_expr(parser));

        if(parser->token->type == TOKT_SEMI) {
            prsr_eat(parser, TOKT_SEMI);
        }
    }

    if(should_close)
        prsr_eat(parser, TOKT_RBRACE);

    return compound;
}