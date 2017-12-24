//Thauany Moedano
//RA 92486
#include <stdio.h>
#include <stdlib.h>



typedef int TChave;
typedef int TIndice;

typedef struct {
    TChave Chave;
    int fixo; //O vetor fixo indica qual s posição da guarita fixa
    int flag; //
    /* outros compomentes */
} TItem;


TItem *Aloca(int n)
{
	return ((n > 0) ? ((TItem *) malloc(n * sizeof(TItem))) : (NULL));
}

int Carrega(TItem **A)
{
	int i, n, g; //G = numero de guaritas
	int x, y; //Coordenadas dos pontos fixos X = linha, Y = coluna

	scanf("%d %d", &n, &g);
	n = n+1;

	(*A) = Aloca(n);
	for(i = 0; i < n; i++) {
        (*A)[i].fixo = 0;
        (*A)[i].flag = 0;
       // printf("Atribuicao: %d\n", (*A)[i].fixo);
	}

	for (i = 0; i < g; i++) {
		scanf("%d %d", &x, &y);
		(*A)[y].fixo = x;
		//(*A)[i].flag = 1;

		//printf("Atribuicao\n");
    }

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
		printf("%d", A[1].Chave);
		for (i = 2; i < n; i++)
			printf(" %d", A[i].Chave);
		printf("\n");
	}
}

int is_a_solution(TItem *A, int k, int N) {
    if(k == N-1)
        return(1);
    else
        return(0);

}

void process_solution(TItem *A, int k, int N) {

    int i, ehSolucao = 1;

    for(i = 1; i < N; i++) {
        if(A[i].fixo != 0) {
            if(A[i].fixo != A[i].Chave) {
                ehSolucao = 0;
                break;
            }
        }
    }

    if(ehSolucao)
        Imprime(A, N);
}
void make_move(TItem *A, int i, int c[]) {
    //if(!A[i].flag) {
        A[c[i]].flag = 1;

}

void unmake_move(TItem *A, int i, int c[]) {
   A[c[i]].flag = 0;

}
void construct_candidates(TItem *A, int k, int N, int c[], int *nCandidates) {
   // printf("Esta chegando aqui?");
    int i; //in_perm[N];
    *nCandidates = 1;


    for(i = 1; i < N; i++) {
        if(A[i].flag == 0) {
            c[*nCandidates] = i;
            *nCandidates = *nCandidates + 1;
        }

    }
}


void backtrack(TItem *A, int k, int N) {
    int c[N]; //Vetor de candidatos
    int nCandidates;
    int i;
   // printf("Que????");
    if(is_a_solution(A, k, N))
        process_solution(A, k, N);

    else {
        k+=1;
        //if(A[k].fixo != 0)
           // A[k].Chave = A[k].fixo;

        construct_candidates(A, k, N, c, &nCandidates);

        for(i = 1; i < nCandidates; i++) {
            A[k].Chave = c[i];
            make_move(A, i, c);
            backtrack(A, k, N);
            unmake_move(A, i, c);
        }

    }

}


int main() {
    //Lembrar de passar N+1 nas funcoes
    TItem *A;
    int n;
    n = Carrega(&A);

    backtrack(A, 0, n);
    return 0;
}
