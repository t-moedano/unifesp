#ifndef LISTALDDE_H_INCLUDED
#define LISTALDDE_H_INCLUDED
#endif 

//Declarando estrutura da LDDE
struct elemento 
{
    int info;
    struct elemento *prox;
    struct elemento *ant;
}; typedef struct elemento tipoElemento;

struct estruturaLDDE
{
    tipoElemento *primeiro;
    tipoElemento *ultimo;
	int tamanhoLista;
}; typedef struct estruturaLDDE tipoLDDE;

//Procedimento que inicializa a lista atribuindo NULL aos valores
void inicializaLista (tipoLDDE *listaAux)
{
    listaAux->primeiro = NULL;
    listaAux->ultimo = NULL;
    listaAux->tamanhoLista = 0;
}

//Procedimento que insere o elemento depois do último
void insereElementoFinal (tipoLDDE *listaAux) 
{
    // Alocando espaço para o elemento
    tipoElemento *novo = (tipoElemento*) malloc(sizeof(tipoElemento));
    // fazendo leitura dos dados para info
    scanf ("%d", &novo->info);

    if (listaAux->tamanhoLista == 0)
	{
        novo->prox = NULL;
        novo->ant = NULL;
        listaAux->primeiro=novo;
        listaAux->ultimo=novo;
    }
    else 
	{
        novo->prox = NULL;
        novo->ant = listaAux->ultimo;
        listaAux->ultimo->prox = novo;
        listaAux->ultimo=novo;
    }

    listaAux->tamanhoLista++;
}

//Insere elemento antes do primeiro
void insereElementoInicio (tipoLDDE *listaAux, int info) 
{

    //Alocando elemento
    tipoElemento *novoElem = malloc(sizeof(tipoElemento));

    novoElem->info = info;
    //As atribuições são bem parecidas com a insereElementoFim
    if (listaAux->tamanhoLista == 0)
	{
        novoElem->prox = NULL;
        novoElem->ant = NULL;
        listaAux->primeiro = novoElem;
        listaAux->ultimo = novoElem;
    }

    //Neste caso devemos atualizar o ponteiro do primeiro
    else 
	{
        listaAux->primeiro->ant = novoElem;
        novoElem->prox = listaAux->primeiro;
        novoElem->ant = NULL;
        listaAux->primeiro = novoElem;
    }

    listaAux->tamanhoLista++;
}

//Procedimento que busca o sucessor de um elemento
tipoElemento* buscaSucessor (tipoLDDE *listaAux, int valor) 
{

    int i;

    tipoElemento *e = listaAux->primeiro;

    for (i = 0; i < listaAux->tamanhoLista; i ++) 
	{

        if (e->prox == valor) 
		{
            return (e); //retorna sucessor do valor
        }

        e = e->prox;
    }

    return(NULL);
}

//Insere um elemento entre dois elementos
void insereElementoIntermediario(tipoLDDE *listaAux, int info, tipoElemento *sucessor, tipoElemento *antecessor) 
{

    //Aloca um elemento
    tipoElemento *novoElem = malloc(sizeof(tipoElemento));

    novoElem->info = info;

    //Atualiza os ponteiros
    antecessor->prox = novoElem;
    sucessor->ant = novoElem;
    novoElem->prox = sucessor;
    novoElem->ant = antecessor;
    listaAux->tamanhoLista++;
}

//Este é um procedimento que mostra a lista
void imprimeLista (tipoLDDE *listaAux) 
{

    int i;
    //Utilizamos um ponteiro auxiliar para tal
    tipoElemento *p = listaAux->primeiro;

    for (i = 0; i < listaAux->tamanhoLista; i++) 
	{
        printf ("%d\n", p->info);
        p = p->prox;
    }
}

//Procedimento que remove o primeiro elemento da lista
void removeElementoInicio (tipoLDDE *listaAux) 
{

    //Fazemos uso de dois ponteiros auxiliares
   tipoElemento *primeiro;


   //Guardamos o endereço do primeiro elemento da lista e seu valor
   primeiro = listaAux->primeiro;
   primeiro->info = listaAux->primeiro->info;

   //Atualizamos o ponteiro do primeiro
   listaAux->primeiro = listaAux->primeiro->prox;
   listaAux->primeiro->ant = NULL;

   //Liberamos a memória
   free(primeiro);

   //Atualizamos o tamanho da lista
   listaAux->tamanhoLista--;
}

//Procedimento que remove o último elemento
void removeElementoFim (tipoLDDE *listaAux) 
{

    //Também uilizamos um ponteiro auxiliar
    tipoElemento *ultimo;

    //Guardamos as informações do último
    ultimo = listaAux->ultimo;
    ultimo->info = listaAux->ultimo->info;

    //Atualizamos o próximo
    listaAux->ultimo = listaAux->ultimo->ant;
    listaAux->ultimo->prox = NULL;
    //Liberamos a memória
    free(ultimo);

    //Atualizamos o tamanho da lista
    listaAux->tamanhoLista--;

}

//Procedimento que remove um elemento que não é o último nem o primeiro
void removeElementoIntermedario (tipoLDDE *listaAux, tipoElemento *valor, tipoElemento *ant, tipoElemento *prox) 
{

    //Utilizamos um auxiliar
    tipoElemento *removeV;

    removeV = valor;

    //Atualizamos os ponteiros
    ant->prox = valor->prox;
    prox->ant = valor->ant;

    //Liberamos a memória
    free(removeV);

    //Atualizamos a lista
    listaAux->tamanhoLista--;
}

//Busca o endereço de memória de um determinado elemento
tipoElemento* buscaValor (tipoLDDE *listaAux, int valor) 
{

    int i;

    tipoElemento *e = listaAux->primeiro;

    for (i = 0; i < listaAux->tamanhoLista; i++) 
	{

        //Quando o valor for encontrado, seu endereço E será retornado
        if (e->info == valor) 
		{
            return (e);
        }

        e = e->prox;
    }
}
