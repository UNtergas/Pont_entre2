#include "user.h"

struct User *find_user_by_sock_fd(int sock_fd)
{
    struct User *current = head;
    while (current != NULL)
    {
        if (current->sock_fd == sock_fd)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

struct User *find_user_by_nickname(char *nickname)
{
    struct User *current = head;
    while (current != NULL)
    {
        if (strcmp(current->nickname, nickname) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
struct User *find_user_by_nickname_registered(char *nickname)
{
    struct User *current = head;
    while (current != NULL)
    {
        if (strcmp(current->nickname_register, nickname) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}
void add_user(char *nickname, int sock_fd)
{
    struct User *new_user = (struct User *)malloc(sizeof(struct User));
    strcpy(new_user->nickname, nickname);
    memset(new_user->passwd, 0, MAX_NAME);
    memset(new_user->nickname_register, 0, MAX_NAME);
    new_user->sock_fd = sock_fd;
    new_user->next = head;
    new_user->registre = False;
    head = new_user;
}

void remove_user(int sock_fd)
{
    struct User *current = head;
    struct User *previous = NULL;

    while (current != NULL)
    {
        if (current->sock_fd == sock_fd)
        {
            if (previous == NULL)
            {
                head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void print_list()
{
    struct User *current = head;
    while (current != NULL)
    {
        printf("Nickname: %s,fd: %d,reg%d,passwd%s\n", current->nickname, current->sock_fd, current->registre, current->passwd);
        current = current->next;
    }
}