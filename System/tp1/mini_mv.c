#include "mini_lib.h"

int main(int argc, char *argv[])
{
    if (argc < 3 || argc > 4)
    {
        mini_printf("too many or too much arguments");
        exit(1);
    }
    char *src = argv[1];
    char *dest = argv[2];

    int a = link(src, dest);
    if (a == -1)
    {
        mini_perror("erro link");
        exit(1);
    }

    a = unlink(src);
    if (a == -1)
    {
        mini_perror(" errordeleting ");
        exit(1);
    }
}