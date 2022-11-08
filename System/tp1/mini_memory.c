
#include "mini_lib.h"

static malloc_element *malloc_list = NULL;

malloc_element *trouver_bloc_libre(malloc_element **last, int size)
{
    malloc_element *current = malloc_list;
    while (current && (current->statut != 0 && current->taille >= size))
    {
        *last = current;
        current = current->next_malloc;
    }
    return current;
}

malloc_element *cree_mem_os(malloc_element *last, int size)
{
    malloc_element *block;
    block = sbrk(0);
    // void *resquest_mem = sbrk(size + DATA_SIZE);
    if (sbrk(size + DATA_SIZE) == (void *)-1)
    {
        mini_perror("echec sbrk\n");
        return NULL; // echec du sbrk
    }
    block->taille = size;
    block->next_malloc = NULL;
    block->statut = 1;
    if (last)
    {
        last->next_malloc = block;
    }
    return block;
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
            bloc->statut = 0;
        }
        else
        {
            bloc = cree_mem_os(last, size);
            if (!bloc)
            {
                mini_perror("calloc failed");
                return NULL;
            }
        }
    }
    else
    {
        bloc = cree_mem_os(NULL, size);
        if (!bloc)
        {
            mini_perror("first fail");
            return NULL;
        }
        malloc_list = bloc;
    }
    // bloc->zone = bloc + 1;
    // return (bloc->zone);
    return (bloc + 1);
}

void *mini_calloc(int size_ele, int nombre_ele)
{
    void *p;
    p = mini_malloc(size_ele * nombre_ele);
    if (!p)
        return NULL;
    bzero(p, size_ele * nombre_ele);
    return (p);
}

void mini_free(void *ptr)
{
    if (!ptr)
    {
        mini_perror("trouv pas ptr pr free\n");
        exit(EXIT_FAILURE);
    }
    malloc_element *bloc_ptr = (struct malloc_element *)ptr;
    bloc_ptr->statut = 0;
}

void mini_exit()
{
    exit(EXIT_SUCCESS);
}