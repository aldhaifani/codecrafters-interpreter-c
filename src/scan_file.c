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
    for (size_t i = 0; i < file_size;)
    {
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
                    // Skip the rest of the line
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
                i += 1;
                continue;
            }
            printf("%s %s %s\n", token->token_name, token->key, token->value);
            i++; // Move to the next character
        }
        else
        {
            fprintf(stderr, "[line 1] Error: Unexpected character: %c\n", file_contents[i]);
            exit_code = 65;
            i++; // Move to the next character, even if it's invalid
        }
    }
    return exit_code;
}

