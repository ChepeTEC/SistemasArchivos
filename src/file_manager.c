#include "file_manager.h"
#include "operations.h"
#include <stdio.h>
#include <string.h>

void init_filesystem(FileSystem *fs) {
    fs->file_count = 0;
    fs->used_storage = 0;
    
    // Inicializar todos los archivos como no usados
    for (int i = 0; i < MAX_FILES; i++) {
        fs->files[i].is_used = 0;
        fs->files[i].size = 0;
        fs->files[i].block_count = 0;
        memset(fs->files[i].name, 0, MAX_FILENAME_LENGTH);
        memset(fs->files[i].blocks, -1, sizeof(fs->files[i].blocks));
    }
    
    // Inicializar todos los bloques como libres
    for (int i = 0; i < MAX_BLOCKS; i++) {
        fs->blocks[i].is_used = 0;
        memset(fs->blocks[i].data, 0, BLOCK_SIZE);
    }
}

int fm_create(FileSystem *fs, const char *filename, int size) {
    return ops_create_file(fs, filename, size);
}

int fm_write(FileSystem *fs, const char *filename, int offset, const char *data) {
    return ops_write_file(fs, filename, offset, data);
}

int fm_read(FileSystem *fs, const char *filename, int offset, int size, char *buffer) {
    return ops_read_file(fs, filename, offset, size, buffer);
}

int fm_delete(FileSystem *fs, const char *filename) {
    return ops_delete_file(fs, filename);
}

void fm_list(FileSystem *fs) {
    ops_list_files(fs);
}