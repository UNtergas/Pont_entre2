#include "mini_lib.h"
int __read_count = 0;
int __write_count = 0;
MYFILE *file_ptr_constructor()
{
    MYFILE *_ptr = mini_calloc(sizeof(MYFILE), 1);
    _ptr->ind_read = -1;
    _ptr->ind_write = -1;
    _ptr->buffer_read = NULL;
    _ptr->buffer_write = NULL;
    _ptr->fd = -1;
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
            mini_perror("cant open");
            return NULL;
        }

        // return _flag;
        break;
    }
    case OPEN_RW:
    {
        _flag = open(file, O_RDWR | O_CREAT, 0777);
        if (_flag == -1)
        {
            mini_perror("cant open");
            return NULL;
        }

        // return _flag;
        break;
    }
    case OPEN_WRITE:
    {
        _flag = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        if (_flag == -1)
        {
            mini_perror("cant open");
            return NULL;
        }
        // return _flag;
        break;
    }
    case OPEN_ADD_END:
    {
        _flag = open(file, O_APPEND | O_CREAT, 0777);
        if (_flag == -1)
        {
            mini_perror("cant open");
            return NULL;
        }
        // return _flag;
        break;
    }
    default:
        mini_printf("invalid mode input\n");
        break;
    }
    // MYFILE *_ptr = mini_calloc(sizeof(MYFILE), 1);
    // _ptr->ind_read = -1;
    // _ptr->ind_write = -1;
    // _ptr->buffer_read = NULL;
    // _ptr->buffer_write = NULL;
    MYFILE *_ptr = file_ptr_constructor();
    _ptr->fd = _flag;
    return _ptr;
}

int mini_fread(void *buffer, int size_element, int number_element, MYFILE *file)
{
    if (!file)
    {
        mini_perror("file NULL");
        return -1;
    }
    if (file->ind_read == -1)
    {
        file->buffer_read = mini_calloc(IOBUFFER_SIZE, size_element);

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
        mini_perror("file Null");
        return -1;
    }
    if (file->ind_write == -1)
    {
        file->buffer_write = mini_calloc(IOBUFFER_SIZE, size_element);
        printf("mallco\n");
        file->ind_write = 0;
    }
    else if (file->ind_write > IOBUFFER_SIZE)
    {
        file->ind_write = IOBUFFER_SIZE;
    }
    int _flag = 0;
    mini_printf(buffer);
    while (_flag < number_element && *((char *)buffer + file->ind_write) != '\0')
    {
        printf("%d-", _flag);
        *((char *)file->buffer_write + _flag) = *((char *)buffer + file->ind_write);
        file->ind_write++;
        _flag++;
    }
    *((char *)file->buffer_write + _flag) = '\0';
    printf("\n");
    mini_printf(file->buffer_write);
    int __count_fwrite = write(file->fd, (char *)file->buffer_write, _flag);
    if (__count_fwrite == -1)
        mini_perror("cant write:code:");
    return __count_fwrite;
}