#include "mini_lib.h"
void print_stat(char *ref, struct stat *statut)
{
    struct passwd *pw;
    struct group *gr;
    char *type = mini_calloc(sizeof(char), 1);
#define LTEMPS 32
    char pws[9], grs[9], temps[LTEMPS];

    type = "?";
    if (S_ISREG(statut->st_mode))
        type = "-";
    else if (S_ISDIR(statut->st_mode))
        type = "d";
    else if (S_ISCHR(statut->st_mode))
        type = "c";
    else if (S_ISBLK(statut->st_mode))
        type = "b";
    else if (S_ISFIFO(statut->st_mode))
        type = "p";
    else if (S_ISLNK(statut->st_mode))
        type = "l";

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

    if (statut->st_mode & S_IRUSR)
    {
        mini_printf("r");
    }
    else
    {
        mini_printf("-");
    }
    if (statut->st_mode & S_IWUSR)
    {
        mini_printf("w");
    }
    else
    {
        mini_printf("-");
    }
    if (statut->st_mode & S_IXUSR)
    {
        mini_printf("x");
    }
    else
    {
        mini_printf("-");
    }
    if (statut->st_mode & S_IRGRP)
    {
        mini_printf("r");
    }
    else
    {
        mini_printf("-");
    }
    if (statut->st_mode & S_IWGRP)
    {
        mini_printf("w");
    }
    else
    {
        mini_printf("-");
    }
    if (statut->st_mode & S_IXGRP)
    {
        mini_printf("x");
    }
    else
    {
        mini_printf("-");
    }
    if (statut->st_mode & S_IROTH)
    {
        mini_printf("r");
    }
    else
    {
        mini_printf("-");
    }
    if (statut->st_mode & S_IWOTH)
    {
        mini_printf("w");
    }
    else
    {
        mini_printf("-");
    }
    if (statut->st_mode & S_IXOTH)
    {
        mini_printf("x");
    }
    else
    {
        mini_printf("-");
    }
    mini_printf(" ");
    mini_printf(temps);
    mini_printf(" ");
    mini_printf(type);
    // mini_printf(mini_itoa(statut->st_nlink));
    mini_printf(pws);
    mini_printf(" ");
    mini_printf(grs);
    mini_printf(" "); // mini_printf(mini_itoa(statut->st_size));
    mini_printf(ref);
    mini_printf("\n");
}
void mini_ls()
{
    DIR *_dir;
    struct dirent *dp;

    struct stat statut;
    if ((_dir = opendir(".")) == NULL)
    {
        mini_perror("dir can't open");
    }
    while ((dp = readdir(_dir)) != NULL)
    {
        stat(dp->d_name, &statut);
        if (mini_strcmp(dp->d_name, ".") != 0 && mini_strcmp(dp->d_name, ".."))
            print_stat(dp->d_name, &statut);
    }
    closedir(_dir);
}

int main(int argc, char **argv)
{
    mini_ls();
}