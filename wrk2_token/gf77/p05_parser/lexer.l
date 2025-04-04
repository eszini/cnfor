
%{
#include "parser.tab.h"
%}

%%

[ \t\r\n]+           ;
"SUBROUTINE"         return SUBROUTINE;
"ENTRY"              return ENTRY;
"END"                return END;
"REAL"               return REAL;
"IMPLICIT"           return IMPLICIT;
"USE"                return USE;
[A-Za-z_][A-Za-z_0-9]* return IDENTIFIER;
"("                  return LPAREN;
")"                  return RPAREN;
","                  return COMMA;
"="                  return EQUAL;
"*"                  return TIMES;
"+"                  return PLUS;
.                    return UNKNOWN;

%%

int yywrap() { return 1; }
