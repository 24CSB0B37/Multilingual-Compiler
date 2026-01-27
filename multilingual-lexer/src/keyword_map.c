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
            if (strcmp(table[i].canonical, "int") == 0) return TOK_INT;
            if (strcmp(table[i].canonical, "float") == 0) return TOK_FLOAT;
            if (strcmp(table[i].canonical, "printf") == 0) return TOK_PRINTF;
        }
    }
    return TOK_IDENTIFIER;
}
