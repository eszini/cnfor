
# Paso 09: Loop de análisis de KPIs para múltiples fuentes

Este programa toma como entrada un archivo de texto que contiene
una lista de archivos `.for` o `.f90`, uno por línea.

Para cada archivo, calcula los KPIs definidos y una puntuación de complejidad.

## Uso:

1. Crear una lista de archivos, por ejemplo:
    ls ../*.for > lista.txt

2. Ejecutar:
    ./kpi_loop lista.txt > resumen_kpis.csv
