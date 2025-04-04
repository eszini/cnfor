
%{
#include <stdio.h>
extern int yylineno;
extern char *yytext;
void yyerror(const char *s);
int yylex(void);
%}

%token SUBROUTINE END ENTRY REAL IMPLICIT USE
%token IDENTIFIER
%token LPAREN RPAREN COMMA EQUAL TIMES PLUS
%token UNKNOWN

%%

programa:
    subrutina
;

subrutina:
    SUBROUTINE IDENTIFIER LPAREN argumentos RPAREN declaraciones instrucciones END
;

argumentos:
    IDENTIFIER
    | argumentos COMMA IDENTIFIER
;

declaraciones:
    /* vacío */
    | declaraciones declaracion
;

declaracion:
    REAL lista_identificadores
    | USE IDENTIFIER
    | IMPLICIT IDENTIFIER
;

lista_identificadores:
    IDENTIFIER
    | lista_identificadores COMMA IDENTIFIER
;

instrucciones:
    /* vacío */
    | instrucciones instruccion
;

instruccion:
    asignacion
    | entry
;

asignacion:
    IDENTIFIER EQUAL expresion
;

entry:
    ENTRY IDENTIFIER LPAREN argumentos RPAREN
;

expresion:
    IDENTIFIER
    | IDENTIFIER PLUS IDENTIFIER
    | IDENTIFIER TIMES IDENTIFIER
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error de sintaxis en línea %d: %s (token: '%s')\n", yylineno, s, yytext);
}
