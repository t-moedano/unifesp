//Thauany Moedano
//RA: 92486
/*Este problema busca o menor número de movimentos possíveis que um cavalo de um tabuleiro de xadrez pode fazer
iniciando de uma posição de origem e desejando ir até outra destino*/

#include <iostream>
#include <utility>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

/*Esta função transforma o char inserido em um número*/
int chooseChar(char letra)
{
    if(letra == 'a')
        return 1;
    else if(letra == 'b')
        return 2;
    else if(letra == 'c')
        return 3;
    else if(letra == 'd')
        return 4;
    else if(letra == 'e')
        return 5;
    else if(letra == 'f')
        return 6;
    else if(letra == 'g')
        return 7;
    else if(letra == 'h')
        return 8;
}

/*O cavalo tem 8 movimentos possíveis. Esta função escolhe, de acordo com a iteração, qual o movimento que o cavalo
deve fazer, se isto for possível. Para isso, é analisado o valor da linha e da coluna (dezena e unidade) do valor
do vértice. Por esta razão não é necessário armazenar o tabuleiro em um grafo*/
int chooseNeighbor(int i, int u)
{
    int coluna;
    int linha;
    linha = u % 10;
    coluna = u / 10;


    //2 na vertical, 1 na horizontal
    if(i == 0 && linha <= 6 && coluna >= 2)
        return(u-10+2);
    else if(i == 1 && linha <= 6 && coluna <= 7)
        return(u+10+2);
    else if(i == 2 && linha >= 3 && coluna >= 2)
        return(u-10-2);
    else if(i == 3 && linha >= 3 && coluna <= 7)
        return(u+10-2);
    //1 na vertical, 2 na horizontal
    else if(i == 4 && linha <= 7 && coluna >= 3)
        return(u-20+1);
    else if(i == 5 && linha <= 7 && coluna <= 6)
        return(u+20+1);
    else if(i == 6 && linha >= 2 && coluna >= 3)
        return(u-20-1);
    else if(i == 7 && linha >= 2 && coluna <= 6)
        return(u+20-1);
    else
        return(-1);
}
/*A função BFS pode ser usada para calcular o valor mínimo de movimentos do cavalo. Assim que o cavalo chegar ao seu destino,
o valor do nível corresponde ao número de arestas percorridas pelo cavalo*/
int BFS(int origem, int destino, int l[], int mark[])
{
    queue<int> Q;
    int u, v;
    mark[origem] = 1;
    Q.push(origem);
    l[origem] = 0;
    while(!Q.empty())
    {
        u = Q.front();
        Q.pop();
        for(int i = 0; i < 8; ++i) //O for corresponde ao número de movimentos possíveis do cavalo (8)
        {
            v = chooseNeighbor(i, u);
            if(v != -1 && !mark[v])
            {
                mark[v] = 1;
                Q.push(v);
                l[v] = l[u] + 1;
                if(v == destino)
                    return(l[v]);
            }
        }
    }
}

int main()
{
    char letraOrigem, letraDestino;
    int numeroOrigem, numeroDestino, linhaOrigem, colunaOrigem, linhaDestino, colunaDestino;
    int mark[89], l[89], res;
    //inicializa os vetores
    for(int i = 0; i < 89; ++i)
    {
        mark[i] = 0;
        l[i] = -1;
    }
    //Entra com as coordenadas
    cin >> letraOrigem;
    cin >> numeroOrigem;
    cin >> letraDestino;
    cin >> numeroDestino;

    /*Esta série de funções serve para concatenar dois números. Assim, obtemos, por exemplo, os valores 1 de linha e 1 de coluna,
    e temos como saída o valor 11*/
    linhaOrigem = numeroOrigem;
    colunaOrigem = chooseChar(letraOrigem);
    linhaDestino = numeroDestino;
    colunaDestino = chooseChar(letraDestino);

    ostringstream ossOrigem;
    ossOrigem << colunaOrigem << linhaOrigem;
    istringstream issOrigem(ossOrigem.str());
    int origem;
    issOrigem >> origem;

    ostringstream ossDestino;
    ossDestino << colunaDestino << linhaDestino;
    istringstream issDestino(ossDestino.str());
    int destino;
    issDestino >> destino;

    //Calcula a resposta e imprime
    res = BFS(origem, destino, l, mark);
    cout << res << endl;

    return 0;
}
