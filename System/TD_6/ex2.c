#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    // Ouvrir le fichier en lecture/écriture
    FILE *file = fopen("test.txt", "w+");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    // Créer le processus fils
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Error creating child process");
        return 1;
    }

    if (pid == 0)
    {
        // Processus fils
        // Écrire "foo" à l'offset 3 dans le fichier
        fseek(file, 3, SEEK_SET);
        printf("child write");
        fwrite("foo", 1, 3, file);

        // Pause de 2 secondes
        sleep(2);

        // Lire et afficher 3 caractères à l'offset 3
        fseek(file, 3, SEEK_SET);
        char buffer[4];
        fread(buffer, 1, 3, file);
        buffer[3] = '\0';
        printf("Child read: %s\n", buffer);
    }
    else
    {
        wait(NULL);
        // Processus père
        // Écrire "bar" à l'offset 3 dans le fichier
        fseek(file, 3, SEEK_SET);
        printf("parent write");
        fwrite("bar", 1, 3, file);

        // Pause de 1 seconde
        sleep(1);

        // Lire et afficher 3 caractères à l'offset 3
        fseek(file, 3, SEEK_SET);
        char buffer[4];
        fread(buffer, 1, 3, file);
        buffer[3] = '\0';
        printf("Parent read: %s\n", buffer);

        // Attendre la fin du processus fils
        // wait(NULL);
    }

    // Fermer le fichier
    fclose(file);

    return 0;
}
