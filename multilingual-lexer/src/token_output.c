#include <stdio.h>
#include "token_output.h"

void emit_token(Token t) {
    printf("<%d, %s>\n", t.type, t.lexeme);
}
