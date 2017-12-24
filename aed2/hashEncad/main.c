//Thauany Moedano
//RA 92486

#include <stdio.h>
#include <stdlib.h>

typedef struct SLista *PLista;

typedef int TChave;

typedef struct {
	TChave Chave;
	/* outros compomentes */
} TItem;

typedef int TIndice;

typedef struct {
	PLista Lista;
	TIndice m, n;
} THash;

typedef struct SNo *TCelula;

typedef struct SNo {
	TItem Item;
	TCelula Prox;
} TNo;

typedef struct SLista {
	TCelula Primeiro, Ultimo;
} TLista;

void TLista_Inicializa(TLista *L)
{
	L->Primeiro = (TCelula) malloc(sizeof(TNo));
	L->Ultimo = L->Primeiro;
	L->Primeiro->Prox = NULL;
}

int TLista_EhVazia(TLista *L)
{
	return (L->Primeiro == L->Ultimo);
}

/* Insere um item no final da lista */
void TLista_Insere(TLista *L, TItem x)
{

        L->Ultimo->Prox = (TCelula) malloc(sizeof(TNo));
        L->Ultimo = L->Ultimo->Prox;
        L->Ultimo->Item = x;
        L->Ultimo->Prox = NULL;

}

/* Remove um dado no da lista */
void TLista_Remove(TLista *L, TCelula No)
{
	TCelula aux;

	aux = No->Prox;
	No->Prox = aux->Prox;
	if (No->Prox == NULL)
		L->Ultimo = No;
	free(aux);
}

/* Imprime os elementos da lista */
void TLista_Imprime(TLista *L)
{
	TCelula No;

	No = L->Primeiro->Prox;
	while (No != NULL) {
		printf(" %d", No->Item.Chave);
		No = No->Prox;
	}
}

void TLista_Libera(TLista *L)
{
	TCelula No;

	while (L->Primeiro->Prox != NULL) {
		No = L->Primeiro->Prox;
		L->Primeiro->Prox = No->Prox;
		free(No);
	}
	free(L->Primeiro);
}

TIndice h(THash *T, TChave k)
{
	return k % T->m;
}

THash *Inicializa(int m)
{
	TIndice i;
	THash *T;

	T = (THash *) malloc(sizeof(THash));

	T->n = 0; T->m = m;
	T->Lista = (PLista) malloc(T->m * sizeof(TLista));
	for (i = 0; i < T->m; i++)
		TLista_Inicializa(&T->Lista[i]);

	return T;
}

TCelula Pesquisa(THash *T, TChave x)
{   //Procura-se o índice utilizando a função de transformação
    int i = h(T, x);
    TCelula No;
    No = T->Lista[i].Primeiro; //Atribui esse índice a uma lista
    if(!TLista_EhVazia(&T->Lista[i])) {
        while(No != NULL) { //Procura o nó na lista
            if(No->Item.Chave == x) {
                return(No); //Caso for encontrado, ele é retornado
            }
        No = No->Prox;
        }
    }
    return(NULL);
}

int Insere(THash *T, TItem x)
{

	int i = h(T, x.Chave); //Para inserir basta saber em qual lista o nó deve ser inserido

	TCelula No;
    No = T->Lista[i].Primeiro; //Atribui esse índice a uma lista

        while(No != NULL) { //Procura o nó na lista
            if(No->Item.Chave == x.Chave) {
                return(0);
            }
        No = No->Prox;
        }
	TLista_Insere((&T->Lista[i]), x);
                return(1);


}

int Remove(THash *T, TChave x)
{
	int i = h(T, x);
    TCelula No;
    No = T->Lista[i].Primeiro;
    //Para remover precisamos saber o antecessor ao nó que será removido
    while(No != NULL) {
        if(No->Prox->Item.Chave == x) {
            TLista_Remove((&T->Lista[i]), No);//Ao encontrar esté nó será passado na função remove
            return(1);
        }
        No = No->Prox;
    }
    return(0);
}

void Carrega(THash *T)
{
	int i, n;
	TItem x;

	scanf("%d", &n);
	for (i = 0; i < n ; i++) {
		scanf("%d", &x.Chave);
		Insere(T, x);
	}
}

void Libera(THash **T)
{
	THash *aux;
	int i;

	aux = *T;
	if (aux != NULL) {
		for (i = 0; i < aux->m; i++) TLista_Libera(&aux->Lista[i]);
		if (aux->Lista != NULL) free(aux->Lista);
		free(aux);
		(*T) = NULL;
	}
}

void Imprime(THash *T)
{
	int i;
	if (T->m > 0) {
		for (i = 0; i < T->m; i++) {
			printf("[%d]", i);
			TLista_Imprime(&T->Lista[i]);
			printf("\n");
		}
	}
}

int main()
{
	TIndice m;
	THash *T;
	TItem x;
	//TCelula No;

	scanf("%d", &m);
	T = Inicializa(m);
	Carrega(T);
	scanf("%d", &x.Chave);
	if (Pesquisa(T, x.Chave) == NULL)
		Insere(T, x);
	else
		Remove(T, x.Chave);
	Imprime(T);
	Libera(&T);

	return 0;
}
