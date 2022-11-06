#ifndef MINI_LIB_H
#define MINI_LIB_H
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

// allocation memoire
struct malloc_element
{
    void *zone;
    int taille;
    int statut;
    struct malloc_element *next_malloc;
};
#define DATA_SIZE sizeof(struct malloc_element)
typedef struct malloc_element malloc_element;

malloc_element *trouver_bloc_libre(malloc_element **last, int size);
malloc_element *cree_mem_os(malloc_element *last, int size);
void *mini_malloc(int size);
void *mini_calloc(int size_ele, int nombre_ele);
void mini_free(void *ptr);
void mini_exit();
// gestion chain caractere
#define BUF_SIZE 1024
void mini_printf(char *msg);
int mini_scanf(char *msg, int size_msg);
int mini_strlen(char *s);

#endif