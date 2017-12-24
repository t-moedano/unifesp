#ifndef PALAVRAS_H_INCLUDED
#define PALAVRAS_H_INCLUDED
#endif 
//Biblioteca com funções para o programa de caça palavras

//Função que aloca uma matriz dinamicamente
char** alocarMatriz (int linhas, int colunas) 
{

    int i;
    char **m = (char**) malloc(linhas*sizeof(char*)); //Alocando o número de linhas
    //Alocando o número de colunas
    for (i = 0; i < linhas; i++) {
        m[i] = (char*) malloc(colunas * sizeof(char));
    }

    return (m);
 }

//Procedimento que procura uma palavra na horizontal
void procuraHorizontal (char palavra[50], int linhas, int colunas, int tam, char** matrizBusca, int* achaPalavra) 
{
    //Declarando índices. I são linhas, J colunas, C é o índice de cada Char e T é o controle da forma que a matriz será rodada
    int c = 0;
    int i = 0;
    int j = 0;
    int t = 0;

    //Declarando variáveis de coordenadas das posições iniciais e finais de I e J
    int auxMatrizI;
    int auxMatrizJ;
    int auxFimMatrizI;
    int auxFimMatrizJ;

    /*Declarando variáveis que vão armazenar um pedaço da matriz em uma string. A variável 'compara' é a string que será
    comparada com nossa palavra. */
    char compara[50];


    /*Laço que irá percorrer a matriz, pegar o número de caracteres correspondente ao tamanho da nossa palavra
    e comparar se são iguais. O laço para quando chegarmos ao final da matriz*/
    while (j != (colunas) && i != (linhas)) 
	{
        for (c = 0; c < tam; c ++) {
                //No início salvamos as posições de I e J. Elas serão exibidas caso a string salva seja igual a palavra digitada
                if (c == 0) {
                        auxMatrizI = i;
                        auxMatrizJ = j;
                    }
        //Motamos a string de acordo com cada caractere da matriz
        compara[c] = matrizBusca[i][j];
        //Como se trata de palavras na horizontal, sempre mudamos as colunas
        j++;
    }
    //Como o laço conta uma vez a mais J, devemos subtraí-lo para ter a informação da posição final correta
    j--;
    /*A função strnmp compara se duas strings são iguais até o tamanho dado. Comparamos se a string montada é idêntica
    a palavra digitada. Caso seja, esta função retorna um valor zero armazenada na variável retorno*/
    int retorno = strncmp(palavra, compara, tam);
    //Armazenamos as posições finais que serão exibidas caso a palavra seja idêntica
    auxFimMatrizI = i;
    auxFimMatrizJ = j;

        if (retorno == 0)
		{
            //Exibindo coordenadas acrescido de 1 pois a matriz em C começa em zero mas um caça-palavras geralmente começa em 1
            printf ("%d,%d:%d,%d ", auxMatrizI+1, auxMatrizJ+1, auxFimMatrizI+1, auxFimMatrizJ+1);
            *achaPalavra = 1; //O controle se torna verdade
            c = 0; //Zeramos a variável C para contarmos a próxima string da matriz
        }
    //Caso contrário não exibimos nada, apenas zeramos a variável C
        else if (retorno != 0) 
		{
            c = 0;
        }
    /*Acrescentamos um a t, pois agora ele irá montar uma palavra a partir de t+1. Se montamos uma palavra inicialmente
    em i = 0 e j = 0, por exemplo, agora ele irá montar uma palavra a partir de i = 0 e j = 1, até que seja necessário mudar
    de linha. Um exemplo visual:
    0 1 2 3 4 5 6 7 8
   0A B C D E F G H I
   1J K L M N O P Q R
   Inicialmente montamos a palavra ABCD. Depois acrescentamos um a T (controle de Tempo) e montamos BCDE até que não seja mais
   possível montar uma palavra na linha (quando o valor da coluna estourar)*/
    t++;
    j = t;
        //Quando J estourar as colunas, resetamos o T (controle de tempo) e o J, e vamos para a próxima linha
        if (j >= colunas) 
		{
            j = 0;
            t = 0;
            i++;

        }
    }
}

