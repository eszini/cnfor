
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE 1024
#define MAX_TOKEN 256
#define MAX_KEYWORDS 128

const char *keywords[] = {
    "PROGRAM", "SUBROUTINE", "FUNCTION", "END", "STOP", "RETURN", "CALL", "COMMON",
    "DATA", "DIMENSION", "IMPLICIT", "CONTINUE", "GOTO", "IF", "THEN", "ELSE", "ENDIF",
    "DO", "READ", "WRITE", "FORMAT", "PAUSE", "SAVE", "EQUIVALENCE", "ENTRY", "INTEGER",
    "REAL", "LOGICAL", "CHARACTER", "COMPLEX", "INCLUDE", "PARAMETER",
    "MODULE", "USE", "INTERFACE", "CONTAINS", "ALLOCATABLE", "ALLOCATE", "DEALLOCATE",
    "CASE", "SELECT", "CYCLE", "EXIT", "INTENT", "OPTIONAL", "PRIVATE", "PUBLIC",
    "RECURSIVE", "RESULT", "KIND", "ENDDO", "END IF", "END PROGRAM", "END SUBROUTINE",
    "END FUNCTION", "END MODULE"
};

int keyword_count = sizeof(keywords) / sizeof(keywords[0]);

int is_keyword(const char *token) {
    for (int i = 0; i < keyword_count; i++) {
        if (strcasecmp(token, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int in_list(const char *token, char seen[][MAX_TOKEN], int count) {
    for (int i = 0; i < count; i++) {
        if (strcasecmp(token, seen[i]) == 0)
            return 1;
    }
    return 0;
}

void to_upper(char *s) {
    for (int i = 0; s[i]; i++) s[i] = toupper((unsigned char)s[i]);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s archivo.for\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("No se pudo abrir el archivo");
        return 1;
    }

    int line_count = 0;
    int total_keywords = 0;
    int unique_keywords = 0;
    int nested_structures = 0;
    int complex_constructs = 0;

    char seen_keywords[MAX_KEYWORDS][MAX_TOKEN];
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp)) {
        line_count++;
        char *token = strtok(line, " ,();\t\r\n");
        while (token != NULL) {
            char upper[MAX_TOKEN];
            strncpy(upper, token, MAX_TOKEN - 1);
            upper[MAX_TOKEN - 1] = '\0';
            to_upper(upper);

            if (is_keyword(upper)) {
                total_keywords++;
                if (!in_list(upper, seen_keywords, unique_keywords)) {
                    strncpy(seen_keywords[unique_keywords++], upper, MAX_TOKEN);
                }

                if (!strcmp(upper, "IF") || !strcmp(upper, "DO") || !strcmp(upper, "THEN") || !strcmp(upper, "ENDIF"))
                    nested_structures++;

                if (!strcmp(upper, "COMMON") || !strcmp(upper, "ENTRY") || !strcmp(upper, "EQUIVALENCE"))
                    complex_constructs++;
            }
            token = strtok(NULL, " ,();\t\r\n");
        }
    }

    fclose(fp);

    printf("Archivo: %s\n", argv[1]);
    printf("line_count,%d\n", line_count);
    printf("keyword_count,%d\n", total_keywords);
    printf("unique_keywords,%d\n", unique_keywords);
    printf("nested_structures,%d\n", nested_structures);
    printf("complex_constructs,%d\n", complex_constructs);
    return 0;
}
