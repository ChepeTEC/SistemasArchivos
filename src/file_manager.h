#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#define BLOCK_SIZE 512
#define MAX_FILES 100
#define MAX_STORAGE 1048576  // 1 MB
#define MAX_FILENAME_LENGTH 50
#define MAX_BLOCKS (MAX_STORAGE / BLOCK_SIZE)

//
typedef struct {
    char name[MAX_FILENAME_LENGTH];
    int size;
    int block_count;
    int blocks[MAX_BLOCKS];
    int is_used;
} FileEntry;

//Elemento básico del sistema de archivos
typedef struct {
    char data[BLOCK_SIZE];
    int is_used;
} Block;

//Estructura del sistema de archivos
typedef struct {
    FileEntry files[MAX_FILES];
    Block blocks[MAX_BLOCKS];
    int used_storage;
    int file_count;
} FileSystem;

// Funciones de inicialización
void init_filesystem(FileSystem *fs);

// Funciones de interfaz (llaman a operations)
int fm_create(FileSystem *fs, const char *filename, int size);
int fm_write(FileSystem *fs, const char *filename, int offset, const char *data);
int fm_read(FileSystem *fs, const char *filename, int offset, int size, char *buffer);
int fm_delete(FileSystem *fs, const char *filename);
void fm_list(FileSystem *fs);

#endif