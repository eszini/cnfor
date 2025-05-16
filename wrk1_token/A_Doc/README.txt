
# Proyecto: #gramatica_f77

## Objetivo general:
Construir una gramática personalizada (basada en 250 archivos fuente) para analizar código en Fortran 77 y Fortran 90, usando Flex/Bison y C. Todo el proceso debe poder integrarse eventualmente en Ollama con LLaMA2.

## Estrategia paso a paso:

0) 📌 Este proyecto se integrará con Ollama usando LLaMA2. Al final de cada paso, se documentarán instrucciones para usarlo con Ollama.

1) 🧱 Crear un tokenizador en C para extraer entidades básicas (palabras clave, identificadores, etc.)

2) ✍️ Crear un programa de prueba en Fortran (válido, simple).

3) 🔍 Ejecutar el tokenizador sobre el programa de prueba y listar palabras clave.

4) 📘 Con los tokens encontrados, generar una primera gramática con Bison.

5) 🔄 Escribir un parser en C que valide el código Fortran contra esa gramática.

6) ❌ Generar un programa Fortran con errores para probar el parser.

7) 🛠 Crear un script o Makefile para compilar todo usando flex, bison, gcc.

8) ✅ Ejecutar el parser contra fuentes correctos e incorrectos.

9) 🔁 Definir un ciclo iterativo de mejora de la gramática.

10) 📦 Comprimir todo en una estructura ordenada por pasos, lista para compartir o usar en Ollama.

## Estructura sugerida:
- paso_01_tokenizador_c/
- paso_02_programa_fortran_ejemplo/
- paso_03_analisis_tokens/
- paso_04_gramatica_bison/
- paso_05_parser_c/
- paso_06_programa_con_error/
- paso_07_script_compilacion/
- paso_08_pruebas/
- paso_09_mejoras/
- paso_10_entrega/

