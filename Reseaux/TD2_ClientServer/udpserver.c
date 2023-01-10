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
    char *mess = "PONG";
    struct sockaddr_in servaddr, cliaddr;

    // creation

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        stop("SOCKET CREATION FAIL");
    }
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // fill server infos
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // bind socket with server

    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        stop("BINDING FAIL");
    }
    int n;
    socklen_t len;
    while (1)
    {
        len = sizeof(cliaddr);
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        // printf("reception %s\n", buffer);
        printf("reception %s, from %d ,via %d\n", buffer, cliaddr.sin_addr.s_addr, cliaddr.sin_port);
        sendto(sockfd, (const char *)mess, strlen(mess), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        printf("messgsent\n");
    }
    exit(EXIT_SUCCESS);
}