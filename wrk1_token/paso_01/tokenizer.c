
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN 256

void print_token(const char *token) {
    if (strlen(token) > 0) {
        printf("[TOKEN] %s\n", token);
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;
    char ch, token[MAX_TOKEN];
    int i = 0;

    if (argc < 2) {
        printf("Uso: %s archivo.f\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (!fp) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (isalnum(ch) || ch == '_') {
            token[i++] = ch;
            if (i >= MAX_TOKEN - 1) i = 0; // prevenir overflow
        } else {
            token[i] = '\0';
            print_token(token);
            i = 0;
            // también imprimimos símbolos individuales relevantes
            if (!isspace(ch)) {
                printf("[SIMBOLO] %c\n", ch);
            }
        }
    }

    token[i] = '\0';
    print_token(token); // último token si hay

    fclose(fp);
    return 0;
}
