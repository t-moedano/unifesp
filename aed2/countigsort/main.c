    //Thauany Moedano
    //RA 92486
    //25/03/2015
    //Couting

    #include <math.h>
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

    TChave maiorChave(TItem *A, int n)
    {
        TChave max;
        int i;

        max = 0;
        for (i = 0; i < n; i++)
            if (A[i].Chave > max)
                max = A[i].Chave;

        return max;
    }



    void Ordena(TItem *A, int n, int k) // Ajuste o parametro do seu metodo aqui!
    {
        k++; //Variavel K define a maior chave. Pra criar um vetor que vai de 0 a k, precisamos criar um vetor com k+1 elementos
        TItem *C = Aloca(k); //Alocando vetores C e B auxiliares
        TItem *B = Aloca(n);
        int p; //Controla índices

        //Inicializando o vetor C (que faz a contagem)
        for(p = 0; p < k; p++) {
            C[p].Chave = 0;
        }

        //Verificando e acumulando valores
        for (p = 0; p < n; p++) {
            C[A[p].Chave].Chave++;
        }

        //Agora a partir de primeira posição + 1 (1), acumulamos os valores
        for (p = 1; p < k; p++) {
            C[p].Chave += C[p-1].Chave;
        }

        //Agora posicionamos os valores na posição correta
        for(p = n-1; p >= 0; p--) {
            C[A[p].Chave].Chave--;
            B[C[A[p].Chave].Chave] = A[p];
        }

        //Copiamos o vetor B para o vetor original
        for(p = 0; p < n; p++) {
            A[p] = B[p];
        }

        free(C);
        free(B);

    }

    int main()
    {
        TItem *A;
        TChave k;
        int d, n;

        n = Carrega(&A);
        k = maiorChave(A, n);

        Ordena(A, n, k); // Ajuste o parametro do seu metodo aqui!
        Imprime(A, n);
        Libera(&A);

        return 0;
    }
