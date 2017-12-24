// Thauany Moedano
//RA 92486
#include <stdio.h>
#include <stdlib.h>

//typedef int TChave;

typedef struct {
	int indicado;
	int nIndicacoes;
	//int flag;
	/* outros compomentes */
} Pessoa; //Struct Pessoa contém os convidados para o evento

typedef struct {
    int tam;
    int inicio;
    int fora;
} Fora; //Struct fora contém as pessoas que não vao para a segunda fase

Pessoa *Aloca(int n)
{
	return ((n > 0) ? ((Pessoa *) malloc(n * sizeof(Pessoa))) : (NULL));
}

Fora *AlocaF(int n)
{
	return ((n > 0) ? ((Fora *) malloc(n * sizeof(Fora))) : (NULL));
}


int Carrega(Pessoa **A)
{
	int i, n;
	int pessoa, indicado;
	scanf("%d", &n);
    n+=1;
	(*A) = Aloca(n);
	for(i = 0; i < n; i++) {
        (*A)[i].nIndicacoes = 0; //Inicializa contagem de numero de indicações
      //  (*A)[i].flag = 0;
	}
    //Preenchendo o vetor de convidados
	for (i = 1; i < n ; i++) {
		scanf("%d %d", &pessoa, &indicado);
		(*A)[pessoa].indicado = indicado;
		(*A)[indicado].nIndicacoes += 1;
	}

	return n;
}

void Libera(Pessoa **A)
{
	if ((*A) != NULL) {
		free(*A);
		(*A) = NULL;
	}
}

void Imprime(Pessoa *A, int n)
{
	int i;
	if (n > 0) {
      //  if(A[1].nIndicacoes > 0 )
        //    printf("%d", 1);
		for (i = 1; i < n; i++)
            if(A[i].nIndicacoes > 0 )
                printf("%d ", i);

		printf("\n");
	}
}


void ImprimeF(Fora *A)
{
	int i;
	if (A[0].tam > 0) {
		printf("%d ", A[0].fora);
   // if(A[0].tam >= 1)
	//	printf("%d", A[1].fora);
		for (i = 1; i < A[0].tam; i++)
			printf("%d \n", A[i].fora);

		printf("\n");
	}
}

void Subgrupo (Pessoa *A, Fora *F, int n) {
    if(F[F[0].inicio].fora == NULL) //A solução é quando todos os nós restantes indicam e são indicados por alguem
        Imprime(A, n);
    else { //PS: VOU SONHAR COM A E F O-O
        A[F[F[0].inicio].fora].nIndicacoes = -1; //remoção
        A[A[F[F[0].inicio].fora].indicado].nIndicacoes -= 1; //Retiro a indicação do removido
            if(A[A[F[F[0].inicio].fora].indicado].nIndicacoes == 0) { //Verifico se a pessoa indicada pelo removido ainda faz parte da solução
                F[F[0].tam].fora = A[F[F[0].inicio].fora].indicado; //Se não faz parte da solução, coloco no vetor de q nao é solução
                F[0].tam += 1; //Aumenta o tamanho desse vetor
            }
            F[0].inicio += 1; //Anda com o vetor
       // Imprime(A, n);
        Subgrupo(A, F, n); //Retorna o subgrupo com o elemento removido e verifica se é solução
    }

}


int main()
{
	Pessoa *A;
	Fora *F;

	int n;

	n = Carrega(&A);
	F = AlocaF(n);
	F[0].tam = 0;
	F[0].inicio = 0;
	//printf("%d %d", F[0].tam, F[0].inicio);
	//Ordena(A, n);



	int i, k = 0;
    for(i = 0; i < n; i++) {
        F[i].fora = NULL;
    }


	for(i = 1; i < n; i++) {
        if(A[i].nIndicacoes == 0) {
           // printf("%d sem indicacoes: ", i);
            F[F[0].tam].fora = i;
           // printf("i: %d \n", F[F[0].tam].fora);
            F[0].tam += 1;
        }
	}

	//Imprime(A,n);
	Subgrupo(A, F, n);
	//F[0].tam -= 1;

//	ImprimeF(F);

	Libera(&A);

	return 0;
}
