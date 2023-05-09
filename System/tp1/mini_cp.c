#include "mini_lib.h"

void mini_cp(char *src, char *dest)
{
    if (mini_strcmp(src, dest) == 0)
    {
        mini_printf("src et dest sont les meme\n");
    }
    MYFILE *_src_ptr = mini_open(src, OPEN_READ);
    if (_src_ptr == NULL)
    {
        mini_printf("file '");
        mini_printf(src);
        mini_printf("' ");
        mini_perror("error");
        exit(1);
    }
    MYFILE *_dest_ptr = mini_open(dest, OPEN_WRITE);
    if (_dest_ptr == NULL)
    {
        mini_printf("file '");
        mini_printf(dest);
        mini_printf("' ");
        mini_perror("error");
    }
    char buffer[2000];
    int _count = mini_fread(buffer, 1, 2000, _src_ptr);
    mini_fwrite(buffer, 1, _count, _dest_ptr);
    mini_fclose(_dest_ptr);
    mini_fclose(_src_ptr);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        mini_printf("insufficant argument ");
        exit(1);
    }
    mini_cp(argv[1], argv[2]);
}