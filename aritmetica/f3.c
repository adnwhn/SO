/*
F3. (2.5 puncte) Scrieti un program care primeste ca argument in linia de
 comanda un intreg si afisaza descompunerea sa in factori primi.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

    if(x<2) // daca x este 1, 0 sau numar negativ
    {
        fprintf(stderr, "Numarul %d nu poate fi descompus in factori primi\n", x);
        exit(EXIT_FAILURE);
    }

    printf("Descompunerea numarului %d in factori primi este: \n", x);

    /*
    int c=2;
    while(x>1)
    {
        if(x%c==0)
        {
            printf("%d ", c);
            x/=c;
        } 
        else
        {
            c++;
        }
    }
    */

   while(x%2==0)
   {
    printf("%d ", 2);
    x=x/2;
   }

   for(int i=3; i <= sqrt(x); i = i+2)
   {
        while(x%i==0)
        {
            printf("%d ", i);
            x/=i;
        }
   }

   if(x>2)
   {
    printf("%d ", x);
   }

    printf("\n");

    return 0;
}