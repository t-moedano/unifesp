//Thauany Moedano
//RA 92486

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
	int fb; // fator de balanceamento: -1, 0, +1
} TNo;

int FB(TArvBin No)
{
	if (No == NULL)
		return 0;

	return No->fb;
}

//Rotação LL
void LL(TArvBin *pA, int IorR)
{
	TArvBin pB = (*pA)->Esq; //Utilizando ponteiros para trocar os nos de lugar. Isso acontece para a todas as rotacoes

    //Para a inserção, sempre A e B ficam zero
    if(IorR == 1) {
        (*pA)->fb = 0;
        pB->fb = 0;
    }
    //No caso da remoção, os FBs de A e B passam a ser +1 e -1 no caso do antigo FB ser zero.
    else if(IorR == 2) {
        if(pB->fb == 0){
            (*pA)->fb = 1;
            pB->fb = -1;
        }
        else {
            (*pA)->fb = 0;
            pB->fb = 0;
        }
    }

    //Atualizamos os ponteiros
    (*pA)->Esq = pB->Dir;
    pB->Dir = (*pA);
    (*pA) = pB;
}

void RR(TArvBin *pA, int IorR)
{
	TArvBin pB = (*pA)->Dir;

	//Para a inserção A e B sempre serão zero
    if(IorR == 1) {
        (*pA)->fb = 0;
        pB->fb = 0;
    }
    //No caso da remoção, os FBs de A e B passam a ser +1 e -1 quando o antigo FB de é zero
    else if(IorR == 2) {
        if(pB->fb == 0){
            (*pA)->fb = -1;
            pB->fb = 1;
        }
        else {
            (*pA)->fb = 0;
            pB->fb = 0;
        }
    }
    //Efetuando a rotação
    (*pA)->Dir = pB->Esq;
    pB->Esq = (*pA);
    (*pA) = pB;
}

void LR(TArvBin *pA, int IorR)
{
	TArvBin pB = (*pA)->Esq;
    TArvBin pC = pB->Dir;

    //EM LR temos diferentes casos.

    //Inserção
    if(IorR == 1) {
        //Para LR corrigimos os fatores de balanceamento em fução do nó C
        if(pC->fb == 1) { //Se C era 1, os novos fatores são A: -1 e B: 0
            (*pA)->fb = -1;
            pB->fb = 0;
        }
        else if(pC->fb == -1) { //Se C é -1, os novos fatores serão A: 0 e B: 1
            (*pA)->fb = 0;
            pB->fb = 1;
        }

        else if (pC->fb == 0) { //Se era 0, A e B passam a ser 0
            (*pA)->fb = 0;
            pB->fb = 0;
        }

    }
    //No caso da remoção temos um tratamento similiar
    else if(IorR == 2) {

        if(pC->fb == -1){  //Se C era -1, A e B passam a ser 1 e 0
            (*pA)->fb = 0;
            pB->fb = 1;

        }
        else if(pC->fb == 1) { //Se C era 1, A e B passam a ser 0 e -1
            (*pA)->fb = -1;
            pB->fb = 0;

        }
        else if (pC->fb == 0) { //Se era 0, A e B passam a ser 0
            (*pA)->fb = 0;
            pB->fb = 0;

        }
    }
    //Independente do caso o novo fator de C sempre é zero
     pC->fb = 0;

    pB->Dir = pC->Esq;
    pC->Esq = pB;
    (*pA)->Esq = pC->Dir;
    pC->Dir = (*pA);
    *pA = pC;

}

void RL(TArvBin *pA, int IorR)
{
	TArvBin pB = (*pA)->Dir;
    TArvBin pC = pB->Esq;
    //Os casos para inserção e remoção em RL acontecem de maneira simetrica a LR
    if(IorR == 1) {
        if(pC->fb == 1) {
            (*pA)->fb = 0;
            pB->fb = -1;
        }
        else if(pC->fb == -1) {
            (*pA)->fb = 1;
            pB->fb = 0;
        }

        else if (pC->fb == 0) {
            (*pA)->fb = 0;
            pB->fb = 0;
        }

    }

    else if(IorR == 2) {

        if(pC->fb == -1){
            (*pA)->fb = 1;
            pB->fb = 0;
        }
        else if(pC->fb == 1) {
            (*pA)->fb = 1;
            pB->fb = -1;

        }
        else if (pC->fb == 0) {
            (*pA)->fb = 0;
            pB->fb = 0;
        }
    }
    pC->fb = 0;

    pB->Esq = pC->Dir;
    pC->Dir = pB;
    (*pA)->Dir = pC->Esq;
    pC->Esq = *pA;
    *pA = pC;


}

