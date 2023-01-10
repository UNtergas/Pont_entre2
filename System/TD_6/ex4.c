#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    // Créer le processus fils
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Error creating child process");
        return 1;
    }

    if (pid == 0)
    {
        // Processus fils
        // Pause de 2 secondes
        printf("%d procs\n", getpid());
        sleep(2);
    }
    else
    {
        // Processus père
        // Attendre la fin du processus fils
        pid_t t = waitpid(pid, NULL, 0);
        printf("Child process %d,has finished\n", t);
    }

    return 0;
}
