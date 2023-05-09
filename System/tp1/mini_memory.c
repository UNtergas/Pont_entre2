
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

            return bloc->zone;
        }
        if (!bloc)
        {

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

        bloc = _ajouter_nouvel(NULL, size);
        if (!bloc)
        {
            mini_perror("first fail");
            return NULL;
        }
        malloc_list = bloc;
    }

    return (bloc->zone);
}

void *mini_calloc(int size_ele, int nombre_ele)
{
    void *p;
    p = mini_malloc(size_ele * nombre_ele);
    if (!p)
        return NULL;

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
        mini_perror("trouv pas ptr pr free\n");
        exit(EXIT_FAILURE);
    }
    malloc_element *bloc_ptr = (char *)ptr - DATA_SIZE;
    bloc_ptr->statut = 0;
}

void mini_exit()
{
    while (__list_file)
    {
        mini_fflush(__list_file);
        __list_file = __list_file->next_file;
    }
    exit(EXIT_SUCCESS);
}
