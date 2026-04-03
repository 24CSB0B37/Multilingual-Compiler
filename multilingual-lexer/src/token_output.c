#include <stdio.h>
#include "token_output.h"

//void emit_token(Token t) {
//    printf("<%d, %s>\n", t.type, t.lexeme);
//}
const char *token_to_string(TokenType t) {
    switch (t) {
        case TOK_IF:       return "if";
        case TOK_ELSE:     return "else";
        case TOK_WHILE:    return "while";
        case TOK_FOR:      return "for";
        case TOK_RETURN:   return "return";
        case TOK_BREAK:    return "break";
        case TOK_CONTINUE: return "continue";
        case TOK_SWITCH:   return "switch";
        case TOK_CASE:     return "case";
        case TOK_DEFAULT:  return "default";
        case TOK_ENUM:     return "enum";
        case TOK_STRUCT:   return "struct";
        case TOK_TYPEDEF:  return "typedef";
        case TOK_VOID:     return "void";
        case TOK_LONG:     return "long";
        case TOK_SHORT:    return "short";
        case TOK_UNSIGNED: return "unsigned";
        case TOK_SIGNED:   return "signed";
        case TOK_CONST:    return "const";
        case TOK_STATIC:   return "static";
        case TOK_INT:      return "int";
        case TOK_FLOAT:    return "float";
        case TOK_CHAR:     return "char";
        case TOK_DOUBLE:   return "double";
        case TOK_STRING:   return "string";
        case TOK_SCANF:    return "scanf";
        case TOK_COUT:     return "cout";
        case TOK_PRINTF:   return "printf";
        default:          return NULL;
    }
}

void emit_token(Token t) {
    const char *s = token_to_string(t.type);
    if (s) {
        printf("%s", s);
    } else {
        printf("%s", t.lexeme);
    }
}
