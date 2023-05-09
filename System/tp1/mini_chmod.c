#include "mini_lib.h"

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (strlen(argv[1]) > 3)
        {
            mini_printf("command chmod: ");
            mini_printf(argv[1]);
            mini_printf(" unknown");
            exit(EXIT_FAILURE);
        }

        if (chmod(argv[2], (mode_t)atoi(argv[1])) < 0)
        {
            mini_perror("error chmod");
            exit(1);
        }
        // mini_free(permission);
    }
    else
    {
        mini_printf("insufficent argument for chmods\n");
    }
    mini_exit();
}