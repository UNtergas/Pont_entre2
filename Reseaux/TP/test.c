#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#define PORT 8000
#define SERV_IP "127.0.0.1"
#define MAX 512
#define True 1
#define False 0
struct link_client
{
    char *name;
    int client_sock_id;
    int addr_len;
    struct link_client *next;
};

//-----------------------------------------
//---------PROTOTYPE
//---------------------
struct link_client *find_node_name(struct link_client *head, char *name);
struct link_client *find_node_id(struct link_client *head, int sock_id);
void traverse_list(struct link_client *head);
void insert_node(struct link_client **head_ref, char *name, int client_sock_id);
void delete_node(struct link_client **head_ref, char *name);
//-----------------linklist----------
void stop(char *mesg);
void remove_ENTER(char *string);
void init_server(struct sockaddr_in *serv_addr, int *master_socket);
void accept_connect(fd_set *readfds, struct sockaddr_in *client_addr, int *fd_max, struct link_client **link_head, int master_socket);
//----------------server--------------
void remove_ENTER(char *string);
int nickname_available(struct link_client *head, char *name);
int get_nickname(struct link_client **head, char *nickname, int client_socket);
char *mesg_styling(char *mesg, char *sender_name);
//----------------management--------------
//-----------------------------------------
/*
                                                    FUNCTION
*/
//-----------------linklist----------
struct link_client *find_node_name(struct link_client *head, char *name)
{
    struct link_client *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->name, name) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
struct link_client *find_node_id(struct link_client *head, int sock_id)
{
    struct link_client *temp = head;
    while (temp != NULL)
    {
        if (temp->client_sock_id == sock_id)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}
void traverse_list(struct link_client *head)
{
    struct link_client *temp = head;
    while (temp != NULL)
    {
        printf("Name: %s, Socket ID: %d\n", temp->name, temp->client_sock_id);
        temp = temp->next;
    }
}
void delete_node(struct link_client **head_ref, char *name)
{
    struct link_client *temp = *head_ref, *prev;
    if (temp != NULL && strcmp(temp->name, name) == 0)
    {
        *head_ref = temp->next;
        free(temp->name);
        free(temp);
        return;
    }
    while (temp != NULL && strcmp(temp->name, name) != 0)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp->name);
    free(temp);
}
void insert_node(struct link_client **head_ref, char *name, int client_sock_id)
{
    struct link_client *new_node = (struct link_client *)malloc(sizeof(struct link_client));
    new_node->name = malloc(strlen(name) + 1);
    strcpy(new_node->name, name);
    new_node->client_sock_id = client_sock_id;
    new_node->next = *head_ref;
    *head_ref = new_node;
}
//----------------management--------------
//-----------------------------------------
int nickname_available(struct link_client *head, char *name)
{
    struct link_client *c_node = find_node_name(head, name);
    if (c_node != NULL)
    {
        return True;
    }
    return False;
}
int get_nickname(struct link_client **head, char *nickname, int client_socket)
{
    char *notice = "nickname not available";
    char *welcome = "BRRRR ON BOARD";
    int name_len;
    do
    {
        name_len = read(client_socket, nickname, MAX);
        if (name_len <= 0)
        {
            stop("cant get client nickname");
        }
        if (nickname_available(*head, nickname) == False)
        {
            if (send(client_socket, notice, strlen(notice), 0) <= 0)
            {
                stop("cant send notice ");
            }
        }
        else
        {
            if (send(client_socket, welcome, strlen(welcome), 0) <= 0)
            {
                stop("cant send welcome");
            }
        }
    } while (nickname_available(*head, nickname) == False);
    return name_len;
}
void remove_ENTER(char *string)
{
    int len = strlen(string);
    if (string[len - 1] == '\n')
    {
        string[len - 1] = '\0';
    }
}
//----------------server--------------
void stop(char *mesg)
{
    perror(mesg);
    exit(EXIT_FAILURE);
}

