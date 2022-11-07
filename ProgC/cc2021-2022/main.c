#include <stdio.h>
#include <string.h>
#define LG_MAX 10
void main()
{
    char ch[LG_MAX];
    do
    {
        printf("done chine: ");
        fgets(ch, LG_MAX, stdin);
        printf("chaine lue: ");
        puts(ch);
    } while (strlen(ch) != 1);
}