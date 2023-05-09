#include "mini_lib.h"

void _del(char **c)
{
    while (**c == ' ')
    {
        (*c)++;
    }
}
void mini_wc(char *file)
{
    MYFILE *_ptr = mini_open(file, OPEN_READ);
    int _count = 1;
    char *_buf = mini_calloc(1, IOBUFFER_SIZE);
    int _num_mot = mini_fread(_buf, 1, IOBUFFER_SIZE, _ptr);
    int _count_saut = 0;
    for (int i = 0; _buf[i] != '\0'; i++)
    {
        if (_buf[i] == '\n')
            _count_saut++;
    }

    /**/
    int _parcour = 0;
    while (_buf[_parcour] != '\0')
    {
        if (_buf[_parcour] == ' ' || _buf[_parcour] == '\n')
        {
            _count++;
            _buf += _parcour;
            _del(&_buf);
            _parcour = 0;
        }
        _parcour++;
    }
    /**/
    char temp[3][IOBUFFER_SIZE];
    mini_strncpy(mini_itoa(_count_saut), temp[0], IOBUFFER_SIZE);
    mini_strncpy(mini_itoa(_count), temp[1], IOBUFFER_SIZE);
    mini_strncpy(mini_itoa(_num_mot), temp[2], IOBUFFER_SIZE);
    mini_printf(temp[0]);
    write(1, " ", 1);
    mini_printf(temp[1]);
    write(1, " ", 1);
    mini_printf(temp[2]);
    write(1, "  ", 1);
    mini_printf(file);
    write(1, "\n", 1);

    mini_fclose(_ptr);
}