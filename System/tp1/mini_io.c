#include "mini_lib.h"

int __read_count = 0;
MYFILE *__list_file = NULL;

MYFILE *file_ptr_constructor()
{
    MYFILE *_ptr = mini_calloc(sizeof(MYFILE), 1);
    _ptr->ind_read = -1;
    _ptr->ind_write = -1;
    _ptr->buffer_read = NULL;
    _ptr->buffer_write = NULL;
    _ptr->fd = -1;
    _ptr->next_file = NULL;
    return _ptr;
}

MYFILE *mini_open(char *file, char mode)
{
    int _flag;
    switch (mode)
    {
    case OPEN_READ:
    {
        _flag = open(file, O_RDONLY);
        if (_flag == -1)
        {
            mini_perror("cant open:");
            return NULL;
        }

        break;
    }
    case CREAT_DEL:
    {
        _flag = open(file, O_CREAT | O_TRUNC, 0777);
        if (_flag == -1)
        {
            mini_perror("cant open:");
            return NULL;
        }

        break;
    }
    case OPEN_RW:
    {
        _flag = open(file, O_RDWR | O_CREAT, 0777);
        if (_flag == -1)
        {
            mini_perror("cant open:");
            return NULL;
        }

        break;
    }
    case OPEN_WRITE:
    {
        _flag = open(file, O_WRONLY | O_CREAT, 0666);
        if (_flag == -1)
        {
            mini_perror("cant open:");
            return NULL;
        }

        break;
    }
    case OPEN_ADD_END:
    {
        _flag = open(file, O_APPEND | O_CREAT, 0777);
        if (_flag == -1)
        {
            mini_perror("cant open:");
            return NULL;
        }

        break;
    }
    default:
        mini_printf("invalid mode input\n");
        break;
    }
    MYFILE *_ptr = file_ptr_constructor();
    _ptr->fd = _flag;
    if (!__list_file)
    {
        __list_file = _ptr;
    }
    else
    {
        MYFILE *temp = __list_file;
        _ptr->next_file = temp;
        __list_file = _ptr;
    }
    return _ptr;
}

int mini_fread(void *buffer, int size_element, int number_element, MYFILE *file)
{
    if (!file)
    {
        mini_perror("file NULL:");
        return -1;
    }
    if (file->ind_read == -1)
    {
        file->buffer_read = mini_calloc(IOBUFFER_SIZE, 1);

        file->ind_read = 0;
    }
    else if (file->ind_read >= IOBUFFER_SIZE)
    {
        file->ind_read = 0;
    }
    if (file->ind_read == 0 || file->ind_read == __read_count)
    {
        int _count = read(file->fd, (char *)file->buffer_read, IOBUFFER_SIZE);
        if (_count == -1)
            mini_perror("cant read:code:");
        __read_count += _count;
        *((char *)file->buffer_read + file->ind_read + _count + 1) = '\0';
    }
    int _flag = 0;
    while (_flag < number_element && *((char *)file->buffer_read + file->ind_read) != '\0')
    {

        *((char *)buffer + _flag) = *((char *)file->buffer_read + file->ind_read);
        file->ind_read++;
        _flag++;
    }
    *((char *)buffer + _flag) = '\0';

    return _flag;
}
int mini_fwrite(void *buffer, int size_element, int number_element, MYFILE *file)
{
    if (!file)
    {
        mini_perror("file Null:");
        return -1;
    }
    if (file->ind_write == -1)
    {
        file->buffer_write = mini_calloc(IOBUFFER_SIZE, 1);
        file->ind_write = 0;
    }

    int _flag = 0;

    while (_flag < number_element && *((char *)buffer + file->ind_write) != '\0')
    {

        *((char *)(file->buffer_write + file->ind_write)) = *((char *)(buffer + _flag));
        file->ind_write++;
        _flag++;
    }
    *((char *)file->buffer_write + _flag) = '\0';
    if (file->ind_write >= IOBUFFER_SIZE)
    {
        int __count_fwrite = write(file->fd, (char *)file->buffer_write, file->ind_write);
        if (__count_fwrite == -1)
        {
            mini_perror("cant write:code:");
            return -1;
        }
    }
    return _flag;
}
int mini_fflush(MYFILE *file)
{
    if (!file->buffer_write)
        return -1;
    int __count_fwrite;
    if (file->ind_write != -1)
    {
        __count_fwrite = write(file->fd, (char *)file->buffer_write, file->ind_write);
        if (__count_fwrite == -1)
            mini_perror("cant write here:code:");
    }
    file->ind_write = 0;
    return __count_fwrite;
}

int mini_fclose(MYFILE *file)
{
    mini_fflush(file);
    int __close_idx = close(file->fd);
    if (__close_idx == -1)
    {
        mini_perror("error close,code:");
        return -1;
    }
    if (__list_file == file)
    {
        __list_file = __list_file->next_file;
    }
    else
    {

        MYFILE *_last = __list_file;
        while (_last)
        {
            if (_last->next_file == file)
            {
                _last->next_file = _last->next_file->next_file;
            }
            else
            {
                _last = _last->next_file;
            }
        }
    }

    mini_free(file);
    return 0;
}

int mini_fgetc(MYFILE *file)
{
    char *_char_ptr = mini_calloc(4, 1);
    mini_fread(_char_ptr, 1, 1, file);
    mini_printf(_char_ptr);
    char _char = *_char_ptr;
    return (int)_char;
}

int mini_fputc(MYFILE *file, char c)
{
    char a[1];
    a[0] = c;

    if (mini_fwrite(a, 1, 1, file) == -1)
    {
        mini_perror("error fputc:code>");
    }
    return 1;
}
