//Thauany Moedano
//RA: 92486
//Trabalho feito no Linux Ubuntu 15.10

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.141592654
///VARIAVEIS AUXILIARES
float angulo; //Usado para plotar os pontos na janela
float fatorX, fatorY; //Variavel usada para deslocar a borboleta pela janela
int flagT, flagR, flagTRNeg,flagN, flagBorda, flagMais, flagMenos;
//Flags usadas para direcionar o movimento
float thetaD, thetaE, thetaR,  thetaNeg, D, E, thetaNeg, maxNeg;
//Conjunto de angulos utilizados para direcionr o movimento

///VETOR AUXILIAR
/*O vetor caixaX e caixaY definem um retangulo imaginario ao redor da borboleta
para definir ate que ponto a borboleta pode se deslocar.
O vetor ponto define uma coordenada que eh a referencia para a borboleta transladar*/
float caixaX[4] = {-1.0, 1.0, 1.0, -1.0};
float caixaY[4] = {1.1, 1.1, -0.8, -0.8};
float ponto[2];

///VETORES DE PONTOS DA BORBOLETA
    /*Para cada desenho da borboleta ha um vetor para os pontos em X e Y
    Os vetores estao separados por primitiva. Achei mais facil trabalhar desta forma para localizar
    pontos especificos de maneira mais simples como as pontas das antenas e das asas*/

///ANTENA
float VetorAntenaX1[51];
float VetorAntenaY1[51];

float VetorAntenaX2[51];
float VetorAntenaY2[51];

float VetorAntenaX3[26];
float VetorAntenaY3[26];

///CORPO
float VetorCorpoX[51];
float VetorCorpoY[51];

///CABECA
float VetorCabecaX[51];
float VetorCabecaY[51];

///ASA DIREITA SUPERIOR
float VetorAsaDSX1[51];
float VetorAsaDSY1[51];

float VetorAsaDSX2[51];
float VetorAsaDSY2[51];

float VetorAsaDSX3[51];
float VetorAsaDSY3[51];

///ASA DIREITA INFERIOR
float VetorAsaDIX1[51];
float VetorAsaDIY1[51];

float VetorAsaDIX2[51];
float VetorAsaDIY2[51];

///VETOR ASA ESQUERDA SUPERIOR
float VetorAsaESX1[51];
float VetorAsaESY1[51];

float VetorAsaESX2[51];
float VetorAsaESY2[51];

float VetorAsaESX3[51];
float VetorAsaESY3[51];

///VETOR ASA ESQUERDA INFERIOR
float VetorAsaEIX1[51];
float VetorAsaEIY1[51];

float VetorAsaEIX2[51];
float VetorAsaEIY2[51];



///FUNCOES AUXILIARES

/*A rotacaoRef rotaciona a coordenada de referencia para a borboleta nao perder a orientacao*/
void rotacaoRef(float rRefX, float rRefY, float theta)  {
float x, y;
        x = rRefX + (ponto[0] - rRefX)*cos(theta) - (ponto[1] - rRefY)*sin(theta);
        y = rRefY + (ponto[0] - rRefX)*sin(theta) + (ponto[1] - rRefY)*cos(theta);
        ponto[0] = x;
        ponto[1] = y;

}

/*Funcao modulo ajuda no calculo da permissao de aumentar a borboleta. Implementei
  pois a funcao do C soh retorna valores inteiros e neste caso precisamos trabalhar com
  ponto flutuantes*/
float modulo(float num) {
    if (num >= 0.0)
        return(num);
    else
        return(-num);
}

/*Funcao para calcular a distancia entre dois pontos. Utilizo para calcular a permissao
para diminuir a borboleta*/
float distPontos(float x_a, float x_b, float y_a, float y_b) {
    float A = (x_b - x_a)*(x_b -x_a);
    float B = (y_b - y_a)*(y_b - y_a);
    float C = A + B;
    return(sqrt(C));
}

/*Esta funcao eh utilizada para ativar glutTimerFunc que permite
que animacoes sejam feitas como o movimento das asas e a pirueta*/
void timer () {
    glutPostRedisplay();
    glutTimerFunc(20, timer, 0);
}

