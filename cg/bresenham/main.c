//Thauany Moedano
//RA 92486
//Trabalho feito em Linux Ubuntu 15.10

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

//Inicializando variaveis globais
int a = 1, b, c, delta = -1;

//Funcao de reshape
void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
}

void Bresenham() {
    //Iniciando variaveis
    /*x e y comecam valendo o vertice, os demais valores sao atribuidos os resultados
      da deducao do algoritmo da parabola levando em consideracao o minimo de multiplicacoes
      possiveis na inicializacao dos valores*/
    int x = -b/(2*a), y = -delta/(4*a), a2 = a*a, quatroA = 4*a, oitoA2 = 8*a*a, Xv = 2*x,
        N = -quatroA, NE = oitoA2*x + oitoA2 + quatroA*b - quatroA,
        S = quatroA, SE = oitoA2*x + oitoA2 + quatroA*b + quatroA, d, i;

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20, 20, -20, 20,-20, 20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


     glLineWidth(3);
     glColor3f(0,1,0);

      glBegin(GL_LINES);
         glVertex2f(-20,0);
         glVertex2f(20,0);
         glVertex2f(0,-20);
         glVertex2f(0, 20);
     glEnd();

     ///Calculo Bresenham
     glPointSize(5.0);
     glColor3f(1, 0, 0);
     glBegin(GL_POINTS);
        glVertex2d(x, y);  //Dividi o Bresenham em duas partes, uma quando a parabola eh concava para cima e outra para baixo
        if(a < 0) { ///Parabola concava para baixo
            d = a2 + quatroA; //Inicializando de Dinic
            for(i = 0; i < 100; i++) {
                if(d <= 0) {//Escolhe SE
                    d += SE;
                    SE += oitoA2;
                    x += 1;
                }
                else {
                    d += S;
                }
                y -= 1;
                glVertex2d(x, y);
                glVertex2d(-x+Xv, y);

            }
        }
        else {
            d = a2 - quatroA; ///Parabola concava pra cima
            for(i = 0; i < 100; i++) {
                if(d <= 0) {//Escolhe SE
                    d += NE;
                    NE += oitoA2;
                    x += 1;
                }
                else {
                    d += N;
                }

                y += 1;
                glVertex2d(x, y);
                glVertex2d(-x+Xv, y);

            }

        }
    glEnd();



 glutSwapBuffers();

}

int  main ( int argc, char** argv ) {

    while(delta <= 0 || a == 0) {
        printf("Entre com os valores de a, b, c, respectivamente: \n");
        scanf("%d %d %d", &a, &b, &c);
        delta = b*b - 4*a*c;
        if(delta < 0 || a == 0)
            printf("Valores invalidos\n");
    }


    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(650, 500);
    glutCreateWindow("Bresenham");
    glutDisplayFunc(Bresenham);
    glutMainLoop();

    return 0;
}
