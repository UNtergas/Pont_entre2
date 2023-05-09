#include <unistd.h>

int main()
{
    char *argv[] = {"ls", "-l", "/tmp", NULL};
    execve("/bin/ls", argv, NULL);
    return 0;
}