#include <stdio.h>
#include "token_output.h"

//void emit_token(Token t) {
//    printf("<%d, %s>\n", t.type, t.lexeme);
//}
void emit_token(Token t) {
    switch (t.type) {
        case TOK_IF:       printf("if"); break;
        case TOK_ELSE:     printf("else"); break;
        case TOK_WHILE:    printf("while"); break;
        case TOK_FOR:      printf("for"); break;
        case TOK_RETURN:   printf("return"); break;
        case TOK_INT:      printf("int"); break;
        case TOK_FLOAT:    printf("float"); break;
        case TOK_PRINTF:   printf("printf"); break; 
        default:
            printf("%s", t.lexeme);
    }
}
