#include "lang_config.h"
#include <string.h>
#include <stddef.h>

/* Japanese → C keywords */
static KeywordEntry jp_keywords[] = {
    {"もし", "if"},
    {"ならば", "else"},
    {"間", "while"},
    {"繰返す", "for"},
    {"戻る", "return"},
    {"整数", "int"},
    {"浮動", "float"},
    {"表示", "printf"},
    {NULL, NULL}
};

const KeywordEntry* load_language(const char *lang) {
    if (lang && strcmp(lang, "jp") == 0)
        return jp_keywords;
    return NULL;
}
