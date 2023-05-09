#ifndef SERVER_TOOL_H
#define SERVER_TOOL_H
#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

#define BUF_LEN 1024
#define PORT 1234
#define MAX_ARGS 20
#define RED "\033[1;31m"
void stop(char *msg);
int remove_enter_in_buffer(char *buffer);

int nickname_available(char *name);
void broadcast_message(char *message, int sender_socket);

char *mesg_styling(char *mesg, char *sender_name);

int input_traitment(char *input, char **args);
void cmd(int argc, char **args, int fd);
void change_nickname(char *new_nickname, int fd);
int authentification(char *nickname, char *passwd, int fd);
void register_pseudo(char *nickname, char *passwd, int fd);
void force_change_nickname(char *nickname, char *passwd, int fd);
void unregister_pseudo(char *nickname, char *passwd, int fd);
void send_private_mesg(char *mesg, char *pseudo, int fd);
char *change_color_buffer(char *buffer, char *color_code);
void alert_broadcast(char *mesg, int fd);
void serv_to_client(int fd, char *mesg);
void file_transmettre(char *file, char *nickname, int sock_fd);
#endif