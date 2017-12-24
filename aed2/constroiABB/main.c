    //Thauany Moedano
    //RA 92486
     ///Algoritmo que dado percursos em ordem e pré ordem devolve uma árvore binária de busca///
    #include <stdio.h>
    #include <stdlib.h>

    typedef int TChave;

    typedef struct {
        TChave Chave;
        /* outros compomentes */
    } TItem;

    typedef struct SNo *TArvBin;

    typedef struct SNo {
        TItem Item;
        TArvBin Esq, Dir;
    } TNo;

    TItem *Aloca(int n)
    {
        return ((n > 0) ? ((TItem *) malloc(n * sizeof(TItem))) : (NULL));
    }

    int Carrega(TItem **PreOrdem, TItem **EmOrdem)
    {
        int i, n;

        scanf("%d", &n);

        (*PreOrdem) = Aloca(n);
        for (i = 0; i < n ; i++)
            scanf("%d", &(*PreOrdem)[i].Chave);

        (*EmOrdem) = Aloca(n);
        for (i = 0; i < n ; i++)
            scanf("%d", &(*EmOrdem)[i].Chave);

        return n;
    }

    void Libera(TArvBin *pNo)
    {
        TArvBin No;

        No = *pNo;
        if (No != NULL) {
            Libera(&No->Esq);
            Libera(&No->Dir);
            free(No);
            (*pNo) = NULL;
        }
    }

    //Função recursiva que devolve uma árvore construída a partir de dois vetores

    TArvBin Constroi(TItem *PreOrdem, TItem *EmOrdem, int esq, int dir, int *no) //Nó é passado por referencia
    {

        TArvBin pNo = NULL; //Declarando um nó nulo
        int raiz;
        if (esq <= dir) { //Enquanto esq for diferente de direita níveis de recursão são chamados

            for (raiz = esq; raiz <= dir; raiz++) {

                if ((PreOrdem)[*no].Chave == (EmOrdem)[raiz].Chave) { //Procuro o nó da pré ordem no vetor em ordem

                    TNo* No = (TNo*) malloc (sizeof(TNo)); //Crio uma subárvore com esse nó encontrado
                    No->Item = (PreOrdem)[*no];
                    *no += 1;
                    No->Esq = Constroi(PreOrdem, EmOrdem,esq, raiz-1, &(*no)); //Os filhos esq e dir são procurados a partir de cortes no vetor em ordem
                    No->Dir = Constroi(PreOrdem, EmOrdem,  raiz+1, dir, &(*no));
                    pNo = No;

                }
            }

        //Quando a recursão acaba, deveria retornar uma árvore

        }
          return(pNo);

    }








    void PosOrdem(TArvBin No)
    {
        if(No != NULL) {
            PosOrdem(No->Esq); //Imprimindo em pós ordem - Primeiro Imprime todos os filhos esq
            PosOrdem(No->Dir); //Dir e depois a raiz
            printf("%d ", No->Item.Chave);
        }
        printf("\n");
    }

    int main()
    {
        TItem *PreOrdem, *EmOrdem;
        TArvBin Raiz = NULL;
        int n, esq = 0, dir, no = 0;

        n = Carrega(&PreOrdem, &EmOrdem);
        dir = n - 1;
        Raiz = Constroi(PreOrdem, EmOrdem,  esq, dir, &no);
        PosOrdem(Raiz);
        Libera(&Raiz);
        free(EmOrdem);
        free(PreOrdem);

        return 0;
    }
