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

void print_stat(char *ref, struct stat *statut)
{
    struct passwd *pw;
    struct group *gr;
    char type;
#define LTEMPS 32
    char pws[9], grs[9], temps[LTEMPS];

    type = '?';
    if (S_ISREG(statut->st_mode))
        type = '-';
    else if (S_ISDIR(statut->st_mode))
        type = 'd';
    else if (S_ISCHR(statut->st_mode))
        type = 'c';
    else if (S_ISBLK(statut->st_mode))
        type = 'b';
    else if (S_ISFIFO(statut->st_mode))
        type = 'p';
    else if (S_ISLNK(statut->st_mode))
        type = 'l';

    strftime(temps, LTEMPS, "%a %e %h %Y %H:%M:%S", localtime(&(statut->st_mtime)));
    pw = getpwuid(statut->st_uid);
    if (pw != NULL)
        strcpy(pws, pw->pw_name);
    else
        sprintf(pws, "%8d", (int)statut->st_uid);
    gr = getgrgid(statut->st_gid);
    if (gr != NULL)
        strcpy(grs, gr->gr_name);
    else
        sprintf(grs, "%8d", (int)statut->st_gid);
    printf("%c%c%c%c%c%c%c%c%c%c %2d %8s %8s %9d %s %s\n", type,
           statut->st_mode & S_IRUSR ? 'r' : '-',
           statut->st_mode & S_IWUSR ? 'w' : '-',
           statut->st_mode & S_IXUSR ? 'x' : '-',
           statut->st_mode & S_IRGRP ? 'r' : '-',
           statut->st_mode & S_IWGRP ? 'w' : '-',
           statut->st_mode & S_IXGRP ? 'x' : '-',
           statut->st_mode & S_IROTH ? 'r' : '-',
           statut->st_mode & S_IWOTH ? 'w' : '-',
           statut->st_mode & S_IXOTH ? 'x' : '-',
           (int)statut->st_nlink, pws, grs,
           (int)statut->st_size, temps, ref);
}

void mini_ls_l()
{
    DIR *_dir;
    struct dirent *dp;

    struct stat statut;
    if ((_dir = opendir(".")) == NULL)
    {
        perror("dir can't open");
        return 0;
    }
    while ((dp = readdir(_dir)) != NULL)
    {
        stat(dp->d_name, &statut);
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, ".."))
            print_stat(dp->d_name, &statut);
    }
    closedir(_dir);
}
void mini_ls()
{
    DIR *_dir;
    struct dirent *dp;

    struct stat statut;
    if ((_dir = opendir(".")) == NULL)
    {
        perror("dir can't open");
        return 0;
    }
    while ((dp = readdir(_dir)) != NULL)
    {
        stat(dp->d_name, &statut);
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, ".."))
            printf("%s\n", dp->d_name);
    }
    closedir(_dir);
}

void ls_RP(char *path)
{
    DIR *_dir;
    struct dirent *dp;

    struct stat statut;
    if ((_dir = opendir(path)) != NULL)
    {
        printf("\ncontenu>%s:\n", path);
        while ((dp = readdir(_dir)) != NULL)
        {
            // printf("contenu>%s:\n", path);
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, ".."))
                ls_RP(dp->d_name);
            stat(dp->d_name, &statut);
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, ".."))
                printf("%s\n", dp->d_name);
        }
        closedir(_dir);
        printf("\n");
    }
}

int main()
{
    puts("ls");
    mini_ls();
    puts("ls-l");
    mini_ls_l();
    puts("ls-rp");
    ls_RP(".");
}