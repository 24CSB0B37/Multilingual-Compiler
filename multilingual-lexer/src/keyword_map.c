#include <string.h>
#include "keyword_map.h"

TokenType map_keyword(const char *lexeme, const KeywordEntry *table) {
    for (int i = 0; table && table[i].localized; i++) {
        if (strcmp(lexeme, table[i].localized) == 0) {
            if (strcmp(table[i].canonical, "if") == 0) return TOK_IF;
            if (strcmp(table[i].canonical, "else") == 0) return TOK_ELSE;
            if (strcmp(table[i].canonical, "while") == 0) return TOK_WHILE;
            if (strcmp(table[i].canonical, "for") == 0) return TOK_FOR;
            if (strcmp(table[i].canonical, "return") == 0) return TOK_RETURN;
            if (strcmp(table[i].canonical, "break") == 0) return TOK_BREAK;
            if (strcmp(table[i].canonical, "continue") == 0) return TOK_CONTINUE;
            if (strcmp(table[i].canonical, "switch") == 0) return TOK_SWITCH;
            if (strcmp(table[i].canonical, "case") == 0) return TOK_CASE;
            if (strcmp(table[i].canonical, "default") == 0) return TOK_DEFAULT;
            if (strcmp(table[i].canonical, "enum") == 0) return TOK_ENUM;
            if (strcmp(table[i].canonical, "struct") == 0) return TOK_STRUCT;
            if (strcmp(table[i].canonical, "typedef") == 0) return TOK_TYPEDEF;
            if (strcmp(table[i].canonical, "void") == 0) return TOK_VOID;
            if (strcmp(table[i].canonical, "long") == 0) return TOK_LONG;
            if (strcmp(table[i].canonical, "short") == 0) return TOK_SHORT;
            if (strcmp(table[i].canonical, "unsigned") == 0) return TOK_UNSIGNED;
            if (strcmp(table[i].canonical, "signed") == 0) return TOK_SIGNED;
            if (strcmp(table[i].canonical, "const") == 0) return TOK_CONST;
            if (strcmp(table[i].canonical, "static") == 0) return TOK_STATIC;
            if (strcmp(table[i].canonical, "int") == 0) return TOK_INT;
            if (strcmp(table[i].canonical, "float") == 0) return TOK_FLOAT;
            if (strcmp(table[i].canonical, "char") == 0) return TOK_CHAR;
            if (strcmp(table[i].canonical, "double") == 0) return TOK_DOUBLE;
            if (strcmp(table[i].canonical, "string") == 0) return TOK_STRING;
            if (strcmp(table[i].canonical, "scanf") == 0) return TOK_SCANF;
            if (strcmp(table[i].canonical, "cout") == 0) return TOK_COUT;
            if (strcmp(table[i].canonical, "printf") == 0) return TOK_PRINTF;
        }
    }
    return TOK_IDENTIFIER;
}
