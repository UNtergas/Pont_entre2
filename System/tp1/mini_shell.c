#include "mini_lib.h"

static void promt()
{
    mini_printf("************************************************************************\n");
    mini_printf("**                            MINI SHELLL                             **\n");
    mini_printf("************************************************************************\n");
    mini_printf("**                         TO EXIT MINI SHELL                         **\n");
    mini_printf("**     type >> exit                OR             press CTRL+D        **\n");
    mini_printf("************************************************************************\n");
    mini_printf("**                         available command                          **\n");
    mini_printf("**--------------------------------------------------------------------**\n");
    mini_printf("-- 1 argument function |                                              --\n");
    mini_printf("-----------------------|                                              --\n");
    mini_printf("--         >>touch file                     >>cat file                --\n");
    mini_printf("--  >>echo command            >>clean file               >>wc file    --\n");
    mini_printf("------------------------------------------------------------------------\n");
    mini_printf("-- multiple argument function|                                        --\n");
    mini_printf("-----------------------------|                                        --\n");
    mini_printf("--  >>grep file keyword                      >>cp src dest            --\n");
    mini_printf("--  >>head file                              >>tail file              --\n");
    mini_printf("--  >>head -n file                           >>tail -n file           --\n");
    mini_printf("************************************************************************\n");
}

void remove_spaces(char *str)
{

    int count = 0;

    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] != ' ')
            str[count++] = str[i];
    str[count] = '\0';
}
void _del(char **c)
{
    while (**c == ' ')
    {
        (*c)++;
    }
}
static void run_case(char *c)
{

    char _command[4][50];
    int _count = 0;
    _del(&c);
    for (int i = 0; c[i] != ' ' && c[i] != '\0' && c[i] != '\n'; i++)
    {
        _count++;
    }
    mini_strncpy(c, _command[0], _count);
    remove_spaces(_command[0]);
    c += _count;
    _del(&c);
    if (mini_strcmp(_command[0], "cat") == 0 || mini_strcmp(_command[0], "echo") == 0 || mini_strcmp(_command[0], "touch") == 0 || mini_strcmp(_command[0], "clean") == 0 || mini_strcmp(_command[0], "wc") == 0)
    {
        _count = 0;
        for (int i = 0; c[i] != '\0' && c[i] != '\n'; i++)
        {
            _count++;
        }
        mini_strncpy(c, _command[1], _count);
        if (mini_strcmp(_command[0], "echo") != 0)
            remove_spaces(_command[1]);
    }
    else if (mini_strcmp(_command[0], "cp") == 0 || mini_strcmp(_command[0], "grep") == 0)
    {
        _count = 0;
        for (int i = 0; c[i] != ' ' && c[i] != '\0' && c[i] != '\n'; i++)
        {
            _count++;
        }
        mini_strncpy(c, _command[1], _count);
        remove_spaces(_command[1]);
        c += _count;
        _del(&c);
        _count = 0;
        for (int i = 0; c[i] != ' ' && c[i] != '\0' && c[i] != '\n'; i++)
        {
            _count++;
        }
        mini_strncpy(c, _command[2], _count);
        remove_spaces(_command[2]);
    }
    else if (mini_strcmp(_command[0], "head") == 0 || mini_strcmp(_command[0], "tail") == 0)
    {
        _count = 0;
        for (int i = 0; c[i] != ' ' && c[i] != '\0' && c[i] != '\n'; i++)
        {
            _count++;
        }
        mini_strncpy(c, _command[1], _count);
        remove_spaces(_command[1]);
        if (mini_strcmp(_command[1], "-n") == 0)
        {
            if (mini_strlen(_command[1]) > 2)
            {
                int _gap = mini_strlen(_command[1]);
                char *temp = mini_calloc(1, _gap + 1);
                mini_strncpy(_command[1], temp, _gap);
                temp += 2;
                mini_strncpy(temp, _command[2], _gap - 2);
            }
            else
            {
                c += _count;
                _del(&c);
                _count = 0;
                for (int i = 0; c[i] != ' ' && c[i] != '\0' && c[i] != '\n'; i++)
                {
                    _count++;
                }
                mini_strncpy(c, _command[2], _count);
                remove_spaces(_command[2]);
            }
            c += _count;
            _del(&c);
            _count = 0;
            for (int i = 0; c[i] != ' ' && c[i] != '\0' && c[i] != '\n'; i++)
            {
                _count++;
            }
            mini_strncpy(c, _command[3], _count);
            remove_spaces(_command[3]);
        }
        else
        {

            _count = 0;
            for (int i = 0; c[i] != '\0' && c[i] != '\n'; i++)
            {
                _count++;
            }
            mini_strncpy(c, _command[3], _count);
            mini_strncpy("-1", _command[2], 2);
            // }
        }
    }

    if (mini_strcmp(_command[0], "cat") == 0)
        *c = '1';
    if (mini_strcmp(_command[0], "echo") == 0)
        *c = '2';
    if (mini_strcmp(_command[0], "cp") == 0)
        *c = '3';
    if (mini_strcmp(_command[0], "clean") == 0)
        *c = '4';
    if (mini_strcmp(_command[0], "wc") == 0)
        *c = '5';
    if (mini_strcmp(_command[0], "touch") == 0)
        *c = '6';
    if (mini_strcmp(_command[0], "head") == 0)
        *c = '7';
    if (mini_strcmp(_command[0], "tail") == 0)
        *c = '8';
    if (mini_strcmp(_command[0], "grep") == 0)
        *c = '9';
    switch (*c)
    {

    case '1':
        mini_cat(_command[1]);
        break;
    case '2':
        mini_echo(_command[1]);
        break;
    case '3':
        mini_cp(_command[1], _command[2]);
    case '4':
        mini_clean(_command[1]);
        break;
    case '5':
        mini_wc(_command[1]);
        break;
    case '6':
        mini_touch(_command[1]);
        break;
    case '7':
        if (atoi(_command[2]) == -1)
        {
            mini_cat(_command[3]);
        }
        mini_head(atoi(_command[2]), _command[3]);
        break;
    case '8':
        if (atoi(_command[2]) == -1)
        {
            mini_cat(_command[3]);
        }
        mini_tail(atoi(_command[2]), _command[3]);
        break;
    case '9':

        mini_grep(_command[1], _command[2]);
        break;
    case ' ':
    case '\t':
        break;
    case '\n':
        write(1, "\n", 1);
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
        char *a = mini_calloc(1, BUF_SIZE);
        mini_scanf(a, BUF_SIZE);
        if (mini_strcmp(a, "exit") == 0)
        {
            mini_printf("quiting shell\n");
            break;
        }
        int _id = fork();
        if (_id == 0)
        {
            run_case(a);
            mini_free(a);
            mini_exit();
        }
        else
        {
            wait(NULL);
        }
        mini_free(a);
    }
    mini_exit();
}