//Thauany Moedano
//RA 9286
//Trabalho feito no linux Ubuntu 15.10
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

//Declaracao de parametros
/*Os thetaX, thetaY e thetaZ sao responsaveis por rotacionar a figura*/
float thetaX = 0.0, thetaY = 0.0, thetaZ = 0.0;

/*Essas variaveis definem parametros e flags para ativar o sweep*/
float flagT, flagR, z;
/*escolheForma ativa a flag de qual figura deve ser mostrada. tam define tamanho de vetores
Os vetores sao utilizados para armazenar os pontos quando ocorre o sweep*/
int escolheForma, tam;
float vetorPontosAX[50],vetorPontosAZ[50];
float vetorPontosBX[50], vetorPontosBZ[50];


//Funcao para modificar a janela caso tenha sido minimizada ou deslocada
void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
}

void Desenha() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    /*Se escolheForma e zero, o sweep a ser realizado eh o rotacional em cima de uma reta girando ao redor
    de um circulo imaginario (eixo z)*/
    if(escolheForma == 0) {
        glColor3f(0.0, 0.0, 1.0); // Definindo a cor da reta
        glBegin(GL_LINE_STRIP);
            glVertex3f(1.0, 2.0, 0.0);
            glVertex3f(1.7, -1.0, 0.0); //Desenhando a reta (primitiva 2D)
        glEnd();

        //Quando a flag e ativada, a animacao para formar um sweep eh disparada
        if(flagR == 1) {

        //Se o vetor nao estiver completamente preenchido, a reta eh deslocada no eixo z com uma rotacao tridimensional
        if(tam < 50) {
            vetorPontosAX[tam] = vetorPontosAX[tam-1]*cos(0.17) - vetorPontosAZ[tam-1]*sin(0.17);
            vetorPontosAZ[tam] = vetorPontosAX[tam-1]*sin(0.17) + vetorPontosAZ[tam-1]*cos(0.17);

            vetorPontosBX[tam] = vetorPontosBX[tam-1]*cos(0.17) - vetorPontosBZ[tam-1]*sin(0.17);
            vetorPontosBZ[tam] = vetorPontosBX[tam-1]*sin(0.17) + vetorPontosBZ[tam-1]*cos(0.17);
            tam++;
        }

        int i;
        /*Redesenhamos a reta ao redor do eixo Z e ligamos os pontos para ter melhor
        visualizacao do desenho*/
        glBegin(GL_LINE_STRIP);
            for(i = 0; i < tam; i++)
                glVertex3f(vetorPontosAX[i], 2.0, vetorPontosAZ[i]);
        glEnd();

        glBegin(GL_LINE_STRIP);
            for(i = 0; i < tam; i++)
                glVertex3f(vetorPontosBX[i], -1.0, vetorPontosBZ[i]);
        glEnd();

        glBegin(GL_LINES);
            for(i = 0; i < tam; i++) {
                glVertex3f(vetorPontosBX[i], -1.0, vetorPontosBZ[i]);
                glVertex3f(vetorPontosAX[i], 2.0, vetorPontosAZ[i]);
            }
        glEnd();
        }
    }

//Se escolheForma eh 1, o sweep eh translacional
    else if(escolheForma == 1) {
        glColor3f(1.0,0.0,0.0);
        glBegin(GL_LINE_LOOP);
            glVertex3f(0.0,3.0,0.0);
            glVertex3f(-4.0,-3.0,0.0);
            glVertex3f(4.0,-3.0,0.0);
        glEnd();
        //Quando a flag eh disparada, o sweep translacional eh ativado
        if(flagT == 1) {
            z += 0.03;  //Os pontos se movem ao longo do eixo Z
            if(z >= 3.5)
                z = 3.5;
            //Apenas o z eh alterado, gerando o sweep translacional
            glBegin(GL_LINE_LOOP);
                glVertex3f(0.0,3.0,z);
                glVertex3f(-4.0,-3.0,z);
                glVertex3f(4.0,-3.0,z);
            glEnd();

            glBegin(GL_LINE_STRIP);
                glVertex3f(0.0,3.0,0.0);
                glVertex3f(0.0, 3.0,z);
            glEnd();

            glBegin(GL_LINE_STRIP);
                glVertex3f(-4.0,-3.0,0.0);
                glVertex3f(-4.0,-3.0,z);
            glEnd();

            glBegin(GL_LINE_STRIP);
                glVertex3f(4.0,-3.0,0.0);
                glVertex3f(4.0,-3.0,z);
            glEnd();
        }

    }
}
/*A funcao de display habilita o teste de profundidade
e define a projecao para que, ao rotacionarmos os objetos
possamos os ver em um plano 3D*/
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10,-10, 10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
         glRotatef(thetaX, 1.0, 0.0, 0.0);
         glRotatef(thetaY, 0.0, 1.0, 0.0);
         glRotatef(thetaZ, 0.0, 0.0, 1.0);
         Desenha();
    glPopMatrix();

   glutSwapBuffers();
}

//A funcao timer eh utilizada para controlar a animacao
void timer () {
    glutPostRedisplay();
    glutTimerFunc(150, timer, 0);
}

void keyboard (unsigned char key, int x, int y) {
	switch (key)
	{
		case 'q':
        case 'Q':
		      thetaX += 5;
		   break;
		case 'w':
        case 'W':
		      thetaX -= 5;
		   break;
		case 'a':
        case 'A':
		      thetaY += 5;
		   break;
		case 's':
        case 'S':
		      thetaY -= 5;
		   break;

		case 'z':
        case 'Z':
		      thetaZ += 5;
		   break;
		case 'x':
        case 'X':
		      thetaZ -= 5;
            break;
        case 't':
        case 'T':
            flagT = 1;

            break;
        case 'r':
        case 'R':
            flagR = 1;
        break;

        case '1':
            escolheForma = 1;
        break;

        case '0':
            escolheForma = 0;
        break;

	}
	glutPostRedisplay();
}



int  main (int argc, char** argv) {
    printf("MENU:\nPara ver a figura com Sweep Rotacional: Aperte 0 (default)\n");
    printf("Ao selecionar Sweep Rotacional, aperte r/R para iniciar a animacao\n\n");
    printf("Para ver a figura com Sweep Translacional: Aperte 1\n");
    printf("Ao selecionar Sweep Translacional, aperte t/T para iniciar a animacao\n\n");

    printf("Em qualquer modo e possivel rotacionar as figuras com os comandos:\n");
    printf("Eixo x: q/Q (positivo) ou w/W (negativo)\n");
    printf("Eixo y: a/A (positivo) ou s/S (negativo)\n");
    printf("Eixo z: z/Z (positivo) ou x/X (negativo)\n");


    //Iniciado variaveis
    flagT = 0;
    flagR = 0;
    z = 0.0;
    tam = 1;
    vetorPontosAX[0] = 1.0;
    vetorPontosAZ[0] = 0.0;
    vetorPontosBX[0] = 1.7;
    vetorPontosBZ[0] = 0.0;

    //Chamando funcoes do openGL
    glutInit  (&argc, argv);
    glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition (50,50);
    glutInitWindowSize(650, 500);
    glutCreateWindow("Sweep");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard) ;
    glutTimerFunc(300, timer, 0);
    glutMainLoop();

    return (0);
}
