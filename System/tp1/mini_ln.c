#include "mini_lib.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        mini_printf("not enough arguments");
        mini_exit();
    }

    const char *oldpath = argv[1];
    const char *newpath = argv[2];

    if (symlink(oldpath, newpath) != 0)
    {
        mini_perror("syslinkfailed");
        mini_exit();
    }

    return 0;
}
