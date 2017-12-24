#include <iostream>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <ctime>
#define QUEENS 8

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

            srand((unsigned)time(0));
            chosenNumber = rand()%(maior-menor+1) + menor;
        } while(numbers[chosenNumber] == 1);
        numbers[chosenNumber] = 1;
        rainhas[i] = chosenNumber/2;
        if(chosenNumber > 1)
        {
            numbers[chosenNumber-1] = 0;
            numbers[chosenNumber-2] = 0;
        }
        if(chosenNumber < QUEENS - 2)
        {
            numbers[chosenNumber+1] = 0;
            numbers[chosenNumber+2] = 0;
        }

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

void subidaEncosta(int rainhas[])
{
    clock_t start, timePassed;
    start = clock();
    timePassed = clock();
    int hIncial = 0, hMov = 0, bestLinha, bestColuna;
    int numMov = 0;
    srand((unsigned)time(0));
    /*Calcula h inicial*/
    for(int i = 0; i < QUEENS; ++i)  //coluna Q 1
    {
        for(int k = 0; k < QUEENS; ++k)  //coluna Q 2
        {
            if(i != k)
                hIncial += emAtaque(i, k, rainhas);
        }
    }
    cout << "hInicial: " << hIncial << endl;


    while(hIncial > 0 && (((float)timePassed-start)/CLOCKS_PER_SEC < 0.01))
    {
        for(int a = 0; a < QUEENS; ++a)
        {
            int posAtual = rainhas[a];
            for(int b = 0; b < QUEENS; ++b)
            {
                if(posAtual != b)
                    rainhas[a] = b;

                for(int i = 0; i < QUEENS; ++i)  //coluna Q 1
                {
                    for(int k = 0; k < QUEENS; ++k)  //coluna Q 2
                    {
                        if(i != k)
                            hMov += emAtaque(i, k, rainhas);
                    }
                }
                if(hMov <= hIncial)
                {
                    hIncial = hMov;
                    bestLinha = rainhas[a];
                    bestColuna = a;
                }
                hMov = 0;
            }

            rainhas[a] = posAtual;
        }
        rainhas[bestColuna] = bestLinha;
        numMov++;

        timePassed = clock();
    }
    cout << "Tempo: " << ((float)timePassed-start)/CLOCKS_PER_SEC << endl;
    cout << "Numero de Movimentos: " << numMov << endl;
    if(hIncial == 0)
        cout << "Encontrou solucao!" << endl;
    else
        cout << "Nao encontrou solucao :(" << endl;

    cout << "Tabuleiro final " << endl;
   criaTabuleiro(rainhas);

}

int main()
{
    int rainhas[QUEENS];

    criaVetores(rainhas);
    criaTabuleiro(rainhas);


    subidaEncosta(rainhas);

    return 0;
}
