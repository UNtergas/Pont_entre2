
#include "mini_lib.h"

malloc_element *malloc_list = NULL;

malloc_element *trouver_bloc_libre(malloc_element **last, int size)
{
    malloc_element *current = malloc_list;
    while (current)
    {
        if (current->statut == 0 && current->taille >= size)
        {
            return current;
        }
        *last = current;
        current = current->next_malloc;
    }
    return current;
}

// malloc_element *cree_mem_os(malloc_element *last, int size)
// {
//     malloc_element *block;
//     block = sbrk(0);
//     // void *resquest_mem = sbrk(size + DATA_SIZE);
//     if (sbrk(ALIGN(size) + DATA_SIZE) == (void *)-1)
//     {
//         mini_perror("echec sbrk\n");
//         return NULL; // echec du sbrk
//     }
//     block->taille = ALIGN(size);
//     block->next_malloc = NULL;
//     block->statut = 1;
//     block->zone = block + 1;
//     if (last)
//     {
//         last->next_malloc = block;
//     }
//     return block;
// }

malloc_element *_ajouter_nouvel(malloc_element *_parcour, int size)
{
    malloc_element *_bloc;
    _bloc = sbrk(0);
    sbrk(DATA_SIZE);
    _bloc->taille = ALIGN(size);
    _bloc->zone = sbrk(ALIGN(size));
    _bloc->next_malloc = NULL;
    _bloc->statut = 1;
    if (_parcour)
    {
        _parcour->next_malloc = _bloc;
    }
    return _bloc;
}

void *mini_malloc(int size)
{
    malloc_element *last;
    malloc_element *bloc;
    if (malloc_list)
    { // find block
        last = malloc_list;
        bloc = trouver_bloc_libre(&last, size);
        if (bloc)
        {
            bloc->statut = 1;
            // printf("\nfind spot\n");
            return bloc->zone;
        }
        if (!bloc)
        {
            // bloc = cree_mem_os(last, size);
            bloc = _ajouter_nouvel(last, size);
            if (!bloc)
            {
                mini_perror("calloc failed");
                return NULL;
            }
        }
    }
    else
    {
        // bloc = cree_mem_os(NULL, size);
        bloc = _ajouter_nouvel(NULL, size);
        if (!bloc)
        {
            mini_perror("first fail");
            return NULL;
        }
        malloc_list = bloc;
    }
    // bloc->zone = bloc + 1;
    // printf("\ntaille\n%d", bloc->taille);
    // printf("\n%p\n", bloc->zone);
    return (bloc->zone);
    // return bloc + 1;
}

void *mini_calloc(int size_ele, int nombre_ele)
{
    void *p;
    p = mini_malloc(size_ele * nombre_ele);
    if (!p)
        return NULL;
    // bzero(p, size_ele * nombre_ele);
    for (int i = 0; i < size_ele * nombre_ele; i++)
    {
        *((char *)p + i) = 0;
    }
    return (p);
}

void mini_free(void *ptr)
{
    if (!ptr)
    {
        // mini_perror("trouv pas ptr pr free\n");
        exit(EXIT_FAILURE);
    }
    malloc_element *bloc_ptr = (char *)ptr - DATA_SIZE;
    bloc_ptr->statut = 0;
    // printf("\nfree %d\n", bloc_ptr->statut);
}

void mini_exit()
{
    exit(EXIT_SUCCESS);
}