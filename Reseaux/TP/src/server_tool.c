#include "server_tool.h"

void stop(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int remove_enter_in_buffer(char *buffer)
{

    int k;
    for (k = 0; k < BUF_LEN; k++)
    {
        if (buffer[k] == '\n')
        {
            buffer[k] = '\0';
            break;
        }
    }
    return k;
}

int nickname_available(char *name)
{
    struct User *result = find_user_by_nickname(name);
    if (result == NULL)
    {
        return True;
    }
    else
    {
        return False;
    }
}

void broadcast_message(char *message, int sender_socket)
{
    struct User *current = head;
    while (current != NULL)
    {
        if (current->sock_fd != sender_socket)
        {
            send(current->sock_fd, message, strlen(message), 0);
        }
        current = current->next;
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
    // snprintf(format_mesg, total_size + strlen("At ") + strlen("|'") + strlen("'say: "), "%s%s%s%s%s%s", "At ", time_string, "|'", sender_name, "'say: ", mesg);
    snprintf(format_mesg, total_size + 4, "%s||%s>>%s", time_string, sender_name, mesg);
    return format_mesg;
}
int input_traitment(char *input, char **args)
{
    remove_enter_in_buffer(input);
    int _len_args = 0;
    int _no_args = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == ' ')
        {
            args[_no_args][_len_args] = '\0';
            // printf("args %s no %d \n", args[_no_args], _no_args);
            _no_args++;
            _len_args = 0;
        }
        else if (input[i] == '\n')
        {
            args[_no_args][_len_args] = '\0';
            _no_args++;
            break;
        }
        else
        {
            args[_no_args][_len_args] = input[i];
            _len_args++;
        }
    }
    return _no_args;
}

void unknow_cmd(int fd)
{
    char *err = "command not foudn\n";
    send(fd, err, strlen(err), 0);
}
void cmd(int argc, char **args, int fd)
{
    // printf("argument 1:%s 2:%s 3:%s\n", args[0], args[1], args[2]);
    if (strcmp(args[0], "/nickname") == 0 && args[1] != NULL)
    {
        char *new_nickname = args[1];

        if (argc < 2)
        {
            change_nickname(new_nickname, fd);
        }
        else if (argc >= 2 && argc < 3)
        {
            printf("forced change\n");
            char *passwd = args[2];
            force_change_nickname(new_nickname, passwd, fd);
        }
    }
    else if (strcmp(args[0], "/mp") == 0 && argc < 3 && argc > 1)
    {
        char *mesg = args[2];
        char *pseudo = args[1];
        send_private_mesg(mesg, pseudo, fd);
    }
    else if (strcmp(args[0], "/alert") == 0 && args[1] != NULL)
    {

        char mesg[BUF_LEN * 3] = "";
        for (int i = 1; i <= argc; i++)
        {
            strcat(mesg, args[i]);
            strcat(mesg, " ");
        }
        alert_broadcast(mesg, fd);
    }
    else if (strcmp(args[0], "/register") == 0 && argc < 3 && argc > 1)
    {
        char *pseudo = args[1];
        char *passwd = args[2];
        printf("mode resgister\n");
        register_pseudo(pseudo, passwd, fd);
    }
    else if (strcmp(args[0], "/unregister") == 0 && argc < 3 && argc > 1)
    {
        char *pseudo = args[1];
        char *passwd = args[2];
        unregister_pseudo(pseudo, passwd, fd);
    }
    else if (strcmp(args[0], "/send") == 0 && argc < 3 && argc > 1)
    {
        char *nickname = args[1];
        char *file = args[2];
        file_transmettre(file, nickname, fd);
    }
    else
    {
        unknow_cmd(fd);
    }
}

