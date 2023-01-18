/*
D2. (4 puncte) Program care primeste ca argument in linia de comanda un
 director si calculeaza suma dimensiunilor fisierelor din arborescenta cu
 originea in el.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

off_t total = 0;

void functie_recursiva(const char *dirName)
{
    DIR *dir = opendir(dirName);
    if(dir == NULL){
        perror(dirName);
        exit(EXIT_FAILURE);
    }
    //se salveaza directorul initial
    char *directorCurent = getcwd(NULL, 0);

    chdir(dirName);

    struct dirent *entry; //pointer catre primul elem
    while((entry = readdir(dir)) != NULL) //entry devine null cand a ajuns la finalul listei de elem
    {
        //sa nu fie recursivitate infinita 
        //se verifica sa nu fie intrare in directorul curent (.)
        //sau sa nu fie o intoarcere recursiva care nu poate trece de root (..)
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        
        //stat da informatii detaliate despre fisier
        struct stat filestat;
        if(stat(entry->d_name, &filestat) == -1)
        {
            perror("stat()");
            exit(EXIT_FAILURE);
        }

        total += filestat.st_size;

        //se verifica daca elementul e director pentru a intra pe urmatorul nivel din ierarhie
        if(S_ISDIR(filestat.st_mode))
        {
            functie_recursiva(entry->d_name);
        }
    }
    //se revine in directorul initial
    chdir(directorCurent);
    closedir(dir);
    //se dezaloca spatiul de memorie
    free(directorCurent);
}

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Programul %s accepta 2 argumente, nu %d \n", argv[0], argc);
        exit(EXIT_FAILURE);
    }

    char *dirName = argv[1];

    struct stat flinit;
    if (stat(dirName, &flinit) == -1)
    {
        perror("stat()");
        exit(EXIT_FAILURE);
    }
    total += flinit.st_size;

    functie_recursiva(dirName);
    printf("Dimensiune totala: %ld\n", total);
    return 0;
}