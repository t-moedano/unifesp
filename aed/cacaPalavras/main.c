//*******************************************************************
// Lista de Exercícios : 
// Autor: Thauany Moedano
// Matricula: 92486
// Data: 19/09/2014
// Curso : BCT Noturno - Turma B
// Prof: Valério Rosset
//*******************************************************************

/* EXERCÍCIO. LAB01 - CAÇA PALAVRAS. Fazer um caça palavras*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "palavras.h" //Implementando biblioteca palavras. Sugiro que leia esta biblioteca primeiro


int main() {
    //Abrindo o programa MatrizLetras.txt
    printf ("~~~Lendo o arquivo....\n");
    FILE *cacaPalavras;
    cacaPalavras = fopen("matrizLetras.txt", "r");

    //Declarando variáveis para contar quantas linhas e colunas tem a matriz do arquivo
    int marcacao;
    int linhas = 1;
    int caracteres = 0;
    int colunas;

    //Se o arquivo não for encontrado, uma mensagem de erro será exibida
    if(cacaPalavras == NULL) 
	{
        printf("Erro! Arquivo nao encontrado\n");
        return(0);
    }
    else
	{
        printf ("Arquivo lido com sucesso! Transpondo matriz.... \n");
	}

    //Contando número de caracteres e linhas
    while ((marcacao = fgetc(cacaPalavras))!= EOF)
	{
        caracteres ++;
        if(marcacao =='\n' || marcacao == '\l') 
		{
            linhas++;
        }
    }
    //Deduzindo o número de colunas a partir do número de caracteres e linhas
    colunas = caracteres / linhas;
    //Fechando o arquivo
    fclose(cacaPalavras);

/************************************************/

    /*Alocando a matriz dinamicamente. ATENÇÃO: PARA O PROGRAMA FUNCIONAR CORRETAMENTE EM LINUX
    BASTA TIRAR O +1 DE COLUNAS +1 DA ALOCAÇÃO DINAMICA E DO FOR DE PREENCHIMENTO DA MATRIZ*/
    char **matrizBusca;
    matrizBusca = alocarMatriz(linhas, colunas+1);
    //Caso não haja memória suficiente, uma mensagem de erro será exibida
    if (matrizBusca == NULL) 
	{
        printf ("Nao foi possivel alocar a matriz!");
        return(0);
    }

/************************************************/

    //Reabrindo o arquivo de matriz
    FILE *matrizLetras;
    matrizLetras = fopen("MatrizLetras.txt", "r");

    //Transpondo o arquivo de matriz para uma matriz alocada dinamicamente
    int i;
    int j;

    for (i = 0; i < linhas; i++) 
	{
        for (j = 0; j < colunas+1; j++) 
		{
            matrizBusca[i][j] = fgetc(matrizLetras);
        }
    }
    //Fechando o arquivo
    fclose(matrizLetras);

/************************************************/

    printf("Digite uma palavra: ");
    //Lendo do teclado a palavra a ser procurada
    char palavra[50];
    scanf ("%s", &palavra);
    //Verificando o tamanho da palavra. Será utilizado para procurá-la na matriz
    int tam;
    tam = strlen(palavra);

    //Controle que verifica se uma palavra foi encontrada.
    int achaPalavra = 0;
    //Se o usuário inserir uma palavra que estoure a matriz, uma mensagem de erro será exibid
    if (tam > colunas || tam > linhas) 
	{
        printf ("Estouro de memoria. Palavra muito grande. Erro \n");
        return (0);
    }
    //Procurando a palavra na horizontal, vertical e diagonal
    procuraHorizontal(palavra, linhas, colunas, tam, matrizBusca, &achaPalavra);
    procuraVertical(palavra, linhas, colunas, tam, matrizBusca, &achaPalavra);
    procuraDiagonal(palavra, linhas, colunas, tam, matrizBusca, &achaPalavra);

/************************************************/
//Invertendo a palavra para procurá-la de trás para frente
    //Declarando índices
    int r;
    int s = 0;
    char palavraInvertida[50];
    /*Invertendo a palavra. Existe uma função da biblioteca <string.h> chamada strrev() que faz a mesma coisa*/
    for (r = tam-1; r >= 0; r--) 
	{
        palavraInvertida[s] = palavra[r];
        s++;
    }
    //Procurando a palavra de trás pra frente na horizontal, vertical e diagonal
    procuraHorizontal(palavraInvertida, linhas, colunas, tam, matrizBusca, &achaPalavra);
    procuraVertical(palavraInvertida, linhas, colunas, tam, matrizBusca, &achaPalavra);
    procuraDiagonal(palavraInvertida, linhas, colunas, tam, matrizBusca, &achaPalavra);
    //Se nenhuma palavra foi encontrda, um X será exibido na tela.
    if (achaPalavra == 0) 
	{
        printf ("X");
    }

    //Liberando a memória da matriz e encerrando o programa
    free(matrizBusca);
    return (0);
 }
