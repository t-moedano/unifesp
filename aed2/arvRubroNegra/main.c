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
	int cor; //1 - rubro ; 0 - negro
} TNo;

//Calcula a altura Negra de uma árvore qualquer
int AlturaNegra(TArvBin No)
{
    int esq, dir;
    if(No == NULL)
        return(0);
    else {
        esq = AlturaNegra(No->Esq); //Conta a altura negra da esquerda
        dir = AlturaNegra(No->Dir); //Conta a altura negra da direita
    }

    if(esq > dir)
        return(EhNegro(No)+esq); //Retorna somente o número de nós negros
    else
        return(EhNegro(No)+dir);
}

int EhNegro(TArvBin No)
{
return (No == NULL) || (No->cor == 0);
}
int EhRubro(TArvBin No)
{
return (No != NULL) && (No->cor == 1);
}

//Verifica se uma árvore é Rubro Negra
int ArvoreARN(TArvBin No)
{
    if(No == NULL || (ArvoreARN(No->Esq) && ArvoreARN(No->Dir))) //Se o nó e NULL e se Dir e Esq são ARN, a árvore é ARN
        return(1);

    //Se a Altura Negra da direita e da esquerda são diferentes ou se existem duplos rubros, a árvore não é ARN
    if(AlturaNegra(No->Dir) != AlturaNegra(No->Esq) || (EhRubro(No) && (EhRubro(No->Esq) || EhRubro(No->Dir))))
        return(0);

}
//Função que inverte as cores de um nó
void TrocaCores(TArvBin No)
{
    if(No != NULL) {
    if(EhNegro(No)) //Se o nó é negro, ele passa a ser rubro
        (No)->cor = 1;
    else if(EhRubro(No)) //Se o nó é rubro, ele passa a ser negro
        (No)->cor = 0;
    }
}

void RotacaoDireita(TArvBin *pA)
{
	TArvBin pB = (*pA)->Esq;
	(*pA)->Esq = pB->Dir;
    pB->Dir = (*pA);
    (*pA) = pB;
}

void RotacaoEsquerda(TArvBin *pA)
{
    TArvBin pB = (*pA)->Dir;
	(*pA)->Dir = pB->Esq;
    pB->Esq = (*pA);
    (*pA) = pB;
}


void BalancaNo(TArvBin *Avo, TArvBin *Pai, TArvBin *Filho)
{
    TArvBin Tio; //Declarando e definindo o tio
    //Verificando se é necessário rebalancear a árvore
    if(EhRubro(*Pai) && EhRubro(*Filho) && (Avo) != NULL) {

        //Definindo quem é o tio
        if((*Avo)->Esq == (*Pai))
            Tio = (*Avo)->Dir;
        else if((*Avo)->Dir == (*Pai))
            Tio = (*Avo)->Esq;

        //Caso 01 - Tio é rubro - basta colorir todos os envolvidos
        if(EhRubro(Tio)){
            TrocaCores(*Pai);
            TrocaCores(Tio);
            TrocaCores(*Avo);
        }
        //Caso 02 - Tio é  negro
         else if(EhNegro(Tio)) {

            if((*Avo)->Dir == (*Pai)){
                if((*Pai)->Esq == (*Filho)) //Subcaso 02 - Pai e filho de lados opostos, faço uma rotação para cair no subcaso 03
                    RotacaoDireita(Pai);
                TrocaCores(*Avo); //Subcaso 02 - Troca cores e faz uma rotação no avô
                TrocaCores(*Pai);
                RotacaoEsquerda(Avo);

            }
            //Os mesmos casos se repetem de maneira simétrica
            else if((*Avo)->Esq == (*Pai)){
                if((*Pai)->Dir == (*Filho))
                    RotacaoEsquerda(Pai);
                TrocaCores(*Avo);
                TrocaCores(*Pai);
                RotacaoDireita(Avo);
            }
        }
    }
 }


TArvBin Inicializa()
{
	return NULL;
}
//Função que insere um nó
int InsereRec(TArvBin *Pai, TArvBin *Avo, TItem x) {

    if (*Pai == NULL) { //Caso a pesquisa seja sem sucesso inserimos utilizando a alocação
        TNo* No = (TNo*) malloc (sizeof(TNo));
        No->cor = 1;
        No->Item = x;
        No->Esq = NULL;
        No->Dir = NULL;
        *Pai = No;
        return(1);
    }
    //Caso contrário percorremos a árvore
     else {
        if (x.Chave > (*Pai)->Item.Chave) {
                InsereRec(&(*Pai)->Dir, Pai, x);
                BalancaNo(Avo, Pai, &(*Pai)->Dir); //Toda vez que um nó é inserido, verificamos se é preciso balancear
        }
        else if (x.Chave < (*Pai)->Item.Chave) {
                InsereRec(&(*Pai)->Esq, Pai, x);
                BalancaNo(Avo, Pai, &(*Pai)->Esq);
        }
        else if (x.Chave == (*Pai)->Item.Chave)
            return(0);
    }

}

void Insere(TArvBin *pRaiz, TItem x)
{
	InsereRec(pRaiz, NULL, x);
	if((*pRaiz)!=NULL)
        (*pRaiz)->cor = 0;
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
		if (EhNegro(No))
			printf("(N%d", No->Item.Chave);
		else
			printf("(R%d", No->Item.Chave);
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
	if (ArvoreARN(Raiz)) {
		printf("%d\n", AlturaNegra(Raiz));
		Imprime(Raiz);
	}
	Libera(&Raiz);

	return 0;
}
