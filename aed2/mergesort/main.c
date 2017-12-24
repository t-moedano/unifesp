#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"

int main()
{

   int vet[11] = {25, 40, 55, 20, 44, 35, 38, 99, 10, 65, 50};

   Mergesort(0, 10, vet);

   int i;

   for (i = 0; i < 11; i++) {
    printf ("%d \n", vet[i]);
   }
    return 0;
}
