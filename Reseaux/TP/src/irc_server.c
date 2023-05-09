#include "server_tool.h"
#include "user.h"

struct User *head;

int main()
{
    int opt = 1;
    int master_socket;
    char buffer[BUF_LEN];
    memset(buffer, 0, BUF_LEN);
    char *wellcome = "WELCOME ONBOARD\n\0";

    /**
     * * : init socket_fd, setsockopt
     */

    master_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (master_socket < 0)
    {
        stop("error creation socket");
    }
    if ((setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt))) < 0)
    {
        stop("error setsockopt");
    }
    /**
     * *init sockaddr structure
     */
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        stop("error binding master sock");
    }
    if (listen(master_socket, 3) < 0)
    {
        stop("error listen");
    }

    printf("Wating for connection.......\n");

    /**
     * *Main loop, with select and fd_set
     */
    fd_set readfds;
    int fd_max;
    int fd_current;
    int addr_len;
    int nom_read;
    int socket_client[MAX_CLIENT];
    for (int i = 0; i < MAX_CLIENT; ++i)
    {
        socket_client[i] = 0;
    }
    while (True)
    {
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);
        fd_max = master_socket;

        /**
         * todo: parcour database, add existing client to fd_set
         */
        for (int i = 0; i < MAX_CLIENT; i++)
        {
            // fd_current = DATABASE[i].sock_fd;
            fd_current = socket_client[i];
            if (fd_current > 0)
            {
                FD_SET(fd_current, &readfds);
            }
            if (fd_current > fd_max)
            {
                fd_max = fd_current;
            }
        }
        /**
         * todo: fd selection
         */
        if (((select(fd_max + 1, &readfds, NULL, NULL, NULL)) < 0) && (errno != EINTR))
        {
            stop("error select");
        }

        /**
         * todo : server action
         */
        if (FD_ISSET(master_socket, &readfds))
        {
            fflush(stdin);
            int new_fd = accept(master_socket, (struct sockaddr *)(&address), &addr_len);
            if (new_fd < 0)
            {
                stop("error accepting");
            }
            printf("incoming connection\n");
            struct User new_client;
            new_client.sock_fd = new_fd;
            memset(new_client.nickname, 0, MAX_NAME);
            /**
             * todo: loop until get available nickname
             */
            do
            {
                char *wallning = "name not available\n";
                memset(buffer, 0, BUF_LEN);
                nom_read = recv(new_fd, buffer, BUF_LEN, 0);
                remove_enter_in_buffer(buffer);
                buffer[nom_read - 2] = '\0';
                if (nickname_available(buffer) == False)
                {
                    send(new_fd, wallning, strlen(wallning), 0);
                }
            } while (nickname_available(buffer) == False);
            printf("%s has connected\n", buffer);
            send(new_fd, wellcome, strlen(wellcome), 0);
            // if (add_client(new_client) == False)
            // {
            //     stop("error add client to DB");
            // }

            broadcast_message(buffer, master_socket);
            broadcast_message("has joined the server", master_socket);
            for (int i = 0; i < MAX_CLIENT; ++i)
            {
                if (socket_client[i] == 0)
                {
                    socket_client[i] = new_fd;
                    break;
                }
            }
            if (new_fd > fd_max)
            {
                fd_max = new_fd;
            }
            add_user(buffer, new_fd);
            // print_list();
            // broadcast_message(buffer, master_socket);
            // broadcast_message(" joined in", master_socket);
        }
        /**
         * todo: client action
         */
        for (int i = 0; i < MAX_CLIENT; i++)
        {
            fd_current = socket_client[i];
            if (FD_ISSET(fd_current, &readfds))
            {
                // chat_service(fd_current, &readfds, fd_max, socket_client, i);
                struct User *mesg_sender = find_user_by_sock_fd(fd_current);
                char chat_buffer[BUF_LEN];
                memset(chat_buffer, 0, BUF_LEN);
                int nbyte = read(fd_current, chat_buffer, BUF_LEN);

                if (nbyte == 0)
                {
                    struct User *client = find_user_by_sock_fd(fd_current);
                    printf("username'%d'%s:: DISCONNECT\n", fd_current, client->nickname);
                    remove_user(fd_current);
                    close(fd_current);
                    socket_client[i] = 0;
                }
                else if (chat_buffer[0] == '/')
                {
                    // remove_enter_in_buffer(chat_buffer);
                    // printf("incoming cmd %s", chat_buffer);
                    char **args = (char **)malloc(sizeof(char *) * MAX_ARGS);
                    for (int i = 0; i < MAX_ARGS; i++)
                    {
                        args[i] = (char *)malloc(1 * BUF_LEN);
                    }
                    int argc = input_traitment(chat_buffer, args);
                    // printf("%d numarg\n", argc);
                    cmd(argc, args, fd_current);
                }
                else
                {
                    char *ready_to_send = mesg_styling(chat_buffer, mesg_sender->nickname);
                    broadcast_message(ready_to_send, mesg_sender->sock_fd);
                }
            }
        }
    }

    close(master_socket);
}