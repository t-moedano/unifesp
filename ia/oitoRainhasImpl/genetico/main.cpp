#include <iostream>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <ctime>
#define QUEENS 8
#include <stack>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

void criaVetores (int rainhas[])
{
    int i, j;
    int numbers[QUEENS] = {0, 0, 0, 0, 0, 0, 0, 0};
    int chosenNumber;
    int maior = QUEENS-1;
    int menor = 0;

    for (i = 0; i < QUEENS; i++)
    {
        do
        {


            chosenNumber = rand()%(maior-menor+1) + menor;
        } while(numbers[chosenNumber] == 1);
        numbers[chosenNumber] = 1;
        rainhas[i] = chosenNumber;
    }

}

int emAtaque(int coluna1, int coluna2, int rainhas[])
{
    int linha1 = rainhas[coluna1];
    int linha2 = rainhas[coluna2];


    if(linha1 == linha2 || coluna1 == coluna2 ||
       fabs(linha1+coluna1-2) == fabs(linha2+coluna2-2) ||
       fabs(linha1-coluna1+7) == fabs(linha2-coluna2+7))
            return 1;
    return 0;

}

void criaTabuleiro(int rainhas[])
{
    int tabuleiro[QUEENS][QUEENS];
     for(int i = 0; i < QUEENS; ++i)
    {
        for(int j = 0; j < QUEENS; ++j)
        {
            tabuleiro[i][j] = 0;
        }
    }



    for(int i = 0; i < QUEENS; ++i)
    {
        tabuleiro[rainhas[i]][i] = 1;
    }

    //Desenha tabuleiro

    for(int i = 0; i < QUEENS; ++i)
    {

        for(int j = 0; j < QUEENS; ++j)
        {
            if(tabuleiro[i][j] == 0)
                cout << "|   |";
            else
                cout << "| Q |";
         }
          cout << endl;
          cout << "- - - - - - - - - - - - - - - - - - - - " << endl;
    }
}

