#!/bin/bash

# Nombre del ejecutable por defecto
DEFAULT_EXEC="cnv_f08"

# Si se proporciona un argumento, úsalo como nombre del ejecutable
EXEC=${1:-$DEFAULT_EXEC}

# Parámetros para la ejecución del programa
PARAMS="-v -opciones=d5 -inp=programa1.for -out=programa2.for -aux=parser.log "

# Ejecutar el comando
./$EXEC $PARAMS > log

# miro si el parser encontro caracteres que no tiene en la tabla
cat parser.log

# check basico
wc programa1.for programa2.for

