    //Thauany Moedano
    //92486

    #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h> //Biblioteca que inclui o MAX de cada

    typedef int TChave;
    typedef int TIndice;

    typedef struct {
        TChave Chave;
        //TIndice Indice;
        /* outros compomentes */
    } TItem; //Vetor com itens normais

    typedef struct {
        TChave Chave;
        TIndice Indice;
        //TTam Tam;
        /* outros compomentes */
    } THeap; //Um vetor tipo Heap tem o campo INDICE que armazena

    //Função MinHeapiFY retorna refaz um Heap Minimo
    void MinHeapiFY(THeap *A, int i, int heapSize) {

        int esq = (i*2)+1, dir = (i*2)+2, maior;
        THeap troca;

        if(esq < heapSize && A[esq].Chave <= A[i].Chave)
            maior = esq;
        else
            maior = i;
        if (dir < heapSize && A[dir].Chave <= A[maior].Chave) //maior por i
            maior = dir;

        if(maior != i) {
            troca = A[maior];
            A[maior] = A[i];
            A[i] = troca;
            MinHeapiFY(A, maior, heapSize);
        }
    }
    //Constroi um Min Heap
    void buildMinHeap (THeap *A, int n) {
        int heapSize = n, i;
        for(i = n/2; i >= 0; i--)
            MinHeapiFY(A, i, heapSize);
    }

    //Refaz um Heap Maximo
    void MaxHeapiFY(THeap *A, int i, int heapSize) {

        int esq = (i*2)+1, dir = (i*2)+2, maior;
        THeap troca;

        if(esq < heapSize && A[esq].Chave > A[i].Chave)
            maior = esq;
        else
            maior = i;
        if (dir < heapSize && A[dir].Chave > A[maior].Chave) //maior por i
            maior = dir;

        if(maior != i) {
            troca = A[maior];
            A[maior] = A[i];
            A[i] = troca;
            MaxHeapiFY(A, maior, heapSize);
        }
    }

    //Constroi uma heap maximo
    void buildMaxHeap (THeap *A, int n) {
        int heapSize = n, i;
        for(i = n/2; i >= 0; i--)
            MaxHeapiFY(A, i, heapSize);
    }

    //Ordena um vetor via método HeapSort
    void HeapSort (THeap *A, int n) {

        int i, heapSize = n;
        THeap troca;
        buildMaxHeap(A, n);
        for(i = n-1; i >= 1; i--) {
            troca = A[0];
            A[0] = A[i];
            A[i] = troca;
            heapSize--;
            MaxHeapiFY(A, 0, heapSize);
        }
    }

    TItem *Aloca(int n) {
        return ((n > 0) ? ((TItem *) malloc(n * sizeof(TItem))) : (NULL));
    }

    int Carrega(TItem **A) {
        int i, n;

        scanf("%d", &n);

        (*A) = Aloca(n);
        for (i = 0; i < n ; i++)
            scanf("%d", &(*A)[i].Chave);

        return n;
    }


    int main() {


        TItem **A; //Declarando um vetor de ponteiros
        TItem *Tam; //Declarando um vetor tamanho que contém o tamanho dos vetores
        THeap *H;
        int k, j, i, z, w, x, y;

        scanf("%d %d", &k, &i); //Scan numero de vetores e total de iterações

        if(k <= 0)
            return(0); //Se K é menor q zero o programa n é executado

        Tam = (TItem*)malloc(k*sizeof(TItem)); //Vetor com o tamanho de cada vetor;
        A = (TItem**)malloc(k*sizeof(TItem*)); //Vetor com os vetores;

        for(j = 0; j < k; j++) {
            scanf("%d", &Tam[j].Chave);
            A[j] = (TItem*) malloc(Tam[j].Chave*sizeof(TItem)); //Atribundo para cada posição do Vetor um novo vetor

            if(Tam[j].Chave > 0) {  //Se o Tam do vetor for maior que zero, valores devem ser atribuidos a ele
                for(z = 0; z < Tam[j].Chave; z++)
                    scanf("%d", &A[j][z].Chave);
            }
        }

        //Alocando um vetor final do TIpoHEap
        H = (THeap*)malloc(k*sizeof(THeap));
        for(x = 0; x < k; x++) {
            if(Tam[x].Chave > 0)
                H[x].Chave = A[x][0].Chave; //Preenchedo o vetor H com os menores valores da sequencia de vetores A[x][0]
            else
                H[x].Chave = INT_MAX; //Se o vetor está vazio, INT_MAX é atribuido a ele (o maior valor para INT)

            H[x].Indice = x;
        }

        buildMinHeap(H, k); //Um heap é construido para esta sequencia final

        for(w = 0; w < i; w++) {

            Tam[H[0].Indice].Chave -= 1; //Ação de remover um elemento da sequencia

            if(Tam[H[0].Indice].Chave == 0) //Se o tamanho do vetor é zero, INT_MAX é atribuido
                A[H[0].Indice][0].Chave = INT_MAX;

            for(y = 0; y < (Tam[H[0].Indice].Chave); y++) //O vetor cujo teve um elemento removido tem as posições deslocadas
                A[H[0].Indice][y] = A[H[0].Indice][y+1];

            if(w < i-1)
                H[0].Chave = A[H[0].Indice][0].Chave; //O heap recebe o novo elemento do vetor que foi deslocado

            MinHeapiFY(H, 0, k); //E é refeito o Heap uma vez que apenas a primeira posição está errada a principio
        }

        HeapSort(H, k); //Após construir a sequencia final, ela é ordenada via HeapSort
        for(j = 0; j < k; j++) {
            if(H[j].Chave < INT_MAX) //Os valores com INT_MAX nao devem ser mostrados
                printf("%d ", H[j].Chave);
        }
            printf("\n");

        return(0);
    }
