#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#define MAX_MESSAGE_LENGTH 256
#define SERV_IP "127.0.0.1"
#define PORT 8000
#define True 1
//-------------------------
//-------[PROTOTYPE]-------
void stop(char *mesg);
void remove_ENTER(char *string);
void init_client(struct sockaddr_in *serv_addr, int *self_fd);
void connection(int *self_fd, struct sockaddr *serv_addr);
void client_regulation(fd_set *readfds, struct sockaddr_in *address, int self_sd);
//--------------------------
void stop(char *mesg)
{
    perror(mesg);
    exit(EXIT_FAILURE);
}
void remove_ENTER(char *string)
{
    int len = strlen(string);
    if (string[len - 1] == '\n')
    {
        string[len - 1] = '\0';
    }
}
void init_client(struct sockaddr_in *serv_addr, int *self_fd)
{
    memset(serv_addr, 0, sizeof(*serv_addr));
    (*serv_addr).sin_family = AF_INET;
    (*serv_addr).sin_addr.s_addr = inet_addr(SERV_IP);
    (*serv_addr).sin_port = htons(PORT);

    *self_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (*self_fd == 0)
    {
        stop("socketfailed");
    }
}
void connection(int *self_fd, struct sockaddr *serv_addr)
{
    if (connect(*self_fd, serv_addr, sizeof(*serv_addr)) < 0)
    {
        stop("Error connecting to server");
    }
}

void client_regulation(fd_set *readfds, struct sockaddr_in *address, int self_sd)
{
    FD_ZERO(readfds);
    FD_SET(0, readfds);
    FD_SET(self_sd, readfds);
    int recv_len = 0;
    char message[MAX_MESSAGE_LENGTH];
    char *dafaukte = (char *)malloc(sizeof(char) * MAX_MESSAGE_LENGTH);
    if ((select(self_sd + 1, readfds, NULL, NULL, NULL) < 0) && (errno != EINTR))
    {
        perror("select");
    }
    // puts("pressanykey");
    for (int i = 0; i <= self_sd; i++)
    {
        if (FD_ISSET(i, readfds))
        {
            if (i == self_sd)
            {
                recv_len = read(self_sd, message, strlen(message));
                if (recv_len <= 0)
                {
                    perror("recv");
                }
                // message[recv_len] = '\0';
                // printf("recu: %s\n", message);
            }
            printf("recu: %s\n", message);
            if (i == 0)
            {
                printf("Enter:>> ");
                fgets(dafaukte, MAX_MESSAGE_LENGTH, stdin);
                // printf("\nwhat i type:....%s\n", dafaukte);
                remove_ENTER(dafaukte);
                send(self_sd, dafaukte, strlen(dafaukte), 0);
            }
        }
    }
}
int main()
{
    int self_sd;
    struct sockaddr_in address;
    fd_set readfds;
    init_client(&address, &self_sd);
    connection(&self_sd, (struct sockaddr *)&address);
    while (True)
    {
        client_regulation(&readfds, &address, self_sd);
    }
    close(self_sd);
}