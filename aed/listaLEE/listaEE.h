//Biblioteca com funções de implementação de Lista encadeada

#ifndef LISTAEE_H_INCLUDED
#define LISTAEE_H_INCLUDED
#define N 10
#endif 

//Declarando estrtura do tipo Lista Encadeada
struct info 
{
    int valor;
    int prox;
};
    typedef struct info tipoInfo;

struct listaEE 
{
    int tamanhoLista;
    int primeiro;
    int ultimo; // 0 ocupado, 1 livre
    int posLivre[N];
    tipoInfo elemento[N];
}; typedef struct listaEE tipoListaEE;


//Procedimento que inicializa a lista
void inicializaLista (tipoListaEE *listaAux) 
{


     // Inicializa elementos da lista
     listaAux->tamanhoLista = 0;
     listaAux->primeiro = -1;
     listaAux->ultimo = -1;

     int i;
       //Atribuindo valores zero e -1 a todos os elementos da lista. Indicando que a posição é livre (= 1)
     for (i = 0; i < N; i++) 
	 {
        listaAux->elemento[i].valor = 0;
        listaAux->elemento[i].prox = -1;
        listaAux-> posLivre[i] = 1;
    }
}

//Função que indica qual a próxima posição livre
int proxPosLivre(tipoListaEE *listaAux)
{

    int i;
    //Procura um espaço na lista que esteja vazio
    for (i = 0; i < N; i++)
	{
        if (listaAux->posLivre[i]== 1)
        return (i);
    }
 //Caso não haja espaços a lista retorna -1
 return (-1);
}

//Insere um elemento no fim da lista
void insereElementoFinal (tipoListaEE *listaAux, int posicao) 
{

    if (posicao != -1)
	{
        scanf ("%d", &listaAux->elemento[posicao].valor);
    }

    //Atualiza elementos da lista conforme o seu tamanho
    if (listaAux->tamanhoLista != 0) 
	{

        listaAux->elemento[listaAux->ultimo].prox = posicao;
        listaAux->elemento[posicao].prox = -1;
        listaAux->tamanhoLista ++;
        listaAux->ultimo = posicao;
        listaAux->posLivre[posicao]= 0;
    }


    if (listaAux->tamanhoLista == 0) 
	{

        listaAux->primeiro = posicao;
        listaAux->ultimo = posicao;
        listaAux->posLivre[posicao] = 0;
        listaAux->tamanhoLista++;

    }
    printf ("Elemento adicionado com sucesso! \n");
}

//Insere um elemento antes do primeiro na lista
/*Não está sendo utilizada no programa pois o enfoque dele é para a remoção de elementos*/
void insereElementoInicio (tipoListaEE *listaAux, int posicao) 
{

    //Guardamos o primeiro elemento em uma variável
    int primeiroE = listaAux->primeiro;

    if (posicao!=-1) 
	{
        printf ("Digite o elemento da lista:  ");
        scanf ("%d", &listaAux->elemento[posicao].valor);
    }

    if (listaAux->tamanhoLista == 0) 
	{
        listaAux->primeiro = posicao;
        listaAux->posLivre[posicao] = 0;
        listaAux->tamanhoLista++;
    }

    //Atribuimos a listaAux->primeiro o novo indice do primeiro elemento.
    else 
	{
        listaAux->elemento[posicao].prox = primeiroE;
        listaAux->tamanhoLista++;
        listaAux->primeiro = posicao;
        listaAux->posLivre[posicao] = 0;
    }
    printf ("Elemento adicionado com sucesso!\n");

}

