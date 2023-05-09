#include "mini_lib.h"
#define MAX_ARGS 10

extern char **environ;
void env_equivalent()
{

    while (*environ)
    {
        printf("\n%s", *environ);
        environ++;
    }
}

char *env_variable(char *nom_variable)
{

    while (*environ)
    {

        char *s = *environ;

        char nom_s[100] = "";

        while (*s != '=')
        {

            strncat(nom_s, s, 1);
            s++;
        }

        // Comparision
        if (strcmp(nom_s, nom_variable) == 0)
        {
            return s;
        }
        environ++;
    }
}
static void prompt()
{
    mini_printf("-------------------mini_shell----------------------------\n");
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
void remove_enter(char *str)
{
    int count;
    for (count = 0; count < mini_strlen(str); count++)
    {
        if (str[count] == '\n')
        {
            str[count] = '\0';
            break;
        }
    }
}

int input_traitment(char *input, char **args)
{
    remove_enter(input);
    int _len_args = 0;
    int _no_args = 0;
    for (int i = 0; i < mini_strlen(input); i++)
    {
        if (input[i] == ' ')
        {
            args[_no_args][_len_args] = '\0';
            // printf("args %s no %d \n", args[_no_args], _no_args);
            _no_args++;
            _len_args = 0;
        }
        else if (input[i] == '\n')
        {
            args[_no_args][_len_args] = '\0';
            _no_args++;
            break;
        }
        else
        {
            args[_no_args][_len_args] = input[i];
            _len_args++;
        }
    }
    args[_no_args + 1] = NULL;
    return _no_args;
}

void exec(char **input)
{
    if (strcmp(input[0], "exit") == 0)
    {
        mini_printf("quiting shell\n");
        exit(0);
    }
    pid_t process = fork();
    if (process == 0)
    {
        // child

        char *_fichier = mini_calloc(sizeof(char), BUF_SIZE);
        _fichier[0] = '.';
        _fichier[1] = '/';
        for (int i = 0; i < strlen(input[0]); i++)
        {

            _fichier[i + 2] = input[0][i];
        }
        _fichier[strlen(input[0]) + 2] = '\0';
        mini_strcpy(_fichier, input[0]);
        // printf("%s\n", input[0]);
        if (strcmp(input[0], "./mini_cd") == 0)
        {
            if (chdir(input[1]) == -1)
            {
                mini_perror("chdir");
                exit(0);
            }
        }
        else if (strcmp(input[0], "./mini_env") == 0)
        {
            env_equivalent();
        }
        else if (strcmp(input[0], "./mini_getenv") == 0)
        {
            if (input[1] == NULL)
            {
                mini_perror("argument error in mini_getenv");
                exit(1);
            }
            if (env_variable(input[1]) != NULL)
            {
                mini_printf(env_variable(input[1]));
                mini_printf("\n");
            }
        }
        else if (strcmp(input[0], "./") != 0)
        {
            int status = execvp(input[0], input);
            if (status == -1)
            {
                mini_perror("command not found");
            }
        }

        exit(0);
    }
    else
    {
        wait(NULL);
    }
}
int main()
{
    prompt();
    while (true)
    {
        char cwd[BUF_SIZE];
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            mini_perror("dir ");
            exit(0);
        }
        mini_printf(cwd);
        char *buffer = mini_calloc(1, BUF_SIZE);
        char **args = mini_calloc(sizeof(char *), MAX_ARGS);
        for (int i = 0; i < MAX_ARGS; i++)
        {
            args[i] = mini_calloc(1, BUF_SIZE);
        }
        mini_scanf(buffer, BUF_SIZE);
        input_traitment(buffer, args);
        exec(args);
        mini_free(buffer);
    }
    exit(0);
}
