#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOK_IF,
    TOK_ELSE,
    TOK_WHILE,
    TOK_FOR,
    TOK_RETURN,
    TOK_BREAK,
    TOK_CONTINUE,
    TOK_SWITCH,
    TOK_CASE,
    TOK_DEFAULT,
    TOK_ENUM,
    TOK_STRUCT,
    TOK_TYPEDEF,
    TOK_VOID,
    TOK_LONG,
    TOK_SHORT,
    TOK_UNSIGNED,
    TOK_SIGNED,
    TOK_CONST,
    TOK_STATIC,
    TOK_INT,
    TOK_FLOAT,
    TOK_CHAR,
    TOK_DOUBLE,
    TOK_STRING,
    TOK_SCANF,
    TOK_COUT,
    TOK_PRINTF,
    TOK_IDENTIFIER,
    TOK_NUMBER,
    TOK_SYMBOL,
    TOK_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[128];
    int line;
    int column;
} Token;

#endif
