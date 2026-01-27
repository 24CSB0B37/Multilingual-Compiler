#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOK_IF,
    TOK_ELSE,
    TOK_WHILE,
    TOK_FOR,
    TOK_RETURN,
    TOK_INT,
    TOK_FLOAT,
    TOK_IDENTIFIER,
    TOK_NUMBER,
    TOK_SYMBOL,
    TOK_PRINTF,
    TOK_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[128];
    int line;
    int column;
} Token;

#endif
