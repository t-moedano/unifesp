#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 500 //Definindo o numero de neuro
#include <math.h>
#include <string.h>

//Estrutura do Grafo
struct Grafo {
    int V;
    int A;
    int **adj;
    int **inc;
    int *grau;
};
typedef struct Grafo *tipoGrafo;

//Estrutura do neurônio
struct Neuronio {
    float x;
    float y;
    float I;
    float Si;
};
typedef struct Neuronio NeuronioInfo;

//Criando uma lista de neurônios
struct ListaNeuronios {
    NeuronioInfo neuro[N];
}; typedef struct ListaNeuronios tipoLN;


//Inicializando lista de neurônios
void inicializa (tipoLN *lista, tipoGrafo G) {

    int i;
    for(i = 0; i < N; i++) {
        lista->neuro[i].x = 0; //No onício tudo é zero ?
        lista->neuro[i].y = 0;
        lista->neuro[i].I = 0.2;
    }
}
//Alocando matriz de adj para o grafo
int **alocaMatriz(int linhas, int colunas) {
    int i, j;

    int **m = (int**)malloc( linhas * sizeof (int *));
    for (i = 0; i < linhas; i++)
        m[i] = (int*)malloc( colunas * sizeof (int));
    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            m[i][j] = 0;
    return m;
}
//Inicializando o grafo
tipoGrafo inicializaGrafo(int vertice) {
    tipoGrafo G = (tipoGrafo*) malloc(sizeof (G));
    G->V = vertice;
    G->A = 0;
    G->adj = alocaMatriz(vertice, vertice);
    G->grau = (int*)calloc(vertice, sizeof (int));
    int i;
    for(i = 0; i < vertice; i++)
        G->grau[i] = 0;
    return G;
}
//Função que insere uma aresta
void insereAresta (tipoGrafo G, int orig, int dest) {

    if (G->adj[orig][dest] == 0) {
        G->adj[orig][dest] = 1;
        G->adj[dest][orig] = 1;
        G->A++;
        G->grau[orig]+=1;
        G->grau[dest]+=1;

    }

}

//Gerador de Grafo Regular com o grau desejado
tipoGrafo Regular(int V, int E, int grau) {
    srand(time(NULL));
    int v, w, i, j;
    tipoGrafo G = inicializaGrafo(V);
    for(i = 0; i < V; i++) {
        for(j = G->grau[i]; j < grau; j++) {
            do {
                w = rand()%V;
            }while(G->grau[w] >= 2);
            insereAresta(G, w, i);
        }

    }
    return G;
}
//Gerador de Grafo aleatório
tipoGrafo Aleatorio(int V, int E) {
     srand(time(NULL));
    int v, w, inseriu = 0, e = 0, x, y;
    int p = 1;
    tipoGrafo G = inicializaGrafo( V);
    for (v = 0; v < V; v++) {
        for (w = 0; w < V; w++) {
            if (rand( )%1001 < p) {
                insereAresta(G, v, w);
                inseriu = 1;
            }
        }
        if(inseriu == 0)
            insereAresta(G, v, v+1);
        inseriu = 0;
        e++;
        if(e>E)
            break;
    }
    return G;

}

//Gerador de grafo de rede livre de escala
tipoGrafo LivredeEscala (int V) {

    tipoGrafo G = inicializaGrafo(V);
    int vet[V], i, j;
    int soma = 2, sorteado, somavet;
    srand(time(NULL));
    rand();
    rand();
    rand();
    rand();

    G->adj[0][1] = 1;
    G->adj[1][0] = 1;
    vet[0] = 1;
    vet[1] = 1;

    for(i = 2; i < V; i++) {
        somavet = 0;
        for(j = 0; j < V; j++) {
            sorteado = rand()%soma;
            somavet += vet[j];
            if(sorteado <= somavet) {
                insereAresta(G, i, j);
                soma+=2;
                vet[j]++;
                vet[i]++;
                break;
            }
        }
    }
    return(G);

}

//Função que imprime o grafo em um arquivo texto
void imprimeGrafo(tipoGrafo G) {
    FILE *texto;
    texto = fopen("grafrand.txt", "w");
    int v, w;
    for (v = 0; v < G->V; v++) {
        fprintf(texto, " %2d:", v);

        for (w = 0; w < G->V; w++)
            if (G->adj[v][w] == 1)
                fprintf(texto, " %2d", w);

        fprintf(texto, "\n");

    }
    fclose(texto);
}



int main() {
    //Declarando o grafo e a lista de neurônios
    tipoGrafo G;
    tipoLN l_n;

    int count=0;

    G = Regular(500, 500, 2); //Gerando grafo desejado
    inicializa(&l_n, G);
    FILE *matriz01;


    matriz01 = fopen("matriz01.txt", "w");

    int i, j, a, b;
    //Inicializando variaveis
    float t,w_ij = 0.1, theta = 0.5, alpha = 6.0, epsilon = 0.02, beta = 0.1;
    int vizinho;
    float deltaT = 0.01;
    float deltaX, deltaY;
    imprimeGrafo(G);

    for(a = 0; a < 250 ; a++)
        l_n.neuro[a].I = -0.02; //Inativando alguns neurônios (opcional)

    for(t=0; t<1000 ; t+=deltaT){

        for(a = 0; a < N; a++){
            l_n.neuro[a].Si = 0;
           for(b = 0; b<N; b++){
            if(a == b) continue;
           if(l_n.neuro[b].x > 0 && G->adj[a][b])
                 l_n.neuro[a].Si+= w_ij;
            }
        }
        for(j = 0; j < N; j++) {
            deltaX = (3.0* l_n.neuro[j].x - pow(l_n.neuro[j].x,3.0) + 2.0 - l_n.neuro[j].y +l_n.neuro[j].Si+ l_n.neuro[j].I)*deltaT; //+ Si;
            deltaY = epsilon*(alpha*(1.0+tanh(l_n.neuro[j].x/beta))-l_n.neuro[j].y)*deltaT;

            l_n.neuro[j].x+= deltaX;
            l_n.neuro[j].y+= deltaY;
        }
int w;
    for(j=0; j<N; j++){
            l_n.neuro[j].x+= j/10;
        }
        if (count % 100 == 0){
            fprintf(matriz01, "%f ", t);
            for(w = 0; w < N; w+=50) {
                fprintf(matriz01, "%f ", l_n.neuro[w].x);
            }
             fprintf(matriz01, "\n", l_n.neuro[w].x);
        }
        count++;
        for(j=0; j<N; j++){
            l_n.neuro[j].x-= j/10;
        }
    }
    fclose(matriz01);

    return(0);
}
