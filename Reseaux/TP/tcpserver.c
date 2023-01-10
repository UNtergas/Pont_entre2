#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <netdb.h>
// #include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>

#define MAX 512
void stop(char *mesg)
{
    printf("FAILLED:");
    perror(mesg);
    exit(EXIT_FAILURE);
}

void func(int connfd)
{
    char buff[MAX];
    int n;

    while (true)
    {
        read(connfd, buff, sizeof(buff));
        printf("from client:%s\n", buff);
        bzero(buff, MAX);
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        if (strncmp(buff, "exit", 4) == 0)
        {
            printf("exit\n");
            break;
        }
        send(connfd, buff, strlen(buff), 0);
    }
}
int main()
{
    int sockfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        stop("socket");
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr.s_addr);
    servaddr.sin_port = htons(1234);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        stop("bind");
    }
    if (listen(sockfd, 5) != 0)
    {
        stop("listen");
    }
    len = sizeof(cliaddr);
    connfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
    if (connfd < 0)
    {
        stop("connect");
    }
    printf("client connect");
    func(connfd);
    close(sockfd);
}