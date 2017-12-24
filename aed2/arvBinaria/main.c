    //Thauany Moedano
    //RA: 92486
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

    TArvBin Inicializa()
    {
        return NULL;
    }

    TArvBin Pesquisa(TArvBin No, TChave x)
    {   //Primeiro verifica se a árvore nao está vazia
         if (No == NULL)
            return(NULL);
        //Caso contrário, verificamos se a chave é maior ou menor
         else {
            if (x > No->Item.Chave) //Assim chamamos a pesquisa recursivamente
                Pesquisa(No->Dir, x);

            else if (x < No->Item.Chave)
                Pesquisa(No->Esq, x);

            else if (x == No->Item.Chave)
                return(No);
        }


    }

    int Insere(TArvBin *pNo, TItem x)
    { //Inserção funciona de maneira semelhante a pesquisa
        if (*pNo == NULL) { //Caso a pesquisa seja sem sucesso inserimos utilizando a alocação
            TNo* No = (TNo*) malloc (sizeof(TNo));
            No->Item = x;
            No->Esq = NULL;
            No->Dir = NULL;
            *pNo = No;
        }
        //Caso contrário percorremos a árvore
         else {
            if (x.Chave > (*pNo)->Item.Chave)
                Insere(&(*pNo)->Dir, x);

            else if (x.Chave < (*pNo)->Item.Chave)
                Insere(&(*pNo)->Esq, x);

            else if (x.Chave == (*pNo)->Item.Chave)
                return(1);
        }


    }
    //Função auxiliar que percorre toda a direita da árvore
    void libera (TArvBin *Aux, TArvBin *Susc) {

        if ((*Susc)->Esq == NULL) {
            (*Aux)->Item = (*Susc)->Item;
            *Aux = *Susc;
            *Susc = (*Susc)->Dir;
           // return (&(*Aux)->Esq);
        }
        else
            libera(Aux, &(*Susc)->Esq);
    }

    int Remove(TArvBin *pNo, TChave x)
    {
        TArvBin Aux;
        if (*pNo == NULL)
            return(0);

         else {
            if (x > (*pNo)->Item.Chave)
                Remove(&(*pNo)->Dir, x);

            else if (x < (*pNo)->Item.Chave)
                Remove(&(*pNo)->Esq, x);

            else if (x == (*pNo)->Item.Chave) { //Pesquisa com sucesso deve remover o nó
                Aux = *pNo;

                if ((*pNo)->Esq == NULL) //Se só existe um filho a esquerda, trocamos de lugar com a direita
                    *pNo = Aux->Dir;
                else if ((*pNo)->Dir ==  NULL) //Se so existe um filho a direita, trocamos com a esquerda
                    *pNo = Aux->Esq;

                else
                    libera(&Aux, &Aux->Dir); // Se ele possui os dois filhos, percorremos toda a direita e troacmos o ultimo da direita
                free(Aux);
            }

        }
    }


    void Carrega(TArvBin *pNo)
    {
        int i, n;
        TItem x;

        scanf("%d", &n);
        for (i = 0; i < n ; i++) {
            scanf("%d", &x.Chave);
            Insere(pNo, x);
        }
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

    void Imprime(TArvBin No)
    {
        if (No != NULL) {
            printf("(C%d", No->Item.Chave);
            Imprime(No->Esq);
            Imprime(No->Dir);
            printf(")");
        }
        else
            printf("()");
    }

    int main()
    {
        TArvBin Raiz;
        TItem x;

        Raiz = Inicializa();
        Carrega(&Raiz);
        scanf("%d", &x.Chave);
        if (Pesquisa(Raiz, x.Chave) == NULL)
            Insere(&Raiz, x);
        else
        Remove(&Raiz, x.Chave);
        Imprime(Raiz);
        Libera(&Raiz);

        return 0;
    }
