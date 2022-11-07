#include "mini_lib.h"

void test_memoire()
{
    puts("test");
    // int *tmp = mini_malloc(4 * sizeof(int));
    int *tmp = mini_calloc(sizeof(int), 3);
    for (int i = 0; i < 3; i++)
    {
        printf("%d\n", *(tmp + i));
    }
    for (int i = 0; i < 3; i++)
    {
        *(tmp + i) = i;
    }
    for (int i = 0; i < 3; i++)
    {
        printf("%d\n", *(tmp + i));
    }
    puts("-");
}
void test_chaine_carac()
{
    puts("");
    mini_printf("test\nabc defg\n  ee");
    puts("");
    char haidang[10];
    printf("carac lu:%d\n", mini_scanf(haidang, BUF_SIZE));
    printf("strlen lu%d\n", mini_strlen(haidang));
    mini_printf(haidang);
    char a[3];
    char b[] = "aiosima";
    char c[] = "aios";
    printf("compare> %d %d\n", mini_strcmp(b, c), mini_strncpy(b, a, 3));
    mini_printf(a);
    puts("");
    static FILE *stream;
    stream = fopen("file.txt", "r");
    if (!stream)
        mini_perror("code num:>");
}
void test_io()
{
    static MYFILE *file_ptr;
    file_ptr = mini_open("text.txt", 'r');
    // printf("%d", file_ptr->fd);
    char a[50];
    int a_idx = mini_fread(a, sizeof(char), 10, file_ptr);
    // read(file_ptr->fd, a, 10);
    mini_printf(a);
}
int main(int argc, char **argv)
{
    // test_memoire();
    // test_chaine_carac();
    test_io();
    mini_exit();
}