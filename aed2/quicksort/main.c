    //Thauany Moedano
    //RA 92486
    //26/03/2015
    //Quicksort
    #include <stdio.h>
    #include <stdlib.h>

    typedef int TChave;

    typedef struct {
        TChave Chave;
        /* outros compomentes */
    } TItem;

    TItem *Aloca(int n)
    {
        return ((n > 0) ? ((TItem *) malloc(n * sizeof(TItem))) : (NULL));
    }

    int Carrega(TItem **A)
    {
        int i, n;

        scanf("%d", &n);

        (*A) = Aloca(n);
        for (i = 0; i < n ; i++)
            scanf("%d", &(*A)[i].Chave);

        return n;
    }

    void Libera(TItem **A)
    {
        if ((*A) != NULL) {
            free(*A);
            (*A) = NULL;
        }
    }

    void Imprime(TItem *A, int n)
    {
        int i;
        if (n > 0) {
            printf("%d", A[0].Chave);
            for (i = 1; i < n; i++)
                printf(" %d", A[i].Chave);
            printf("\n");
        }
    }

    int quickSort_particao(TItem *A, int p, int r)
    {
        int j, i = -1; //Declarando variaveis. O j se incicia em um elemento antes de i, ou seja, -1
        TItem troca; //Declarando uma variavel auxiliar para fazer trocas

        for (j = 0; j < r; j++) {
            if (A[r].Chave >= A[j].Chave) {
                i++; //Neste for particionamos o vetor, deixando os elementos menores que o pivo antes dele, e os maiores depois
                troca = A[i];
                A[i] = A[j];
                A[j] = troca;

            }

        }
        troca = A[i+1]; //No fim retornamos a posição que o pivo está para particioná-lo novamente
        A[i+1] = A[r];
        A[r] = troca;
        return(i+1);
    }

    void quickSort_ordena(TItem *A, int p, int r)
    {
        int pivo;
        if (p <= r) { //Quicksort ordena funciona recursivamente, portanto particionamos o vetor e chamamos a função para cada metade
            pivo = quickSort_particao(A, p, r);
            quickSort_ordena(A, p, pivo-1);
            quickSort_ordena(A, pivo+1, r);
        }

    }

    void quickSort(TItem *A, int n)
    {
        quickSort_ordena(A, 0, n-1);
    }

    int main()
    {
        TItem *A;
        int n;

        n = Carrega(&A);
        quickSort_particao(A, 0, n-1);
        Imprime(A, n);
        quickSort(A, n);
        Imprime(A, n);
        Libera(&A);

        return 0;
    }
