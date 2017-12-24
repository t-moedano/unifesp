/*Algoritmo de busca gulosa com h = numero de peças na posição errada para resolver
o problema 8 puzzle (quebra cabeça de 8 peças)
Thauany Moedano
RA: 92486
*/
#include <list>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>

#define PIECES 3

using namespace std;

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

struct graph { int V; int E; int **adj; };
Graph GRAPHinit (int V)
{
    Graph G = (Graph) malloc (sizeof *G);
    G->V = V;
	G->E = 0;
    G->adj = MATRIXint (V, V);
    return G;
}

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

/*Funcao que calcula o H dado um estado do grafo*/
int calculaH(Graph G, int posXCorreto[], int posYCorreto[], string posicoesCorretas[], int tipoH)
{
    int h = 0;
    int dist = 0;
    int linhaCorreta = 0;

    if(tipoH == 3)
    {
        for(int i = 0; i < 3; ++i)
        {
            int maior = -1;
            for(int j = 0; j < 3; ++j)
            {
                int peca = G->adj[i][j];
                int xCorreto = posXCorreto[peca];
                int yCorreto = posYCorreto[peca];

                if(xCorreto > i)
                    dist += (xCorreto - i);
                else
                    dist += (i - xCorreto);

                if(yCorreto > j)
                    dist += (yCorreto - j);
                else
                    dist += (j - yCorreto);

                if(peca != 8)
                {


                        h += dist;


                    if(fabs(xCorreto - i) == 0 && fabs(yCorreto) != 0)
                    {
                       if(peca > maior)
                            maior = peca;
                       else
                        h += 2;
                    }
                }

                dist = 0;

            }
        }
    }
    else if(tipoH == 2)
    {
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                int peca = G->adj[i][j];
                int xCorreto = posXCorreto[peca];
                int yCorreto = posYCorreto[peca];

                if(xCorreto > i)
                    dist += (xCorreto - i);
                else
                    dist += (i - xCorreto);

                if(yCorreto > j)
                    dist += (yCorreto - j);
                else
                    dist += (j - yCorreto);

                if(peca != 8)
                    h += dist;

                dist = 0;

            }
        }
    }
    else if(tipoH == 1)
    {
        for(int i = 0; i < 3; ++i)
        {
            for(int j = 0; j < 3; ++j)
            {
                char x = i+48;
                char y = j+48;
                char peca = G->adj[i][j]+48;
                string idPos = "";
                idPos += x;
                idPos += y;
                idPos += peca;
                string posCorreta = posicoesCorretas[G->adj[i][j]];

                if(posCorreta.compare(idPos) != 0 && G->adj[i][j] != 8)
                {
                    h++;
                }
            }
    }
    }

    return h;
}

/* Função que verifica se a troca já não gera um estado visitado.
** params: Grafo G, linha e coluna do estado desejado, linha e coluna do estado atual e uma lista
** que contém todos os IDs dos estados visitados.
** return: true se a troca gera um não visitado. Falso do contrário.
*/
bool testaTroca(Graph G, int linha, int coluna, int& xPos, int& yPos, list<string> listIDs)
{

    int troca = G->adj[linha][coluna];
    G->adj[xPos][yPos] = troca;
    G->adj[linha][coluna] = 8;

    string id = geraId(G);

    troca = G->adj[xPos][yPos];
    G->adj[linha][coluna] = troca;
    G->adj[xPos][yPos] = 8;

    if((find(listIDs.begin(), listIDs.end(), id) == listIDs.end()))
    {
        return true;
    }
    return false;
}