void algoritmoGenetico(int numPop, int numSelecao, int numGeracao)
{
    /*1º passo - criar populações*/
    int matrizPop[numPop][QUEENS], matrizFilhos[numPop][QUEENS];
    int linhaRainha[QUEENS], d1[QUEENS], d2[QUEENS];
    int hPop[numPop];
    int popsCriadas = 0;
    int maior = QUEENS-1;
    int menor = 0;
    int rodada;
    bool achou = false;
    clock_t start, timePassed;
    start = clock();
    timePassed = clock();
    srand((unsigned)time(NULL));
    /*inicializa hPop*/
    for(int h = 0; h < numPop; ++h)
    {
        hPop[h] = 0;
    }

    /*Pop inicial*/
    for(int i = 0; i < numPop; ++i)
    {

        criaVetores(linhaRainha);
        for(int j = 0; j < QUEENS; ++j)
            matrizPop[i][j] = linhaRainha[j];
    }



    /*O for define o número de gerações criadas*/
    for(rodada = 0; rodada < numGeracao; ++rodada)
    {
         popsCriadas = 0;

        /*2º passo - Calcular Aptidão para cada população*/

        for(int h = 0; h < numPop; ++h)
        {
            hPop[h] = 0;  //incializa o vetor de cada H
        }

        /*Faz o cálculo para cada população*/
        for(int pop = 0; pop < numPop; ++pop)
        {
            for(int r = 0; r < QUEENS; ++r)
            {
                linhaRainha[r] = matrizPop[pop][r];
            }

            for(int i = 0; i < QUEENS; ++i)  //coluna Q 1
            {
                for(int k = 0; k < QUEENS; ++k)  //coluna Q 2
                {
                    if(i != k)
                        hPop[pop] += emAtaque(i, k, linhaRainha);
                }
            }
        }

        /*3º passo - Rankear para seleção*/
        vector<pair <int, int> > rankPops;

        /*Cria um vetor de pares para rankear o H de cada população pelo menor H*/
        for(int p = 0; p < numPop; ++p)
        {
             rankPops.push_back(make_pair(hPop[p], p));
        }
        sort( rankPops.begin(),rankPops.end());

        /*Montar vetor com os melhores*/
        int selecionados[numSelecao];
        vector< pair<int, int> >::iterator pop = rankPops.begin();
        for(int i = 0; i < numSelecao; ++i)
        {

            selecionados[i] = pop->second;
            ++pop;
        }

        /*4º passo - Cruzar os numSelecao selecionados e criar uma nova pop de tamanho numPop*/
        int i1 = 0, i2 = 0;



        int k = rand()%(maior-menor+1) + menor; //Escolhe um ponto de cruzamento

        while(popsCriadas < numPop)
        {
            /*Descendente 1*/
            for(int d = 0; d < QUEENS; ++d)  //Cria um filho d1
            {
                if(d < k)
                    d1[d] = matrizPop[selecionados[i1]][d];
                else
                     d1[d] = matrizPop[selecionados[i2]][d];

            }
            for(int j = 0; j < QUEENS; ++j)
            {
                matrizFilhos[popsCriadas][j] = d1[j];
            }
            popsCriadas++;

            /*Descendente 2*/
            if(popsCriadas < numPop)  //Cria um filho d2
            {
               for(int d = 0; d < QUEENS; ++d)  //Cria um filho d1
               {
                    if(d < k)
                        d2[d] = matrizPop[selecionados[i2]][d];
                    else
                        d2[d] = matrizPop[selecionados[i1]][d];
                }
            }

            for(int j = 0; j < QUEENS; ++j)  //Preenche a matriz com o filho d2
            {
                matrizFilhos[popsCriadas][j] = d2[j];
            }
            popsCriadas++;

            /*Forma o proximo par a gerar um filho*/
            i2++;
            if(i2 > numSelecao-1)
            {
                i2 = 0;
                i1++;
            }

            if(i1 > numSelecao-1)
                i1 = 0;


            k = rand()%(maior-menor+1) + menor;
            k+=1;
            if(k > numSelecao-1)
                  k = rand()%(maior-menor+1) + menor;
        }

         int vetor[QUEENS];

         /*5º passo - mutação sobre a população*/
         /*Estratégia - mutar elementos que gerem linhas repetidas*/
        for(int i = 0; i < numPop; ++i)
        {
            for(int v = 0; v < QUEENS; ++v)
                vetor[v] = 0;

            for(int j = 0; j < QUEENS; ++j)
            {
                vetor[matrizFilhos[i][j]] = 1;

            }

            for(int k = 0; k < QUEENS; ++k)
            {
                if(vetor[matrizFilhos[i][k]] == 1)
                {
                    for(int p = 0; p < QUEENS; ++p)
                    {
                        if(vetor[p] == 0)
                        {
                            matrizFilhos[i][k] = p;
                            vetor[p] = 1;
                        }

                    }
                }
            }

        }

        /*Estratégia - trocar alguns números de lugar*/
        for(int i = 0; i < numSelecao; ++i)
        {

        int col1 = rand()%(maior-menor+1) + menor;

        int col2 = rand()%(maior-menor+1) + menor;

        int linha1 = rand()%(numPop-menor+1) + menor;

        int troca = matrizFilhos[linha1][col1];
        matrizFilhos[linha1][col1] = matrizFilhos[linha1][col2];
        matrizFilhos[linha1][col2] = troca;


        }



         /*Copia os filhos para a nova populaão*/
         for(int i = 0; i < numPop; ++i)
         {
             for(int j = 0; j < QUEENS; ++j)
             {
                matrizPop[i][j] = matrizFilhos[i][j];
             }

         }

         /*Verifica se alguns dos filhos é o resultado*/
         int h = 0;
         for(int i = 0; i < numPop; ++i)
         {
             for(int q = 0; q < QUEENS; ++q)
                linhaRainha[q] = matrizPop[i][q];

            for(int m = 0; m < QUEENS; ++m)  //coluna Q 1
            {
                for(int n = 0; n < QUEENS; ++n)  //coluna Q 2
                {
                    if(m != n)
                        h += emAtaque(m, n, linhaRainha);
                }
            }

            if(h == 0)
			{
				criaTabuleiro(linhaRainha);
                achou = true;
				break;
			}
            else
                h = 0;
         }



        if(achou == true)
            break;

    }

	if(achou == true)
		cout << "Solucao encontrada" << endl;
	else
		cout << "Nao encontrou solucao" << endl;

    timePassed = clock();
    cout << "Tempo: " << ((float)timePassed-start)/CLOCKS_PER_SEC << endl;
    cout << "Numero de populacoes: " << numPop << endl;
    cout << "Numero de selecionados por geracao: " << numSelecao << endl;
    cout << "Numero de geracoes: " << numGeracao << endl;
    cout << "Numero de rodadas: " << rodada << endl;
}

int main()
{
    int numPop = 10;
    int numGeracao = 10;
    int numSelecao = 5;
    algoritmoGenetico(numPop, numSelecao, numGeracao);
    return 0;
}
