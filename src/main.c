#include "common.h"
#include "main.h"


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
