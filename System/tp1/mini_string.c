#include "mini_lib.h"

static char *buffer;
static int ind = -1;

void mini_printf(char *msg)
{
    if (ind == -1)
    {
        buffer = mini_calloc(sizeof(char), BUF_SIZE);
        // buffer = calloc(BUF_SIZE, sizeof(char));
        if (!buffer)
        {
            strerror("buffer vide");
            mini_exit();
        }
        ind = 0;
    }
    for (int i = 0; i < mini_strlen(msg) + 1; i++)
    {
        if (ind >= BUF_SIZE || msg[i] == '\n')
        {
            if (write(1, buffer, ind) == -1)
                strerror("max");
            ind = -1;
            mini_free(buffer);
        }
        else if (msg[i] == '\0')
        {
            if (write(1, buffer, ind) == -1)
                strerror("max");
            ind = -1;
            mini_free(buffer);
        }
        else
        {
            buffer[ind] = msg[i];
            ind++;
        }
    }
}
int mini_scanf(char *buffer, int size_buffer)
{
    int cara_lus = 0;
    write(STDOUT_FILENO, ">>", 2);
    if (read(STDIN_FILENO, buffer, size_buffer) == -1)
        return -1;
    for (int i = 0; i < mini_strlen(buffer) + 1; i++)
    {
        if (buffer[i] == '\0')
        {
            write(1, buffer, cara_lus);
            return cara_lus;
        }
        else
        {
            cara_lus++;
        }
    }
}
int mini_strlen(char *s)
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}