void init_server(struct sockaddr_in *server_addr, int *master_sockfd)
{
    // (*serv_addr).sin_family = AF_INET;
    // (*serv_addr).sin_addr.s_addr = inet_addr(SERV_IP);
    // (*serv_addr).sin_port = htons(PORT);

    // *master_socket = socket(AF_INET, SOCK_STREAM, 0);
    // if (*master_socket < 0)
    // {
    //     stop("socketfailed");
    // }
    // int opt = True;

    // if (setsockopt(*master_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    // {
    //     stop("setsockopt");
    // }
    // if (bind(*master_socket, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) < 0)
    // {
    //     stop("bind");
    // }
    int opt = True;

    // Create server address structure
    server_addr->sin_port = htons(PORT);
    server_addr->sin_family = AF_INET;
    server_addr->sin_addr.s_addr = inet_addr("127.0.0.1");

    // Create master socket
    if ((*master_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        stop("could not create a master socket");
    }

    // Allow multiple client to connect to the master server
    if (setsockopt(*master_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) == -1)
    {
        stop("Error occurs when setsockopt was called");
    }

    // Bind master socket to localhost and communicate with clients through PORT
    if (bind(*master_sockfd, (struct sockaddr *)server_addr, sizeof(struct sockaddr)) < 0)
    {
        stop("error occurs when binding the server_addr to master socket");
    }

    // Listen
    if (listen(*master_sockfd, 3) < 0)
    {
        stop("error occurs when listenning for incomming connection");
    }
    printf("\nServer listenning on port 1234\n");
    fflush(stdout);
}

void accept_connect(fd_set *readfds, struct sockaddr_in *client_addr, int *fd_max, struct link_client **link_head, int master_socket)
{
    printf("Awaiting connection..\n");
    socklen_t client_addr_len = sizeof(struct sockaddr_in);
    int client_socket = accept(master_socket, (struct sockaddr *)client_addr, &client_addr_len);
    if (client_socket < 0)
    {
        stop("client socket");
    }
    printf("incomming resquest from %d\n", client_socket);
    char nickname[MAX];
    int name_len;
    memset(nickname, 0, MAX);
    name_len = get_nickname(link_head, nickname, client_socket);
    insert_node(link_head, nickname, client_socket);
    FD_SET(client_socket, readfds);
    if (client_socket > *fd_max)
    {
        *fd_max = client_socket;
    }
    printf("%d::%s join the server", client_socket, nickname);
}

void chat_service(int fd, fd_set *readfds, int fd_max, int master_socket, struct link_client **head)
{
    // char *nickname = (char *)calloc(MAX, sizeof(char));
    // memset(nickname, 0, MAX);
    struct link_client *c_node = find_node_id(*head, fd);
    // if (c_node != NULL){
    //     nickname
    // }
    char buffer[MAX];
    memset(buffer, 0, MAX);
    int nbyte = read(fd, buffer, MAX);
    if (nbyte < 0)
    {
        stop("cant get mesg from client");
    }
    else if (nbyte == 0)
    {
        printf("%d:: DISCONNECT", fd);
        FD_CLR(fd, readfds);
        close(fd);
    }
    else
    {
        char *ready_to_send = mesg_styling(buffer, c_node->name);
        for (int i = 0; i <= fd_max; i++)
        {
            if (FD_ISSET(i, readfds))
            {
                if (i != master_socket && i != fd)
                {
                    if (send(i, ready_to_send, strlen(ready_to_send), 0) < 0)
                    {
                        stop("can't forwarding mesg");
                    }
                }
            }
        }
    }
}
char *mesg_styling(char *mesg, char *sender_name)
{
    time_t current_time;
    struct tm *time_info;
    char time_string[9];

    time(&current_time);
    time_info = localtime(&current_time);

    strftime(time_string, sizeof(time_string), "%H:%M", time_info);
    int total_size = strlen(sender_name) + strlen(mesg) + strlen(time_string);
    char *format_mesg = (char *)calloc(total_size, sizeof(char));
    snprintf(format_mesg, total_size, "%s%s%s", time_string, sender_name, mesg);
    return format_mesg;
}

int main()
{
    int master_socket, fd_max;
    struct sockaddr_in serv_addr, client_addr;
    fd_set readfds;
    struct link_client *cli_head = NULL;
    FD_ZERO(&readfds);
    init_server(&serv_addr, &master_socket);
    printf("server fd %d\n", master_socket);
    printf("Listening on port %d\n", PORT);
    printf("behind listen");
    FD_SET(master_socket, &readfds);
    fd_max = master_socket;
    while (True)
    {
        if ((select(fd_max, &readfds, NULL, NULL, NULL) < 0) && (errno != EINTR))
        {
            stop("select");
        }
        for (int i = 0; i <= fd_max; i++)
        {
            if (FD_ISSET(i, &readfds))
            {
                if (i == master_socket)
                {
                    // accept_connect(&readfds, &client_adrr, &fd_max, &cli_head, master_socket);
                    printf("Awaiting connection..\n");
                    socklen_t client_addr_len = sizeof(struct sockaddr_in);
                    int client_socket = accept(master_socket, (struct sockaddr *)&client_addr, &client_addr_len);
                    if (client_socket < 0)
                    {
                        stop("client socket");
                    }
                    printf("incomming resquest from %d\n", client_socket);
                    char nickname[MAX];
                    int name_len;
                    memset(nickname, 0, MAX);
                    name_len = get_nickname(cli_head, nickname, client_socket);
                    insert_node(cli_head, nickname, client_socket);
                    FD_SET(client_socket, &readfds);
                    if (client_socket > fd_max)
                    {
                        fd_max = client_socket;
                    }
                    printf("%d::%s join the server", client_socket, nickname);
                }
                else
                {
                    chat_service(i, &readfds, fd_max, master_socket, &cli_head);
                }
            }
        }
    }
    close(master_socket);
}