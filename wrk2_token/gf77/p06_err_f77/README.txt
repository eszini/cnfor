
# Paso 06: Programa Fortran con errores sintácticos

Este archivo `error.f` contiene dos errores intencionales:

1. Falta el paréntesis de cierre en la línea de SUBROUTINE.
2. Falta el END final que indica el fin de la subrutina.

Puedes probarlo así:

    ./parser < error.f

Debería mostrar un mensaje como:

    Error de sintaxis: syntax error
