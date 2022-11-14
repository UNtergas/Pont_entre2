#include "mini_lib.h"

static void promt()
{
    mini_printf("************************************\n");
    mini_printf("*************MINI SHELLL************\n");
    mini_printf("************************************\n");
}
void remove_spaces(char *s)
{
    char *d = s;
    do
    {
        while (*d == ' ')
        {
            ++d;
        }
    } while (*s++ = *d++);
}

void run_case(char *c)
{
    char *_command = mini_calloc(1, 20);
    char *_arg = mini_calloc(1, 20);
    char *_arg_2 = mini_calloc(1, 20);
    int _flag = 0;
    int _flag_2 = mini_strlen(c) - 1;
    while (c[_flag] != ' ')
    {
        _flag++;
    }
    mini_strncpy(c, _command, _flag);
    c += _flag;
    if (mini_strcmp(_command, "cp") == 0)
    {
        while (*c == ' ')
        {
            c++;
        }
        mini_printf(c);
        int _count = 0;
        while (c[_count] != ' ')
        {
            _count++;
        }

        mini_strncpy(c, _arg, _count);
        remove_spaces(_arg);
        c += _count;
        mini_strncpy(c, _arg_2, _flag_2 - _flag - _count);
        remove_spaces(_arg_2);
    }
    else
    {
        mini_strncpy(c, _arg, _flag_2 - _flag);
        remove_spaces(_arg);
    }

    if (mini_strcmp(_command, "cat") == 0)
        *c = '1';
    if (mini_strcmp(_command, "echo") == 0)
        *c = '2';
    if (mini_strcmp(_command, "cp") == 0)
        *c = '3';
    if (mini_strcmp(_command, "clean") == 0)
        *c = '4';
    if (mini_strcmp(_command, "wc") == 0)
        *c = '5';
    switch (*c)
    {

    case '1':
        mini_cat(_arg);
        break;
    case '2':
        mini_echo(_arg);
        break;
    case '3':
        mini_cp(_arg, _arg_2);
    case '4':
        mini_clean(_arg);
        break;
    case '5':
        mini_wc(_arg);
        break;
    case ' ':
    case '\t':
        break;
    case '\n':
        write(1, (char *)'\n', 1);
        break;
    default:
        mini_printf("try again\n");
        break;
    }
}

int main()
{
    promt();
    while (true)
    {
        char a[10];
        mini_scanf(a, BUF_SIZE);
        if (mini_strcmp(a, "exit") == 0)
        {
            mini_printf("quiting shell\n");
            break;
        }
        // int _id = fork();
        // if (_id == 0)
        // {
        run_case(a);
        // }
        // else
        // {
        //     wait(NULL);
        // }
    }
    mini_exit();
}