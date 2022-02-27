#include "include/klin.h"
#include "include/io.h"

void print_root(AbstractTree* root) {
    print_ast(root, 0);
    for(int i = 0; i < root->children->size; i++) {
        AbstractTree* child_ast = (AbstractTree*) root->children->items[i];
        print_ast(child_ast, 0);
        if(child_ast->type == AST_FUNCTION) {
            print_root(child_ast->value);
        }
    }
}

void kln_compile(char* src) {
    Lexer* lexer = create_lexer(src);
    Parser* parser = create_parser(lexer);
    AbstractTree* root = prsr_parse(parser);

    printf("\n");
    print_root(root);
    printf("\n");

    char* s = as_f_root(root);
    printf("``\n%s\n``\n", s);
}

void kln_compile_file(const char* filename) {
    char* src = read_file(filename);
    kln_compile(src);
    free(src);
}