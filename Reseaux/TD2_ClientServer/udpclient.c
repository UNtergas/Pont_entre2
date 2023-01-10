#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 1234
#define MAXLINE 1024

void stop(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char *mess = "PING";
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        stop("FAILED CREATE SOCKET");
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    // servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = PORT;

    int n;
    socklen_t len;
    while (1)
    {
        len = sizeof(servaddr);
        sendto(sockfd, (const char *)mess, strlen(mess), MSG_CONFIRM, (struct sockaddr *)&servaddr, sizeof(servaddr));
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        printf("reception %s, from %d ,via %d\n", buffer, servaddr.sin_addr.s_addr, servaddr.sin_port);
    }
    close(sockfd);
    exit(EXIT_SUCCESS);
}