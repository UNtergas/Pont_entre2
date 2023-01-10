#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        // Erreur lors de la création du processus fils
        perror("Erreur lors de la création du processus fils");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // Code exécuté par le processus fils
        printf("Processus fils : PID = %d, PPID = %d\n", getpid(), getppid());

        // Détachement du processus fils du processus père
        setsid();

        printf("Processus fils : PID = %d, PPID = %d (après détachement)\n", getpid(), getppid());
        sleep(5);
    }
    else
    {
        // Code exécuté par le processus père
        printf("Processus père : PID = %d\n", getpid());
        exit(EXIT_SUCCESS);
    }

    return 0;
}