//
// Created by Tareq Aldhaifani on 22/12/2024.
//
#include <string.h>

#include "common.h"
#include "scan_file.h"

const Token* find_lexeme(const char* key)
{
    for (int i = 0; i < sizeof(tokens) / sizeof(Token); i++)
    {
        if (strcmp(tokens[i].key, key) == 0)
        {
            return &tokens[i];
        }
    }

    return NULL;
}

int scan_file(const char* file_contents)
{
    int exit_code = 0;
    size_t file_size = strlen(file_contents);
    int line_number = 1; // Start from line 1
    for (size_t i = 0; i < file_size;)
    {
        // Check for string literal
        if (file_contents[i] == '"')
        {
            size_t start_index = i;
            i++; // Move past the opening quote
            // Find the closing quote
            while (i < file_size && file_contents[i] != '"')
            {
                if (file_contents[i] == '\\')  // Handle escape sequences
                {
                    i++; // Skip the escaped character (e.g., \", \n)
                }
                i++;
            }

            if (i >= file_size || file_contents[i] != '"')  // Unterminated string
            {
                fprintf(stderr, "[line %d] Error: Unterminated string.\n", line_number);
                exit_code = 65;
                while (i < file_size && file_contents[i] != '\n')  // Skip to next line to recover
                {
                    i++;
                }
                continue;
            }

            size_t string_length = i - start_index - 1;  // Exclude the quotes
            char *literal = malloc(string_length + 1);
            if (literal == NULL)
            {
                exit_code = 1;
                break;
            }
            strncpy(literal, &file_contents[start_index + 1], string_length);
            literal[string_length] = '\0';  // Null-terminate the string

            printf("STRING \"%s\" %s\n", literal, literal);  // Print string token with literal content
            free(literal);

            i++;  // Move past the closing quote
            continue;  // Skip checking other lexemes after a string literal
        }

        // Check for two-character lexemes first
        const Token* token = NULL;
        if (i + 1 < file_size)
        {
            char lexeme[3] = {file_contents[i], file_contents[i + 1], '\0'};
            token = find_lexeme(lexeme);
            if (token != NULL)
            {
                if (strcmp(token->key, "//") == 0)
                {
                    // Skip the rest of the line (comment)
                    while (i < file_size && file_contents[i] != '\n')
                    {
                        i++;
                    }
                    continue;
                }
                printf("%s %s %s\n", token->token_name, token->key, token->value);
                i += 2; // Skip the next character as it's part of the lexeme
                continue;
            }
        }
        // Check for one-character lexemes
        token = find_lexeme((char[]){file_contents[i], '\0'});
        if (token != NULL)
        {
            // if space, tab, newline, continue
            if (strcmp(token->key, " ") == 0 || strcmp(token->key, "\t") == 0 || strcmp(token->key, "\n") == 0)
            {
                if (file_contents[i] == '\n')
                {
                    line_number++; // Increment line number if newline character is encountered
                }
                i += 1;
                continue;
            }
            printf("%s %s %s\n", token->token_name, token->key, token->value);
            i++; // Move to the next character
        }
        else
        {
            // Print error with line number
            fprintf(stderr, "[line %d] Error: Unexpected character: %c\n", line_number, file_contents[i]);
            exit_code = 65;
            i++; // Move to the next character, even if it's invalid
        }
    }
    return exit_code;
}

