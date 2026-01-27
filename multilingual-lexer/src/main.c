#include <stdio.h>
#include "input_handler.h"
#include "lang_config.h"
#include "lexer.h"
#include "token_output.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: mlexer <lang> <file>\n");
        return 1;
    }

    //check
    printf("#include <stdio.h>\n");

    FILE *src = open_source(argv[2]);
    const KeywordEntry *keywords = load_language(argv[1]);

    Token t;
    while ((t = next_token(src, keywords)).type != TOK_UNKNOWN) {
        emit_token(t);
    }

    fclose(src);
    return 0;
}
