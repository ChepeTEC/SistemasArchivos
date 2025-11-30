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


## test.txt entradas/salidas ejemplo
Inicializando sistema de archivos...
Sistema listo. Escribe HELP para ver los comandos disponibles.

> CREATE documento.txt 500
Archivo 'documento.txt' creado exitosamente (500 bytes, 1 bloques)

> CREATE imagen.png 1200
Archivo 'imagen.png' creado exitosamente (1200 bytes, 3 bloques)

> CREATE datos.bin 300
Archivo 'datos.bin' creado exitosamente (300 bytes, 1 bloques)

> LIST
=== Lista de Archivos ===
documento.txt - 500 bytes
imagen.png - 1200 bytes
datos.bin - 300 bytes
Total: 3 archivos, 2000/1048576 bytes usados

> WRITE documento.txt 0 "Este es el contenido del primer archivo"
Escritos 39 bytes en 'documento.txt' desde offset 0

> READ documento.txt 0 45
Salida: "Este es el contenido del primer archivo"

> WRITE imagen.png 0 "Datos de imagen simulados"
Escritos 25 bytes en 'imagen.png' desde offset 0

> READ imagen.png 0 25
Salida: "Datos de imagen simulados"

> WRITE datos.bin 0 "1234567890"
Escritos 10 bytes en 'datos.bin' desde offset 0

> READ datos.bin 0 10
Salida: "1234567890"

> LIST
=== Lista de Archivos ===
documento.txt - 500 bytes
imagen.png - 1200 bytes
datos.bin - 300 bytes
Total: 3 archivos, 2000/1048576 bytes usados

> WRITE documento.txt 45 " - texto adicional al final"
Escritos 27 bytes en 'documento.txt' desde offset 45

> READ documento.txt 0 70
Salida: "Este es el contenido del primer archivo - texto adicional al final"

> WRITE imagen.png 25 " con extension"
Escritos 14 bytes en 'imagen.png' desde offset 25

> READ imagen.png 20 20
Salida: "lados con extension"

> WRITE datos.bin 10 "ABCDEF"
Escritos 6 bytes en 'datos.bin' desde offset 10

> READ datos.bin 5 11
Salida: "67890ABCDEF"

> LIST
=== Lista de Archivos ===
documento.txt - 500 bytes
imagen.png - 1200 bytes
datos.bin - 300 bytes
Total: 3 archivos, 2000/1048576 bytes usados

> WRITE documento.txt 70 " mas datos"
Escritos 10 bytes en 'documento.txt' desde offset 70

> WRITE documento.txt 80 " continuacion"
Escritos 13 bytes en 'documento.txt' desde offset 80

> READ documento.txt 0 95
Salida: "Este es el contenido del primer archivo - texto adicional al final mas datos continuacion"

> CREATE log.txt 200
Archivo 'log.txt' creado exitosamente (200 bytes, 1 bloques)

> WRITE log.txt 0 "=== INICIO DE LOG ==="
Escritos 21 bytes en 'log.txt' desde offset 0

> WRITE log.txt 22 " [INFO] Sistema activo"
Escritos 22 bytes en 'log.txt' desde offset 22

> WRITE log.txt 45 " [ERROR] Problema detectado"
Escritos 27 bytes en 'log.txt' desde offset 45

> READ log.txt 0 70
Salida: "=== INICIO DE LOG === [INFO] Sistema activo [ERROR] Problema detectado"

> LIST
=== Lista de Archivos ===
documento.txt - 500 bytes
imagen.png - 1200 bytes
datos.bin - 300 bytes
log.txt - 200 bytes
Total: 4 archivos, 2200/1048576 bytes usados

> READ archivo_inexistente.txt 0 10
Error: Archivo 'archivo_inexistente.txt' no encontrado

> WRITE archivo_inexistente.txt 0 "datos"
Error: Archivo 'archivo_inexistente.txt' no encontrado

> DELETE archivo_inexistente.txt
Error: Archivo 'archivo_inexistente.txt' no encontrado

> WRITE documento.txt 600 "fuera de limites"
Error: Offset o tamaño de datos excede los límites del archivo

> WRITE datos.bin 350 "excede tamaño"
Error: Offset o tamaño de datos excede los límites del archivo

> CREATE demasiado_grande.txt 2000000
Error: No hay suficiente espacio en el sistema de archivos

> LIST
=== Lista de Archivos ===
documento.txt - 500 bytes
imagen.png - 1200 bytes
datos.bin - 300 bytes
log.txt - 200 bytes
Total: 4 archivos, 2200/1048576 bytes usados

> DELETE imagen.png
Archivo 'imagen.png' eliminado exitosamente

> LIST
=== Lista de Archivos ===
documento.txt - 500 bytes
datos.bin - 300 bytes
log.txt - 200 bytes
Total: 3 archivos, 1000/1048576 bytes usados

> DELETE datos.bin
Archivo 'datos.bin' eliminado exitosamente

> LIST
=== Lista de Archivos ===
documento.txt - 500 bytes
log.txt - 200 bytes
Total: 2 archivos, 700/1048576 bytes usados

> CREATE nuevo.txt 100
Archivo 'nuevo.txt' creado exitosamente (100 bytes, 1 bloques)

> WRITE nuevo.txt 0 "Archivo nuevo después de eliminar"
Escritos 34 bytes en 'nuevo.txt' desde offset 0

> READ nuevo.txt 0 35
Salida: "Archivo nuevo después de eliminar"

> LIST
=== Lista de Archivos ===
documento.txt - 500 bytes
nuevo.txt - 100 bytes
log.txt - 200 bytes
Total: 3 archivos, 800/1048576 bytes usados

