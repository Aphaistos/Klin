#include "include/klin.h"
#include "include/io.h"

void kln_compile(char* src) {
    Lexer* lexer = create_lexer(src);
    Parser* parser = create_parser(lexer);
    AbstractTree* root = prsr_parse(parser);

    char* s = as_f(root);

    printf("%s\n", s);
}

void kln_compile_file(const char* filename) {
    char* src = read_file(filename);
    kln_compile(src);
    free(src);
}