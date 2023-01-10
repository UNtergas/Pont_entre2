#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;

    printf("Le processus père commence ici, son PID est %d\n", getpid());

    pid = fork();
    if (pid == 0) {
        // Code exécuté par le fils
        printf("Je suis le fils, mon PID est %d et mon père est %d\n", getpid(), getppid());
    } else {
        // Code exécuté par le père
        printf("Je suis le père, mon PID est %d et mon fils a le PID %d\n", getpid(), pid);
    }

    printf("Le processus père et fils terminent ici\n");

    return 0;
}
