#include "mini_lib.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        mini_printf(" \n");
        exit(0);
    }
    for (int i = 1; i < argc; i++)
    {
        mini_printf(argv[i]);
        mini_printf(" ");
    }
    mini_printf("\n");
    exit(0);
}