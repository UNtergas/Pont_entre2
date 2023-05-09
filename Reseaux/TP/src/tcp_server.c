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

#define PORT 1234
#define BUFFER_SIZE 1024

void stop(char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

int main()
{
    char message_to_client[BUFFER_SIZE] = "PONG";
    char message_from_client[BUFFER_SIZE];
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr, client_addr;

    int client_size = sizeof(client_addr);

    if (sockfd < 0)
    {
        stop("\nCould not create a tcp socket\n");
    }

    server_addr.sin_port = htons(PORT);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        stop("could not bind the localhost address to server");
    }

    if (listen(sockfd, 5) < 0)
    {
        stop("error occur when listenning incomming connection");
    }

    int accepted_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_size);

    if (accepted_sockfd < 0)
    {
        stop("error occur when accepting incomming connection");
    }
    printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    int n;
    for (int i = 0; i < 1000; i++)
    {

        n = recv(accepted_sockfd, message_from_client, BUFFER_SIZE, 0);

        if (n < 0)
        {
            stop("error occurs in recvfrom");
        }

        message_from_client[n] = '\0';

        printf("\nmessage from clients: %s\n", message_from_client);

        if (send(accepted_sockfd, message_to_client, strlen(message_to_client), 0) < 0)
        {
            stop("cant send message from server to client");
        }
    }
    close(accepted_sockfd);
    close(sockfd);

    return 0;
}