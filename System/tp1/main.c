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
    int *a = mini_malloc(4);
    int *b = mini_malloc(4);
    int *c = mini_malloc(4);
    printf("\n%p,%p,%p\n", a, b, c);
    mini_free(a);
    mini_free(b);
    int *_a = mini_malloc(4);
    int *_b = mini_malloc(4);
    printf("\n%p,%p,%p,%p,%p\n", a, b, _a, _b, c);
}

void test_chaine_carac()
{
    puts("");
    mini_printf("12345\n");
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
    static MYFILE *_file;
    _file = file_ptr_constructor();
    _file = mini_open("write.txt", 'b');
    // _file = mini_open("write.txt", 'w');
    char _write[] = "im going to write y'all";
    // char *ptr = mini_calloc(1, 100);
    // char a[50], b[20];
    // int _read_a = mini_fread(a, sizeof(char), 6, _file);
    // mini_printf(a);
    // mini_printf(b);
    // printf("\nread_a:%d|read_b:%d\n", _read_a, _read_b);
    // int a = mini_fwrite(_write, 1, 43, _file);
    char b[20], c[20];
    mini_fread(b, 1, 2, _file);
    mini_fread(c, 1, 4, _file);
    // // printf("%d\n", a);
    mini_printf(b);
    printf("\n");
    mini_printf(c);
    printf("\n");
    char a_1 = mini_fgetc(_file);
    char a_2 = mini_fgetc(_file);
    char a_3 = mini_fgetc(_file);
    char c_1 = '8';
    printf("\n%c %c %c\n", a_1, a_2, a_3);
    mini_fputc(_file, c_1);
}
int main(int argc, char **argv)
{
    // test_memoire();
    // test_chaine_carac();
    test_io();

    mini_exit();
}