///FUNCOES DE TRANSFORMACAO
///TRANSLACAO
void transladaBorboleta(float dx, float dy) {
    int k;

    for(k = 0; k <= 25; k++) {
        VetorAntenaX3[k] += dx;
        VetorAntenaY3[k] += dy;
    }

    for(k = 0; k <= 50; k++) {
        VetorAntenaX1[k] += dx;
        VetorAntenaX2[k] += dx;
        VetorAntenaY1[k] += dy;
        VetorAntenaY2[k] += dy;


        VetorCabecaX[k] += dx;
        VetorCabecaY[k] += dy;

        VetorCorpoX[k] += dx;
        VetorCorpoY[k] += dy;


        VetorAsaDSX1[k] += dx;
        VetorAsaDSX2[k] += dx;
        VetorAsaDSX3[k] += dx;
        VetorAsaDSY1[k] += dy;
        VetorAsaDSY2[k] += dy;
        VetorAsaDSY3[k] += dy;

        VetorAsaDIX1[k] += dx;
        VetorAsaDIY1[k] += dy;

        VetorAsaDIX2[k] += dx;
        VetorAsaDIY2[k] += dy;

        VetorAsaESX1[k] += dx;
        VetorAsaESX2[k] += dx;
        VetorAsaESX3[k] += dx;
        VetorAsaESY1[k] += dy;
        VetorAsaESY2[k] += dy;
        VetorAsaESY3[k] += dy;

        VetorAsaEIX1[k] += dx;
        VetorAsaEIY1[k] += dy;

        VetorAsaEIX2[k] += dx;
        VetorAsaEIY2[k] += dy;


    }

    for(k = 0; k < 4; k++) {
        caixaX[k] += dx;
        caixaY[k] += dy;

    }

}

///ESCALA
void escalaBorbola(float sRefX, float sRefY, float sy, float sx) {

    int k;

     for(k = 0; k <= 25; k++) {
        VetorAntenaX3[k] *= sx + sRefX*(1-sx);
        VetorAntenaY3[k] *= sy + sRefY*(1-sy);
    }

    for(k = 0; k <= 50; k++) {

        VetorAntenaX1[k] *= sx + sRefX*(1-sx);
        VetorAntenaX2[k] *= sx + sRefX*(1-sx);

        VetorAntenaY1[k] *= sy + sRefY*(1-sy);
        VetorAntenaY2[k] *= sy + sRefY*(1-sy);

        VetorCabecaX[k] *= sx + sRefX*(1-sx);
        VetorCabecaY[k] *= sy + sRefY*(1-sy);

        VetorCorpoX[k] *= sx + sRefX*(1-sx);
        VetorCorpoY[k] *= sy + sRefY*(1-sy);

        VetorAsaDSX1[k] *= sx + sRefX*(1-sx);
        VetorAsaDSX2[k] *= sx + sRefX*(1-sx);
        VetorAsaDSX3[k] *= sx + sRefX*(1-sx);
        VetorAsaDSY1[k] *= sy + sRefY*(1-sy);
        VetorAsaDSY2[k] *= sy + sRefY*(1-sy);
        VetorAsaDSY3[k] *= sy + sRefY*(1-sy);

        VetorAsaDIX1[k] *= sx + sRefX*(1-sx);
        VetorAsaDIY1[k] *= sy + sRefY*(1-sy);

        VetorAsaDIX2[k] *= sx + sRefX*(1-sx);
        VetorAsaDIY2[k] *= sy + sRefY*(1-sy);

        VetorAsaESX1[k] *= sx + sRefX*(1-sx);
        VetorAsaESX2[k] *= sx + sRefX*(1-sx);
        VetorAsaESX3[k] *= sx + sRefX*(1-sx);
        VetorAsaESY1[k] *= sy + sRefY*(1-sy);
        VetorAsaESY2[k] *= sy + sRefY*(1-sy);
        VetorAsaESY3[k] *= sy + sRefY*(1-sy);

        VetorAsaEIX1[k] *= sx + sRefX*(1-sx);
        VetorAsaEIY1[k] *= sy + sRefY*(1-sy);

        VetorAsaEIX2[k] *= sx + sRefX*(1-sx);
        VetorAsaEIY2[k] *= sy + sRefY*(1-sy);
    }

     for(k = 0; k < 4; k++) {
        caixaX[k] *= sx + sRefX*(1-sx);
        caixaY[k] *= sy + sRefY*(1-sy);
    }
}

