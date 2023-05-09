#include "mini_lib.h"

void mini_tail(int n, char *_file)
{
    MYFILE *_ptr = mini_open(_file, OPEN_READ);
    if (_ptr == NULL)
    {
        mini_printf("file '");
        mini_printf(_file);
        mini_printf("' ");
        mini_perror("error");
        exit(1);
    }
    char *_buf = mini_calloc(1, IOBUFFER_SIZE);
    mini_fread(_buf, 1, IOBUFFER_SIZE, _ptr);
    // mini_printf(_buf);
    // write(1, "\n", 1);
    int _count_saut = 1;
    for (int i = 0; _buf[i] != '\0'; i++)
    {
        if (_buf[i] == '\n')
            _count_saut++;
    }
    int _num_ligne = _count_saut - n;
    while (_num_ligne > 0 && *_buf != '\0')
    {

        if (*_buf == '\n')
        {
            _num_ligne--;
            _buf++;
        }
        else
        {
            _buf++;
        }
    }
    mini_printf(_buf);
    write(1, "\n", 1);
    mini_free(_buf);
    mini_fclose(_ptr);
}

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
    {
        mini_printf("too many or too few argument");
        exit(1);
    }

    mini_tail(atoi(argv[1]), argv[2]);
}