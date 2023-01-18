/*
F5. (1 punct) Scrieti un program care primeste ca argument in linia de
 comanda un intreg si afisaza imaginea sa in oglinda (ex: 1234 -> 4321).
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        fprintf(stderr, "Programul %s accepta 2 argumente, nu %d \n", argv[0], argc);
        exit(EXIT_FAILURE);
    }

    char *eroarePtr = NULL;
    int x = strtol(argv[1], &eroarePtr, 10); // baza 10

    // daca argv[1] este caracterul nul sau daca eroarea pointeaza diferit de null
    if(*argv[1] == '\0' || *eroarePtr != '\0')
    {
        fprintf(stderr, "Stringul %s nu este numeric, contine %s\n", argv[1], eroarePtr);
        exit(EXIT_FAILURE);
    }

    //daca numarul e format doar dintr-o cifra, oglinditul lui este chiar el insusi
    if (x<10 && x>-10)
    {
        printf("Oglinditul numarului %d este : %d\n", x, x);
        return 0;
    }

    int oglindit = 0;
    int copie = x;

    if(copie%10 == 0){
        fprintf(stderr, "Oglinditul numarului %d nu are sens\n", x);
        exit(EXIT_FAILURE);
    }

    while (copie!=0)
    {
        oglindit = copie%10 + oglindit * 10;
        copie /= 10;
    }

    printf("Oglinditul numarului %d este : %d\n", x, oglindit);

    return 0;
}