void procuraVertical (char palavra[50], int linhas, int colunas, int tam, char** matrizBusca, int* achaPalavra) 
{
    //A lógica para a vertical é bem parecido, as variáveis utilizadas tem as mesmas funções
    int c = 0;
    int i = 0;
    int j = 0;
    int t = 0;

    int auxMatrizI;
    int auxMatrizJ;
    int auxFimMatrizI;
    int auxFimMatrizJ;

    char compara[50];
    /*A montagem de palavras segue exatamente a mesma lógica. A única diferença é que agora mudamos de linha (I) constantemente
    enquanto o número de colunas só muda determinadas vezes (mesma ocorrência para colunas e linhas na horizontal*/
    while (j != (colunas) && i != (linhas)) 
	{
        for (c = 0; c < tam; c ++) 
		{
            if (c == 0) 
			{
                auxMatrizI = i;
                auxMatrizJ = j;
            }

        compara[c] = matrizBusca[i][j];
        i++;

            if (i >= linhas) 
			{
                i = 0;
                t = 0;
                j++;
                break;
            }
        }

        if ( i != 0 ) 
		{
            i --;
        }

    int retorno = strncmp(palavra, compara, tam);

    auxFimMatrizI = i;
    auxFimMatrizJ = j;

        if (retorno == 0)
		{
            printf ("%d,%d:%d,%d ", auxMatrizI+1, auxMatrizJ+1, auxFimMatrizI+1, auxFimMatrizJ+1);
            *achaPalavra = 1;
            c = 0;
        }
        else if (retorno != 0) 
		{
            c = 0;
        }

        if (i != 0) {
            t++;
            i = t;
        }
    }
}

/*A lógica para procurar a palavra na diagonal parte de uma lógica parecida com as anteriores. Neste caso temos que
alternar I e J na mesma medida sendo que o I não se inicial mais do zero e sim do índice final da matriz. Por isso nosso
controle de tempo vai alterar J de maneira similar ao modo de procurar na horizontal e I sempre vai voltar para a posição
inicial*/

void procuraDiagonal (char palavra[50], int linhas, int colunas, int tam, char **matrizBusca, int *achaPalavra) 
{
    /*As variáveis tem as mesmas funções dos procedimentos anteriores. iInicial e tempoJ tem a mesma função de controle
    da variável T dos outros procedimentos*/

    int  c = 0;
    int iInicial = linhas-1;
    int tempoJ = 0;
    int i = linhas - 1;
    int  j = 0;

    int auxMatrizI;
    int auxMatrizJ;
    int auxFimMatrizI;
    int auxFimMatrizJ;

    char compara[50];
    //Mesma lógica de montagem. Entretanto, I e J se alternam na mesma medida
    do {
        for (c = 0; c < tam; c ++) {
            if (c == 0) {
                auxMatrizI = i;
                auxMatrizJ = j;

            }

            compara[c] = matrizBusca[i][j];
                 i--;
                 j++;
        }

        i++;
        j--;

    int retorno = strncmp(palavra, compara, tam);

    auxFimMatrizI = i;
    auxFimMatrizJ = j;

        if (retorno == 0){
            printf ("%d:%d, %d:%d ", auxMatrizI+1, auxMatrizJ+1, auxFimMatrizI+1, auxFimMatrizJ+1);
            *achaPalavra = 1;
            c = 0;
        }

        else if (retorno != 0) {
            c = 0;
        }
       
    //O controle é feito desta maneira, retornamos I na posição inicial e o J ganha uma nova posição
    tempoJ ++;
    j = tempoJ;
    i = iInicial;
        /*Caso J exceda a diferença de colunas e o tamanho da palavra, significa que não é possível formar
        uma nova palavra naquela linha. Então o Iinicial muda de posição e o tempoJ retorna a zero.*/
        if (j > colunas-tam) 
		{
            tempoJ = 0;
            j = tempoJ;
            iInicial--;
            i = iInicial;
        }
    } while(j == colunas-1 && i == 0);
}
