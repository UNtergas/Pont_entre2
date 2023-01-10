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

int line_occurence(char *line, char *keyword)
{
    char *temp = mini_calloc(1, BUF_SIZE);
    mini_strncpy(line, temp, mini_strlen(line));
    int flag = 0;
    while (line[flag] != '\n' && line[flag] != '\0')
    {

        int count = 0;
        while (temp[count] != ' ' && temp[count] != '\0' && temp[count] != '\n')
        {
            count++;
            flag++;
        }
        char mots[20];
        mini_strncpy(temp, mots, count);
        if (mini_strcmp(mots, keyword) == 0)
        {
            return 1;
        }
        else
        {
            temp += count;
            _del(&temp);
        }
    }
    return 0;
}
void mini_grep(char *file, char *keyword)
{
    MYFILE *_ptr = mini_open(file, OPEN_READ);
    char *_buf = mini_calloc(1, IOBUFFER_SIZE);
    mini_fread(_buf, 1, IOBUFFER_SIZE, _ptr);
    int _count_saut = 0;
    for (int i = 0; _buf[i] != '\0'; i++)
    {
        if (_buf[i] == '\n')
            _count_saut++;
    }
    while (_count_saut >= 0)
    {

        char temp[BUF_SIZE];
        int flag = 0;
        while (_buf[flag] != '\n' && _buf[flag] != '\0')
        {
            flag++;
        }

        mini_strncpy(_buf, temp, flag);
        if (line_occurence(temp, keyword) == 1)
        {

            mini_printf(temp);
            write(1, "\n", 1);
        }
        _buf = _buf + 1 + flag;
        _del(&_buf);
        _count_saut--;
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