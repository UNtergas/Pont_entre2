#include "mini_lib.h"

void mini_clean(char *file)
{
    MYFILE *_file = mini_open(file, CREAT_DEL);
    if (_file != NULL)
    {
        mini_fclose(_file);
    }
    else
    {
        mini_printf("file '");
        mini_printf(file);
        mini_printf("' ");
        mini_perror("error");
    }
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        mini_printf("too many or few arguments");
        exit(1);
    }
    for (int i = 1; i < argc; i++)
    {
        mini_clean(argv[i]);
    }
}