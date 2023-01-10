#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    pid_t status;

    printf("processus pere id:%d\n", getpid());
    status = fork();
    switch (status)
    {
    case -1:
        perror("creation fils");
        exit(EXIT_FAILURE);
    case 0:
        printf("jsuis fils id%d, avec pere id:%d\n", getpid(), getppid());
        break;
    default:
        printf("jsuis pere %d,mon  fils %d\n", getpid(), status);
        break;
    }
    printf("%d termine\n", getpid());
    return 0;
}