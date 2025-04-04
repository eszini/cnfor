
# Paso 07b: Parser con manejo técnico correcto de yylineno (%option)

Este parser usa la forma recomendada para contar líneas en Flex:

- Se activa con `%option yylineno`
- No requiere declarar ni inicializar `yylineno` manualmente
- Permite detectar errores con línea y token

## Uso:

    make
    ./parser < ../p06_err_f77/error.f

## Ejemplo de salida:

    Error de sintaxis en línea 2: syntax error (token: ')')
