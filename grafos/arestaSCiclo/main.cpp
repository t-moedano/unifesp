/*Thauany Moedano
RA: 92486

Este programa calcula quais arestas não fazem parte de um ciclo em grafo baseado no cálculo de seu f*[]
Se o f*[] do vértice for maior que o f[] de seu ancestral na árvore DFS, significa que este par de arestas
não faz parte de um ciclo
*/

#include <iostream>
#include <stdlib.h>
#include <stack>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;
//Declarando estruuras iniciais
typedef struct
{
    int v;
    int w;
} Edge;

Edge EDGE(int, int);
typedef struct graph *Graph;
Graph GRAPHinit (int);
void GRAPHinsertE (Graph, Edge);
void GRAPHremoveE (Graph, Edge);
Graph GRAPHcopy (Graph);
void GRAPHdestroy (Graph);

typedef struct node *link;
struct node
{
    int v;
    link next;
};
struct graph
{
    int V;
    int E;
    link *adj;
};

link NEW (int v, link next)
{
    link x = (link) malloc (sizeof *x);
    x->v = v;
    x->next = next;
    return x;
}

Graph GRAPHinit (int V)
{
    int v;
    Graph G = (Graph) malloc (sizeof *G);
    G->V = V;
    G->E = 0;
    G->adj = (link*) malloc (V*sizeof (link));
    for (v=0;v<V; v++)
    G->adj[v] = NULL;
    return G;
}

void GRAPHinsertE (Graph G, Edge e)
{
    int v = e.v, w = e.w;
    G->adj[v] = NEW (w, G->adj[v]);
    G->adj[w] = NEW (v, G->adj[w]);
    G->E += 2;
}

/*Implementação da árvore de busca DFS de forma recursiva. Desta maneira é mais fácil de localizar quem é o f* de
cada vértice */
void DFSrec(Graph G, int v, int mark[], int& i, int f[], int fStar[], int father[],  vector<pair <int, int> >& vecVU)
{
    int u;
    mark[v] = 1;
    i += 1;
    f[v] = i;
    fStar[v] = f[v]; //Inicialmente o f* é definido como o próprio valor de entrada do vértice
    link t;
    for (t = G->adj[v]; t != NULL; t = t->next)
    {
        u = t->v;
        if(mark[u] == -1)
        {
            father[u] = v; //guardando o ancestral de u
            DFSrec(G, u, mark, i, f, fStar, father, vecVU);
            /*Na volta da chamada recursiva, já teremos os valores de f* e f para comparar*/
            if(fStar[u] < fStar[v])
                fStar[v] = fStar[u];
            /* Se o f* de u é maior que o f de seu ancestral v, ele não faz parte de um ciclo e é inserido na solução.
            O par é formado de acordo com o critério de ordenação */
            if(fStar[u] > f[v])
            {
                if(u > v)
                    vecVU.push_back(make_pair(v, u));
                else
                    vecVU.push_back(make_pair(u, v));

            }

        }
        /*Aqui verifica-se se o par u-v formam uma aresta de volta*/
        else if(u != father[v] && f[u] < fStar[v])
            fStar[v] = f[u];

    }
}

/*Função que imprime os pares u-v de arestas que não fazem parte de um ciclo*/
void findPair(Graph G, int mark[], int f[], int fStar[], int father[], int N, vector<pair <int, int> >& vecVU)
{
    int i = 0, v, k, m, pai;
    for(v = 0; v < N; ++v)
    {
        if(f[v] == -1)
        {
            father[v] = v;
            DFSrec(G, v, mark, i, f, fStar, father, vecVU);
        }

    }
    /*O vetor de pares é ordenado. Por default do c++, a base de comparação é o primeiro elemento, depois o segundo*/
    sort(vecVU.begin(), vecVU.end());
    for (vector< pair<int, int> >::iterator it = vecVU.begin() ; it != vecVU.end(); ++it)
        cout << it->first << " " << it->second << endl;

}


int main()
{

    int N, M, i,  A, B;

    Graph G;
    Edge e;

    cin >> N;
    cin >> M;
    int f[N], l[N], p[N], mark[N], mark_t[N], fStar[N], father[N];
    G = GRAPHinit(N);
    vector<pair <int, int> > vecVU;

    for(i = 0; i < N; ++i)
    {
        f[i] = -1;
        l[i] = -1;
        p[i] = -1;
        mark[i] = -1;
        fStar[i] = -1;
        father[i] = -1;
    }

    for(i = 0; i < M; ++i)
    {
        cin >> A;
        cin >> B;
        e.v = A;
        e.w = B;
        GRAPHinsertE(G, e);
    }
    findPair(G, mark, f, fStar, father, N, vecVU);
    return 0;
}
