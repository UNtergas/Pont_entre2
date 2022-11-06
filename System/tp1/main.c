#include "mini_lib.h"
#include <stdio.h>

void test_memoire()
{
    puts("test");
    // int *tmp = mini_malloc(4 * sizeof(int));
    int *tmp = mini_calloc(sizeof(int), 3);
    for (int i = 0; i < 3; i++)
    {
        printf("\t%d", *(tmp + i));
    }
    for (int i = 0; i < 3; i++)
    {
        *(tmp + i) = i;
    }
    for (int i = 0; i < 3; i++)
    {
        printf("\t%d", *(tmp + i));
    }
    puts("-");
}
void test_chaine_carac()
{
    puts("");
    mini_printf("test abc");
    puts("");
    char haidang;
    printf("\t%d\t", mini_scanf(&haidang, BUF_SIZE));
    // printf("%s", haidang);
    puts("");
}
int main(int argc, char **argv)
{
    // test_memoire();
    test_chaine_carac();
    mini_exit();
}