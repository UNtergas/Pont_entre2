#include "mini_lib.h"
void mini_head(int n, char *_file)
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
    char _buf[IOBUFFER_SIZE];
    mini_fread(_buf, 1, IOBUFFER_SIZE, _ptr);
    _ptr->ind_read = 0;
    int i = 0;
    while (i < n)
    {
        while (_buf[_ptr->ind_read] != '\n' && _buf[_ptr->ind_read] != '\0')
        {
            _ptr->ind_read += 1;
        }

        _ptr->ind_read++;
        i++;
    }
    char *temp = mini_calloc(1, _ptr->ind_read);
    mini_strncpy(_buf, temp, _ptr->ind_read);
    mini_printf(temp);
    mini_free(temp);
    mini_fclose(_ptr);
}

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
    {
        mini_printf("too many or too much argument");
        exit(1);
    }

    mini_head(atoi(argv[1]), argv[2]);
}