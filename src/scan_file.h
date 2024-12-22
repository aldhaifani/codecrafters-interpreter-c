//
// Created by Tareq Aldhaifani on 22/12/2024.
//

#ifndef SCAN_FILE_H
#define SCAN_FILE_H

typedef struct
{
    const char* key;
    const char* token_name;
    const char* value;
} Token;

static Token tokens[] = {
    {"(", "LEFT_PAREN", "null"},
    {")", "RIGHT_PAREN", "null"},
    {"{", "LEFT_BRACE", "null"},
    {"}", "RIGHT_BRACE", "null"},
    {";", "SEMICOLON", "null"},
    {",", "COMMA", "null"},
    {".", "DOT", "null"},
    {"-", "MINUS", "null"},
    {"+", "PLUS", "null"},
    {"/", "SLASH", "null"},
    {"*", "STAR", "null"},
    {"=", "EQUAL", "null"},
    {"<", "LESS", "null"},
    {">", "GREATER", "null"},
    {">=", "GREATER_EQUAL", "null"},
    {"<=", "LESS_EQUAL", "null"},
    {"==", "EQUAL_EQUAL", "null"},
    {"!=", "BANG_EQUAL", "null"},
    {"!", "BANG", "null"},
    {"//", "COMMENT", "null"},
    {" ", "SPACE", "null"},
    {"\t", "TAB", "null"},
    {"\n", "NEWLINE", "null"},
    {"\0", "EOF", "null"},
};

const Token* find_lexeme(const char* key);
int scan_file(const char* file_contents);

#endif //SCAN_FILE_H
