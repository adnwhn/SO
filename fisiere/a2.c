/*
A2. (3 puncte) Scrieti un program "sortint" care se va lansa sub forma:
     sortint   f
 unde f este un fisier continand reprezentari interne de intregi si sorteaza
 intregii din acest fisier. Se vor folosi doar functiile de la nivelul 
 inferior de prelucrare a fisierelor si nu se vor folosi fisiere auxiliare.
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Programul %s accepta 2 argumente, nu %d \n", argv[0], argc);
        exit(EXIT_FAILURE);
    }

    int fd = open(argv[1], O_RDWR); // open for reading and writing
    
    if(fd == -1)
    {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    // size este egal cu ultima pozitie
    off_t size = lseek(fd, 0, SEEK_END);

    if(size % sizeof(int) != 0){
        fprintf(stderr, "Fisierul %s nu este fisier binar de numere intregi\n", argv[1]);
        close(fd);
        exit(EXIT_FAILURE);
    }

    int numElems = size/sizeof(int);

    // vectorul inainte de sortare
    lseek(fd, 0, SEEK_SET);

    
    for(int i = 0; i < numElems; i++)
    {
        int elem;
        read(fd, &elem, sizeof(int));
        printf("%d ", elem);
    }
    printf("\n");
    
    // sortare cu doua for-uri: compara toate numerele cu toate numerele
    for(int i = 0; i < numElems; i++)
    {
        for(int j = 0; j < numElems; j++)
        {
            int v_i = 0;
            int v_j = 0;
            lseek(fd, i*sizeof(int), SEEK_SET);
            read(fd, &v_i, sizeof(int));
            lseek(fd, j*sizeof(int), SEEK_SET);
            read(fd, &v_j, sizeof(int));
            if(v_i < v_j)
            {
                lseek(fd, i*sizeof(int), SEEK_SET);
                write(fd, &v_j, sizeof(int));
                lseek(fd, j*sizeof(int), SEEK_SET);
                write(fd, &v_i, sizeof(int));
            }
        }
    }
        
    // vectorul dupa sortare
    lseek(fd, 0, SEEK_SET);
    for(int i = 0; i < numElems; i++)
    {
        int elem;
        read(fd, &elem, sizeof(int));
        printf("%d ", elem);
    }
    printf("\n");
    return 0;
}