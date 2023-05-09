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
            status = mkdir(argv[i], 0777);
            if (errno == 17)
            {
                mini_printf("cannot create directory '");
                mini_printf(argv[i]);
                mini_printf("': Folder already exist\n");
            }
            else if (status == -1)
            {
                mini_perror("errormkdir");
            }
        }
    }
}