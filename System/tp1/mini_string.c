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
    int read_result = read(STDIN_FILENO, buffer, size_buffer - 1);
    if (read_result == -1)
        return -1;
    buffer[read_result] = '\0';
    return read_result;
}
int mini_strlen(char *s)
{
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}
int mini_strcpy(char *s, char *d)
{
    if (!d)
    {
        return -1;
    }
    while (*s != '\0')
    {
        *d = *s;
        d++;
        s++;
    }
    *d = '\0';
    return mini_strlen(d);
}
int mini_strcmp(char *s1, char *s2)
{
    if (!s1 || !s2)
    {
        return -1;
    }
    if (mini_strlen(s1) != mini_strlen(s2))
    {
        return -1;
    }
    else
    {
        int i = 0;
        while (i < mini_strlen(s1))
        {
            if (s1[i] != s2[i])
                return -1;
            i++;
        }
    }
    return 0;
}
void mini_perror(char *message)
{
}