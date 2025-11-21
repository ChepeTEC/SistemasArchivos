# Sistema de Archivos Simple

## Descripción
Implementación de un sistema de archivos simple en C que simula operaciones básicas de gestión de archivos usando bloques de memoria y una tabla de archivos.

## Autores
- José Miguel González Barrantes
- Erick Abarca

## Características
- Crear, escribir, leer y eliminar archivos
- Gestión de bloques de memoria de 512 bytes
- Manejo robusto de errores
- Límites: 100 archivos máximo, 1MB almacenamiento total
- Interfaz de comandos interactiva

## Compilación
cd src
make

## Ejecución
./filesystem

## Comandos
CREATE <nombre> <tamaño>            - Crear archivo
WRITE <nombre> <offset> "<datos>"   - Escribir datos
READ <nombre> <offset> <tamaño>     - Leer datos
DELETE <nombre>                     - Eliminar archivo
LIST                                - Listar archivos
HELP                                - Mostrar ayuda
EXIT                                - Salir

## Ejemplo de uso
> CREATE ejemplo.txt 100

> WRITE ejemplo.txt 0 "Hola mundo"

> READ ejemplo.txt 0 11
Salida: "Hola mundo"

> LIST
ejemplo.txt - 100 bytes

> DELETE ejemplo.txt