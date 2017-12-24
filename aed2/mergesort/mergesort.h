#ifndef MERGESORT_H_INCLUDED
#define MERGESORT_H_INCLUDED
#endif // MERGESORT_H_INCLUDED

                        //n/2
void Intercala (int vet[], int inicio, int meio, int fim) {

   int aux[fim-inicio];
   int i, j, k;
   i = 0;
   for (k = inicio; k <= meio; k++) {
        aux[i] = vet[k];
        i++;
   }
   j = ((fim-inicio)/2)+1;
   for (k = fim; k > meio; k--) {
        aux[j] = vet[k];
        j++;
   }

   i = 0;
   j = fim-inicio;

   for (k = inicio; k <= fim; k++) {

        if(aux[i] <= aux[j]) {
            vet[k] = aux[i];
            i++;
        }
        else {
            vet[k] = aux[j];
            j--;
        }

   }


}
void Mergesort (int inicio, int fim, int vet[]) {

    int meio;
    if (inicio < fim) {
        meio = (inicio+fim)/ 2;
        Mergesort(inicio, meio, vet);
        Mergesort(meio+1, fim, vet);
        Intercala(vet, inicio, meio, fim);

    }

}
