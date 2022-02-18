#include "include/klin.h"
#include "include/io.h"

void kln_compile(char* src) {
    Lexer* lexer = create_lexer(src);
    Parser* parser = create_parser(lexer);
    AbstractTree* root = prsr_parse(parser);
    
    
    Token* token = 0;
    unsigned int index = 0;

    while((token = lxr_next_token(lexer))->type != TOKT_EOFL) {
        printf("token(%d): %s\n", index, token_to_str(token));
        index++;
    }
}

void kln_compile_file(const char* filename) {
    char* src = read_file(filename);
    kln_compile(src);
    free(src);
}