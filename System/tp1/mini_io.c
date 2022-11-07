#include "mini_lib.h"
MYFILE *file_ptr_constructor()
{
    MYFILE *_ptr = mini_calloc(sizeof(MYFILE), 1);
    _ptr->ind_read = -1;
    _ptr->ind_write = -1;
    _ptr->buffer_read = malloc(sizeof(char));
    _ptr->buffer_write = malloc(sizeof(char));
    _ptr->fd = -1;
    return _ptr;
}
MYFILE *mini_open(char *file, char mode)
{
    MYFILE *open_ptr = file_ptr_constructor();
    switch (mode)
    {
    case OPEN_READ:
    {
        open_ptr->fd = open(file, O_RDONLY);
        if (open_ptr->fd == -1)
        {
            mini_perror("cant open");
            return NULL;
        }

        return open_ptr;
    }
    case OPEN_RW:
    {
        open_ptr->fd = open(file, O_RDWR);
        if (open_ptr->fd == -1)
        {
            mini_perror("cant open");
            return NULL;
        }

        return open_ptr;
    }
    case OPEN_WRITE:
    {
        open_ptr->fd = open(file, O_WRONLY);
        if (open_ptr->fd == -1)
        {
            mini_perror("cant open");
            return NULL;
        }
        return open_ptr;
    }
    case OPEN_ADD_END:
    {
        open_ptr->fd = open(file, O_WRONLY);
        if (open_ptr->fd == -1)
        {
            mini_perror("cant open");
            return NULL;
        }
        return open_ptr;
    }
    default:
        mini_printf("invalid mode input\n");
        break;
    }
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
        // file->buffer_read = mini_calloc(size_element, IOBUFFER_SIZE);
        file->buffer_read = (char *)malloc(10 * sizeof(char));
        file->ind_read = 0;
    }
    // mini_printf("here\n");
    if (file->ind_read >= IOBUFFER_SIZE)
    {
        if (read(file->fd, (char *)file->buffer_read, IOBUFFER_SIZE - 1) == -1)
            mini_perror("cant read");
        *((char *)file->buffer_read + IOBUFFER_SIZE) = '\0';
        return IOBUFFER_SIZE;
    }
    else if (file->ind_read == mini_strlen(file->buffer_read))
    {
        file->ind_read = read(file->fd, (char *)file->buffer_read, IOBUFFER_SIZE);
        *((char *)file->buffer_read + file->fd) = '\0';
        mini_printf(file->buffer_read);
    }
    int count = 0;
    for (int i = 0; i < number_element; i++)
    {
        *((char *)buffer + i) = *((char *)file->buffer_read + i);
        count++;
    }
    *((char *)buffer + count) = '\0';
    return count;
}
