#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000
#include <math.h>

//Estrutura do Grafo

struct Grafo {

    int V;
    int A;
    int contaminados;
    int **adj;
    int *grau;
    int **inc;
};
typedef struct Grafo *tipoGrafo;

struct Colaborador {
    int ehColaborador;
    int entrou;
    int numVizColab;
    int numViztot;
    int salRec;

    float ftDesiste;
};
typedef struct Colaborador colabInfo;

struct listaColab {
    colabInfo lista[N];
};
typedef struct listaColab l_colab;

void inicializaLista(l_colab *aux){
    int a;

    for(a = 0; a < N; a++){
        aux->lista[a].ehColaborador = 0;
        aux->lista[a].numVizColab = 0;
        aux->lista[a].ftDesiste = 0;
    }

}

int **alocaMatriz(int linhas, int colunas) {
    int i, j;

    int **m = (int**)malloc( linhas * sizeof (int *));
    for (i = 0; i < linhas; i++)
        m[i] = (int*)malloc( colunas * sizeof (int));
    for (i = 0; i < linhas; i++)
        for (j = 0; j < colunas; j++)
            m[i][j] = 0;
    return m;
}
//Inicializando o grafo
tipoGrafo inicializaGrafo(int vertice) {
    tipoGrafo G = (tipoGrafo*) malloc(sizeof (G));
    G->V = vertice;
    G->A = 0;
    G->adj = alocaMatriz(vertice, vertice);
    G->grau = (int*)calloc(vertice, sizeof (int));
    int i;
    for(i = 0; i < vertice; i++)
        G->grau[i] = 0;
    return G;
}
//Função que insere uma aresta
void insereAresta (tipoGrafo G, int orig, int dest) {

    if (G->adj[orig][dest] == 0) {
        G->adj[orig][dest] = 1;
        G->adj[dest][orig] = 1;
        G->A++;
        G->grau[orig]+=1;
        G->grau[dest]+=1;
        //return(1);
    }
    //else return(0);
}

//Criando um grau regular
tipoGrafo Regular(int V, int grau) {
    srand(time(NULL));
    int w, i, j;
    tipoGrafo G = inicializaGrafo(V);
    for(i = 0; i < V; i++) {
        for(j = G->grau[i]; j < grau; j++) {
            do {
                w = rand()%V;
            }while(G->grau[w] >= grau);
            insereAresta(G, w, i);
        }

    }
    return G;
}

tipoGrafo Aleatorio(int V, int E) {
    srand(time(NULL));
    int v, w, inseriu = 0, e = 0;
    int p = 1;
    tipoGrafo G = inicializaGrafo( V);
    for (v = 0; v < V; v++) {
        for (w = 0; w < V; w++) {
            if (rand( )%1001 < p) {
                insereAresta(G, v, w);
                inseriu = 1;
            }
        }
        if(inseriu == 0)
            insereAresta(G, v, v+1);
        inseriu = 0;
        e++;
        if(e>=E)
            break;
    }
    return G;
}

tipoGrafo barabasi(int numVertices){
    srand(time(NULL));
    tipoGrafo G = inicializaGrafo(numVertices);
    int m = 2;
    int verLig;
    int prob[(2*numVertices)+1];

    prob[0] = 0;
    prob[1] = 1;

    G->adj[0][1] = 1;
    G->adj[1][0] = 1;

    for(m = 0; m < numVertices; m++){
        verLig = prob[rand()%2*m];
        G->adj[m][verLig] = 1;
        G->adj[verLig][m] = 1;

        prob[2*m -1] = m;
        prob[2*m] =  verLig;
    }
    return G;
}

tipoGrafo LivredeEscala (int V) {

    tipoGrafo G = inicializaGrafo(V);
    int vet[V], i, j;
    int soma = 2, sorteado;
    srand(time(NULL));
    rand();
    rand();
    rand();
    rand();

    G->adj[0][1] = 1;
    G->adj[1][0] = 1;
    vet[0] = 1;
    vet[1] = 1;

    for(i = 2; i < V; i++) {
        for(j = 0; j < V; j++) {
            sorteado = rand()%soma;
            if(sorteado <= vet[j]) {
                insereAresta(G, i, j);
                soma+=2;
                vet[j]++;
                vet[i]++;
                break;
            }
        }
    }
    return(G);

}