int BalancaEsquerda(TArvBin *pA, int IorR)
{
	 TArvBin pB = (*pA)->Esq; //Se a esquerda esta desbalanceada devemos verificar qual tipo se rotacao sera feito

    if((pB->fb) >= 0) //Se o filho esquerdo esta desbalanceado a direita, chamamos esquerda esquerda
        LL(&(*pA), IorR);
    else if(pB->fb < 0)
        LR(&(*pA), IorR);

    return(0);
}

int BalancaDireita(TArvBin *pA, int IorR)
{
	TArvBin pB = (*pA)->Dir; //Se a direita esta desbalanceada devemos verificar qual tipo de rotacao sera feito

    if(pB->fb > 0) //Se o filho esquerdo esta desbalanceado a direita, chamamos direita esquerda
        RL(&(*pA), IorR);
    else if (pB->fb <= 0)
        RR(&(*pA), IorR);

    return(0);
}

TArvBin Inicializa()
{
	return NULL;
}

TArvBin Pesquisa(TArvBin No, TChave x)
{
	if (No == NULL)
		return NULL; // retorna NULL caso a chave nao seja encontrada
	else if (x < No->Item.Chave)
		return Pesquisa(No->Esq, x);
	else if (x > No->Item.Chave)
		return Pesquisa(No->Dir, x);
	else
		return No;
}

int Insere(TArvBin *pNo, TItem x)
{
	 if (*pNo == NULL) { //Caso a pesquisa seja sem sucesso inserimos utilizando a alocação
        TNo* No = (TNo*) malloc (sizeof(TNo));
        No->Item = x;
        No->Esq = NULL;
        No->Dir = NULL;
        No->fb = 0;
        *pNo = No;
        return(1);
    }
    //Caso contrário percorremos a árvore
     else {
        if (x.Chave > (*pNo)->Item.Chave) {
            if(Insere(&(*pNo)->Dir, x)) {
                (*pNo)->fb -= 1;

                if((*pNo)->fb == 0)
                    return(0);
                else if ((*pNo)->fb == -1)
                    return(1);
                else
                    return(BalancaDireita(&(*pNo), 1));
            }
        }
        else if (x.Chave < (*pNo)->Item.Chave) {
            if(Insere(&(*pNo)->Esq, x)){
                (*pNo)->fb += 1;

                if((*pNo)->fb == 0)
                    return(0);
                else if ((*pNo)->fb == 1)
                    return(1);
                else
                    return(BalancaEsquerda(&(*pNo), 1));
            }
        }
        else if (x.Chave == (*pNo)->Item.Chave)
            return(0);
    }

}

int desceDir (TArvBin *Aux, TArvBin *Susc) {

    if ((*Susc)->Esq == NULL) {
        (*Aux)->Item = (*Susc)->Item;
        *Aux = *Susc;
        *Susc = (*Susc)->Dir;

        (*Aux)->fb += 1;

                if((*Aux)->fb == 0)
                    return(0);
                else if ((*Aux)->fb == 1)
                    return(1);
                else
                    return(BalancaEsquerda(&(*Aux), 2));

    }
    else{
        desceDir(Aux, &(*Susc)->Esq);

                (*Aux)->fb -= 1;
                if((*Aux)->fb == 0)
                    return(0);
                else if ((*Aux)->fb == -1)
                    return(1);
                else
                    return(BalancaDireita(&(*Aux), 2));


}

}

int Remove(TArvBin *pNo, TChave x)
{
	TArvBin Aux;
    if (*pNo == NULL)
        return(0);

     else {
        if (x > (*pNo)->Item.Chave) {

            if(Remove(&(*pNo)->Dir, x)){

                (*pNo)->fb += 1;

                if((*pNo)->fb == 0)
                    return(0);
                else if ((*pNo)->fb == 1)
                    return(1);
                else
                    return(BalancaEsquerda(&(*pNo), 2));
            }
        }

        else if (x < (*pNo)->Item.Chave) {

            if(Remove(&(*pNo)->Esq, x)) {
                (*pNo)->fb -= 1;
                if((*pNo)->fb == 0)
                    return(0);
                else if ((*pNo)->fb == -1)
                    return(1);
                else
                    return(BalancaDireita(&(*pNo), 2));
            }
        }

        else if (x == (*pNo)->Item.Chave) { //Pesquisa com sucesso deve remover o nó
            Aux = *pNo;

            if ((*pNo)->Esq == NULL) //Se só existe um filho a esquerda, trocamos de lugar com a direita
                *pNo = Aux->Dir;
            else if ((*pNo)->Dir ==  NULL) //Se so existe um filho a direita, trocamos com a esquerda
                *pNo = Aux->Esq;

            else
                desceDir(&Aux, &Aux->Dir); // Se ele possui os dois filhos, percorremos toda a direita e troacmos o ultimo da direita

            free(Aux);

            return(1);
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
