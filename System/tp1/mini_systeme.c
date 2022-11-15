#include "mini_lib.h"

void mini_touch(char *file)
{
    MYFILE *_file = mini_open(file, OPEN_WRITE);
    mini_fclose(_file);
}

void mini_cp(char *src, char *dest)
{
    if (mini_strcmp(src, dest) == 0)
    {
        mini_printf("src et dest sont les meme\n");
    }
    MYFILE *_src_ptr = mini_open(src, OPEN_READ);
    MYFILE *_dest_ptr = mini_open(dest, OPEN_WRITE);
    char buffer[2000];
    int _count = mini_fread(buffer, 1, 2000, _src_ptr);
    mini_fwrite(buffer, 1, _count, _dest_ptr);
    mini_fclose(_dest_ptr);
    mini_fclose(_src_ptr);
}

void mini_echo(char *chaine)
{
    mini_printf(chaine);
    write(1, "\n", 1);
}

void mini_cat(char *_file)
{
    MYFILE *_ptr = mini_open(_file, OPEN_READ);
    char buffer[IOBUFFER_SIZE];
    mini_fread(buffer, 1, IOBUFFER_SIZE, _ptr);
    mini_printf(buffer);
    write(1, "\n", 1);
    mini_fclose(_ptr);
}

void mini_head(int n, char *_file)
{
    MYFILE *_ptr = mini_open(_file, OPEN_READ);
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

void mini_tail(int n, char *_file)
{
    MYFILE *_ptr = mini_open(_file, OPEN_READ);
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
void mini_clean(char *file)
{
    MYFILE *_file = mini_open(file, CREAT_DEL);
    mini_fclose(_file);
}

void mini_grep(char *file, char *keyword)
{
    MYFILE *_ptr = mini_open(file, OPEN_READ);
    char *_buf = mini_calloc(1, IOBUFFER_SIZE);
    mini_fread(_buf, 1, IOBUFFER_SIZE, _ptr);
    int _count_saut = 1;
    for (int i = 0; _buf[i] != '\0'; i++)
    {
        if (_buf[i] == '\n')
            _count_saut++;
    }
    //
    while (_count_saut > 0)
    {
        int _count = 0;
        for (int i = 0; _buf[i] != '\n' && _buf[i] != '\0'; i++)
        {
            _count++;
        }
        char _line[_count];
        char *temp = mini_calloc(1, _count);
        mini_strncpy(_buf, temp, _count);
        mini_strncpy(_buf, _line, _count);
        int _parcour = 0;
        while (_line[_parcour] != '\0' && *temp != '\0')
        {
            int _wwc = 0;
            for (int i = 0; temp[i] != ' ' && temp[i] != '\0'; i++)
            {
                _wwc++;
                _parcour++;
            }
            char *_mot = mini_calloc(1, _wwc);
            mini_strncpy(temp, _mot, _wwc);
            remove_spaces(_mot);
            if (mini_strcmp(_mot, keyword) == 0)
            {

                mini_printf(_line);
                write(1, "\n", 1);
                break;
            }
            else
            {
                temp = temp + _wwc;
                int c = 0;
                while (temp[c] == ' ')
                {
                    temp++;
                }
            }
            mini_free(_mot);
        }
        //
        mini_free(temp);
        _count_saut--;
        _buf = _buf + _count + 1;
    }
    mini_fclose(_ptr);
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