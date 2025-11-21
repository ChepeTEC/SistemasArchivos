
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Funcion para trimmear los espacios en blanco
void trim_whitespace(char *str) {
    char *end;
    
    // Trim leading space
    while(isspace((unsigned char)*str)) str++;
    
    if(*str == 0) return;
    
    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    
    // Write new null terminator
    *(end + 1) = 0;
}

//Funcion principal que se encarga en procesar cada comando
int parse_command(char *input, char *tokens[]) {
    int token_count = 0;
    char *start = input;
    int in_quotes = 0;
    char *dest = input;
    
    // Procesar caracter por caracter para manejar comillas
    for (char *p = input; *p != '\0' && token_count < MAX_TOKENS - 1; p++) {
        if (*p == '"') {
            in_quotes = !in_quotes;
            // No copiamos las comillas al resultado
            continue;
        }
        
        if (*p == ' ' && !in_quotes) {
            // Fin de un token
            if (dest > start) {
                *dest = '\0';
                tokens[token_count++] = start;
                dest++;
                start = dest;
            }
            continue;
        }
        
        // Copiar caracter al destino
        *dest = *p;
        dest++;
    }
    
    // Último token
    if (dest > start && token_count < MAX_TOKENS - 1) {
        *dest = '\0';
        tokens[token_count++] = start;
    }
    
    tokens[token_count] = NULL;
    return token_count;
}