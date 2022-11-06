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
    char haidang[10];
    printf("\t%d\t", mini_scanf(&haidang, BUF_SIZE));
    mini_printf(haidang);
    char a[25];
    char b[] = "aiosima";
    char c[] = "aiosima";
    printf("%d %d\n", mini_strcmp(b, c), mini_strcpy(b, a));
    mini_printf(a);
    puts("");
}
int main(int argc, char **argv)
{
    // test_memoire();
    test_chaine_carac();
    mini_exit();
}