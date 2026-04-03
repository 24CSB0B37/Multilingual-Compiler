#ifndef NLP_ASSIST_H
#define NLP_ASSIST_H

void analyze_ambiguity(const char *lexeme);
void maybe_query_ai(const char *source_code, const char *unknown_word);
char *ai_fix_code(const char *source_code, const char *unknown_words);

#endif
