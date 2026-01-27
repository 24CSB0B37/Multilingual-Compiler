#ifndef LANG_CONFIG_H
#define LANG_CONFIG_H

typedef struct {
    const char *localized;
    const char *canonical;
} KeywordEntry;

const KeywordEntry* load_language(const char *lang);

#endif
