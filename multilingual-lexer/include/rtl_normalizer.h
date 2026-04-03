#ifndef RTL_NORMALIZER_H
#define RTL_NORMALIZER_H

void remove_bidi_controls(char *str);
int is_rtl_unicode(unsigned int codepoint);

#endif