//Procedimento que insere um novo elemento exatamento no meio da lista
void insereElementoMeio (tipoListaEE *listaAux) 
{

    //Verificando em que lugar é o meio
    int meio = N/2;

    //Se não há elementos, a leitura é direta
    if (listaAux->posLivre[meio] == 1) 
	{
        scanf ("%d", &listaAux->elemento[meio].valor);
    }

    if (listaAux->tamanhoLista == 0) {
        listaAux->primeiro = meio;
        listaAux->posLivre[meio] = 0;
    }

    else 
	{
        listaAux->elemento[listaAux->ultimo].prox = meio;
        listaAux->elemento[meio].prox = -1;
        listaAux->tamanhoLista++;
        listaAux->ultimo = meio;
        listaAux->posLivre[meio] = 0;
    }

    //Caso o contrário, o elemento que estava no meio é enviado para a próxima posição livre da lista
    if (listaAux->posLivre[meio] == 0) 
	{

        int posLivre = proxPosLivre(&listaAux);

        listaAux->elemento[posLivre].valor = listaAux->elemento[meio].valor;
        listaAux->elemento[posLivre].prox = listaAux->elemento[meio].prox;
        listaAux->posLivre[posLivre] = 0;

        int i;

        for (i = 0; i < N; i++) 
		{
            if (listaAux->elemento[i].prox == meio)
			{
                listaAux->elemento[i].prox = posLivre;
            }
        }

        //Feito isso podemos adicionar o elemento no meio da lista
        int ultimo;
        ultimo = listaAux->ultimo;

        scanf ("%d", &listaAux->elemento[meio].valor);

        listaAux->elemento[ultimo].prox = meio;
        listaAux->elemento[meio].prox = -1; listaAux->tamanhoLista++; listaAux->posLivre[meio] = 0;

    }
}

//Procedimento que remove o primeiro elemento da lista
void removeElementoInicio (tipoListaEE *listaAux) 
{
    int primeiroA = listaAux->primeiro;
    //Resetamos o índice onde estava o primeiro
    //O próximo elemento ao primeiro se torna o novo primeiro.
    listaAux->primeiro = listaAux->elemento[primeiroA].prox;
    listaAux->elemento[primeiroA].valor = 0;
    listaAux->elemento[primeiroA].prox = -1;
    listaAux->posLivre[primeiroA] = 1;
    listaAux->tamanhoLista--;

}

//Procedimento que remove o último elemento da lista
void removeElementoFinal (tipoListaEE *listaAux) 
{

    int i;
    int ultimo;

    ultimo = listaAux->ultimo;

    //Zeramos o último elemento
    listaAux->elemento[ultimo].valor = 0;
    listaAux->elemento[ultimo].prox = -1;
    listaAux->posLivre[ultimo] = 1;
    listaAux->tamanhoLista--;

    //Procuramos o penúltimo elemento da lista. Ele se tornará o novo último elemento.
    for (i = 0; i < N; i ++) 
	{
        if (listaAux->elemento[i].prox == ultimo) 
		{
            listaAux->elemento[i].prox = -1;
            listaAux->ultimo = i;
            break;
        }
    }

}

//Procedimento que remove elementos intermediários
void removeElementoIntermediario (tipoListaEE *listaAux, int indice) 
{

    int i;

    //O elemento que tinha o elemento a ser apagado como próximo tem como novo próximo o próximo do elemento apagado
    /*Ilustrando temos que por exemplo:
    indice: 4
    elemento: 5
    próx: indice 5

    indice: 5
    elemento: 4
    próx: índice 6

    indice: 6
    elemento 2

    se apagarmos o índice 5, o próx do índice 4 se torna o índice 6 que era o próximo do índice 5 que foi apagado*/
    for (i = 0; i < N; i++) 
	{
        if (listaAux->elemento[i].prox == indice) 
		{
             listaAux->elemento[i].prox = listaAux->elemento[indice].prox;
             break;
        }
    }
    //Zeramos o índice que foi apagado
    listaAux->elemento[indice].valor = 0;
    listaAux->elemento[indice].prox = -1;
    listaAux->posLivre[indice] = 1;
    listaAux->tamanhoLista --;
}

//Procedimento que imprime a lista para verificação
void imprimeLista (tipoListaEE *listaAux) 
{
    int i;
    for (i = 0; i < N; i++)
	{
        if (listaAux->posLivre[i] == 0) 
		{
            printf ("%d\n", listaAux->elemento[i].valor);

        }
    }
}


