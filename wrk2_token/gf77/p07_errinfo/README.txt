
# Paso 07: Parser con información de error detallada

Este parser mejora la salida de errores incluyendo:

- Número de línea (`yylineno`)
- Token donde ocurrió el error (`yytext`)

## Uso:

    make
    ./parser < ../p06_err_f77/error.f

## Resultado esperado:

    Error de sintaxis en línea 2: syntax error (token: ')')
