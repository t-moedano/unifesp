/*Busca em largura para resolver o problema do 8 puzzle
(Quebra cabeça de 8 peças)
Thauany Moedano
RA: 92486
*/
#include <iostream>
#include <stack>
#include <string>
#include <list>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>
#include <time.h>

#define PIECES 3

using namespace std;

/* Estruturas utilizadas para o trabalho */
typedef struct
{
   	int v;
   	int w;
} Edge;
Edge EDGE(int, int);
typedef struct graph *Graph;


/* Estrutura de inicialização da matriz. Monta uma matriz com os valores aleatórios.
** Uma fórmula de pseudo-geração de valores aleatórias é utilizada.
** params: número de linhas (rows) e colunas (columns).
** return: matriz de inteiros para associar ao grafo.
*/
int **MATRIXint (int r, int c)
{
    int i, j;
    int numbers[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    int chosenNumber;
    int **t = (int **) malloc (r * sizeof (int *));

    for (i = 0; i < r; i++)
        t[i] = (int *) malloc (c * sizeof (int));

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
        {
            do
            {
                srand((unsigned)time(0));
                int maior = 8;
                int menor = 0;
                chosenNumber = rand()%(maior-menor+1) + menor;
            } while(numbers[chosenNumber] == 1);
            numbers[chosenNumber] = 1;
            t[i][j] = chosenNumber;
        }
    return t;
}

/* Estrutura do grafo */
struct graph { int V; int E; int **adj; };
Graph GRAPHinit (int V)
{
    Graph G = (Graph) malloc (sizeof *G);
    G->V = V;
	G->E = 0;
    G->adj = MATRIXint (V, V);
    return G;
}

/* Função de inserção de valores */
void GRAPHinsertE (Graph G, Edge e, int peca)
{
    int v = e.v, w = e.w;
    G->adj[v][w] = peca;

}

/* Função que verifica se a matriz atual corresponde ao estado-objetivo esperado
** param: id que representa o estado da matriz
** return: true se chegou ao resultado, falso se for o contrário
*/
bool verificaEhObjetivo(string id)
{
    string estadoFinal = "012345678";

   if(id.compare(estadoFinal) == 0)
        return true;

    return false;
}

/* Função que dado um grafo G, gera um ID único para a matriz daquele grafo. O Id é extraido
** das posições das peças na matriz. Por exemplo, se o estado é:
** 2 0 1
** 8 5 4
** 3 6 7
** O id gerado será "201854367"
** params: Grafo G
** return: Id do grafo G
*/
string geraId(Graph G)
{
    int a, b;
    stringstream peca;
    for(int a = 0; a < PIECES; ++a)
    {
        for(int b = 0; b < PIECES; ++b)
        {
            peca << G->adj[a][b];

        }
    }
    return peca.str();
}

void reconstroiMatriz(Graph G, string estadoAtual)
{
    G->adj[0][0] = estadoAtual[0]-48;
    G->adj[0][1] = estadoAtual[1]-48;
    G->adj[0][2] = estadoAtual[2]-48;
    G->adj[1][0] = estadoAtual[3]-48;
    G->adj[1][1] = estadoAtual[4]-48;
    G->adj[1][2] = estadoAtual[5]-48;
    G->adj[2][0] = estadoAtual[6]-48;
    G->adj[2][1] = estadoAtual[7]-48;
    G->adj[2][2] = estadoAtual[8]-48;
}

string geraIdFila(Graph G, int linha, int coluna, int xPos, int yPos)
{
    int troca = G->adj[linha][coluna];
    G->adj[xPos][yPos] = troca;
    G->adj[linha][coluna] = 8;

    string id = geraId(G);

    troca = G->adj[xPos][yPos];
    G->adj[linha][coluna] = troca;
    G->adj[xPos][yPos] = 8;

    return id;
}
void BFS(Graph G, int& xPos, int& yPos, int &numMov)
{
    cout << "Calculando.. " << endl;
    clock_t start, timePassed;

    queue<int> linhaQ;
    queue<int> colunaQ;
    queue<string> idsMatriz;
    list<string> listIds;
    queue<int> oitoXPos;
    queue<int> oitoYPos;

    string id = geraId(G);

    idsMatriz.push(id);
    linhaQ.push(xPos);
    colunaQ.push(yPos);
    oitoXPos.push(xPos);
    oitoYPos.push(yPos);

    int troca;

    start = clock();
    timePassed = clock();

    while(!verificaEhObjetivo(id) && (((float)timePassed-start)/CLOCKS_PER_SEC < 90))
    {
        string estadoAtual = idsMatriz.front();
        reconstroiMatriz(G, estadoAtual);
        xPos = oitoXPos.front();
        yPos = oitoYPos.front();

        if(xPos-1 >= 0)
        {

            id = geraIdFila(G, xPos-1, yPos, xPos, yPos);
            if((find(listIds.begin(), listIds.end(), id) == listIds.end()))
            {
                listIds.push_back(id);
                idsMatriz.push(id);
                linhaQ.push(xPos-1);
                colunaQ.push(yPos);

                oitoXPos.push(xPos-1);
                oitoYPos.push(yPos);
            }

        }
        if(xPos+1 <= 2)
        {
            id = geraIdFila(G, xPos+1, yPos, xPos, yPos);
            if((find(listIds.begin(), listIds.end(), id) == listIds.end()))
            {
                listIds.push_back(id);
                idsMatriz.push(id);
                linhaQ.push(xPos+1);
                colunaQ.push(yPos);

                oitoXPos.push(xPos+1);
                oitoYPos.push(yPos);
            }
        }

        if(yPos-1 >= 0)
        {
            id = geraIdFila(G, xPos, yPos-1, xPos, yPos);
            if((find(listIds.begin(), listIds.end(), id) == listIds.end()))
            {
                listIds.push_back(id);
                idsMatriz.push(id);
                linhaQ.push(xPos);
                colunaQ.push(yPos-1);

                oitoXPos.push(xPos);
                oitoYPos.push(yPos-1);
            }
        }

        if(yPos+1 <= 2)
        {
            id = geraIdFila(G, xPos, yPos+1, xPos, yPos);
            if((find(listIds.begin(), listIds.end(), id) == listIds.end()))
            {
                listIds.push_back(id);
                idsMatriz.push(id);
                linhaQ.push(xPos);
                colunaQ.push(yPos+1);

                oitoXPos.push(xPos);
                oitoYPos.push(yPos+1);
            }
        }

        linhaQ.pop();
        colunaQ.pop();
        idsMatriz.pop();
        oitoXPos.pop();
        oitoYPos.pop();

        numMov+=1;
        timePassed = clock();
    }

    cout << "Algorimo terminou: " << endl;
    if(id.compare("012345678") ==  0)
        cout << "Solucao encontrada!" << endl;
    else
    {
        cout << "O algoritmo nao encontrou solucao." << endl;

    }
    cout << "Matriz final: " << endl;
    for(int a = 0; a < PIECES; ++a)
    {
        for(int b = 0; b < PIECES; ++b)
        {
            if(G->adj[a][b] == 8)
                cout << "  ";
            else
                cout << G->adj[a][b] << " ";

        }
        cout << endl;
    }
    cout << "Tempo final: " << ((float)timePassed-start)/CLOCKS_PER_SEC << endl;
    cout << "Número de movimentos: " << numMov << endl;
    cout << endl;
}

int main()
{
    Graph G;
    int xPos, yPos;
    G = GRAPHinit(PIECES);
    int numMov = 0;

    for(int a = 0; a < PIECES; ++a)
    {
        for(int b = 0; b < PIECES; ++b)
        {
            if(G->adj[a][b] == 8)
            {
                xPos = a;
                yPos = b;
                cout << "  ";
            }
            else
                cout << G->adj[a][b] << " ";
        }
        cout << endl;
    }

    BFS(G, xPos, yPos, numMov);
    return 0;
}


