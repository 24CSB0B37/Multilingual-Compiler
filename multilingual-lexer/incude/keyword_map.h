#ifndef KEYWORD_MAP_H
#define KEYWORD_MAP_H

#include "token.h"
#include "lang_config.h"

TokenType map_keyword(const char *lexeme, const KeywordEntry *table);

#endif
