#ifndef MINI_LIB_H
#define MINI_LIB_H
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <ctype.h>
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
    struct MYFILE *next_file;
};
typedef struct MYFILE MYFILE;

/*
            FONCTIONS
*/
// allocation memoire
#define ALIGNMENT 8
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
/*
    ex: ALIGN(1)=ALIGN(3)=ALIGN(7)=8
    ALIGN(9)=ALIGN(13)=16
*/
#define DATA_SIZE (ALIGN(sizeof(struct malloc_element)))
//-------
malloc_element *trouver_bloc_libre(malloc_element **last, int size);
// malloc_element *cree_mem_os(malloc_element *last, int size);
void *mini_malloc(int size);
void *mini_calloc(int size_ele, int nombre_ele);
void mini_free(void *ptr);
void mini_exit();
// v2
malloc_element *_ajouter_nouvel(malloc_element *_parcour, int size);

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
#define CREAT_DEL 'd'

MYFILE *file_ptr_constructor();
MYFILE *mini_open(char *file, char mode);
extern MYFILE *__list_file;
int mini_fread(void *buffer, int size_element, int number_element, MYFILE *file);
int mini_fwrite(void *buffer, int size_element, int number_element, MYFILE *file);
int mini_fflush(MYFILE *file);
int mini_fclose(MYFILE *file);
int mini_fgetc(MYFILE *file);
int mini_fputc(MYFILE *file, char c);
/*extra*/
int mini_fseek_read(MYFILE *file, int _offset, int _mode);

// command du system
void mini_touch(char *file);
void mini_cp(char *src, char *dest);
void mini_echo(char *chaine);
void mini_cat(char *_file);
void mini_head(int n, char *_file);
void mini_clean(char *file);
void mini_grep(char *file, char *keyword);
void mini_wc(char *file);
#endif
