//*******************************************************************
// Lista de Exercícios : Aula 03
// Autor: Thauany Moedano
// Matricula: 92486
// Data: 29/09/2014
// Curso : BCT Noturno - Turma NB
// Prof: Valério Rosset
//*******************************************************************

/* Exercício 5) Escreva uma rotina completa para remover qualquer elemento da lista EE.*/
#include <stdio.h>
#include <stdlib.h>
#include "listaEE.h"
#define N 10 /*Definimos um N constante uma vez que este exercício só mostra a respeito da exclusão de elementos sem
                nenhum contexto específico. Em uma abordagem mais detalhada N deve ser substituído por outra constante
                ou um número digitado pelo usuário*/

int main() {

    //Tipo lista encadeada
    tipoListaEE testeListaEE;

    //Chamando procedimento que inicializa
    inicializaLista(&testeListaEE);

    //Declarando variaveis
    int opcao = 0;
    int posicao;
    int indice;
    int i;
    int valor;
    int valorEncontrado = 0;

    //Iniciando laço de repetição para manipulação da lista encadeada
    while (opcao != 4) 
	{

		//Imprimindo isntruções e lendo opção do teclado
		printf ("Digite uma uma opcao. 1 - Adiciona, 2 - Remove, 3 - Imprime, 4 - Sair: ");
		scanf ("%d", &opcao);

		//Opção 1 - Adiciona um novo elemento na lista
		/*Somente é utilizado inserção ao final pois o enfoque do exercício é remoção de elementos. Entranto
		na biblioteca constam todos os tipos de inserção*/

		if (opcao == 1) 
		{

			printf ("Digite um elemento: ");
			posicao = proxPosLivre(&testeListaEE);

			//Caso a lista esteja cheia uma mensagem de erro aparecerá
			if (posicao == -1) 
			{
				printf ("Erro!. Lista está cheia");
			}

			else 
			{
				insereElementoFinal(&testeListaEE, posicao);
			}
		}

		//Opção 2 - Remove um elemento da lista
		if (opcao == 2) 
		{

			printf ("Digite o valor a ser excluído da lista: ");
			scanf ("%d", &valor);

			//Verificando se o valor digitado pertence a lista
			for (i = 0; i < N; i++) 
			{
				if (testeListaEE.elemento[i].valor == valor) 
				{
					indice = i;
					valorEncontrado = 1;
					break;
				}
			}

			//Caso não pertença uma mensagem de erro aparecerá
			if (valorEncontrado == 0) 
			{
				printf ("Erro!. Valor não encontrado");
			}

			//Se o elemento for o primeiro utilizamos a rotina de eliminar o primeiro
			if (indice == testeListaEE.primeiro) 
			{
				removeElementoInicio(&testeListaEE);
			}
			//Se o elemento for o último utilizamos a rotina de eliminar o último
			else if (indice == testeListaEE.ultimo) 
			{
				removeElementoFinal(&testeListaEE);
			}
			//Para outros elementos utilizamos a rotina geral de elementos itnermediários
			else 
			{
				removeElementoIntermediario(&testeListaEE, indice);
			}
			//Uma mensagem de remoção aparecerá na tela
			if (valorEncontrado == 1) 
			{
				printf ("Elemento removido com sucesso!\n");
			}
		}
		//Opção 3 - Imprime lista para verificação
		if (opcao == 3) 
		{
			imprimeLista(&testeListaEE);
		}
		//Opção 4 - Encerra o programa
		if (opcao == 4) 
		{
			return (0);
		}

	}
}
