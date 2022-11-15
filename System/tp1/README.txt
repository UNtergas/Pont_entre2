********EX5:********

on le fait parce qu’avec un malloc normal, le zone mémoire alloué est init avec un value quelcon, donc pour une meilleur optimization, on alloue le mémoire et tous le met à ‘\0’

**EX6**:

le fonction free signaler les zones qu’on veut plus ultiliser pour le reecrire(data overwrtite) quand on appel a malloc oc calloc ou realloc  

**********EX12:**********

on teste avec un declaration d’une pointer sur 1 char,  et apres on l’afficher le contenu pointe par cet pointeur pour assurer que la memoire a bien reservee pour le pointer

pour tester le free, on peut ajouter un compteur(flag) :

idée c’est après on a déjà free un bloc mémoire, donc après on fait le calloc, le nombre d’élement dans notre list chainée devrait reste unchangé

>> flag (avant calloc) = flag (après calloc) → free succédé;

>> flag (avant calloc) < flag (après calloc) → free échec, un nouvel bloc était ajouté au fin du list

ou on peut tester le free avec printf %p pour imprimer l’adresse du pointeur, le free sera reussi si par example, on a un pointer _ptr pointe vers 0xfff231 par example, après on avait free *ptr, quand on fera le calloc sur _ptr2, il doit pointé sur le même adresse.*

************EX17:************

si on mets mini_printf selon les critères du exercise 16,si on met”a”, on trouve pas ‘\0’ pour arreter et si on rencontre un ‘\n’ au milieu du chain, on perdu tous les élements après le saut du ligne,

**********EX20:**********

si le nombre de caractères saisis est égal à la taille du buffer, donc le caractère signifier le fin du string ‘\0’ sera pas ajouter, donc on doit avoir une attribut read_result qui compte le nombre de caractère lu par la commande read() et après on ajoute le ‘\0’ à la position read_result du buffer.

**********EX22:**********

Pour le fonction mini_strcpy, si le taille du source est plus grand que le destination, y aura des problème, donc pour le fixer, on fait le mini_strncpy qui prend un extra parametre, c’est le nombre de caractère qu’on veut copier

**********EX34:**********

Si on termine le programme quand le buffer d’écriture n’était pas plein, tous les infos qu’on veut écrire dans le fichier sera tout perdu, donc on doit ajouter le mini_fflush() lors de la termination du program dans mini_exit()

> ******BREF RESUMÉ DES FONCTION******


****1.1 Gestion du memoire:****

je implemente le mini_calloc avec un liste_chainé, j’ai fait un alignement pour que chaque bloc dans le list aura la même taille.

principe du malloc_list:

-parcourir le list, si on trouvé un spot libre(marqué avec statut =0) le zone sera pointé vers d’ici pour réécriture.

-sinon, un nouvel bloc sera ajouté à la fin du list.

**********1.2 Gestion des chaîne de caractères:**********

j’ai implement tous les printf,scanf, strcpy, strncpy , strcmp ,strlen et perror

Pour le printf, j’ai ajoute la capacité d’écrire le caractère ‘\n’ au sein d’une chaîne de caractères à stdout.

Pour le perror, j’ai écrit un fonction extra mini_itoa qui convertir le entier à chaîne du caractères pour afficher le code du errno.

****1.3 Gestion des Entrées/Sorties:****

J’ai implementé un liste de MYFILE file, quand un nouvel file pointeur est créé, il sera ajouté au debut du list, quand on fait le fclose(), on l’enlève et le free avec mini_free().

Pour le mini_exit(), il parcourir le file liste, si le liste n’est pas encore NULL, tous les file sera fllushé pour assurer qu’aucune infos en terme des mini_fwrite().

**2 Commandes Système et Mini Shell:**

Pour le shell, j’ai cree un fonction run_case, qui traitera le command saisir pendant l’execution du mini_shell, il sépare la chaîne en mots, enlève les caractères espace ‘ ‘  unneccessaire, et après les passe en un switch case correspond à chaque command système

Dans le main , j’ai utiliser le fork() pour créer 2 processus, le processus père sera lequel gêne le boucle de entrer command et le wait() pour attendre le processus fils de terminer, le run_case sera placé dedans le processus file avec un mini_exit().