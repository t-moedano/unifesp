//*******************************************************************
// Lista de Exercícios : Aula 05
// Autor: Thauany Moedano
// Matricula: 92486
// Data: 06/10/2014
// Curso : BCT Noturno - Turma B
// Prof: Valério Rosset
//*******************************************************************


/* Exercício LDDE -

a) Escreva uma rotina para remoção do primeiro
elemento de uma LCD-DE.

b) Escreva uma função para remoção do elemento
intermediário de uma LCD-DE*/


#include <stdio.h>
#include <stdlib.h>
#include "listaLDDE.h"


int main()
{
    //Declarando o tipo lista LDDE
    tipoLDDE listaTeste;

    //Inicializando
    inicializaLista(&listaTeste);

    int opcao = 0;

    //Criando laço
    while (opcao != 4) 
	{

        printf ("Digite 1 - Adicionar elemento, 2 - Remover, 3 - Imprimir, 4 - Sair: ");
        scanf ("%d", &opcao);

        //Opção 1 - Adiciona elemento
        if (opcao == 1) 
		{
            //Como o excercicio tem foco em remoção só é utilizada inserção ao final da lista
            insereElementoFinal(&listaTeste);
        }

        //Opçõ 2 - remove um elemento da lista
        else if (opcao == 2) 
		{
            int valor;
            //Lendo o valor a ser removido
            scanf ("%d", &valor);

            //Dependendo da posição do valor, um tipo diferente de remoção será implementado
            if (valor == listaTeste.primeiro->info) 
			{
                removeElementoInicio(&listaTeste);
            }

            else if (valor == listaTeste.ultimo->info)
			{
                removeElementoFim(&listaTeste);
            }
            else 
			{
                //Para remover elementos intermediáros procuramos quais os antecessores e sucessores do elemento
                tipoElemento *valoR = buscaValor(&listaTeste, valor);
                tipoElemento *ant;
                tipoElemento *prox;

                ant = valoR->ant;
                prox = valoR->prox;
                removeElementoIntermedario(&listaTeste, valoR, ant, prox);
            }
        }
        //Opção 3 - imprime a lista
        else if (opcao == 3) 
		{
            imprimeLista(&listaTeste);
        }

        else if (opcao == 4) 
		{
            return(0);
        }


    }
	return (0);
}
