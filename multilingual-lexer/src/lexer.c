#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "keyword_map.h"

Token next_token(FILE *src, const KeywordEntry *keywords) {
    Token tok = {TOK_UNKNOWN, "", 0, 0};
    int c = fgetc(src);

    if (c == EOF) return tok;

    if (isalpha(c) || (c & 0x80)) {
        int i = 0;
        tok.lexeme[i++] = c;
        while ((c = fgetc(src)) != EOF &&
               (isalnum(c) || (c & 0x80))) {
            tok.lexeme[i++] = c;
        }
        tok.lexeme[i] = '\0';
        ungetc(c, src);
        tok.type = map_keyword(tok.lexeme, keywords);
        return tok;
    }

    if (isdigit(c)) {
        tok.type = TOK_NUMBER;
        tok.lexeme[0] = c;
        tok.lexeme[1] = '\0';
        return tok;
    }

    tok.type = TOK_SYMBOL;
    tok.lexeme[0] = c;
    tok.lexeme[1] = '\0';
    return tok;
}