/*Funcao que faz a busca gulosa utilizando H1 de heuristica.*/
void buscaGulosa(Graph G, int& xPos, int& yPos, int tipoH)
{
    cout << endl;
    cout << "Calculando ..." << "h" << tipoH;
    cout << endl;
    string posicoesCorretas[9] = {"000", "011", "022", "103", "114", "125", "206", "217", "228"};
    int posXCorreto[9] = {0, 0, 0, 1, 1, 1, 2, 2, 2};
    int posYCorreto[9] = {0, 1, 2, 0, 1, 2, 0, 1, 2};
    clock_t start, timePassed;
    int h = calculaH(G, posXCorreto, posYCorreto, posicoesCorretas, tipoH);
    int hEsq = h;
    int hDir = h;
    int hCima = h;
    int hBaixo = h;
    int melhorH = 5; //1 - Cima, 2 - Dir, 3 - Baixo, 4 - Esq
    int melhorHVal = h;
    int troca;
    int ordem[4] = {1, 2, 3, 4};
    bool moveu = false;
    bool flagMelhorou = false;
    srand((unsigned)time(0));
    int maior = 4;
    int menor = 1;
    int chosenNumber;
    int numMov = 0;
    srand((unsigned)time(0));

    string id = geraId(G);
    list<string> listIDs;
    start = clock();
    timePassed = clock();

  while(!verificaEhObjetivo(id) && (((float)timePassed-start)/CLOCKS_PER_SEC < 90))
  {
    for(int i = 0; i < 30; ++i)
    {
        chosenNumber = rand()%(maior-menor+1) + menor;
        if(xPos+1 <= 2 && testaTroca(G, xPos+1, yPos, xPos, yPos, listIDs) && chosenNumber == ordem[3])
        {
            int troca = G->adj[xPos+1][yPos];
            G->adj[xPos][yPos] = troca;
            G->adj[xPos+1][yPos] = 8;

            hBaixo = calculaH(G, posXCorreto, posYCorreto, posicoesCorretas, tipoH);

            troca = G->adj[xPos][yPos];
            G->adj[xPos+1][yPos] = troca;
            G->adj[xPos][yPos] = 8;

            if(hBaixo <= melhorHVal)
            {
                melhorHVal = hBaixo;
                melhorH = 3;
                flagMelhorou = true;
            }
        }

        if(yPos+1 <= 2 && testaTroca(G, xPos, yPos+1, xPos, yPos, listIDs) && chosenNumber == ordem[1])
        {
            int troca = G->adj[xPos][yPos+1];
            G->adj[xPos][yPos] = troca;
            G->adj[xPos][yPos+1] = 8;

            hDir = calculaH(G, posXCorreto, posYCorreto, posicoesCorretas, tipoH);

            troca = G->adj[xPos][yPos];
            G->adj[xPos][yPos+1] = troca;
            G->adj[xPos][yPos] = 8;

            if(hDir <= melhorHVal)
            {
                melhorHVal = hDir;
                melhorH = 2;
                flagMelhorou = true;
            }
        }

        if(xPos-1 >= 0  && testaTroca(G, xPos-1, yPos, xPos, yPos, listIDs) && chosenNumber == ordem[0])
        {

            int troca = G->adj[xPos-1][yPos];
            G->adj[xPos][yPos] = troca;
            G->adj[xPos-1][yPos] = 8;

            hCima = calculaH(G, posXCorreto, posYCorreto, posicoesCorretas, tipoH);

            troca = G->adj[xPos][yPos];
            G->adj[xPos-1][yPos] = troca;
            G->adj[xPos][yPos] = 8;

            if(hCima <= melhorHVal)
            {
                melhorHVal = hCima;
                melhorH = 1;
                flagMelhorou = true;
            }
        }

        if(yPos-1 >= 0 && testaTroca(G, xPos, yPos-1, xPos, yPos, listIDs) && chosenNumber == ordem[2])
        {
            int troca = G->adj[xPos][yPos-1];
            G->adj[xPos][yPos] = troca;
            G->adj[xPos][yPos-1] = 8;

            hEsq = calculaH(G, posXCorreto, posYCorreto, posicoesCorretas, tipoH);

            troca = G->adj[xPos][yPos];
            G->adj[xPos][yPos-1] = troca;
            G->adj[xPos][yPos] = 8;

            if(hEsq <= melhorHVal)
            {
                melhorHVal = hEsq;
                melhorH = 4;
                flagMelhorou = true;
            }
        }
    }
    h = melhorHVal;

    if(flagMelhorou == false)
    {
        melhorHVal += 1;
        moveu = false;
        if(melhorHVal >= 50)
            listIDs.clear();
    }
    else
    {
        moveu = true;
        if(melhorH == 1)
        {
            troca = G->adj[xPos-1][yPos];
            G->adj[xPos][yPos] = troca;
            G->adj[xPos-1][yPos] = 8;
            xPos = xPos - 1;

        }
        else if(melhorH == 2)
        {
            troca = G->adj[xPos][yPos+1];
            G->adj[xPos][yPos] = troca;
            G->adj[xPos][yPos+1] = 8;
            yPos = yPos + 1;
        }
        else if(melhorH == 3)
        {
            troca = G->adj[xPos+1][yPos];
            G->adj[xPos][yPos] = troca;
            G->adj[xPos+1][yPos] = 8;
            xPos = xPos + 1;
        }
        else if(melhorH == 4)
        {
            troca = G->adj[xPos][yPos-1];
            G->adj[xPos][yPos] = troca;
            G->adj[xPos][yPos-1] = 8;
            yPos = yPos - 1;
        }
   }
    id = geraId(G);
    numMov+=1;
    timePassed = clock();
    listIDs.push_back(id);
    flagMelhorou = false;
    if(moveu == true)
        numMov+=1;
    moveu = false;
    for(int i = 0; i < 4; ++i)
    {
        ordem[i] += 1;
        if(ordem[i] > 4)
            ordem[i] = 1;

    }

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

using namespace std;

int main()
{
    Graph G, Gcopia;
    int xPos, yPos;
    G = GRAPHinit(PIECES);
    Gcopia = GRAPHinit(PIECES);

     for(int a = 0; a < PIECES; ++a)
    {
        for(int b = 0; b < PIECES; ++b)
        {
            Gcopia->adj[a][b] = G->adj[a][b];

        }
    }



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

    cout << endl;




    buscaGulosa(G, xPos, yPos, 1);

     for(int a = 0; a < PIECES; ++a)
    {
        for(int b = 0; b < PIECES; ++b)
        {
            G->adj[a][b] = Gcopia->adj[a][b];
            if(G->adj[a][b] == 8)
            {
                xPos = a;
                yPos = b;

            }

        }
    }



    buscaGulosa(G, xPos, yPos, 2);


    for(int a = 0; a < PIECES; ++a)
    {
        for(int b = 0; b < PIECES; ++b)
        {
            G->adj[a][b] = Gcopia->adj[a][b];
            if(G->adj[a][b] == 8)
            {
                xPos = a;
                yPos = b;

            }

        }
    }

    buscaGulosa(G, xPos, yPos, 3);
    return 0;
}
