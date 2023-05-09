#include "mini_lib.h"

void mini_cat(char *_file)
{
    MYFILE *_ptr = mini_open(_file, OPEN_READ);
    if (_ptr != NULL)
    {
        char buffer[IOBUFFER_SIZE];
        mini_fread(buffer, 1, IOBUFFER_SIZE, _ptr);
        mini_printf(buffer);
        write(1, "\n", 1);
        mini_fclose(_ptr);
    }
    else
    {
        mini_printf("file '");
        mini_printf(_file);
        mini_printf("' ");
        mini_perror("error");
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        mini_printf("insuffi argument");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; i++)
    {
        mini_cat(argv[i]);
    }
}