#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nlp_assist.h"

static void escape_json(const char *in, char *out, size_t out_size) {
    size_t oi = 0;
    for (size_t i = 0; in[i] && oi + 1 < out_size; i++) {
        char c = in[i];
        if (c == '\\' && oi + 2 < out_size) {
            out[oi++] = '\\';
            out[oi++] = '\\';
        } else if (c == '"' && oi + 2 < out_size) {
            out[oi++] = '\\';
            out[oi++] = '"';
        } else if (c == '\n' && oi + 2 < out_size) {
            out[oi++] = '\\';
            out[oi++] = 'n';
        } else if (c == '\r' && oi + 2 < out_size) {
            out[oi++] = '\\';
            out[oi++] = 'r';
        } else if (c == '\t' && oi + 2 < out_size) {
            out[oi++] = '\\';
            out[oi++] = 't';
        } else {
            out[oi++] = c;
        }
    }
    out[oi] = '\0';
}

static char *load_groq_api_key(void) {
    char *key = getenv("GROQ_API_KEY");
    if (key && key[0] != '\0') {
        return strdup(key);
    }

    FILE *f = fopen(".env", "r");
    if (f) {
        char line[512];
        while (fgets(line, sizeof(line), f)) {
            if (strncmp(line, "GROQ_API_KEY=", 13) == 0) {
                size_t len = strlen(line);
                while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r')) len--;
                char *val = malloc(len - 12);
                if (val) {
                    strncpy(val, line + 13, len - 13);
                    val[len - 13] = '\0';
                }
                fclose(f);
                return val;
            }
        }
        fclose(f);
    }

    // Prompt user to set up API key if it was not found in env or .env.
    printf("GROQ_API_KEY not found in environment or .env. Enter API key (or leave empty to cancel): ");
    char user_key[256];
    if (!fgets(user_key, sizeof(user_key), stdin)) {
        return NULL;
    }
    size_t l = strlen(user_key);
    while (l > 0 && (user_key[l-1] == '\n' || user_key[l-1] == '\r')) {
        user_key[--l] = '\0';
    }
    if (l == 0) return NULL;

    char *val = strdup(user_key);
    FILE *out = fopen(".env", "a");
    if (out) {
        fprintf(out, "GROQ_API_KEY=%s\n", val);
        fclose(out);
        printf("Saved GROQ_API_KEY to .env\n");
    }
    return val;
}

static char *call_groq_api(const char *payload, const char *api_key) {
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), "curl -s -X POST https://api.groq.com/openai/v1/chat/completions -H 'Authorization: Bearer %s' -H 'Content-Type: application/json' -d '%s'", api_key, payload);
    FILE *pipe = popen(cmd, "r");
    if (!pipe) return NULL;
    char *output = malloc(32768);
    if (!output) { pclose(pipe); return NULL; }
    size_t used = 0;
    while (fgets(output + used, 32768 - used, pipe)) {
        used = strlen(output);
        if (used + 512 >= 32768) break;
    }
    pclose(pipe);
    return output;
}

static char *extract_text_output(const char *raw) {
    const char *pos = strstr(raw, "\"content\"");
    if (!pos) return NULL;
    pos = strchr(pos, ':');
    if (!pos) return NULL;
    pos++;
    while (*pos == ' ' || *pos == '\n' || *pos == '\t' || *pos == '"') pos++;
    const char *end = strchr(pos, '"');
    if (!end) return NULL;
    size_t len = end - pos;
    char *out = malloc(len + 1);
    if (!out) return NULL;
    strncpy(out, pos, len);
    out[len] = '\0';
    return out;
}

void analyze_ambiguity(const char *lexeme) {
    printf("[NLP Advisory] Ambiguous token: %s\n", lexeme);
}

void maybe_query_ai(const char *source_code, const char *unknown_word) {
    char answer = 'n';
    printf("Unknown word '%s' detected. Send code+word to Groq AI? [y/N]: ", unknown_word);
    if (scanf(" %c", &answer) != 1) return;
    if (answer != 'y' && answer != 'Y') return;

    char *api_key = load_groq_api_key();
    if (!api_key) {
        printf("[AI] API key not found in GROQ_API_KEY or .env!\n");
        return;
    }

    char escaped_source[16384];
    char escaped_word[512];
    escape_json(source_code, escaped_source, sizeof(escaped_source));
    escape_json(unknown_word, escaped_word, sizeof(escaped_word));

    char payload[32768];
    snprintf(payload, sizeof(payload), "{\"model\":\"llama-3.1-8b-instant\",\"messages\":[{\"role\":\"system\",\"content\":\"You are a C lexer translator assistant. Return a short replacement for the unknown word.\"},{\"role\":\"user\",\"content\":\"Code: %s\\nUnknown word: %s\"}],\"max_tokens\":256}", escaped_source, escaped_word);

    char *response = call_groq_api(payload, api_key);
    free(api_key);

    if (!response) {
        printf("[AI] API request failed.\n");
        return;
    }

    char *decoded = extract_text_output(response);
    if (decoded) {
        printf("[AI] response: %s\n", decoded);
        free(decoded);
    } else {
        printf("[AI] could not parse response; raw: %s\n", response);
    }

    free(response);
}

char *ai_fix_code(const char *source_code, const char *unknown_words) {
    char *api_key = load_groq_api_key();
    if (!api_key) {
        printf("[AI] API key not found in GROQ_API_KEY or .env!\n");
        return NULL;
    }

    char escaped_source[16384];
    char escaped_unknown[1024];
    escape_json(source_code, escaped_source, sizeof(escaped_source));
    escape_json(unknown_words, escaped_unknown, sizeof(escaped_unknown));

    char prompt[32768];
    snprintf(prompt, sizeof(prompt), "{\"model\":\"llama-3.1-8b-instant\",\"messages\":[{\"role\":\"system\",\"content\":\"For each localized token, if it appears to be a user-defined variable or function name, output the token unchanged. Otherwise, output the canonical C keyword replacement. Respond with the outputs separated by spaces.\"},{\"role\":\"user\",\"content\":\"Tokens: %s\"}],\"max_tokens\":512}", escaped_unknown);

    char *response = call_groq_api(prompt, api_key);
    free(api_key);

    if (!response) {
        printf("[AI] API request failed during code fix.\n");
        return NULL;
    }

    char *decoded = extract_text_output(response);
    printf("DEBUG: decoded: %s\n", decoded ? decoded : "NULL");
    free(response);
    return decoded;
}
