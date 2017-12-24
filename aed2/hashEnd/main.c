//Thauany Moedano
//RA: 92486

#include <stdio.h>
#include <stdlib.h>

#define NIL -1

typedef int TChave;

typedef struct {
	TChave Chave;
	/* outros compomentes */
} TItem;

typedef int TIndice;

typedef struct {
	TItem *Item;
	TIndice m, n;
} THash;

TIndice h(THash *T, TChave k)
{
	return k % T->m;
}

TIndice H(THash *T, TChave k, int i)
{
  return (h(T, k) + i) % T->m;
}

THash *Inicializa(int m)
{
	TIndice i;
	THash *T;

	T = (THash *) malloc(sizeof(THash));

	T->n = 0; T->m = m;
	T->Item = (TItem *) malloc(T->m * sizeof(TItem));
	for (i = 0; i < T->m; i++)
		T->Item[i].Chave = NIL;

	return T;
}

TIndice Pesquisa(THash *T, TChave x)
{
	int i = 0, pos = H(T, x, i);
	while(i < T->m && T->Item[pos].Chave != NIL) {

         pos = H(T, x, i); //Pesquiso qual será a posição do veor
        if(T->Item[pos].Chave == NIL)
            return(NIL);
        if(T->Item[pos].Chave == x)
            return(H(T,x,i)); //Se a busca obteve sucesso retorno 1
        i++;
	}


	return(NIL); //Caso contrário retorna-se NIL
}

int Insere(THash *T, TItem x)
{
	int i = 0, pos = H(T, x.Chave, i);

	if (Pesquisa(T, x.Chave) != NIL ) //Pesquiso o item para verificar se ele nao está na tabela
        return 1;
	while(i < T->m) {
        pos = H(T, x.Chave, i); //Procuro uma posição valida para a chave
         if(T->Item[pos].Chave == NIL) { //Se a chave estiver vazia eu adiciono
            T->Item[pos] = x;
            return(0);
         }
        i++;
	}

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
		if (aux->Item != NULL) free(aux->Item);
		free(aux);
		(*T) = NULL;
	}
}

void Imprime(THash *T)
{
	int i;
	if (T->m > 0) {
		for (i = 0; i < T->m; i++)
			printf("[%d] %d\n", i, T->Item[i].Chave);
	}
}

int main()
{
	TIndice m;
	THash *T;
	TItem x;

	scanf("%d", &m);
	T = Inicializa(m);
	Carrega(T);
	scanf("%d", &x.Chave);
	if (Pesquisa(T, x.Chave) == NIL)
		Insere(T, x);
	Imprime(T);
	Libera(&T);

	return 0;
}
