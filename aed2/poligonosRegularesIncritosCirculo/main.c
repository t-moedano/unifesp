        //Thauany Moedano
        //RA: 92486
        #include <stdio.h>
        #include <stdlib.h>
        #define NIL 0

        //Recebe as entradas do programa via scanf na seguinte ordem
        //
        //{perimetro}:   o perimetro da circunferencia (2 pi R) centrada em (0, 0)
        //n:           a quantidade de pontos
        //{pontos[0]},
        //...,
        //{pontos[n-1]}: n pontos na circunferencia, identificados atraves do
        //             comprimento do arco anti-horario entre o ponto e origem (0, R)
        //
        // Os pontos sao fornecidos em ordem crescente

        //Definindo estruturas de Tabela Hash
        typedef int TChave;

        typedef struct {
            TChave Chave;
            /* outros compomentes */
        } TItem;

        typedef int TIndice;

        typedef struct {
            TItem *Item;
            TIndice m, n;
        } THash;

        //Carregando dados de Entrada
        void CarregaDadosDeEntrada (int *perimetro, int *n, int **pontos)
        {
            int i;

            scanf("%d", perimetro);
            scanf("%d", n);

            *pontos = malloc(*n * sizeof(int));
            for (i = 0; i < *n; i++)
                scanf("%d", &((*pontos)[i]));
        }

        //Inicializando a tabela Hash com tamanho do perimetro
        THash *Inicializa(int m)
        {
            TIndice i;
            THash *T;

            T = (THash *) malloc(sizeof(THash));

            T->n = 0;
            T->m = m;
            T->Item = (TItem *) malloc(T->m * sizeof(TItem));
            for (i = 0; i < T->m; i++)
                T->Item[i].Chave = NIL;

            return T;
        }


        // Devolve um ponteiro para a tabela hash a ser utilizada em EncontraMaiorPA
        //
        THash* ConstroiTabelaHash (int perimetro, int n, int *pontos)
        {
            THash *T = Inicializa(perimetro);
            TItem x;
            x.Chave = 1;
            int i;
            for(i = 0; i < n; i++) {
                T->Item[(pontos[i] - pontos[0])%perimetro] = x; //Construindo a tabela utilizando o Hash visto no slide
            }
            //Retornando a tabela
            return(T);
        }


        // Devolve 1 caso
        int EhProgressaoAritmetica (THash *h, int perimetro, int *pontos, int r, int o)
        {
           //Para verificar se é progressão aritmética basta saber se existem pontos na tabela
           //na distância de R (razao)
           //Para isso basta verificar o ponto*razão e utilizar a formula da tabela Hash para se deslocar na tabela
            //Se não houver ponto (zero) significa que não é progressão aritmética
            int i;
            for(i = 0; i <= perimetro/r; i++) {
                if(h->Item[(i*r + pontos[o] - pontos[0])%perimetro].Chave == 0)
                    return(0);
            }
            return(1);

        }



        // Encontra o poligono regular inscrito na circunferencia de perimetro
        // {perimetro} com maior quantidade de lados formados pelos pontos
        // {pontos[0], ..., pontos[n-1]}, utilizando-se a tabela hash {h}.
        //
        // Esta funcao devolve a razao da progressao aritmetica {p >= 3} e
        // o ponto inicial do poligono {pontoInicial}, com menor comprimento de arco.
        // {p=-1} e {pontoInicial=-1} sao retornados caso nenhum poligono .
        //
        void EncontraMaiorPA (int perimetro, int n, int *pontos, THash *h,
                              int *r, int *pontoInicial) {

             int i, j, rangeMin, rangeMax, conf = 0;
            //A priori, pontoInicial e R são -1 e serão devolvidos dessa forma caso nao haja polígono
            *pontoInicial = -1;
            *r = -1;
            //Primeiro estabelecemos os limites em que R será testado
            rangeMin = 0; //O limite mínimo é maior diferença entre dois pontos
            for(i = 1; i < n; i++) {
                if(pontos[i] - pontos[i-1] > rangeMin)
                    rangeMin = pontos[i] - pontos[i-1];
            }
            //printf("%d\n", rangeMin);
            rangeMax = perimetro/3; //O limite máximo é perimetro/3
            //Assim testamos para cada R que seja multiplo do poligono, um ponto inicial e verificamos se é PA
            for(j = rangeMin; j <= rangeMax; j++) {
                if(perimetro % (j) == 0) {
                    for(i = 0; i < n; i+=1) {
                        if(EhProgressaoAritmetica(h, perimetro, pontos, j, i)) {
                            *pontoInicial = pontos[i]; //Caso seja PA basta atribuir a razão e o ponto Inicial
                            *r = j;
                            conf = 1;
                            break;
                        }
                    }
                }
                if(conf == 1)
                    break;
            }
        }



        int main()
        {
            int n, perimetro, *pontos, r, pontoInicial;
            THash *h;

            CarregaDadosDeEntrada (&perimetro, &n, &pontos);

            h = ConstroiTabelaHash (perimetro, n, pontos);
           // Imprime(h);
            EncontraMaiorPA (perimetro, n, pontos, h, &r, &pontoInicial);

            printf ("%d %d", r, pontoInicial);

            free (pontos); free(h);

            return 0;
        }
