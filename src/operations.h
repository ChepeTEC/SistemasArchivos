#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "file_manager.h"

// Funciones de operaciones del sistema de archivos
int ops_create_file(FileSystem *fs, const char *filename, int size);
int ops_write_file(FileSystem *fs, const char *filename, int offset, const char *data);
int ops_read_file(FileSystem *fs, const char *filename, int offset, int size, char *buffer);
int ops_delete_file(FileSystem *fs, const char *filename);
void ops_list_files(FileSystem *fs);

// Funciones auxiliares internas
int ops_find_file(FileSystem *fs, const char *filename);
int ops_allocate_blocks(FileSystem *fs, int block_count);
void ops_free_blocks(FileSystem *fs, int blocks[], int block_count);

#endif