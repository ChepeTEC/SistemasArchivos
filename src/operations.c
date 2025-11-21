#include "operations.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Funcion auxiliar lógica de encontrar archivo
int ops_find_file(FileSystem *fs, const char *filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->files[i].is_used && strcmp(fs->files[i].name, filename) == 0) {
            return i;
        }
    }
    return -1; // Archivo no encontrado
}

//Funcion auxiliar lógica de allocar los bloques
int ops_allocate_blocks(FileSystem *fs, int block_count) {
    int allocated = 0;
    int first_block = -1;
    
    for (int i = 0; i < MAX_BLOCKS && allocated < block_count; i++) {
        if (!fs->blocks[i].is_used) {
            fs->blocks[i].is_used = 1;
            if (first_block == -1) first_block = i;
            allocated++;
        }
    }
    
    return (allocated == block_count) ? first_block : -1;
}

//Funcion auxiliar lógica de liberar los bloques
void ops_free_blocks(FileSystem *fs, int blocks[], int block_count) {
    for (int i = 0; i < block_count; i++) {
        if (blocks[i] != -1) {
            fs->blocks[blocks[i]].is_used = 0;
            memset(fs->blocks[blocks[i]].data, 0, BLOCK_SIZE);
        }
    }
}

//Funcion de operacion de crear archivo
int ops_create_file(FileSystem *fs, const char *filename, int size) {
    // Verificar límites
    if (fs->file_count >= MAX_FILES) { //Limite de archivos
        printf("Error: Se ha alcanzado el número máximo de archivos\n");
        return -1;
    }
    
    if (size <= 0) { //Validación de tamaño
        printf("Error: Tamaño de archivo inválido\n");
        return -1;
    }
    
    if (fs->used_storage + size > MAX_STORAGE) { // Limite de espacio
        printf("Error: No hay suficiente espacio en el sistema de archivos\n");
        return -1;
    }
    
    // Verificar si el archivo ya existe
    if (ops_find_file(fs, filename) != -1) {
        printf("Error: El archivo '%s' ya existe\n", filename);
        return -1;
    }
    
    // Calcular número de bloques necesarios
    int block_count = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    
    // Asignar bloques
    int first_block = ops_allocate_blocks(fs, block_count);
    if (first_block == -1) {
        printf("Error: No hay bloques disponibles\n");
        return -1;
    }
    
    // Encontrar slot libre para el archivo
    int file_index = -1;
    for (int i = 0; i < MAX_FILES; i++) {
        if (!fs->files[i].is_used) {
            file_index = i;
            break;
        }
    }
    
    if (file_index == -1) { //Esto sucede si no se le pudo asignar index al archivo, osea no se creo
        printf("Error: No se pudo crear el archivo\n");
        return -1;
    }
    
    // Inicializar la entrada del archivo
    strncpy(fs->files[file_index].name, filename, MAX_FILENAME_LENGTH - 1);
    fs->files[file_index].size = size;
    fs->files[file_index].block_count = block_count;
    fs->files[file_index].is_used = 1;
    
    // Asignar bloques al archivo
    for (int i = 0; i < block_count; i++) {
        fs->files[file_index].blocks[i] = first_block + i;
    }
    
    //Aumentamos los parámetros del sistema
    fs->file_count++;
    fs->used_storage += size;
    
    printf("Archivo '%s' creado exitosamente (%d bytes, %d bloques)\n", filename, size, block_count);
    return 0;
}

//Funcion de operacion de escribir en un archivo
int ops_write_file(FileSystem *fs, const char *filename, int offset, const char *data) {

    //Se localiza el archivo para obtener su index
    int file_index = ops_find_file(fs, filename);
    if (file_index == -1) {
        printf("Error: Archivo '%s' no encontrado\n", filename);
        return -1;
    }
    
    FileEntry *file = &fs->files[file_index];
    int data_length = strlen(data);
    
    // Verificar límites
    if (offset < 0 || offset + data_length > file->size) {
        printf("Error: Offset o tamaño de datos excede los límites del archivo\n");
        return -1;
    }
    
    // Escribir datos en los bloques
    int bytes_written = 0;
    int current_block = offset / BLOCK_SIZE;
    int block_offset = offset % BLOCK_SIZE;
    
    while (bytes_written < data_length) {
        int block_index = file->blocks[current_block];
        int space_in_block = BLOCK_SIZE - block_offset;
        int bytes_to_write = (data_length - bytes_written < space_in_block) ? 
                            data_length - bytes_written : space_in_block;
        
        memcpy(&fs->blocks[block_index].data[block_offset], 
               &data[bytes_written], bytes_to_write);
        
        bytes_written += bytes_to_write;
        current_block++;
        block_offset = 0;
    }
    
    printf("Escritos %d bytes en '%s' desde offset %d\n", data_length, filename, offset);
    return 0;
}

//Funcion de operacion de leer un archivo
int ops_read_file(FileSystem *fs, const char *filename, int offset, int size, char *buffer) {
    int file_index = ops_find_file(fs, filename);
    if (file_index == -1) { //En caso de que no lo encuentre
        printf("Error: Archivo '%s' no encontrado\n", filename);
        return -1;
    }
    
    FileEntry *file = &fs->files[file_index];
    
    // Verificar límites
    if (offset < 0 || offset >= file->size) {
        printf("Error: Offset fuera de los límites del archivo\n");
        return -1;
    }
    
    if (offset + size > file->size) {
        printf("Error: Tamaño de lectura excede los límites del archivo\n");
        return -1;
    }
    
    // Leer datos de los bloques
    int bytes_read = 0;
    int current_block = offset / BLOCK_SIZE;
    int block_offset = offset % BLOCK_SIZE;
    
    while (bytes_read < size) {
        int block_index = file->blocks[current_block];
        int space_in_block = BLOCK_SIZE - block_offset;
        int bytes_to_read = (size - bytes_read < space_in_block) ? 
                           size - bytes_read : space_in_block;
        
        memcpy(&buffer[bytes_read], 
               &fs->blocks[block_index].data[block_offset], bytes_to_read);
        
        bytes_read += bytes_to_read;
        current_block++;
        block_offset = 0;
    }
    
    buffer[bytes_read] = '\0';
    return 0;
}

//Funcion de operacion de leer un archivo
int ops_delete_file(FileSystem *fs, const char *filename) {
    int file_index = ops_find_file(fs, filename);
    if (file_index == -1) {
        printf("Error: Archivo '%s' no encontrado\n", filename);
        return -1;
    }
    
    FileEntry *file = &fs->files[file_index];
    
    // Liberar bloques
    ops_free_blocks(fs, file->blocks, file->block_count);
    
    // Actualizar variables del sistema de archivo
    fs->used_storage -= file->size;
    fs->file_count--;
    
    // Limpiamos los datos del archivo
    file->is_used = 0;
    file->size = 0;
    file->block_count = 0;
    memset(file->name, 0, MAX_FILENAME_LENGTH);
    memset(file->blocks, -1, sizeof(file->blocks));
    
    printf("Archivo '%s' eliminado exitosamente\n", filename);
    return 0;
}

//Funcion de operacion de listar los archivos existentes
void ops_list_files(FileSystem *fs) {
    printf("\n=== Lista de Archivos ===\n");
    
    if (fs->file_count == 0) {
        printf("No hay archivos en el sistema\n");
        return;
    }
    
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->files[i].is_used) {
            printf("%s - %d bytes\n", fs->files[i].name, fs->files[i].size);
        }
    }
    
    printf("Total: %d archivos, %d/%d bytes usados\n", 
           fs->file_count, fs->used_storage, MAX_STORAGE);
}