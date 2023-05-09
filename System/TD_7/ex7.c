#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <string.h>
int main()
{

    char command[50];
    char first_word[50];
    pid_t status;
    status = fork();
    while (1)
    {
        printf(">>");
        fgets(command, sizeof(command), stdin);
        if (strncmp(command, "exit", 4) == 0)
        {
            break;
        }
        status = fork();
        if (status == 0)
        {
            int i = 0;
            while (command[i] != ' ' && command[i] != '\0')
            {
                first_word[i] = command[i];
                i++;
            }
            first_word[i] = '\0';
            printf("frist%s", first_word);
            char *subString = strstr(command, first_word);
            printf("next::%s", subString);
            execvp(first_word, subString);
        }
        else
        {
            wait(NULL);
        }
    }
    printf("ending");
    exit(0);
}