void change_nickname(char *new_nickname, int fd)
{
    char *error = "nick name exist";
    if (nickname_available(new_nickname) == False)
    {
        send(fd, error, strlen(error), 0);
    }
    else
    {
        struct User *client = find_user_by_sock_fd(fd);
        memset(client->nickname, 0, MAX_NAME);
        strcpy(client->nickname, new_nickname);
        printf("\n%s change name to %s\n", client->nickname, new_nickname);
    }
}
void register_pseudo(char *nickname, char *passwd, int fd)
{
    char *err = "name already registerd";
    char *err2 = "already registered";
    struct User *check = find_user_by_nickname(nickname);
    struct User *new = find_user_by_sock_fd(fd);
    fflush(stdin);
    if (new != NULL)
    {
        if (check == NULL || check->registre == False)
        {
            if (new->registre == True)
            {
                send(fd, err2, strlen(err2), 0);
            }
            else
            {
                new->registre = True;
                memset(new->passwd, 0, MAX_NAME);
                memset(new->nickname, 0, MAX_NAME);
                memset(new->nickname_register, 0, MAX_NAME);
                strcpy(new->passwd, passwd);
                strcpy(new->nickname, nickname);
                strcpy(new->nickname_register, nickname);
                new->registre = True;
                printf("pseudo: '%s' is now registed by %s\n", nickname, new->nickname);
                serv_to_client(fd, "register pseudo sucesss");
            }
        }
        else
        {
            send(fd, err, strlen(err), 0);
        }
    }
}
void force_change_nickname(char *nickname, char *passwd, int fd)
{
    register_pseudo(nickname, passwd, fd);
    char *guest = "GUEST";
    struct User *client = find_user_by_nickname(nickname);
    struct User *source = find_user_by_sock_fd(fd);
    if (client->registre == False)
    {
        memset(client->nickname, 0, MAX_NAME);
        serv_to_client(client->sock_fd, "your current name is being resigtered by another one");
        serv_to_client(client->sock_fd, "name will now be GUEST,pls change");
        strcpy(client->nickname, guest);
    }
}
void unregister_pseudo(char *nickname, char *passwd, int fd)
{
    char *err1 = "wrong password";
    char *err2 = "nickname not yet registered to be unreg";
    int result = authentification(nickname, passwd, fd);
    if (result == True)
    {
        struct User *user = find_user_by_sock_fd(fd);
        memset(user->nickname_register, 0, MAX_NAME);
        memset(user->passwd, 0, MAX_NAME);
        user->registre = False;
        printf("%s is now unreg", nickname);
        serv_to_client(fd, "unreg nickname success\n");
    }
    else if (result == False)
    {
        send(fd, err1, strlen(err1), 0);
    }
    else if (result == 2)
    {
        // serv_to_client(fd, err2);
        send(fd, err2, strlen(err2), 0);
    }
}

int authentification(char *nickname, char *passwd, int fd)
{
    char *err = "this nickname has not been registered, thus no need authenfication";
    struct User *user = find_user_by_nickname_registered(nickname);
    if (user != NULL)
    {
        if (strcmp(passwd, user->passwd) == 0)
        {
            return True;
        }
        return False;
    }
    else
    {
        send(fd, err, strlen(err), 0);
    }
    return 2;
}
void send_private_mesg(char *mesg, char *pseudo, int fd)
{
    char *err = "user not exist";
    struct User *target = find_user_by_nickname(pseudo);
    if (target == NULL)
    {
        send(fd, err, strlen(err), 0);
    }
    else
    {
        char *prefix = "private message from: ";
        int total_len = strlen(prefix) + strlen(mesg);
        char *private_mesg = (char *)malloc(sizeof(char) * total_len);
        snprintf(private_mesg, total_len, "%s%s", prefix, mesg);
        send(target->sock_fd, private_mesg, total_len, 0);
    }
}
char *change_color_buffer(char *buffer, char *color_code)
{
    char *ret = (char *)calloc(sizeof(char), BUF_LEN);
    char *surfix = "\033[0m";
    int total_len = strlen(color_code) + strlen(surfix) + strlen(buffer);
    snprintf(ret, total_len, "%s%s%s", color_code, buffer, surfix);
    return ret;
}

void alert_broadcast(char *mesg, int fd)
{
    struct User *client = find_user_by_sock_fd(fd);
    if (client != NULL)
    {
        char *mesg_color = change_color_buffer(mesg, RED);
        char *ready_to_send = mesg_styling(mesg_color, client->nickname);
        broadcast_message(ready_to_send, fd);
    }
}

void serv_to_client(int fd, char *mesg)
{
    send(fd, mesg, strlen(mesg), 0);
}

void file_transmettre(char *file, char *nickname, int sock_fd)
{
    char buffer[2048];
    struct User *sender = find_user_by_sock_fd(sock_fd);
    struct User *dest = find_user_by_nickname(nickname);
    FILE *file_origin = fopen(file, "r");
    if (file_origin != NULL)
    {
        int fd = open(file, O_RDONLY);
        if (fd < 0)
        {
            perror("Error opening file");
            return;
        }
        char body[1024];
        memset(body, 0, 1024);
        int n = read(fd, body, 1023);
        if (n < 0)
        {
            perror("Error reading file");
            return;
        }
        serv_to_client(dest->sock_fd, sender->nickname);
        serv_to_client(dest->sock_fd, " >>sending you file,incomming file contenu\n");
        send(dest->sock_fd, body, strlen(body), 0);
        serv_to_client(dest->sock_fd, "\n--------------------------");
        close(fd);
    }
    else
    {
        serv_to_client(sock_fd, "file dont exist");
    }
}