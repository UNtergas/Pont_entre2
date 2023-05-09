#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
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
        printf("\nProcessus fils : PID = %d, PPID = %d\n", getpid(), getppid());
        execvp(argv[1], argv + 1);
        exit(0);
    }
    else
    {
        // Code exécuté par le processus père
        printf("\nnProcessus père : PID = %d\n", getpid());
    }
    wait(NULL);
    printf("\npromtp\n");
    return 0;
}