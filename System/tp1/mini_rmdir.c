#include "mini_lib.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        mini_printf("insufficant argument for mkdir");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            int status;
            status = rmdir(argv[i]);
            if (errno == 2)
            {
                mini_printf("failed to delete directory '");
                mini_printf(argv[i]);
                mini_printf("': Folder dont exist\n");
            }
            else if (errno == 20)
            {
                mini_printf("failed to delete '");
                mini_printf(argv[i]);
                mini_printf("': Not a folder\n");
            }
            else if (status == -1)
            {
                mini_perror("errormkdir");
            }
        }
    }
}