//Thauany Moedano
//RA 92486

/*Implementação do algoritmo de Floyd-Warshall para achar todos os caminhos mínimos entre pares de arestas*/

#include <iostream>
#include <stdlib.h>
#define INF 2000000000

using namespace std;
/*Definição da estrutura de grafo*/
typedef struct
{
   	int v;
   	int w;
} Edge;
Edge EDGE(int, int);
typedef struct graph *Graph;


int **MATRIXint (int r, int c)
{
    int i, j;

    int **t = (int **) malloc (r * sizeof (int *));

    for (i = 0; i < r; i++)
        t[i] = (int *) malloc (c * sizeof (int));
        for (i = 0; i < r; i++)
            for (j = 0; j < c; j++)
                t[i][j] = INF;
    return t;
}

struct graph { int V; int E; int **adj; };
Graph GRAPHinit (int V)
{
    Graph G = (Graph) malloc (sizeof *G);
    G->V = V;
	G->E = 0;
    G->adj = MATRIXint (V, V);
    return G;
}

void GRAPHinsertE (Graph G, Edge e, int peso)
{
    int v = e.v, w = e.w;
    G->adj[v][w] = peso;

}

/*Implementação do algoritmo FloydWarshall*/
int FloydWarshall(Graph G, int N, int d[][100])
{
    int i, j, k;

    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < N; ++j)
        {
            if(i == j)
                d[i][j] = 0;
            else
                d[i][j] = G->adj[i][j];
        }
    }
    for(k = 0; k < N; ++k)
    {
        for(i = 0; i < N; ++i)
        {
            for(j = 0; j < N; ++j)
            {

                if(d[i][k]!= INF && d[k][j] != INF
                    && d[i][j] > d[i][k]+d[k][j])

                    d[i][j] = d[i][k]+d[k][j];
            }
        }

    }
    /*Detecta se não existe ciclo negativo no grafo. Caso afirmativo, retorna zero*/
    for(i = 0; i < N; ++i)
    {
        if(d[i][i] < 0)
            return(0);
    }

    return(1);
}

int main()
{
    int N, M, i, j, peso, flag;
    int d[100][100]; //Matriz 2D que guarda as recorrências
    Edge e;
    Graph G;
    cin >> N;
    cin >> M;

    G = GRAPHinit(N);
    //Inicialização dos valores
    for(int k = 0; k < M; ++k)
    {
        cin >> i;
        cin >> j;
        cin >> peso;
        e.v = i;
        e.w = j;
        GRAPHinsertE(G, e, peso);
    }

    flag = FloydWarshall(G, N, d);

    if(!flag)
        cout << "Ciclo negativo" << endl;
    else
    {
        for(int a = 0; a < N; ++a)
        {
            for(int b = 0; b < N; ++b)
            {
                if(d[a][b] == INF)
                    cout << "INF ";
                else
                    cout << d[a][b] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