> CREATE arch1.txt 50
Archivo 'arch1.txt' creado exitosamente (50 bytes, 1 bloques)

> CREATE arch2.txt 50
Archivo 'arch2.txt' creado exitosamente (50 bytes, 1 bloques)

> CREATE arch3.txt 50
Archivo 'arch3.txt' creado exitosamente (50 bytes, 1 bloques)

> CREATE arch4.txt 50
Archivo 'arch4.txt' creado exitosamente (50 bytes, 1 bloques)

> CREATE arch5.txt 50
Archivo 'arch5.txt' creado exitosamente (50 bytes, 1 bloques)

> LIST
=== Lista de Archivos ===
documento.txt - 500 bytes
nuevo.txt - 100 bytes
arch1.txt - 50 bytes
log.txt - 200 bytes
arch2.txt - 50 bytes
arch3.txt - 50 bytes
arch4.txt - 50 bytes
arch5.txt - 50 bytes
Total: 8 archivos, 1050/1048576 bytes usados

> CREATE especial.txt 150
Archivo 'especial.txt' creado exitosamente (150 bytes, 1 bloques)

> WRITE especial.txt 0 "Texto con numeros 123 y simbolos"
Escritos 32 bytes en 'especial.txt' desde offset 0

> WRITE especial.txt 50 "Caracteres especiales"
Escritos 21 bytes en 'especial.txt' desde offset 50

> READ especial.txt 0 80
Salida: "Texto con numeros 123 y simbolosCaracteres especiales"

> READ especial.txt 40 50
Salida: "Caracteres especiales"

> LIST
=== Lista de Archivos ===
documento.txt - 500 bytes
nuevo.txt - 100 bytes
arch1.txt - 50 bytes
log.txt - 200 bytes
arch2.txt - 50 bytes
arch3.txt - 50 bytes
arch4.txt - 50 bytes
arch5.txt - 50 bytes
especial.txt - 150 bytes
Total: 9 archivos, 1200/1048576 bytes usados

> CREATE temp1.txt 80
Archivo 'temp1.txt' creado exitosamente (80 bytes, 1 bloques)

> CREATE temp2.txt 80
Archivo 'temp2.txt' creado exitosamente (80 bytes, 1 bloques)

> CREATE temp3.txt 80
Archivo 'temp3.txt' creado exitosamente (80 bytes, 1 bloques)

> WRITE temp1.txt 0 "Contenido temporal 1"
Escritos 20 bytes en 'temp1.txt' desde offset 0

> WRITE temp2.txt 0 "Contenido temporal 2"
Escritos 20 bytes en 'temp2.txt' desde offset 0

> WRITE temp3.txt 0 "Contenido temporal 3"
Escritos 20 bytes en 'temp3.txt' desde offset 0

> READ temp1.txt 0 20
Salida: "Contenido temporal 1"

> READ temp2.txt 0 20
Salida: "Contenido temporal 2"

> READ temp3.txt 0 20
Salida: "Contenido temporal 3"

> DELETE temp1.txt
Archivo 'temp1.txt' eliminado exitosamente

> DELETE temp2.txt
Archivo 'temp2.txt' eliminado exitosamente

> DELETE temp3.txt
Archivo 'temp3.txt' eliminado exitosamente

> LIST
=== Lista de Archivos ===
documento.txt - 500 bytes
nuevo.txt - 100 bytes
arch1.txt - 50 bytes
log.txt - 200 bytes
arch2.txt - 50 bytes
arch3.txt - 50 bytes
arch4.txt - 50 bytes
arch5.txt - 50 bytes
especial.txt - 150 bytes
Total: 9 archivos, 1200/1048576 bytes usados

> CREATE integridad.txt 60
Archivo 'integridad.txt' creado exitosamente (60 bytes, 1 bloques)

> WRITE integridad.txt 0 "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
Escritos 36 bytes en 'integridad.txt' desde offset 0

> READ integridad.txt 0 36
Salida: "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

> WRITE integridad.txt 10 "abcdefghij"
Escritos 10 bytes en 'integridad.txt' desde offset 10

> READ integridad.txt 0 36
Salida: "ABCDEFGHIJabcdefghijUVWXYZ0123456789"

> READ integridad.txt 5 15
Salida: "FGHIJabcdefghij"

> LIST
=== Lista de Archivos ===
documento.txt - 500 bytes
nuevo.txt - 100 bytes
arch1.txt - 50 bytes
log.txt - 200 bytes
arch2.txt - 50 bytes
arch3.txt - 50 bytes
arch4.txt - 50 bytes
arch5.txt - 50 bytes
especial.txt - 150 bytes
integridad.txt - 60 bytes
Total: 10 archivos, 1260/1048576 bytes usados

> DELETE documento.txt
Archivo 'documento.txt' eliminado exitosamente

> DELETE log.txt
Archivo 'log.txt' eliminado exitosamente

> DELETE nuevo.txt
Archivo 'nuevo.txt' eliminado exitosamente

> DELETE arch1.txt
Archivo 'arch1.txt' eliminado exitosamente

> DELETE arch2.txt
Archivo 'arch2.txt' eliminado exitosamente

> DELETE arch3.txt
Archivo 'arch3.txt' eliminado exitosamente

> DELETE arch4.txt
Archivo 'arch4.txt' eliminado exitosamente

> DELETE arch5.txt
Archivo 'arch5.txt' eliminado exitosamente

> DELETE especial.txt
Archivo 'especial.txt' eliminado exitosamente

> DELETE integridad.txt
Archivo 'integridad.txt' eliminado exitosamente

> LIST
=== Lista de Archivos ===
No hay archivos en el sistema

> EXIT
Saliendo del sistema de archivos...