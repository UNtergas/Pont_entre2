#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <strings.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#define BUF_SIZE 1024

void afficher_dernier_ligne(char *f, int n)
{
    int fd = open(f, O_RDONLY);
    if (fd == -1)
        perror("cant open");
    int _pos = lseek(fd, 0, SEEK_END);
    char a;
    int count = 0;
    char b[BUF_SIZE];
    while (n > 0)
    {
        printf("file_ptr:%d\n", _pos);

        lseek(fd, _pos, SEEK_SET);
        read(fd, &a, 1);
        _pos--;
        if (a != '\n' && a != '\0')
            count++;
        if (a == '\n')
        {
            n--;
        }
    }
    read(fd, b, count);
    b[count + 1] = '\0';
    write(1, b, count);
    close(fd);
}

char *comparisison(char *f1, char *f2)
{
    int fd1 = open(f1, O_RDONLY);
    if (fd1 == -1)
        perror("cant open 1");
    int fd2 = open(f2, O_RDONLY);
    if (fd2 == -1)
        perror("cant open2");
    int size1, size2;
    char buf1[BUF_SIZE];
    char buf2[BUF_SIZE];
    while ((size1 = read(fd1, buf1, BUF_SIZE)) && (size2 = read(fd2, buf2, BUF_SIZE)))
    {
        // printf("size 1,2 %d %d\n", size1, size2);
        // printf("buf\n%s\n", buf1);
        if (size1 != size2)
        {
            close(fd1);
            close(fd2);
            return "NOK";
        }
        for (int i = 0; i < size1; i++)
        {
            if (buf1[i] != buf2[i])
            {
                close(fd1);
                close(fd2);
                return "NOK";
            }
        }
    }
    close(fd1);
    close(fd2);
    return "OK";
}
void stocker(char *nom, int mark)
{
    int fd1 = open("note.dat", O_WRONLY | O_CREAT, 0777);
    if (fd1 == -1)
        perror("cant creat 1");
    write(fd1, *nom, sizeof(*nom));
    write(fd1, &mark, sizeof(int));
    close(fd1);
}
void recuperer(int mark)
{
    int fd1 = open("note.dat", O_RDONLY);
    if (fd1 == -1)
        perror("cant open");
}
int main(int argc, char **argv)
{
    // printf("input%d\n", atoi(argv[1]));
    // printf("result: %s", comparisison("cpfile.txt", "hape.txt"));
    afficher_dernier_ligne("num.txt", 4);
}