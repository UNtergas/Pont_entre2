#include "mini_lib.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        mini_printf("too less arguments");
        exit(1);
    }
    for (int i = 1; i < argc; i++)
    {
        if (unlink(argv[i]) == -1)
        {
            if (errno == 21)
            {
                mini_printf("'");
                mini_printf(argv[i]);
                mini_printf("' is a directory");
            }
            else
            {
                mini_printf(" errordeleting ");
            }
            continue;
        }
    }
    exit(0);
}