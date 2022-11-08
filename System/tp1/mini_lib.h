#ifndef MINI_LIB_H
#define MINI_LIB_H
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
/*
    STRUCT DEF
*/
struct malloc_element
{
    void *zone;
    int taille;
    int statut;
    struct malloc_element *next_malloc;
};

typedef struct malloc_element malloc_element;

struct MYFILE
{
    int fd;
    void *buffer_read;
    void *buffer_write;
    int ind_read;
    int ind_write;
};
typedef struct MYFILE MYFILE;

/*
            FONCTIONS
*/
// allocation memoire
#define DATA_SIZE sizeof(struct malloc_element)
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
int mini_strcpy(char *s, char *d);
int mini_strncpy(char *s, char *d, int size);
int mini_strcmp(char *s1, char *s2);
char *mini_itoa(int a);
void mini_perror(char *message);

// gestion entre sortie

#define IOBUFFER_SIZE 2048

#define OPEN_READ 'r'
#define OPEN_WRITE 'w'
#define OPEN_RW 'b'
#define OPEN_ADD_END 'a'

MYFILE *mini_open(char *file, char mode);
int mini_fread(void *buffer, int size_element, int number_element, MYFILE *file);
#endif