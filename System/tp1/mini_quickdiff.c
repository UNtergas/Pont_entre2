#include "mini_lib.h"
void _del(char **c)
{
    while (**c == ' ')
    {
        (*c)++;
    }
}

int line_comperation(char *s1, char *s2)
{
}

void mini_quickdiff(char *src, char *dest)
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
        exit(1);
    }
    char buffer_src[2000];
    char buffer_dest[2000];
    int _count_src = mini_fread(buffer_src, 1, 2000, _src_ptr);
    int _count_dest = mini_fread(buffer_dest, 1, 2000, _dest_ptr);

    mini_fclose(_dest_ptr);
    mini_fclose(_src_ptr);
}

int main(int argc, char **argv)
{
}