#ifndef PARSER_H
#define PARSER_H

#define MAX_COMMAND_LENGTH 256
#define MAX_TOKENS 10

// Funciones de parsing
int parse_command(char *input, char *tokens[]);
void trim_whitespace(char *str);

#endif