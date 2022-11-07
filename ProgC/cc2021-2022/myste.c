#include <stdio.h>
#include <stdlib.h>
void pop(int *a)
{
    int *parray = malloc(2 * sizeof(int));
    parray[0] = 37;
    parray[1] = 73;
    a = parray;
}

int main()
{
    int *a = NULL;
    pop(a);
    printf("a[0]=%dand a[1] =%d", a[0], a[1]);
    return 0;
}