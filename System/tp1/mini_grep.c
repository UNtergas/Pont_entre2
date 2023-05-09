#include "mini_lib.h"

void _del(char **c)
{
    while (**c == ' ')
    {
        (*c)++;
    }
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
    if (_ptr == NULL)
    {
        mini_printf("file '");
        mini_printf(file);
        mini_printf("' ");
        mini_perror("error");
        exit(1);
    }
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

int main(int argc, char **argv)
{
    if (argc < 3 || argc > 4)
    {
        mini_printf("too many or too few argument");
        exit(1);
    }
    mini_grep(argv[1], argv[2]);
}