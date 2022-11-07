#include <stdio.h>
#include <stdlib.h>
int estSymetric(int array[], int size)
{
    for (int i = 0; i <= (int)(size / 2); i++)
    {
        if (array[i] != array[size - i])
            return 0;
    }
    return 1;
}
int chain_longuer(char *s)
{
    if (*s == '\0')
    {
        return 0;
    }
    else
    {
        s++;
        return 1 + chain_longuer(s);
    }
}
int main()
{
    // int list1[] = {1, 4, 5, 6, 4, 1};
    // int size = sizeof(list1) / sizeof(int);
    // printf("%d\n", estSymetric(list1, size - 1));
    char a[] = "abdcb";
    // char *p = malloc(sizeof(*p));
    // p = a;
    printf("%d\n", chain_longuer(a));
}