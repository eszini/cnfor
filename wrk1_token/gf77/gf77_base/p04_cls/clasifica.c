
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN 256
#define MAX_KEYWORDS 512

char *keywords[MAX_KEYWORDS];
int keyword_count = 0;

void load_keywords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("No se pudo abrir la lista de tokens");
        exit(1);
    }
    char buffer[MAX_TOKEN];
    while (fgets(buffer, sizeof(buffer), file)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        keywords[keyword_count++] = strdup(buffer);
    }
    fclose(file);
}

int is_keyword(const char *token) {
    for (int i = 0; i < keyword_count; i++) {
        if (strcasecmp(token, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

const char* classify_token(const char *token) {
    if (is_keyword(token)) return "KEYWORD";
    if (isalpha(token[0]) || token[0] == '_') return "IDENTIFIER";
    if (isdigit(token[0])) return "NUMBER";
    if (strlen(token) == 1 && strchr("+-=*/(),", token[0])) return "OPERATOR";
    return "UNKNOWN";
}

void print_token(FILE *out, const char *type, const char *token, int width) {
    fprintf(out, "%-16s |%-*s|\n", type, width, token);
}

int main(int argc, char *argv[]) {
    if (argc < 4 || strncmp(argv[3], "-ldt=", 5) != 0) {
        printf("Uso: %s fuente.f salida.txt -ldt=keywords.txt\n", argv[0]);
        return 1;
    }

    const char *input_file = argv[1];
    const char *output_file = argv[2];
    const char *keywords_file = argv[3] + 5;

    load_keywords(keywords_file);

    FILE *in = fopen(input_file, "r");
    FILE *out = fopen(output_file, "w");
    if (!in || !out) {
        perror("Error abriendo archivo");
        return 1;
    }

    char ch, token[MAX_TOKEN];
    int i = 0, maxlen = 0;
    char tokens[1000][MAX_TOKEN];
    int token_count = 0;

    while ((ch = fgetc(in)) != EOF) {
        if (isalnum(ch) || ch == '_') {
            token[i++] = ch;
            if (i >= MAX_TOKEN - 1) i = 0;
        } else {
            token[i] = '\0';
            if (i > 0) {
                strcpy(tokens[token_count++], token);
                int len = strlen(token);
                if (len > maxlen) maxlen = len;
            }
            i = 0;
            if (!isspace(ch)) {
                char symbol[2] = { ch, '\0' };
                strcpy(tokens[token_count++], symbol);
                if (maxlen < 1) maxlen = 1;
            }
        }
    }
    token[i] = '\0';
    if (i > 0) {
        strcpy(tokens[token_count++], token);
        int len = strlen(token);
        if (len > maxlen) maxlen = len;
    }

    for (int j = 0; j < token_count; j++) {
        const char *type = classify_token(tokens[j]);
        print_token(out, type, tokens[j], maxlen);
    }

    fclose(in);
    fclose(out);
    return 0;
}
