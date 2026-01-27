#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"
#include "lang_config.h"

Token next_token(FILE *src, const KeywordEntry *keywords);

#endif
