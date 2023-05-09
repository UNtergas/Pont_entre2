#ifndef USER_H
#define USER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define True 1
#define False 0
#define MAX_CLIENT 30
#define MAX_NAME 200
struct User
{
    char nickname[MAX_NAME];
    char passwd[MAX_NAME];
    char nickname_register[MAX_NAME];
    int sock_fd;
    struct User *next;
    int registre;
};
extern struct User *head;
struct User *find_user_by_sock_fd(int sock_fd);
struct User *find_user_by_nickname(char *nickname);
struct User *find_user_by_nickname_registered(char *nickname);
void add_user(char *nickname, int sock_fd);
void remove_user(int sock_fd);
void print_list();
#endif