#include "mini_lib.h"

int main(int argc, char **argv)
{
    MYFILE *_file = mini_open(argv[1], OPEN_WRITE);
    mini_fclose(_file);
    mini_exit();
}