void imprimeGrafo(tipoGrafo G) {
    FILE *texto;
    texto = fopen("grafrand.txt", "w");
    int v, w;
    for (v = 0; v < G->V; v++) {
        fprintf(texto, " %2d:", v);
        for (w = 0; w < G->V; w++)
            if (G->adj[v][w] == 1)
                fprintf(texto, " %2d", w);

        fprintf(texto, "\n");

    }
    fclose(texto);
}
int sorteia(int rand, int prob){
    if(rand < prob){
        return 1;
    }
    else{
        return 0;
    }
}
//Função que adiciona um colaborador da rede
void somaVizColab(l_colab *aux, tipoGrafo G, int linha){
    int coluna;
    for(coluna = 0; coluna < 1000; coluna++)
        if(G->adj[linha][coluna])
            aux->lista[coluna].numVizColab++;
}
//Função que retira um colaborador da rede
void subtraiVizColab(l_colab *aux, tipoGrafo G, int linha){
    int coluna;
    for(coluna = 0; coluna < 1000; coluna++)
        if(G->adj[linha][coluna])
            aux->lista[coluna].numVizColab--;
}

//Função que conta o numero de colaboradores da rede
int contaColaboradores(l_colab *aux){
    int contColab = 0;
    int i;
    for(i = 0; i <1000; i++){
        if(aux->lista[i].ehColaborador)
            contColab++;
    }

    return contColab;
}


void contaArestas(tipoGrafo G, l_colab *aux){

    int a, b;

    for(a = 0; a < 1000; a++){
        aux->lista[a].numViztot = 0;
        for(b = 0; b < 1000; b++){
            if(G->adj[a][b])
                aux->lista[a].numViztot++;
        }
    }

}
//Função que conta o número de nao colaboradores
int totalNCola(l_colab *aux){
    int a;
    int totalColab = 0;
    for(a = 0; a < 1000; a++){
        totalColab+= aux->lista[a].numVizColab;
    }
    return 1000 - (totalColab/2);
}
//Função que calcula a desistência
void desiste(l_colab *aux,tipoGrafo G, int denuncia, int r){
    int a = 0;
    r++;
    for(a = 0; a < 1000; a+=r){
        if(aux->lista[a].ehColaborador){
            aux->lista[a].ehColaborador = sorteia(r, denuncia);
            if(!aux->lista[a].ehColaborador)
                subtraiVizColab(aux, G, a);
        }
    }

}
int main() {
    srand(time(NULL));
    rand();
    rand();
    rand();
    rand();
    tipoGrafo G;
    FILE *arquivo;
    arquivo = fopen("arquivo.txt" , "w");
    int alpha=0.01 , beta = 0.01;
    int count=0;
    int dias;
    int denuncia = 100;
    int coluna;
    G = Aleatorio(1000, 1000);
    l_colab menbros; //Gerando grafo regular aleatório
    inicializaLista(&menbros);
    int pos = rand()%N;
    menbros.lista[0].ehColaborador = 1;
    menbros.lista[pos].entrou = 0;
    somaVizColab(&menbros, G, pos);

    for(dias = 0; dias < 1000; dias++){
        desiste(&menbros, G, denuncia, rand()%100); //Calcula se algum membro desiste da ideia por conta de denuncia
        //printf("%d ", contaColaboradores(&menbros));
        for(count = 0; count < 1000; count++){
            //Identificamos um menbro que é colaborador
            if(menbros.lista[count].ehColaborador){
                menbros.lista[count].salRec += sorteia(rand()%100, totalNCola(&menbros)/10); //Verifica se um pagamento é recebido
                if(dias - (menbros.lista[count].salRec + menbros.lista[count].entrou)  >= 10){ //Se 10 pagamentos não sao recebidos
                    menbros.lista[count].ehColaborador = 0; //A pessoa desiste
                    subtraiVizColab(&menbros, G, coluna);
                    break;
                }
                for(coluna = 0; coluna <1000; coluna++){
                    //Aplicamos a influência do participante da piramide aos seus vizinhos
                    if((G->adj[count][coluna]) == 1 && menbros.lista[coluna].ehColaborador == 0){
                        if(menbros.lista[coluna].numVizColab < 4){
                            menbros.lista[coluna].ehColaborador = sorteia((int)rand()%100, 5); //Verifica se alguém entrou para a rede

                            if(menbros.lista[coluna].ehColaborador){
                                menbros.lista[coluna].entrou = dias;
                                menbros.lista[coluna].salRec = 0;

                            }
                        }
                        else{
                            if((menbros.lista[coluna].numVizColab*alpha - totalNCola(&menbros)*beta) > 0){
                                menbros.lista[coluna].ehColaborador = 1;
                                somaVizColab(&menbros, G, coluna);
                            }
                        }
                    }
                }
            }
        }
        if(dias%7 == 0)
          denuncia--;
    fprintf(arquivo, "%d %d\n", dias, contaColaboradores(&menbros));
    }
return(0);
}


