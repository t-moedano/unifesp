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

int retornaDigito(TChave x, int digito)
{
    return ((x >> digito) & 1);
}

int EhInterno(TArvBin No)
{
    return ((No == NULL) || (No->Esq != NULL) || (No->Dir != NULL));
}

int EhExterno(TArvBin No)
{
    return ((No != NULL) && (No->Esq == NULL) && (No->Dir == NULL));
}

TArvBin Inicializa()
{
    return NULL;
}

//A pesquisa deve retornar o NO pesquisado ou se nao encontrar, retornar NULL
TArvBin Pesquisa(TArvBin Raiz, TChave x, int d){
    if(Raiz == NULL) //Se a raiz é NULL, retorna NULL
        return NULL;
    //Se o nó é interno, devemos percorrer a árvore para Esq ou Dir
    else if(EhInterno(Raiz)) {
        //Se o digito é 1, a pesquisa corre para a direita
        if(retornaDigito(x, d) == 1)
            return(Pesquisa(Raiz->Dir, x, d+1));
        //Se o digito é 0, a pesquisa corre para a esquerda
        else if(retornaDigito(x, d) == 0)
            return(Pesquisa(Raiz->Esq, x, d+1));
    }
        //Se chegarmos em um nó externo, verificamos se a chave bate com a chave desejada
        else if(EhExterno(Raiz)) {
            if(Raiz->Item.Chave == x)
                return(Raiz); //Se sim devemos retornar o nó
            else
                return(NULL); //Se nao, retornamos NULL
        }
}
//SeparaNos separa dois nós que tem alguns digitos em comum
void SeparaNos (TArvBin *T, TItem J, int d) {

        TArvBin K = *T; //Criando um auxiliar
        *T = (TArvBin) malloc (sizeof(TNo));

        //Se o dígito da chave é zero, ela deve automaticamente cair para a esquerda
        if(retornaDigito(K->Item.Chave, d) == 0) {
            (*T)->Esq = K;
            //Se o dígito do nó também é zero, propagamos recursivamente o SeparaNos
            if(retornaDigito(J.Chave, d) == 0) {
                (*T)->Dir = NULL;
                SeparaNos(&(*T)->Esq, J, d+1);
            }
            //Se o próximo dígito é 1, basta jogar a chave a inserir para a direita
            else {

                TArvBin No = (TArvBin) malloc (sizeof(TNo));
                No->Item = J;
                No->Esq = NULL;
                No->Dir = NULL;
                (*T)->Dir = No;
            }
        }
        //O mesmo ocorre de maneira simétrica quando coincide o número 1
        else {
             (*T)->Dir = K;
            if(retornaDigito(J.Chave, d) == 0) {
                TArvBin No = (TArvBin) malloc (sizeof(TNo));
                No->Item = J;
                No->Esq = NULL;
                No->Dir = NULL;
                (*T)->Esq = No;
            }

            else {
                (*T)->Esq = NULL;
                 SeparaNos(&(*T)->Dir, J, d+1);
            }
        }
}

int Insere(TArvBin *pRaiz, TItem x, int d) {
    //Se a raiz é NULL podemos inserir diretamente
    if(*pRaiz == NULL) {
        TArvBin No = (TArvBin) malloc (sizeof(TNo));
        No->Item = x;
        No->Esq = NULL;
        No->Dir = NULL;
        *pRaiz = No;
        return(1);
    }
    //Senao verificamos se é um nó interno para percorrer a árvore semelhante a ABB
    else if(EhInterno(*pRaiz)) {

        if(retornaDigito(x.Chave, d) == 1)
            return(Insere(&(*pRaiz)->Dir, x, d+1));

        else if(retornaDigito(x.Chave, d) == 0)
            return(Insere(&(*pRaiz)->Esq, x, d+1));
    }
    //No caso de ser externo devemos verificar duas condições
    else if(EhExterno(*pRaiz)) {

        if((*pRaiz)->Item.Chave == x.Chave)
            return(0); //Se a chave ja existe, retorna zero

        else { //Senao, devemos separar os nós e retornar o sucesso da inserção
            SeparaNos(pRaiz, x, d);
            return(1);
        }
    }
}

    void Carrega(TArvBin *pNo)
    {
        int i, n, d = 0;
        TItem x;

        scanf("%d", &n);
        for (i = 0; i < n ; i++) {
            scanf("%d", &x.Chave);
            Insere(pNo, x, d);
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
            printf("(");
            if (EhExterno(No))
                printf("C%d", No->Item.Chave);
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
        int d = 0;

        Raiz = Inicializa();
        Carrega(&Raiz);
        scanf("%d", &x.Chave);
        if (Pesquisa(Raiz, x.Chave, d) == NULL)
            Insere(&Raiz, x, d);
        Imprime(Raiz);
        Libera(&Raiz);

        return 0;
    }
