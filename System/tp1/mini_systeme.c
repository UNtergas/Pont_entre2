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
char *interaction_ligne(char *_buf, MYFILE *_ptr)
{
    while (*(_buf + _ptr->ind_read) != '\n' && *(_buf + _ptr->ind_read) != '\0')
    {
        _ptr->ind_read += 1;
    }

    printf("%d\n", _ptr->ind_read);
    char *temp = mini_calloc(1, _ptr->ind_read);
    mini_strncpy(_buf, temp, _ptr->ind_read);
    return temp;
}
void mini_head(int n, char *_file)
{
    MYFILE *_ptr = mini_open(_file, OPEN_READ);
    char _buf[IOBUFFER_SIZE];
    mini_fread(_buf, 1, IOBUFFER_SIZE, _ptr);
    mini_fseek_read(_ptr, 0, SEEK_SET);
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
    write(1, "\n", 1);
    mini_fclose(_ptr);
}
void mini_tail(int n, char *_file)
{
}
void mini_clean(char *file)
{
    MYFILE *_file = mini_open(file, CREAT_DEL);
    mini_fclose(_file);
}
void mini_grep(char *file, char *keyword)
{
    MYFILE *_ptr = mini_open(file, OPEN_READ);
    char _buf[IOBUFFER_SIZE];
    mini_fread(_buf, 1, IOBUFFER_SIZE, _ptr);
}
void mini_wc(char *file)
{
    MYFILE *_ptr = mini_open(file, OPEN_READ);
    char _buf[IOBUFFER_SIZE];
    int _count = mini_fread(_buf, 1, IOBUFFER_SIZE, _ptr);
    char temp[IOBUFFER_SIZE];
    mini_strncpy(mini_itoa(_count), temp, IOBUFFER_SIZE);
    mini_printf(temp);
    write(1, "\n", 1);
}