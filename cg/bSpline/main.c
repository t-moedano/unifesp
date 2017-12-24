//Thauany Moedano
//RA 92486
//Trabalho feito em Linux Ubuntu 15.10
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

///X,Y armazenam os valores dos pontos
float x,y;
int flag = 0, d = 0; ///Uma flag que controla a execucao da spline e o parametro de grau d
/*d teve que ser declarado globalmente pois eh utilizado no main e na funcao desenha*/

///Estrutura que armazena a lista de pontos
struct elemento {

float x1,y1;
struct elemento *prox;

}; typedef struct elemento tipoElemento;

struct listaDE {

    tipoElemento *primeiro;
    tipoElemento *ultimo;
    int tamanhoLista;
    }; typedef struct listaDE tipoLDE;
///Fim da estrutura

tipoLDE listaPontos; //Declarando a lista de pontos
/*listaPontos e declarado apos a criacao das estruturas senao nao compila*/

///Funcao que calcula o B(k,d,U)
/*Como parametro tem o indice k, grau d, o vetor com U_i e o valor de u a ser calculado*/
float B(int k, int d, int U[], float u) {

    if(d == 1) { //Se o grau da funcao eh 1 retorna ou zero ou um de acordo com a condicao
        if(U[k] <= u && u < U[k+1])
            return(1.0);
        else
            return(0.0);
    }
    ///Tratamento da funcao quando o denominador e zero
    else if(U[k+d-1]-U[k] == 0.00 && U[k+d]-U[k+1] == 0.00) //Se ambos denominadores eh zero, retorna zero
        return (0.0);
    /*Se apenas um dos denominadores eh zero, retorna a fracao valida*/
    else if(U[k+d-1]-U[k] == 0.00)
        return(((U[k+d]-u)/(U[k+d]-U[k+1])) * B(k+1,d-1, U, u));

    else if(U[k+d]-U[k+1] == 0.00)
        return((((u-U[k])/(U[k+d-1]-U[k])) * B(k,d-1, U, u)));

    else
        return(((((u-U[k])/(U[k+d-1]-U[k])) * B(k,d-1, U, u))) + (((U[k+d]-u)/(U[k+d]-U[k+1])) * B(k+1,d-1, U, u)));

}
///Funcao que insere coordenadas numa lista de pontos
void insereElementoFim(tipoLDE *listaAux, float x, float y) {

    tipoElemento *novoElem = malloc(sizeof(tipoElemento));

    novoElem->x1 = x;
    novoElem->y1 = y;

    if (listaAux->tamanhoLista == 0){
        novoElem->prox = NULL;
        listaAux->primeiro = novoElem;
        listaAux->ultimo = novoElem;
    }

    else {
    novoElem ->prox = NULL;
    listaAux->ultimo->prox = novoElem;
    listaAux->ultimo= novoElem;
    }

    listaAux->tamanhoLista++;
}
///Funcao de desenho
void desenha() {
   float newX = 0.0, newY = 0.0, Bk, u; /*newX e newY sao utilizados para calcular a coordenada no intervalo u,
   Bk armazena o retorno da funcao B e u especifica o valor do ponto no intervalo a ser calculado*/
   int n = listaPontos.tamanhoLista-1, tamU = n + d + 1, i, k, U[tamU];
   /*n eh numero de pontos-1, tamU eh o tamanho do vetor Ui, k eh o indice*/
   tipoElemento *c, *p = listaPontos.primeiro; /*ponteiros auxiliares*/
   glPointSize(5.0); //Determina o tamanho do ponto
   glClearColor(0, 0, 0, 0); //Determina o fundo (preto)
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_POINTS); ///Desenha os pontos de controle

        for (i = 0; i < listaPontos.tamanhoLista; i++) {
            glVertex2f(p->x1, p->y1); ///P eh um ponteiro auxiliar para percorrer a lista
            p = p->prox;
        }
        free(p);

    glEnd();

    /*Quando o botao do meio eh clicado, uma flag para desenhar a spline eh levantada
    caso o numero de pontos para desenhar seja suficiente*/
    if(flag == 1) {
        //Se d > 1 a curva eh desenhada. Caso contrario soh eh mostrado os pontos de controle.
        if(d > 1) {

            //Os valores dos U_i sao calculados a seguir seguindo a condicao
            for(i = 0; i < tamU; i++) {
                if(i < d)
                    U[i] = 0;
                else if(d <= i && i <= n)
                    U[i] = i-d+1;
                else
                    U[i] = n-d+2;
            }
            ///A curva tem cor diferente dos pontos de controle para melhor visualizacao
            glColor3f(0.0, 1.0, 0.0);
            glBegin(GL_LINE_STRIP);
                //Dado u dentrode seu intervalo, o polinomio eh calculado
                for(u = 0.0; u < n-d+2; u+=0.1) {

                    c = listaPontos.primeiro; /*c eh um ponteiro auxiliar que percorre a lista de pontos*/
                    for(k = 0; k <= n; k++) { //O polinomio eh calculado respeitando o somatorio
                        Bk = B(k,d,U,u); /*O Bk no intervalo eh calculado e somado a coordenada*/
                        newX += c->x1 * Bk;
                        newY += c->y1 * Bk;
                        c = c->prox;
                    }
                    //O ponto eh plotado
                    glVertex2f(newX, newY);
                    newX = 0.0; //As variaveis de coordenadas sao zeradas
                    newY = 0.0;
                }

            glEnd();
        }

    flag = 0; //A flag eh abaixada para que o usuario possa desenhar uma spline com mais pontos
   }
  glFlush(); //O desenho eh atualizado
}

///Funcao que controla o clique do mouse
void MouseInt (int botao, int estado, int coorX, int coorY) {

    switch(botao) {
        case GLUT_LEFT_BUTTON: /*Caso o botao esquerdo do mouse seja pressionado*/
        if(estado == GLUT_DOWN) {
            if(flag == 0) {
                x = (coorX/300.0) - 1.0; /*O clique do mouse eh rastreado e mapeado para as coordenadas do dispositivo*/
                y = (coorY/300.0) - 1.0;
                y *= (-1.0);
                insereElementoFim(&listaPontos, x, y);
            }
        }
         break;
    case GLUT_MIDDLE_BUTTON: /*Caso o botao do meio seja pressionado*/
            /*A spline eh desenhada se o numero de pontos for suficiente respeitando a regra
                2 <= d <= n+1 (n+1 = listaPontos.tamanhoLista)*/
            if(listaPontos.tamanhoLista < d && estado == GLUT_DOWN)
                printf("Quantidade insuficiente de pontos. Insira mais pontos por favor!\n");
            else
                flag = 1; /*Caso a quantidade seja suficiente a flag eh levantada*/
            break;

 }
  glutPostRedisplay();
}


int main(int argc, char *argv[] ){
     //Coleta o valor de d e verifica se eh valido.
     while(d < 1.0) {
            printf("Por favor, insira o grau do polinomio: ");
            scanf("%d", &d);
            if(d < 1.0)
                printf("Valor nao valido. Insira um valor maior ou igual a 1\n");
        }
        printf("Valor valido. Insira os pontos e aperte o botao do meio para desenhar a spline\n");

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    listaPontos.primeiro = NULL;
    listaPontos.ultimo = NULL;
    listaPontos.tamanhoLista = 0;
    glutInitWindowPosition(50,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("Spline");
    glutDisplayFunc(desenha);
    glutMouseFunc(MouseInt);
    glutMainLoop ();
return 0; }
