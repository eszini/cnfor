
# Paso 08: Análisis de KPIs de complejidad gramatical

Este programa analiza un archivo .for o .f90 y reporta:

- Cantidad total de líneas
- Cantidad total de palabras clave
- Cantidad de palabras clave únicas
- Estimación de estructuras anidadas
- Cantidad de estructuras complejas (COMMON, ENTRY, etc.)

## Uso:

    make
    ./kpi_analyzer archivo.for > archivo.kpi

La salida se imprime en CSV por consola.
