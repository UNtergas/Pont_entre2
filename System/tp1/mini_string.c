#include "mini_lib.h"

char *buffer;
int ind = -1;

void mini_printf(char *msg)
{
    if (ind == -1)
    {
        buffer = mini_malloc(sizeof(char) * BUF_SIZE);
        // buffer = calloc(BUF_SIZE, sizeof(char));
        if (!buffer)
        {
            mini_perror("buffer vide");
            mini_exit();
        }
    }
    ind = 0;
    for (int i = 0; i < mini_strlen(msg) + 1; i++)
    {
        if (ind >= BUF_SIZE)
        {
            if (write(1, buffer, ind) == -1)
                mini_perror("max");
            ind = -1;
            mini_free(buffer);
        }
        else if (msg[i] == '\n')
        {
            if (write(1, buffer, ind) == -1)
                mini_perror("max");
            write(1, "\n", 1);
            if (msg[i + 1] != '\0')
                mini_printf(msg + i + 1);
            break;
        }
        else if (msg[i] == '\0')
        {
            if (write(1, buffer, ind) == -1)
                mini_perror("max");
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
int mini_strncpy(char *s, char *d, int size)
{
    if (!d)
    {
        return -1;
    }
    int i = 0;
    while (*s != '\0' && i < size)
    {
        *d = *s;
        d++;
        s++;
        i++;
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
    int i = 0;
    while (i < mini_strlen(s1) && s1[i] != '\0' && s1[i] != '\0')
    {
        if (s1[i] != s2[i])
            return -1;
        i++;
    }

    return 0;
}
char *mini_itoa(int a)
{
    int digits = 0;
    int _a = a;
    while (_a != 0)
    {
        _a = _a / 10;
        digits++;
    }
    char *returning = mini_calloc(sizeof(char), (digits + 1));
    // char *returning = calloc(1, digits + 1);
    *(returning + digits) = '\0';
    for (int i = 0; a != 0; i++)
    {
        int temp = a % 10;
        *(returning + digits - (i + 1)) = (char)(temp + 48);
        a = a / 10;
    }
    return returning;
}
void mini_perror(char *message)
{
    char temp[4];
    mini_strncpy(mini_itoa(errno), temp, 4);
    mini_printf(message);
    mini_printf(temp);
    write(1, "\n", 1);
}