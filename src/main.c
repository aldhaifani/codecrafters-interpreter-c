#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_file_contents(const char* filename);

typedef struct
{
    char key;
    const char* token_name;
    const char* value;
} Token;

static Token tokens[] = {
    {'(', "LEFT_PAREN", "null"},
    {')', "RIGHT_PAREN", "null"},
    {'{', "LEFT_BRACE", "null"},
    {'}', "RIGHT_BRACE", "null"},
    {';', "SEMICOLON", "null"},
    {',', "COMMA", "null"},
    {'.', "DOT", "null"},
    {'-', "MINUS", "null"},
    {'+', "PLUS", "null"},
    {'/', "SLASH", "null"},
    {'*', "STAR", "null"},
    {'\0', "EOF", "null"},
};

const Token *find_lexeme(char key);
int scan_file(const char *file_contents);


int main(int argc, char* argv[])
{
    // Disable output buffering
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if (argc < 3)
    {
        fprintf(stderr, "Usage: ./your_program tokenize <filename>\n");
        return 1;
    }

    const char* command = argv[1];
    int exit_code = 0;

    if (strcmp(command, "tokenize") == 0)
    {
        char* file_contents = read_file_contents(argv[2]);

        if (strlen(file_contents) > 0)
        {
            exit_code = scan_file(file_contents);
        }
        printf("EOF  null\n"); // Placeholder, remove this line when implementing the scanner

        free(file_contents);
    }
    else
    {
        fprintf(stderr, "Unknown command: %s\n", command);
        return 1;
    }

    return exit_code;
}

char* read_file_contents(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error reading file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* file_contents = malloc(file_size + 1);
    if (file_contents == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(file_contents, 1, file_size, file);
    if (bytes_read < file_size)
    {
        fprintf(stderr, "Error reading file contents\n");
        free(file_contents);
        fclose(file);
        return NULL;
    }

    file_contents[file_size] = '\0';
    fclose(file);

    return file_contents;
}

const Token *find_lexeme(char key)
{
    for (int i = 0; i < sizeof(tokens) / sizeof(Token); i++)
    {
        if (tokens[i].key == key)
        {
            return &tokens[i];
        }
    }

    return NULL;
}

int scan_file(const char *file_contents)
{
    int exit_code = 0;
    for (size_t i = 0; i < strlen(file_contents); i++)
    {
        const Token *token = find_lexeme(file_contents[i]);
        if (token != NULL)
        {
            printf("%s %c %s\n", token->token_name, token->key, token->value);
        }
        else
        {
            fprintf(stderr, "[line 1] Error: Unexpected character: %c\n", file_contents[i]);
            exit_code = 65;
        }
    }
    return exit_code;
}
