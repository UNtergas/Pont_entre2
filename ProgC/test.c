#include <stdio.h>
#include <stdlib.h>
struct rep
{
    int val;
    char data[];
};

int main()
{
    struct rep ex;
    int a[] = {3, 2, 4};
    int *ptr = malloc((sizeof(a) / sizeof(int)) * sizeof(int));
    ptr = a;
    ex.val = 1;
    for (int i = 0; i < 2; i++)
    {
        ex.data[i] = *(ptr + i + 1);
    }

    for (int i = 0; i < 10; i++)
    {
        printf("%d", ex.data[i]);
    }
    return 0;
}