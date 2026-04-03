#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lang_config.h"
#include "lexer.h"
#include "token_output.h"
#include "nlp_assist.h"

static char *read_file(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    size_t n = fread(buffer, 1, size, f);
    buffer[n] = '\0';
    fclose(f);
    return buffer;
}

static int contains_non_ascii(const char *s) {
    for (const unsigned char *p = (const unsigned char *)s; *p; p++) {
        if (*p > 127) return 1;
    }
    return 0;
}

static int append_text(char **buf, size_t *len, size_t *cap, const char *text) {
    size_t tlen = strlen(text);
    if (*len + tlen + 1 > *cap) {
        size_t new_cap = (*cap == 0 ? 4096 : *cap * 2);
        while (new_cap < *len + tlen + 1) new_cap *= 2;
        char *new_buf = realloc(*buf, new_cap);
        if (!new_buf) return 0;
        *buf = new_buf;
        *cap = new_cap;
    }
    memcpy(*buf + *len, text, tlen);
    *len += tlen;
    (*buf)[*len] = '\0';
    return 1;
}

static int add_unknown_token(char ***unknowns, int *count, int *cap, const char *token) {
    for (int i = 0; i < *count; i++) {
        if (strcmp((*unknowns)[i], token) == 0) return 1;
    }
    if (*count >= *cap) {
        int new_cap = (*cap == 0 ? 16 : *cap * 2);
        char **new_arr = realloc(*unknowns, new_cap * sizeof(char *));
        if (!new_arr) return 0;
        *unknowns = new_arr;
        *cap = new_cap;
    }
    (*unknowns)[*count] = strdup(token);
    if (!(*unknowns)[*count]) return 0;
    (*count)++;
    return 1;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: mlexer <lang> <file> [--ai]\n");
        return 1;
    }

    int ai_enabled = 0;
    if (argc >= 4 && strcmp(argv[3], "--ai") == 0) {
        ai_enabled = 1;
    }

    // Auto-add common runtime headers (including printf support).
    printf("#include <bits/stdc++.h>\n");

    char *source_code = read_file(argv[2]);
    if (!source_code) {
        fprintf(stderr, "Unable to open source file: %s\n", argv[2]);
        return 1;
    }

    FILE *src = fmemopen(source_code, strlen(source_code), "r");
    if (!src) {
        fprintf(stderr, "Unable to open in-memory source stream.\n");
        free(source_code);
        return 1;
    }

    const KeywordEntry *keywords = load_language(argv[1]);

    char *phase1 = NULL;
    size_t phase1_len = 0, phase1_cap = 0;
    char **unknowns = NULL;
    int unknown_count = 0, unknown_cap = 0;

    Token t;
    while ((t = next_token(src, keywords)).type != TOK_UNKNOWN) {
        const char *mapped = token_to_string(t.type);
        if (mapped) {
            append_text(&phase1, &phase1_len, &phase1_cap, mapped);
        } else {
            append_text(&phase1, &phase1_len, &phase1_cap, t.lexeme);
        }

        if (t.type == TOK_IDENTIFIER && contains_non_ascii(t.lexeme)) {
            add_unknown_token(&unknowns, &unknown_count, &unknown_cap, t.lexeme);
        }
    }

    fclose(src);

    const char *phase1_file = "phase1_output.c";
    FILE *f1 = fopen(phase1_file, "w");
    if (f1) {
        fprintf(f1, "#include <bits/stdc++.h>\n%s", phase1 ? phase1 : "");
        fclose(f1);
        printf("phase1 output written: %s\n", phase1_file);
    }

    printf("%s", phase1 ? phase1 : "");

    if (ai_enabled && unknown_count > 0) {
        char *unknown_buf = NULL;
        size_t unknown_buf_len = 0, unknown_buf_cap = 0;
        for (int i = 0; i < unknown_count; i++) {
            append_text(&unknown_buf, &unknown_buf_len, &unknown_buf_cap, unknowns[i]);
            if (i + 1 < unknown_count) {
                append_text(&unknown_buf, &unknown_buf_len, &unknown_buf_cap, ", ");
            }
        }

        char *ai_fix = ai_fix_code("", unknown_buf ? unknown_buf : "");
        if (ai_fix) {
            // Parse AI response as space-separated replacements
            char *replacements[16];
            int rep_count = 0;
            char *token = strtok(ai_fix, " \n\t");
            while (token && rep_count < unknown_count && rep_count < 16) {
                replacements[rep_count++] = token;
                token = strtok(NULL, " \n\t");
            }

            // Replace unknowns in phase1 with replacements
            char *final_code = strdup(phase1 ? phase1 : "");
            for (int i = 0; i < unknown_count && i < rep_count; i++) {
                char *pos = strstr(final_code, unknowns[i]);
                if (pos) {
                    size_t len_old = strlen(unknowns[i]);
                    size_t len_new = strlen(replacements[i]);
                    memmove(pos + len_new, pos + len_old, strlen(pos + len_old) + 1);
                    memcpy(pos, replacements[i], len_new);
                }
            }

            const char *ai_file = "ai_fixed.c";
            FILE *f2 = fopen(ai_file, "w");
            if (f2) {
                fprintf(f2, "#include <bits/stdc++.h>\n%s", final_code ? final_code : "");
                fclose(f2);
                printf("AI fixed version written at %s\n", ai_file);

                char answer = 'n';
                printf("Use AI fixed file %s as final output? [y/N]: ", ai_file);
                if (scanf(" %c", &answer) == 1 && (answer == 'y' || answer == 'Y')) {
                    printf("%s", final_code ? final_code : "");
                }
            }
            free(final_code);
            free(ai_fix);
        }

        free(unknown_buf);
    }

    if (phase1) free(phase1);
    for (int i = 0; i < unknown_count; i++) free(unknowns[i]);
    free(unknowns);
    free(source_code);
    return 0;
}
