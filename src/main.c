#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_manager.h"
#include "parser.h"

void print_help() {
    printf("\n=== Sistema de Archivos Simple ===\n");
    printf("Comandos disponibles:\n");
    printf("  CREATE <nombre_archivo> <tamaño_bytes>\n");
    printf("  WRITE <nombre_archivo> <offset> \"<data>\"\n");
    printf("  READ <nombre_archivo> <offset> <tamaño>\n");
    printf("  DELETE <nombre_archivo>\n");
    printf("  LIST\n");
    printf("  HELP\n");
    printf("  EXIT\n");
    printf("===================================\n\n");
}

int main() {
    FileSystem fs;
    char input[MAX_COMMAND_LENGTH];
    char *tokens[MAX_TOKENS];
    int token_count;
    
    printf("Inicializando sistema de archivos...\n");
    init_filesystem(&fs);
    printf("Sistema listo. Escribe HELP para ver los comandos disponibles.\n\n");
    
    while (1) {
        printf("> ");
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // Remover newline
        input[strcspn(input, "\n")] = 0;
        
        if (strlen(input) == 0) {
            continue;
        }
        
        token_count = parse_command(input, tokens);
        
        if (token_count == 0) {
            continue;
        }
        
        // DEBUG: Mostrar tokens
        printf("DEBUG: Tokens encontrados: ");
        for (int i = 0; i < token_count; i++) {
            printf("[%s] ", tokens[i]);
        }
        printf("\n");
        
        // Procesar comandos
        if (strcasecmp(tokens[0], "CREATE") == 0) {
            if (token_count != 3) {
                printf("Error: Uso: CREATE <nombre_archivo> <tamaño_bytes>\n");
            } else {
                fm_create(&fs, tokens[1], atoi(tokens[2]));
            }
        }
        else if (strcasecmp(tokens[0], "WRITE") == 0) {
            if (token_count < 4) {
                printf("Error: Uso: WRITE <nombre_archivo> <offset> \"<data>\"\n");
            } else {
                char data[256] = "";
                for (int i = 3; i < token_count; i++) {
                    if (i > 3) strcat(data, " ");
                    strcat(data, tokens[i]);
                }
                fm_write(&fs, tokens[1], atoi(tokens[2]), data);
            }
        }
        else if (strcasecmp(tokens[0], "READ") == 0) {
            if (token_count != 4) {
                printf("Error: Uso: READ <nombre_archivo> <offset> <tamaño>\n");
            } else {
                int size = atoi(tokens[3]);
                char *buffer = malloc(size + 1);
                if (buffer == NULL) {
                    printf("Error: No se pudo asignar memoria para la lectura\n");
                } else {
                    int result = fm_read(&fs, tokens[1], atoi(tokens[2]), size, buffer);
                    if (result == 0) {
                        printf("Salida: \"%s\"\n", buffer);
                    }
                    free(buffer);
                }
            }
        }
        else if (strcasecmp(tokens[0], "DELETE") == 0) {
            if (token_count != 2) {
                printf("Error: Uso: DELETE <nombre_archivo>\n");
            } else {
                fm_delete(&fs, tokens[1]);
            }
        }
        else if (strcasecmp(tokens[0], "LIST") == 0) {
            fm_list(&fs);
        }
        else if (strcasecmp(tokens[0], "HELP") == 0) {
            print_help();
        }
        else if (strcasecmp(tokens[0], "EXIT") == 0) {
            printf("Saliendo del sistema de archivos...\n");
            break;
        }
        else {
            printf("Error: Comando no reconocido: %s\n", tokens[0]);
            printf("Escribe HELP para ver los comandos disponibles.\n");
        }
    }
    
    return 0;
}