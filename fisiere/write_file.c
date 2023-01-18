#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_ELEMS 10

int main()
{
    //se genereaza un vector cu 10 elemente la intamplare
    srand(time(NULL));
    int v[NUM_ELEMS];

    for(int i=0; i<NUM_ELEMS; i++)
    {
        v[i]=rand()%50;
    }

    FILE *fp = fopen("vector.bin", "wb"); // wb=write binary
    
    if(fp==NULL)
    {
        perror("vector.bin");
        exit(EXIT_FAILURE);
    }

    if(fwrite(v, sizeof(int), NUM_ELEMS, fp) != NUM_ELEMS)
    {
        perror("fwrite()");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fclose(fp);

    return 0;
}