///ROTACAO
void rotacionaBorboleta(float rRefX, float rRefY, float theta) {
    int k;

    float x, y;
    for(k = 0; k <= 25; k++) {
        x = rRefX + (VetorAntenaX3[k] - rRefX)*cos(theta) - (VetorAntenaY3[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAntenaX3[k] - rRefX)*sin(theta) + (VetorAntenaY3[k] - rRefY)*cos(theta);
        VetorAntenaX3[k] = x;
        VetorAntenaY3[k] = y;
    }

    for(k = 0; k <= 50; k++) {
         x = rRefX + (VetorAntenaX1[k] - rRefX)*cos(theta) - (VetorAntenaY1[k] - rRefY)*sin(theta);
         y = rRefY + (VetorAntenaX1[k] - rRefX)*sin(theta) + (VetorAntenaY1[k] - rRefY)*cos(theta);
        VetorAntenaX1[k] = x;
        VetorAntenaY1[k] = y;

         x = rRefX + (VetorAntenaX2[k] - rRefX)*cos(theta) - (VetorAntenaY2[k] - rRefY)*sin(theta);
         y = rRefY + (VetorAntenaX2[k] - rRefX)*sin(theta) + (VetorAntenaY2[k] - rRefY)*cos(theta);
         VetorAntenaX2[k] = x;
         VetorAntenaY2[k] = y;

         x = rRefX + (VetorCabecaX[k] - rRefX)*cos(theta) - (VetorCabecaY[k] - rRefY)*sin(theta);
         y = rRefY + (VetorCabecaX[k] - rRefX)*sin(theta) + (VetorCabecaY[k] - rRefY)*cos(theta);
         VetorCabecaX[k] = x;
         VetorCabecaY[k] = y;

         x = rRefX + (VetorCorpoX[k] - rRefX)*cos(theta) - (VetorCorpoY[k] - rRefY)*sin(theta);
         y = rRefY + (VetorCorpoX[k] - rRefX)*sin(theta) + (VetorCorpoY[k] - rRefY)*cos(theta);
         VetorCorpoX[k] = x;
         VetorCorpoY[k] = y;

         x = rRefX + (VetorAsaDSX1[k] - rRefX)*cos(theta) - (VetorAsaDSY1[k] - rRefY)*sin(theta);
         y = rRefY + (VetorAsaDSX1[k] - rRefX)*sin(theta) + (VetorAsaDSY1[k] - rRefY)*cos(theta);
        VetorAsaDSX1[k] = x;
        VetorAsaDSY1[k] = y;

        x = rRefX + (VetorAsaDSX2[k] - rRefX)*cos(theta) - (VetorAsaDSY2[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaDSX2[k] - rRefX)*sin(theta) + (VetorAsaDSY2[k] - rRefY)*cos(theta);
        VetorAsaDSX2[k] = x;
        VetorAsaDSY2[k] = y;

        x = rRefX + (VetorAsaDSX3[k] - rRefX)*cos(theta) - (VetorAsaDSY3[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaDSX3[k] - rRefX)*sin(theta) + (VetorAsaDSY3[k] - rRefY)*cos(theta);
        VetorAsaDSX3[k] = x;
        VetorAsaDSY3[k] = y;

        x = rRefX + (VetorAsaDIX1[k] - rRefX)*cos(theta) - (VetorAsaDIY1[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaDIX1[k] - rRefX)*sin(theta) + (VetorAsaDIY1[k] - rRefY)*cos(theta);
        VetorAsaDIX1[k] = x;
        VetorAsaDIY1[k] = y;

         x = rRefX + (VetorAsaDIX2[k] - rRefX)*cos(theta) - (VetorAsaDIY2[k] - rRefY)*sin(theta);
         y = rRefY + (VetorAsaDIX2[k] - rRefX)*sin(theta) + (VetorAsaDIY2[k] - rRefY)*cos(theta);
         VetorAsaDIX2[k] = x;
          VetorAsaDIY2[k] = y;

        x = rRefX + (VetorAsaESX1[k] - rRefX)*cos(theta) - (VetorAsaESY1[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaESX1[k] - rRefX)*sin(theta) + (VetorAsaESY1[k] - rRefY)*cos(theta);
        VetorAsaESX1[k] = x;
        VetorAsaESY1[k] = y;

        x = rRefX + (VetorAsaESX2[k] - rRefX)*cos(theta) - (VetorAsaESY2[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaESX2[k] - rRefX)*sin(theta) + (VetorAsaESY2[k] - rRefY)*cos(theta);
        VetorAsaESX2[k] = x;
        VetorAsaESY2[k] = y;

        x = rRefX + (VetorAsaESX3[k] - rRefX)*cos(theta) - (VetorAsaESY3[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaESX3[k] - rRefX)*sin(theta) + (VetorAsaESY3[k] - rRefY)*cos(theta);
        VetorAsaESX3[k] = x;
        VetorAsaESY3[k] = y;

        x = rRefX + (VetorAsaEIX1[k] - rRefX)*cos(theta) - (VetorAsaEIY1[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaEIX1[k] - rRefX)*sin(theta) + (VetorAsaEIY1[k] - rRefY)*cos(theta);
        VetorAsaEIX1[k] = x;
        VetorAsaEIY1[k] = y;

        x = rRefX + (VetorAsaEIX2[k] - rRefX)*cos(theta) - (VetorAsaEIY2[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaEIX2[k] - rRefX)*sin(theta) + (VetorAsaEIY2[k] - rRefY)*cos(theta);
        VetorAsaEIX2[k] = x;
        VetorAsaEIY2[k] = y;
    }

      for(k = 0; k < 4; k++) {
        x = rRefX + (caixaX[k] - rRefX)*cos(theta) - (caixaY[k] - rRefY)*sin(theta);
        y = rRefY + (caixaX[k] - rRefX)*sin(theta) + (caixaY[k] - rRefY)*cos(theta);

        caixaX[k] = x;
        caixaY[k] = y;
    }
}

///ROTACAO APLICADA AS ASAS
/*Para simular o movimento das asas, apliquei uma pequena rotacao
  em cada uma das asas separadamente. Assim eh possivel notar que
  a borboleta move as asas para frente e para tras rotacionando a asa
  em torno de um ponto da propria asa para +theta e -theta*/

void rotacionaAsaE(float theta, float rRefX, float rRefY) {
    float x,y;
    int k;

    for(k = 0; k <= 50; k++) {
        x = rRefX + (VetorAsaESX1[k] - rRefX)*cos(theta) - (VetorAsaESY1[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaESX1[k] - rRefX)*sin(theta) + (VetorAsaESY1[k] - rRefY)*cos(theta);
        VetorAsaESX1[k] = x;
        VetorAsaESY1[k] = y;

        x = rRefX + (VetorAsaESX2[k] - rRefX)*cos(theta) - (VetorAsaESY2[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaESX2[k] - rRefX)*sin(theta) + (VetorAsaESY2[k] - rRefY)*cos(theta);
        VetorAsaESX2[k] = x;
        VetorAsaESY2[k] = y;

        x = rRefX + (VetorAsaESX3[k] - rRefX)*cos(theta) - (VetorAsaESY3[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaESX3[k] - rRefX)*sin(theta) + (VetorAsaESY3[k] - rRefY)*cos(theta);
        VetorAsaESX3[k] = x;
        VetorAsaESY3[k] = y;

        x = rRefX + (VetorAsaEIX1[k] - rRefX)*cos(theta) - (VetorAsaEIY1[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaEIX1[k] - rRefX)*sin(theta) + (VetorAsaEIY1[k] - rRefY)*cos(theta);
        VetorAsaEIX1[k] = x;
        VetorAsaEIY1[k] = y;

        x = rRefX + (VetorAsaEIX2[k] - rRefX)*cos(theta) - (VetorAsaEIY2[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaEIX2[k] - rRefX)*sin(theta) + (VetorAsaEIY2[k] - rRefY)*cos(theta);
        VetorAsaEIX2[k] = x;
        VetorAsaEIY2[k] = y;
    }
}

void rotacionaAsaD(float theta, float rRefX, float rRefY) {
float x,y;
int k;
    for(k = 0; k <= 50; k++) {
         x = rRefX + (VetorAsaDSX1[k] - rRefX)*cos(theta) - (VetorAsaDSY1[k] - rRefY)*sin(theta);
         y = rRefY + (VetorAsaDSX1[k] - rRefX)*sin(theta) + (VetorAsaDSY1[k] - rRefY)*cos(theta);
        VetorAsaDSX1[k] = x;
        VetorAsaDSY1[k] = y;

        x = rRefX + (VetorAsaDSX2[k] - rRefX)*cos(theta) - (VetorAsaDSY2[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaDSX2[k] - rRefX)*sin(theta) + (VetorAsaDSY2[k] - rRefY)*cos(theta);
        VetorAsaDSX2[k] = x;
        VetorAsaDSY2[k] = y;

        x = rRefX + (VetorAsaDSX3[k] - rRefX)*cos(theta) - (VetorAsaDSY3[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaDSX3[k] - rRefX)*sin(theta) + (VetorAsaDSY3[k] - rRefY)*cos(theta);
        VetorAsaDSX3[k] = x;
        VetorAsaDSY3[k] = y;

        x = rRefX + (VetorAsaDIX1[k] - rRefX)*cos(theta) - (VetorAsaDIY1[k] - rRefY)*sin(theta);
        y = rRefY + (VetorAsaDIX1[k] - rRefX)*sin(theta) + (VetorAsaDIY1[k] - rRefY)*cos(theta);
        VetorAsaDIX1[k] = x;
        VetorAsaDIY1[k] = y;

         x = rRefX + (VetorAsaDIX2[k] - rRefX)*cos(theta) - (VetorAsaDIY2[k] - rRefY)*sin(theta);
         y = rRefY + (VetorAsaDIX2[k] - rRefX)*sin(theta) + (VetorAsaDIY2[k] - rRefY)*cos(theta);
         VetorAsaDIX2[k] = x;
         VetorAsaDIY2[k] = y;
        }
}


///FUNCAO DE DESENHO
void brabuleta() {
   glClearColor(0, 1, 1, 0);
   glClear(GL_COLOR_BUFFER_BIT);
   int i;

   /*Todas as formas com excessao do "cabo" da antena sao feitas com GL_POLYGON para plotar circulos
      e elipses que compoe a borboleta. O cabo da antena eh feito com GL_LINE_STRIP. Assim a antena
      apresenta uma leve curva*/
    ///ANTENA
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorAntenaX1[i],VetorAntenaY1[i]);
    glEnd();

    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorAntenaX2[i], VetorAntenaY2[i]);
    glEnd();

    glBegin(GL_LINE_STRIP);
        for(i = 0; i <= 25; i++)
            glVertex2f(VetorAntenaX3[i],VetorAntenaY3[i]);
    glEnd();

    ///CORPO
    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorCorpoX[i], VetorCorpoY[i]);
    glEnd();

    ///CABECA
    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorCabecaX[i], VetorCabecaY[i]);
    glEnd();


    ///ASA DIREITA SUPERIOR
    glColor3f(1.0, 0.3, 0.2);
    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorAsaDSX1[i], VetorAsaDSY1[i]);
    glEnd();

    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorAsaDSX2[i], VetorAsaDSY2[i]);
    glEnd();

    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorAsaDSX3[i], VetorAsaDSY3[i]);
    glEnd();

    ///ASA DIREITA INFERIOR
   // glColor3f(1.0, 0.3, 0.5);
    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorAsaDIX1[i], VetorAsaDIY1[i]);
    glEnd();

    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorAsaDIX2[i], VetorAsaDIY2[i]);
    glEnd();


    ///ASA ESQUERDA SUPERIOR
    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorAsaESX1[i], VetorAsaESY1[i]);
    glEnd();

    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorAsaESX2[i], VetorAsaESY2[i]);
    glEnd();

    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorAsaESX3[i], VetorAsaESY3[i]);
    glEnd();

    ///ASA ESQUERDA INFERIOR
    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorAsaEIX1[i], VetorAsaEIY1[i]);
    glEnd();

    glBegin(GL_POLYGON);
        for(i = 0; i <= 50; i++)
            glVertex2f(VetorAsaEIX2[i], VetorAsaEIY2[i]);
    glEnd();
    /*Quando a flagT (flag de translacao) eh ativada temos que garantir que nenhum outro
    tipo de movimento esteja sendo feito para a borboleta nao perder as referencias da translacao*/
    if(flagT == 1 && flagR == 0 && flagMais == 0 && flagMenos == 0) {
        transladaBorboleta(ponto[0], ponto[1]);

    /*Esta serie de rotacoes simula o movimento das asas*/
        rotacionaAsaD(thetaD, VetorAsaDSX1[35], VetorAsaDSY1[35]);
        rotacionaAsaE(thetaE, VetorAsaESX1[35], VetorAsaESY1[35]);
        thetaD += D;
        thetaE += E;
        if(modulo(thetaD) >= 0.08) {
            thetaD = 0.0;
            thetaE = 0.0;
            thetaD = -thetaD;
            thetaE = -thetaE;
            D = -D;
            E = -E;
        }
        flagT = 0; //A flag sempre eh desligada para impedir que a borboleta nunca pare de andar
        /*Para garantir a aleatoriadade do movimento, uma flag de rotacao eh levantada com uma
        determinada probabilidade*/
        if(rand()%10  > 8) {
            flagTRNeg = 1;
            maxNeg = 0.09; //Define quanto a borboleta gira
        }
    }

    /*Precisamos garantir que a borboleta nao saia da janela. Logo, devemos sempre
      verificar se os limites da borboleta nao estao ultrapassando a janela.
      Caso sim, levantamos uma flag para coloca-la de volta no lugar*/
    if(caixaX[0] <= -1.0 || caixaX[1] <= -1.0)
        flagBorda = -1;

    else if(caixaX[0]  >= 1.0 || caixaX[1]  >= 1.0)
        flagBorda = 1;

    else if(caixaY[0]  <= -1.0 || caixaY[1]  <= -1.0)
        flagBorda = -2;

    if(caixaY[0]  >= 1.0 || caixaY[1]  >= 1.0)
        flagBorda = 2;
    /*Cada sinal indica que tipo de movimento devemos fazer
     para a borboleta voltar para a tela*/

    /*Esta flag eh ativada quando o botao direito do mouse eh pressionado.
      Ela ativa o movimento da pirueta*/
    if(flagR == 1) {
        flagTRNeg = 0;
        flagT = 0; //Desativa a translacao
        //A borboleta rotaciona ate que gire 360 graus
        rotacionaBorboleta(VetorCabecaX[25], VetorCabecaY[25], thetaR);
        thetaR += 0.01;

        if(thetaR >= 0.35) {
            flagR = 0;
            thetaR = 0.0;
        }
    }

    /*Se esta flag eh acionada, a borboleta rotaciona alguns graus*/
    if(flagTRNeg == 1) {
        rotacaoRef(0,0, thetaNeg);
        rotacionaBorboleta(VetorCabecaX[25], VetorCabecaY[25], thetaNeg);
        thetaNeg -= 0.01;

        if(modulo(thetaNeg) >= maxNeg) {
            flagTRNeg = 0;
            thetaNeg = 0.0;
        }

    }

    /*Quando a borboleta esta atingindo o limite da tela devemos
        transladar de volta para dentro. Assim podemos aplicar uma
        rotacao para que a borboleta nao fique com a direcao para
        a borda*/
    if(flagBorda == -1) {
        transladaBorboleta(0.01, 0);
        if(caixaX[0] >-1.0 && caixaX[1] > -1.0) {
            flagBorda = 0;
            flagTRNeg = 1;
            maxNeg = 0.172;
        }
    }
    else if(flagBorda == 1) {
        transladaBorboleta(-0.01, 0);
         if(caixaX[0] < 1.0 && caixaX[1] < 1.0) {
            flagBorda = 0;
            flagTRNeg = 1;
            maxNeg = 0.172;
        }
    }
    else if(flagBorda == -2) {
        transladaBorboleta(0.0, 0.01);
         if(caixaY[0] > -1.0 && caixaY[1] > -1.0) {
            flagBorda = 0;
            flagTRNeg = 1;
            maxNeg = 0.172;
        }
    }
    else if(flagBorda == 2) {
        transladaBorboleta(0.0, -0.01);
        if(caixaY[0] < 1.0 && caixaY[1] < 1.0) {
            flagBorda = 0;
            flagTRNeg = 1;
            maxNeg = 0.172;
        }
    }

    /*Esta flag quando acionada, diminui o tamanho da borboleta. Ela eh diminuida ate um limite
    para nao virar um ponto. Este limite eh calculado em relacao a distancia entre os pontos da asa
    esquerda e direita*/
    if(flagMenos == 1) {
        flagT = 0;
        flagR = 0;
         if(distPontos(VetorAsaDSX1[25], VetorAsaESX1[25], VetorAsaDSY1[25], VetorAsaESY1[25]) < 0.2) {
               flagMenos = 0;
            }
        else
         escalaBorbola(VetorCabecaX[50], VetorCabecaY[50], 0.96, 0.96);
    }

/*Esta flag quando acionada, aumenta o tamanho da borboleta. A borboleta eh aumentada ate que os limites
    estejam perto de estourar a janela. Portanto se estivermos longe da borda conseguimos aumentar a borboleta
    mais de uma vez. Caso contrario o movimento nao sera permitido*/
    if(flagMais == 1) {
        flagT = 0;
        flagR = 0;
         if(modulo(caixaX[0])*1.11 >= 1.0 || modulo(caixaX[1])*1.11 >= 1.0 ||
                modulo(caixaX[2])*1.11 >= 1.0 || modulo(caixaX[3])*1.11 >= 1.0 ||
                modulo(caixaY[0])*1.11 >= 1.0 || modulo(caixaY[1])*1.11 >= 1.0 ||
                modulo(caixaY[2])*1.11 >= 1.0 || modulo(caixaY[3])*1.11 >= 1.0)
                    flagMais = 0;
       else
         escalaBorbola(VetorCabecaX[50], VetorCabecaY[50], 1.1, 1.1);
    }

    glutSwapBuffers();
}

///FUNCOES QUE CONTROLAM A ENTRADA

///TECLADO
void Keyboard (unsigned char key, int x, int y) {
  float i;
    switch(key) {
        case 't':
        case 'T':
        //Aciona a flag de translacao
            flagT = 1;
             break;
        case '-':
            /*Aciona a flag de escala para menos*/
            flagMenos = 1;

            break;
        case '+':
             /*Aciona a flag de escala para mais*/
            flagMais = 1;
             break;
    }
    glutPostRedisplay();
}

///FUNCAO QUE CONTROLA O MOUSE
void MouseInt (int botao, int estado, int coorX, int coorY) {

    switch(botao) {
        case GLUT_RIGHT_BUTTON:
           if(estado == GLUT_DOWN && flagT == 0 &&flagMais == 0 && flagMenos == 0) {
           //Aciona a flag de rotacao
                flagR = 1;
            }
        break;
    }
}


int main(int argc, char *argv[]) {
int i;
///INICIALIZANDO VARIAVEIS PARA O DESENHO
/*Aqui insiro todos os pontos que fazem parte do desenho.
Como a borboleta se trata basicamente de um desenho com curvas,
utilizei as ideias vista em alta para desenhar curvas com ajuda
do GL_POLYGON. */
///ANTENAS
 for(i = 0; i <= 50; i++) {
    angulo = 2*PI*i/50.0;
    VetorAntenaX1[i] = 0.05*cos(angulo)+0.12;
    VetorAntenaY1[i] = 0.05*sin(angulo)+0.9;
}

for(i = 0; i <= 50; i++) {
   angulo = 2*PI*i/50.0;
   VetorAntenaX2[i] = 0.05*cos(angulo)-0.12;
   VetorAntenaY2[i] = 0.05*sin(angulo)+0.9;
}
for(i = 0; i <= 25; i++) {
    angulo = -2*PI*i/50.0;

    VetorAntenaX3[i] = 0.125*cos(angulo);
    VetorAntenaY3[i] = 0.5*sin(angulo)+0.9;
}

///VARIAVEIS PARA O CORPO
for(i = 0; i <= 50; i++) {
    angulo = 2*PI*i/50.0;
    VetorCorpoX[i] = 0.2*cos(angulo);
    VetorCorpoY[i] = 0.5*sin(angulo);
}

///VARIAVEIS PARA A CABECA

 for(i = 0; i <= 50; i++) {
    angulo = 2*PI*i/50.0;
    VetorCabecaX[i] = 0.19*cos(angulo);
    VetorCabecaY[i] = 0.19*sin(angulo)+0.5;
}

///ASA SUPERIOR DIREITA

for(i = 0; i <= 50; i++) {
    angulo = 2*PI*i/50.0;
    VetorAsaDSX1[i] = 0.4*cos(angulo-0.6)+0.55;
    VetorAsaDSY1[i] = 0.1*sin(angulo)+0.35;
}

for(i = 0; i <= 50; i++) {
    angulo = 2*PI*i/50.0;
    VetorAsaDSX2[i] = 0.1*cos(angulo)+0.82;
    VetorAsaDSY2[i] = 0.1*sin(angulo)+0.35;
}

for(i = 0; i <= 50; i++) {
    angulo = -PI*i/50.0;
    VetorAsaDSX3[i] = 0.26*cos(angulo)+0.44;
    VetorAsaDSY3[i] = 0.4*sin(angulo)+0.3;
}

///ASA INFERIOR DIREITA
 for(i = 0; i <= 50; i++) {
    angulo = 2*PI*i/50.0;
    VetorAsaDIX1[i] = 0.15*cos(angulo+0.9)+0.28;
    VetorAsaDIY1[i] = 0.4*sin(angulo)-0.09;
}

for(i = 0; i <= 50; i++) {
   angulo = 2*PI*i/50.0;
   VetorAsaDIX2[i] = 0.13*cos(angulo)+0.4;
   VetorAsaDIY2[i] = 0.13*sin(angulo)-0.2;
}

///ASA SUPERIOR ESQUERDA
 for(i = 0; i <= 50; i++) {
    angulo = 2*PI*i/50.0;
    VetorAsaESX1[i] = 0.4*cos(angulo+0.6)-0.55;
    VetorAsaESY1[i] = 0.1*sin(angulo)+0.35;
}

for(i = 0; i <= 50; i++) {
    angulo = 2*PI*i/50.0;
    VetorAsaESX2[i] = 0.1*cos(angulo)-0.82;
    VetorAsaESY2[i] = 0.1*sin(angulo)+0.35;
}

for(i = 0; i <= 50; i++) {
    angulo = -PI*i/50.0;
    VetorAsaESX3[i] = 0.26*cos(angulo)-0.44;
    VetorAsaESY3[i] = 0.4*sin(angulo)+0.3;
}

///ASA ESQUERDA INFERIOR

for(i = 0; i <= 50; i++) {
    angulo = 2*PI*i/50.0;
    VetorAsaEIX1[i] = 0.15*cos(angulo-0.9)-0.28;
    VetorAsaEIY1[i] = 0.4*sin(angulo)-0.09;
}

 for(i = 0; i <= 50; i++) {
    angulo = 2*PI*i/50.0;
    VetorAsaEIX2[i] = 0.13*cos(angulo)-0.4;
    VetorAsaEIY2[i] = 0.13*sin(angulo)-0.2;
}

/*Esta escala inicial eh apenas para acomodar a borboleta. Ela em seu tamanho original
estava muito grande, logo apliquei uma escala para ficar em um tamanho
medio.*/
escalaBorbola(VetorCorpoX[0], VetorCorpoX[0], 0.1, 0.1);

/*Inicializacao de variaveis auxiliares e flags*/
ponto[0] = 0.0;
ponto[1] = 0.02;


flagT = 0;
flagTRNeg = 0;
thetaD = -0.01;
thetaE = 0.01;
thetaR = 0.00;
flagBorda = 0;
D = 0.01;
E = -0.01;

glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
glutInitWindowPosition(50,100);
glutInitWindowSize(500,500);
glutCreateWindow("Brabuleta");
glutKeyboardFunc(Keyboard);
glutMouseFunc(MouseInt);
glutDisplayFunc(brabuleta);
glutTimerFunc(20, timer, 0);
glutMainLoop ();
return 0;
}
