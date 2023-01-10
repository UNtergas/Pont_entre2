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

void func(int sockfd)
{
    char buff[MAX];
    char *quit = "client_quit";
    int n = 0;
    while (true)
    {
        bzero(buff, MAX);
        while ((buff[n++] = getchar()) != '\n')
            ;
        // if (strncmp(buff, "exit", 4) == 0)
        // {
        //     send(sockfd, quit, strlen(quit), 0);
        //     printf("client_exit\n");
        //     break;
        // }
        send(sockfd, buff, strlen(buff), 0);
        bzero(buff, MAX);
        read(sockfd, buff, sizeof(buff));
        printf("from serv>%s\n", buff);
        if (strncmp(buff, "exit", 4) == 0)
        {
            printf("client_exit\n");
            break;
        }
    }
}
int main()
{
    int sockfd, connfd;
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
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        stop("connetc");
    }
    printf("connect sucress");
    func(sockfd);
    close(sockfd);
}