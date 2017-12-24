///Thauany Moedano
///RA 92486
///Trabalho feito em Linux Ubuntu 15.10

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#define MAX_NO_TEXTURES 25 //Definindo o numero maximo de texturas

///Structs///

/*Gera uma imagem BMP*/
typedef struct BMPImagem {
    int   width;
    int   height;
    char *data;
}BMPImage;

/*Elemento que armazena um par de ponto e sua relacao com a posicao do humanoide*/
struct elemento {

float x;
float z;
int flagNeedMoveBack;
int flagNeedMoveLeft;
int flagNeedMoveOn;
int flagNeedMoveRight;
struct elemento *prox;
int isCesta;

}; typedef struct elemento tipoElemento;

/*Lista de pontos*/
struct listaDE {

    tipoElemento *primeiro;
    tipoElemento *ultimo;
    int tamanhoLista;
    }; typedef struct listaDE tipoLDE;


tipoLDE listaPontos;
tipoElemento *p;
tipoElemento *r;

GLuint texture_id[MAX_NO_TEXTURES];


GLfloat LuzAmbiente2[4] = {0.4, 0.4, 0.4, 1.0};
GLfloat LuzAmbiente[4] = {0.0, 0.0, 0.0, 1.0};

GLfloat LuzDifusa[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat LuzEspecular[4] = {0.3, 0.3, 0.3, 1.0};

GLfloat PosicaoLuz0[4] = {2.0, 4.0, -5.0, 1.0};
GLfloat Direcao0[4] = {-2.0, -4.0, -5.0, 1.0};

GLfloat PosicaoLuz1[4] = {-2.0, 4.0, -3.0, 1.0};
GLfloat Direcao1[4] = {3.0, -5.0, -3.0, 1.0};

GLfloat PosicaoLuz2[4] = {-2.0, 4.0, -12.0, 1.0};
GLfloat Direcao2[4] = {3.0, -5.0, -12.0, 1.0};

GLfloat PosicaoLuz3[4] = {2.0, 4.0, -18.0, 1.0};
GLfloat Direcao3[4] = {-2.0, -4.0, -18.0, 1.0};

GLfloat PosicaoLuz4[4] = {0.0, 1.0, -5.0, 1.0};

GLfloat obj_Amb[4] = {0.3, 0.2, 0.1, 1.0};
GLfloat obj_Dif[4] = {0.2, 0.2, 0.2, 1.0};
GLfloat obj_Esp[4] = {0.1, 0.1, 0.1, 1.0};



float angle = 45, fAspect, xClick = 0.0, yClick = 0, flag = 0, angx = 0, angy = 0, angz = 0,
      rotateShoulderRX = 0, rotateShoulderRZ = 0, rotateShoulderLX = 0, rotateShoulderLZ = 0,
      rotateElbowRX = 0, rotateElbowRZ = 0, rotateElbowLX = 0, rotateElbowLZ = 0, rotateHandLX = 0,
      rotateHandLZ = 0, rotateHandRX = 0, rotateHandRZ = 0, rotateLegLZ = 0, rotateLegLX = 0,
      rotateLegRZ = 0, rotateLegRX = 0, rotateKneeLZ = 0, rotateKneeLX = 0, rotateKneeRX = 0,
      rotateKneeRZ = 0, tLegR = 0.0, tLegL = 0.0, moveZ = -5.0, roofZ = -1.0, camZ = 0.5, camX = 0.0,
      camY = 0.0, catZ = 0.0, moveX = 0.0, rotateDoorY = 0.0, tamTela = 400.0, angCamX = 0.0, angCamY = 0.0,
      angCamZ = 0.0;

int  flagShoulderR = 0, flagShoulderL = 0, flagDrawCat = 0, maior = 0,
      activeZ = 0, flagCall = 0, flagElbowL = 0, flagElbowR = 0, flagLegL = 0, flagLegR = 0, flagKneeL = 0,
      flagKneeR = 0, flagZoom = 0, flagDrawCesta = 0, flagFinaliza = 0, firstTime = 0, flagDay = 0,
      flagNeedRotate180 = 0, flagNeedRotateR = 0, flagNeedRotateL = 0, flagNeedMoveOn = 0, flagNeedMoveBack = 0,
      flagNeedMoveRight = 0, flagNeedMoveLeft = 0, flagNormal = 0, flagMoveRGo = 0, flagMoveRCome = 0,
      flagMoveLGo = 0, flagMoveLCome = 0, flagMove = 0, flagNormaliza = 0, atualF = 0, atualL = 0, atualR = 0,
      atualB = 0, cont = 0;



///Rotinas de Lista///

/*Inicia a lista de pontos*/
void inicializaLista (tipoLDE *listaAux){

    listaAux->primeiro = NULL;
    listaAux->ultimo = NULL;
    listaAux->tamanhoLista = 0;
}

/*Insere um elemento na lista*/
void insereElementoFim(tipoLDE *listaAux, float x, float z,
int flagNeedMoveBack, int flagNeedMoveLeft, int flagNeedMoveOn, int flagNeedMoveRight, int isCesta) {

    tipoElemento *novoElem = malloc(sizeof(tipoElemento));

    if (novoElem == NULL)
        printf ("Não foi possível alocar o elemento. Erro!");


    novoElem->x = x;
    novoElem->z = z;
    novoElem->flagNeedMoveBack = flagNeedMoveBack;
    novoElem->flagNeedMoveLeft = flagNeedMoveLeft;
    novoElem->flagNeedMoveOn = flagNeedMoveOn;
    novoElem->flagNeedMoveRight = flagNeedMoveRight;
    novoElem->isCesta = isCesta;


    //Atualiza lista conforme seu tamanho
    if (listaAux->tamanhoLista == 0){
        novoElem->prox = NULL;
        listaAux->primeiro= novoElem;
        listaAux->ultimo=novoElem;
    }

    else {
    novoElem ->prox = NULL;
    listaAux->ultimo->prox = novoElem;
    listaAux->ultimo= novoElem;
    }
    //Atualiza tamanho da lista
    listaAux->tamanhoLista++;
}

///Rotinhas de textura///
/*Le uma img BMP conforme visto em aula*/
void getBitmapImageData( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
	int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
		printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
		printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
		printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
		printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    fseek( pFile, 24, SEEK_CUR );

    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
		printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

	char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
	{
		charTemp = pImage->data[i];
		pImage->data[i] = pImage->data[i+2];
		pImage->data[i+2] = charTemp;
    }
}

/*Carrega uma textura e computa seu ID em um vetor de ID*/
void CarregaTextura(char* Filename, int id)
{

    BMPImage textura;

    getBitmapImageData( Filename, &textura);

    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture_id[id]);

    glBindTexture(GL_TEXTURE_2D, texture_id[id]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textura.width, textura.height, 0,
GL_RGB, GL_UNSIGNED_BYTE, textura.data);
    glTexGenf(GL_S,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenf(GL_T,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

}

///Rotinas que definem parametros da camera e reposicionamento///
void Viewing()	{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
        gluPerspective(angle,fAspect,0.1,800);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glTranslatef(camX, camY, camZ+1.3);
	glRotatef(angCamZ, 0.0, 0.0, 1.0);
	glRotatef(angCamY, 0.0, 1.0, 0.0);
	glRotatef(angCamX, 1.0, 0.0, 0.0);

    gluLookAt(0,0, 1,0,0,0, 0,1,0);

}

void ChangeSize(GLsizei w, GLsizei h)	{

	if ( h == 0 )
		h = 1;
        glViewport(0, 0, w, w);

	fAspect = (GLfloat)w/(GLfloat)h;
	Viewing();
	tamTela = w/2.0;
}



///Rotina que iniciaiza enables e luzes///
void init(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, LuzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, PosicaoLuz0 );
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Direcao0);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 40.0);

    glLightfv(GL_LIGHT1, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa );
    glLightfv(GL_LIGHT1, GL_SPECULAR, LuzEspecular );
    glLightfv(GL_LIGHT1, GL_POSITION, PosicaoLuz1 );
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Direcao1);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 80.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 20.0);

    glLightfv(GL_LIGHT2, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, LuzDifusa );
    glLightfv(GL_LIGHT2, GL_SPECULAR, LuzEspecular );
    glLightfv(GL_LIGHT2, GL_POSITION, PosicaoLuz2);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Direcao2);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 80.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 40.0);

    glLightfv(GL_LIGHT3, GL_AMBIENT, LuzAmbiente);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, LuzDifusa );
    glLightfv(GL_LIGHT3, GL_SPECULAR, LuzEspecular );
    glLightfv(GL_LIGHT3, GL_POSITION, PosicaoLuz3);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, Direcao3);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 80.0);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 40.0);

    glLightfv(GL_LIGHT4, GL_AMBIENT, LuzAmbiente2);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, LuzDifusa);
    glLightfv(GL_LIGHT4, GL_SPECULAR, LuzEspecular);
    glLightfv(GL_LIGHT4, GL_POSITION, PosicaoLuz4);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, obj_Amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, obj_Dif);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, obj_Esp);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, 2);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT4);
    glEnable(GL_DEPTH_TEST);

}

///Rotinas de desenho///


void drawHuman() {
 ///Humano//
  //   glColor3f(0.0, 0.0, 1.0);
    glPushMatrix(); ///Abre humano
        glTranslatef(moveX, -1.0, moveZ);
        glRotatef(angx,1.0,0.0,0.0);
        glRotatef(angy,0.0,1.0,0.0);
        glRotatef(angz,0.0,0.0,1.0);
        glScalef(0.7, 0.7, 0.4);


        ///Cabeca///

        glPushMatrix(); ///Abre cabeca

             glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_id[16]);
            glPushMatrix();
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidSphere(0.3, 20, 20);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.0, -0.05, -0.3);
             glRotatef(20, 1.0, 0.0, 0.0);
            glRotatef(-10, 0.0, 1.0, 0.0);
            glScalef(0.1, 0.1, 0.1);
            glutSolidTetrahedron();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
            glPushMatrix();
                glTranslatef(0.1, 0.1, -0.3);
                glScalef(0.2, 0.2, 0.2);
                glutSolidSphere(0.3, 20, 20);
            glPopMatrix();
              glPushMatrix();
                glTranslatef(-0.1, 0.1, -0.3);
                glScalef(0.2, 0.2, 0.2);
                glutSolidSphere(0.3, 20, 20);
            glPopMatrix();


        glPopMatrix(); ///Fecha cabeca
        ///Pescoco///
         glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[16]);
        glPushMatrix(); ///Abre pescoco
            glTranslatef(0.0, -0.25, 0.0);
            glScalef(0.3, 0.2, 0.5);
            glRotatef(90, 1.0, 0.0, 0.0);
            gluCylinder(gluNewQuadric(), 0.5, 0.3, 0.3, 20,10);
        glPopMatrix(); ///Fecha pescoco
        glDisable(GL_TEXTURE_2D);
        ///Corpo///
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, texture_id[15]);
        glPushMatrix(); ///Abre corpo
            glTranslatef(0.0, -0.75, 0.0);
            glScalef(0.7, 1.2, 1.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidSphere(0.4, 20, 20.0);
        glPopMatrix(); ///Fecha corpo
        ///Braco Esquerdo///
        glPushMatrix(); ///Abre braco
            glTranslatef(0.13, 0.18, 0.0);
            glScalef(1.5, 1.5, 1.5);
            glTranslatef(-0.2, -0.4, 0.0);
            glRotatef(rotateShoulderLX, 1.0, 0.0, 0.0);
            glRotatef(rotateShoulderLZ, 0.0, 0.0, 1.0);
            glRotatef(20, 0.0, 0.0, 1.0);
            glTranslatef(0.2, 0.4, 0.0);

            glPushMatrix(); ///abre Ombro
                glTranslatef(-0.3, -0.5, 0.0);
                glRotatef(-45, 0.0, 0.0, 1.0);
                glScalef(0.5, 1.3, 0.8);
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidSphere(0.1, 20, 20);
            glPopMatrix(); ///Fecha ombro
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_id[16]);
            glPushMatrix(); ///Abre cotovelo
                glTranslatef(-0.39, -0.56, 0.0);
                glRotatef(rotateElbowLX, 1.0, 0.0, 0.0);
                glRotatef(rotateElbowLZ, 0.0, 0.0, 1.0);
                glRotatef(10, 0.0, 0.0, 1.0);
                glTranslatef(0.39, 0.56, 0.0);
                glPushMatrix(); ///abre Antebraco
                    glTranslatef(-0.45, -0.65, 0.0);
                    glRotatef(-45, 0.0, 0.0, 1.0);
                    glScalef(0.5, 1.3, 0.8);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidSphere(0.1, 20, 20);
                glPopMatrix(); ///Fecha antebraco
                glPushMatrix(); ///Abre pulso
                    glTranslatef(-0.52, -0.72, 0.0);
                    glRotatef(rotateHandLX, 1.0, 0.0, 0.0);
                    glRotatef(rotateHandLZ, 0.0, 0.0, 1.0);
                    glTranslatef(0.52, 0.72, 0.0);
                    glPushMatrix(); ///Abre Mao
                        glTranslatef(-0.55, -0.75, 0.0);
                        glRotatef(-45, 0.0, 0.0, 1.0);
                        glScalef(0.5, 1.3, 0.8);
                        glRotatef(90, 1.0, 0.0, 0.0);
                        glutSolidSphere(0.05, 20, 20);
                    glPopMatrix(); ///Fecha Mao
                glPopMatrix();
            glPopMatrix(); ///Fecha cotovelo
        glPopMatrix(); ///Fecha braco
        glDisable(GL_TEXTURE_2D);
        ///Braco Direito///
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[15]);
        glPushMatrix(); ///Abre braco
            glTranslatef(-0.13, 0.18, 0.0);
            glScalef(1.5, 1.5, 1.5);
            glTranslatef(0.2, -0.4, 0.0);
            glRotatef(rotateShoulderRX, 1.0, 0.0, 0.0);
            glRotatef(rotateShoulderRZ, 0.0, 0.0, 1.0);
            glRotatef(-20, 0.0, 0.0, 1.0);
            glTranslatef(-0.2, 0.4, 0.0);
            glPushMatrix(); ///Abre ombro
                glTranslatef(0.3, -0.5, 0.0);
                glRotatef(45, 0.0, 0.0, 1.0);
                glScalef(0.5, 1.3, 0.8);
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidSphere(0.1, 20, 20);
            glPopMatrix(); ///Fecha ombro
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_id[16]);
            glPushMatrix(); ///Abre cotovelo
                glTranslatef(0.39, -0.56, 0.0);
                glRotatef(rotateElbowRX, 1.0, 0.0, 0.0);
                glRotatef(rotateElbowRZ, 0.0, 0.0, 1.0);
                glRotatef(-10, 0.0, 0.0, 1.0);
                glTranslatef(-0.39, 0.56, 0.0);
                    glPushMatrix(); ///Abre Antebraco
                        glTranslatef(0.45, -0.65, 0.0);
                        glRotatef(45, 0.0, 0.0, 1.0);
                        glScalef(0.5, 1.3, 0.8);
                        glRotatef(90, 1.0, 0.0, 0.0);
                        glutSolidSphere(0.1, 20, 20);
                    glPopMatrix(); ///Fecha antebraco
                    glPushMatrix(); ///Abre pulso
                        glTranslatef(-0.52, -0.72, 0.0);
                        glRotatef(rotateHandRX, 1.0, 0.0, 0.0);
                        glRotatef(rotateHandRZ, 0.0, 0.0, 1.0);
                        glTranslatef(0.52, 0.72, 0.0);
                        glPushMatrix(); ///Abre Mao
                            glTranslatef(0.55, -0.75, 0.0);
                            glRotatef(45, 0.0, 0.0, 1.0);
                            glScalef(0.5, 1.3, 0.8);
                            glRotatef(90, 1.0, 0.0, 0.0);
                            glutSolidSphere(0.05, 20, 20);
                        glPopMatrix(); ///Fecha mao
                    glPopMatrix();///Fecha pulso
                glPopMatrix(); ///Fecha cotovelo
        glPopMatrix(); ///Fecha braco
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[18]);
        ///Perna Esquerda//
        glPushMatrix(); ///Abre perna
            glTranslatef(0.05, 0.7, tLegL);
            glScalef(1.6, 1.6, 1.6);
            glTranslatef(-0.03, -1.2, 0.0);
            glRotatef(rotateLegLX, 1.0, 0.0, 0.0);
            glRotatef(rotateLegLZ, 0.0, 0.0, 1.0);
            glTranslatef(0.03, 1.2, 0.0);
            glPushMatrix(); ///abre Coxa
                glTranslatef(-0.1, -1.25, 0.0);
                glScalef(0.5, 1.3, 1.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidSphere(0.1, 20, 20);
            glPopMatrix(); ///fecha coxa
            glPushMatrix(); ///abre Joelho
                glTranslatef(-0.03, -1.35, 0.0);
                glRotatef(rotateKneeLX, 1.0, 0.0, 0.0);
                glRotatef(rotateKneeLZ, 0.0, 0.0, 1.0);
                glTranslatef(0.03, 1.35, 0.0);
                glPushMatrix(); ///Abre perna 2 ?
                    glTranslatef(-0.1, -1.45, 0.0);
                    glScalef(0.5, 1.3, 1.0);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidSphere(0.1, 20, 20);
                glPopMatrix(); ///fecha perna 2
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_id[14]);
                glPushMatrix(); ///abre Pe
                    glTranslatef(-0.1, -1.60, 0.0);
                    glScalef(0.5, 0.3, 1.4);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidSphere(0.1, 20, 20);
                glPopMatrix(); ///fecha pe
            glPopMatrix(); ///fecha joelho
        glPopMatrix(); ///fecha perna
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[18]);
        ///Perna Direita//
        glPushMatrix(); ///abre perna
            glTranslatef(-0.05, 0.7, tLegR);
            glScalef(1.6, 1.6, 1.6);
            glTranslatef(0.03, -1.2, 0.0);
            glRotatef(rotateLegRX, 1.0, 0.0, 0.0);
            glRotatef(rotateLegRZ, 0.0, 0.0, 1.0);
            glTranslatef(-0.03, 1.2, 0.0);
            glPushMatrix(); ///abre Coxa
                glTranslatef(0.1, -1.25, 0.0);
                glScalef(0.5, 1.3, 1.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                glutSolidSphere(0.1, 20, 20);
            glPopMatrix(); ///fecha coxa
            glPushMatrix(); ///abre Joelho
                glTranslatef(0.03, -1.35, 0.0);
                glRotatef(rotateKneeRX, 1.0, 0.0, 0.0);
                glRotatef(rotateKneeRZ, 0.0, 0.0, 1.0);
                glTranslatef(-0.03, 1.35, 0.0);
                glPushMatrix(); ///abre perna 2
                    glTranslatef(0.1, -1.45, 0.0);
                    glScalef(0.5, 1.3, 1.0);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidSphere(0.1, 20, 20);
                glPopMatrix();
            glDisable(GL_TEXTURE_2D);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_id[14]);
                glPushMatrix(); ///abre Pe
                    glTranslatef(0.1, -1.60, 0.0);
                    glScalef(0.5, 0.3, 1.4);
                    glRotatef(90, 1.0, 0.0, 0.0);
                    glutSolidSphere(0.1, 20, 20);
                glPopMatrix(); ///fecha pe
            glPopMatrix();///fecha joelho
        glPopMatrix(); ///fecha perna
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[15]);
        ///Seios///
        glPushMatrix(); ///abre seios
            glTranslatef(-0.01, 0.8, -0.4);
            glScalef(1.8, 1.6, 1.6);
            glPushMatrix(); ///abre Seio Esquerdo///
                glTranslatef(-0.03, -0.85, 0.0);
                glScalef(0.7, 0.7, 0.7);
                glutSolidSphere(0.1, 20, 20);
            glPopMatrix(); ///fecha seio esquerdo
            glPushMatrix(); ///abre Seio Direito///
                glTranslatef(0.05, -0.85, 0.0);
                glScalef(0.7, 0.7, 0.7);
                glutSolidSphere(0.1, 20, 20);
           glPopMatrix(); ///fecha seios direto
        glPopMatrix(); ///fecha seios
    glPopMatrix(); ///fecha humano
    glDisable(GL_TEXTURE_2D);

}



void drawCat() {

glPushMatrix(); ///Abre gato

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[6]);

        glPushMatrix(); ///Abre Cabeca
            glScalef(0.6, 0.6, 0.6);
            glTranslatef(0.0, 0.6, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidSphere(0.3, 20, 20);
        glPopMatrix(); ///Fecha Cabeca
        glPushMatrix(); ///Abre corpo
            glScalef(0.6, 0.6, 0.6);
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidSphere(0.4, 20, 20);
        glPopMatrix(); ///Fecha Corpo
        glPushMatrix(); ///Abre cauda
            glPushMatrix(); ///Cauda 1
                glTranslatef(0.0, 0.0, -0.28);
                glRotatef(30, 1.0, 0.0, 0.0);
                glScalef(1.0, 0.2, 0.7);
                glutSolidSphere(0.1, 20, 20);
            glPopMatrix(); ///Cauda1
            glPushMatrix(); ///Cauda2
                glTranslatef(0.0, 0.05, -0.36);
                glRotatef(30, 1.0, 0.0, 0.0);
                glScalef(1.0, 0.2, 0.5);
                glutSolidSphere(0.1, 20, 20);
            glPopMatrix();
            glPushMatrix(); ///Cauda3
                glTranslatef(0.0, 0.09, -0.4);
                glRotatef(35, 1.0, 0.0, 0.0);
                glScalef(1.0, 0.2, 0.5);
                glutSolidSphere(0.1, 20, 20);
            glPopMatrix();
            glPushMatrix(); ///Cauda3
                glTranslatef(0.0, 0.12, -0.45);
                glRotatef(40, 1.0, 0.0, 0.0);
                glScalef(1.0, 0.2, 0.5);
                glutSolidSphere(0.1, 20, 20);
            glPopMatrix();
         glPopMatrix();
            glPushMatrix();  ///Orelha 1
                glTranslatef(0.1, 0.5, 0.0);
                glRotatef(60, 0.0, 0.0, 1.0);
                glScalef(0.1, 0.1, 0.1);
                glutSolidTetrahedron();
            glPopMatrix();
            glPushMatrix();  ///Orelha 1
                glTranslatef(-0.1, 0.5, 0.0);
                glScalef(0.1, 0.1, 0.1);
                glutSolidTetrahedron();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-0.075, 0.37, 0.16);
                glScalef(0.1, 0.1, 0.1);
                glutSolidSphere(0.1, 40, 40);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.075, 0.37, 0.16);
                glScalef(0.1, 0.1, 0.1);
                glutSolidSphere(0.1, 40, 40);
            glPopMatrix();
    glPopMatrix(); ///Fecha Gato*/
    glDisable(GL_TEXTURE_2D);

}

void drawHouse() {

    glPushMatrix(); ///abre
        glPushMatrix();
            glTranslatef(-0.33, -0.5, 0.5);
            glScalef(0.4, 0.4, 0.4);
            glRotatef(90, 0.0, 1.0, 0.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-0.33, -0.5, -0.5);
            glScalef(0.4, 0.4, 0.4);
            glRotatef(90, 0.0, 1.0, 0.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, texture_id[22]);
            glTranslatef(-0.2, -0.6, 1.0);
            glScalef(0.4, 0.8, 0.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[4]);
        glPushMatrix(); ///T1
            glTranslatef(-0.45, 0.0, 0.0);
            glRotatef(20, 0.0, 0.0, 1.0);
            glScalef(1.0, 0.1, 2.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix(); ///T2
            glTranslatef(0.0, 0.0, 0.0);
            glTranslatef(0.45, 0.0, 0.0);
            glRotatef(-20, 0.0, 0.0, 1.0);
            glScalef(1.0, 0.1, 2.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        glPushMatrix(); ///Baixo
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[10]);
            glTranslatef(0.0, -0.5, 0.0);
            glScalef(1.0, 1.0, 2.0);
            glutSolidCube(1.0);
        glPopMatrix();

        glPushMatrix();

            glScalef(1.5, 1.0, 1.0);
            glutSolidCube(0.3);

        glPopMatrix();
 glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void drawLighPoleR() {
         glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, texture_id[2]);
         glPushMatrix(); ///Poste D1
            glPushMatrix(); ///P1
                glTranslatef(2.0, -2.0, -5.0);
                glScalef(0.1, 7.0, 0.1);
                glutSolidCube(1.0);
            glPopMatrix();///P2
            glPushMatrix();
                 glTranslatef(1.3, 1.3, -5.0);
                 glScalef(1.5, 0.1, 0.1);
                 glutSolidCube(1.0);
            glPopMatrix();
        glPopMatrix(); ///Fecha Poste
        glDisable(GL_TEXTURE_2D);
}

void drawLighPoleL() {
     glEnable(GL_TEXTURE_2D);
         glBindTexture(GL_TEXTURE_2D, texture_id[2]);
    glPushMatrix(); ///Poste E1

            glTranslatef(-1.5, 0.0, -10.0);
            glPushMatrix(); ///P1
                glTranslatef(-2.0, -2.0, 0.0);
                glScalef(0.1, 7.0, 0.1);
                glutSolidCube(1.0);
            glPopMatrix();///P2
            glPushMatrix();
                 glTranslatef(-1.3, 1.3, 0.0);
                 glScalef(1.5, 0.1, 0.1);
                 glutSolidCube(1.0);
            glPopMatrix();
        glPopMatrix(); ///Fecha
 glDisable(GL_TEXTURE_2D);

}

void drawScenario() {
    glPushMatrix(); ///Abre Cenario
        glPushMatrix(); ///Abre asfalto
            glEnable(GL_TEXTURE_2D);
            glBindTexture ( GL_TEXTURE_2D, texture_id[0]);

            glTranslatef(0.0, -2.0, -5.0);
            glScalef(3.1, 0.08, 4.5);
            glRotatef(-90, 1.0, 0.0, 0.0);
            glutSolidCube(1.0);
         glDisable(GL_TEXTURE_2D);
        glPopMatrix();///Fecha Asfalto


        glPushMatrix(); ///Abre Calcada
            glEnable(GL_TEXTURE_2D);
            glBindTexture ( GL_TEXTURE_2D, texture_id[1]);
            glPushMatrix(); ///Abre Calcada direita
                glTranslatef(-2.0, -2.0, -5.0);
                glScalef(1.0, 0.08, 4.5);
                glRotatef(-90, 1.0, 0.0, 0.0);
                glutSolidCube(1.0);
            glPopMatrix(); ///Fecha calcada direita
            glPushMatrix(); ///Abre calcada esquerda
                glTranslatef(2.0, -2.0, -5.0);
                glScalef(1.0, 0.08, 4.5);
                glRotatef(-90, 1.0, 0.0, 0.0);
                glutSolidCube(1.0);
            glPopMatrix(); ///Fecha calcada esquerda */
         glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    glPopMatrix();


}


void drawRoad() {

     glPushMatrix();
            glTranslatef(0.0, 0.0, -29.0);
            drawScenario();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.0, -25.0);
            drawScenario();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.0, -23.0);
            drawScenario();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.0, -19.0);
            drawScenario();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.0, -15.0);
            drawScenario();
        glPopMatrix();

         glPushMatrix();
            glTranslatef(0.0, 0.0, -12.0);
            drawScenario();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.0, -9.0);
            drawScenario();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.0, -7.5);
            drawScenario();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.0, -4.5);
            drawScenario();
        glPopMatrix();

        drawScenario();

}

void drawBuilding() {
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[5]);
        glScalef(1.0, 4.0, 0.8);
        glutSolidCube(1.0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void drawBank() {

        glPushMatrix(); ///
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[23]);
            glTranslatef(-0.3,-0.1, 0.0);
            glScalef(1.4, 0.8, 1.0);
            glutSolidCube(1.0);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();


      glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[13]);
        glScalef(3.0, 1.0, 1.0);
        glutSolidCube(1.0);
        glPopMatrix();
    glPopMatrix();


    glDisable(GL_TEXTURE_2D);


}

void drawChurch() {

    glPushMatrix(); ///abre igreja
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[3]);
        glPushMatrix(); ///T1
            glTranslatef(-0.45, 0.0, 0.0);
            glRotatef(20, 0.0, 0.0, 1.0);
            glScalef(1.0, 0.1, 2.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix(); ///T2
            glTranslatef(0.0, 0.0, 0.0);
            glTranslatef(0.45, 0.0, 0.0);
            glRotatef(-20, 0.0, 0.0, 1.0);
            glScalef(1.0, 0.1, 2.0);
            glutSolidCube(1.0);
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();
        glPushMatrix(); ///Baixo
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[11]);
            glTranslatef(0.0, -0.5, 0.0);
            glScalef(1.0, 1.0, 2.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0, 0.2, 0.6);
            glutSolidCube(0.8);
        glPopMatrix();
        glPushMatrix();

            glTranslatef(0.0, 0.25, 0.6);
            glScalef(0.1, 1.5, 0.1);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0, 0.8, 0.6);
            glScalef(0.5, 0.1, 0.1);
            glutSolidCube(1.0);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

}

void drawCityHall() {

    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[12]);
        glPushMatrix();
            glTranslatef(-1.0, 0.0, 0.0);
            glScalef(1.1, 1.3, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(1.0, 0.0, 0.0);
            glScalef(1.1, 1.3, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0, 0.35, 0.0);
            glScalef(1.1, 2.0, 1.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();


}


void drawHouse2() {

    glPushMatrix();
        glTranslatef(0.0, 0.0, -5.0);
        glRotatef(90, 0.0, 1.0, 0.0);
         glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture_id[4]);
        glPushMatrix(); ///T1
            glTranslatef(-0.45, 0.5, 0.0);
            glRotatef(20, 0.0, 0.0, 1.0);
            glScalef(1.0, 0.1, 2.0);
            glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix(); ///T2
            glTranslatef(0.45, 0.5, 0.0);
            glRotatef(-20, 0.0, 0.0, 1.0);
            glScalef(1.0, 0.1, 2.0);
            glutSolidCube(1.0);
        glPopMatrix();
           glDisable(GL_TEXTURE_2D);
        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture_id[9]);
            glScalef(1.3, 1.0, 1.8);
            glutSolidCube(1.0);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();
    glPopMatrix();

}


void cesta() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[17]);
    glPushMatrix();
        glScalef(0.5, 0.5, 0.5);
        glRotatef(90, 1.0, 0.0, 0.0);
        gluCylinder(gluNewQuadric(), 0.5, 0.3, 0.3, 20,10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void drawScene() {


        glPushMatrix(); ///Ligh Pole1
            glTranslatef(-0.4, 0.0, 0.0);
            drawLighPoleR();
        glPopMatrix();

        glPushMatrix(); ///Casa1
            glTranslatef(-3.5, -0.5, -3.2);
            glScalef(1.4, 1.4, 1.4);
            glRotatef(90, 0.0, 1.0, 0.0);
            drawHouse();
        glPopMatrix();

         glPushMatrix(); ///Ligh Pole 2
            glTranslatef(1.9, 0.0, 0.0);
            drawLighPoleL();
        glPopMatrix();



        glPushMatrix(); ///Predio
            glTranslatef(-2.8, 0.1, -12.0);
            glRotatef(90, 0.0, 1.0, 0.0);
            drawBuilding();
        glPopMatrix();


        glPushMatrix(); ///Banco
            glTranslatef(-2.7, -1.5, -7.5);
            glRotatef(90, 0.0, 1.0, 0.0);
            drawBank();
        glPopMatrix();

         glPushMatrix(); ///Banco
            glTranslatef(-2.7, -1.5, -15.0);
            glRotatef(90, 0.0, 1.0, 0.0);
            drawBank();
        glPopMatrix();

        glPushMatrix(); ///Igreja
            glTranslatef(-3.0, -1.0, -20.0);
            glRotatef(90, 0.0, 1.0, 0.0);
            drawChurch();
        glPopMatrix();

         glPushMatrix(); ///Ligh Pole3
            glTranslatef(-0.4, 0.0, -12.0);
            drawLighPoleR();
        glPopMatrix();

        glPushMatrix(); ///Ligh Pole 2
            glTranslatef(1.9, 0.0, -16.0);
            drawLighPoleL();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(2.8, -1.5, -8.0);
            glScalef(1.5, 1.1, 1.1);
            glRotatef(90, 0.0, 1.0, 0.0);
            drawCityHall();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(7.5, -1.3, -15.0);
            glRotatef(90, 0.0, 1.0, 0.0);
            drawHouse2();
        glPopMatrix();

        glPushMatrix(); ///Predio
            glTranslatef(2.8, 0.1, -25.0);
            glRotatef(90, 0.0, 1.0, 0.0);
            drawBuilding();
        glPopMatrix();

         glPushMatrix(); ///Casa1
            glTranslatef(-3.5, -0.8, -26.0);
            glScalef(1.4, 1.4, 1.4);
            glRotatef(90, 0.0, 1.0, 0.0);
            drawHouse();
        glPopMatrix();

          glPushMatrix(); ///Banco
            glTranslatef(3.0, -1.5, -30.0);
            glRotatef(90, 0.0, 1.0, 0.0);
            drawBank();
        glPopMatrix();

      glPushMatrix(); ///Casa1
            glTranslatef(0.0, 0.0, -40);
            glScalef(3.0, 3.0, 3.0);
            drawHouse();
        glPopMatrix();

        if(flagFinaliza == 0 && p != NULL) {
            glPushMatrix();
                glTranslatef(0.0, -1.5, -3.0);
                glScalef(2.0, 2.0, 2.0);
                cesta();
            glPopMatrix();
        }
        drawRoad();
}

void bigWall() {

    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        if(flagDay == 0)
            glBindTexture(GL_TEXTURE_2D, texture_id[19]);
        else if(flagDay == 1)
            glBindTexture(GL_TEXTURE_2D, texture_id[20]);
        glTranslatef(0.0, 0.0, -40);
        glScalef(100.0, 100.0, 1.0);
        glutSolidCube(1.0);
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
 glEnable(GL_TEXTURE_2D);
 glBindTexture(GL_TEXTURE_2D, texture_id[21]);
    glPushMatrix();
        glTranslatef(4.7, -2.0, -5.0);
        glScalef(5.0, 0.1, 63.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-4.7, -2.0, -5.0);
        glScalef(5.0, 0.1, 63.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();
glDisable(GL_TEXTURE_2D);
}

///Rotina que roda os cliques e as animacoes
void playGame(void)	{

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     bigWall();

    glPushMatrix();
        drawScene();
    glPopMatrix();

    glPushMatrix();
     glTranslatef(0.0, 0.35, 0.0);
       drawHuman();
    glPopMatrix();



    if(flagDrawCat == 1 && flagFinaliza == 0) {
       /*Redesenha os pontos*/
        if(r != NULL) {
            if(r->isCesta == 0) {
                glPushMatrix();
                    glTranslatef(r->x, -1.8, r->z);
                    glScalef(0.4, 0.4, 0.4);
                    drawCat();
                glPopMatrix();
            }

            if(r->prox == NULL)
                r = p;
            else
            r = r->prox;

        }
        glPushMatrix();
            glTranslatef(p->x, -1.8, p->z);
            glScalef(0.4, 0.4, 0.4);
            drawCat();

        glPopMatrix();

        if(p->flagNeedMoveRight == 1) {
            atualR = 1;
            if(atualF == 1) {
                if(cont < 90) {
                    angy -= 1;
                    cont += 1;
                }
                else {
                    atualF = 0;
                    cont = 0;
                }
            }
            else if(atualB == 1) {
                if(cont < 90) {
                    angy += 1;
                    cont +=  1;
                }
                else {
                    atualB = 0;
                    cont = 0;
                }

            }
            else {
                if(moveX < p->x)
                    moveX += 0.01;
                else {
                    p->flagNeedMoveRight = 0;

                }
            }
        }

        if(p->flagNeedMoveLeft == 1) {
             atualL = 1;
             if(atualF == 1) {
                if(cont < 90) {
                    angy += 1;
                    cont += 1;
                }
                else {
                    atualF = 0;
                    cont = 0;
                }
            }
            else if(atualB == 1) {
                if(cont < 90) {
                    angy -= 1;
                    cont +=  1;
                }
                else {
                    atualB = 0;
                    cont = 0;
                }

            }

            else {
                if(moveX > p->x)
                    moveX -= 0.01;
                else {
                    p->flagNeedMoveLeft = 0;

                }
            }
        }

        if(p->flagNeedMoveOn == 1 && (p->flagNeedMoveLeft == 0 && p->flagNeedMoveRight == 0)) {
              atualF = 1;

             if(atualL == 1) {
                if(cont < 90) {
                    angy -= 1;
                    cont += 1;
                }
                else {
                    atualL = 0;
                    cont = 0;
                }
            }
            else if(atualR == 1) {
                if(cont < 90) {
                    angy += 1;
                    cont +=  1;
                }
                else {
                    atualR = 0;
                    cont = 0;
                }

            }
           else {
                if(p->z < moveZ)
                    moveZ -= 0.01;
                else
                    p->flagNeedMoveOn = 0;
            }

        }
        if(p->flagNeedMoveBack == 1 && (p->flagNeedMoveLeft == 0 && p->flagNeedMoveRight == 0)) {
            atualB = 1;

             if(atualL == 1) {
                if(cont < 90) {
                    angy += 1;
                    cont += 1;
                }
                else {
                    atualL = 0;
                    cont = 0;
                }
            }
            else if(atualR == 1) {
                if(cont < 90) {
                    angy -= 1;
                    cont +=  1;
                }
                else {
                    atualR = 0;
                    cont = 0;
                }

            }
           else {
                if(p->z > moveZ)
                    moveZ += 0.01;
                else
                    p->flagNeedMoveBack = 0;

            }
        }

        if((p->flagNeedMoveBack) == 0 && (p->flagNeedMoveOn) == 0) {

            if(p->prox != NULL) {
                flagShoulderL = 1;
                flagShoulderR = 1;

                p = p->prox;
                if(p->z > moveZ) {
                    p->flagNeedMoveBack = 1;
                    p->flagNeedMoveOn = 0;
                }
                else {
                    p->flagNeedMoveBack = 0;
                    p->flagNeedMoveOn = 1;
                }

                if(p->x < xClick) {
                    p->flagNeedMoveLeft = 1;
                    p->flagNeedMoveRight = 0;
                }
                else {
                    p->flagNeedMoveLeft = 0;
                    p->flagNeedMoveRight = 1;
                }
            }

            else {
                flagDrawCat = 0;
                flagMove = 0;

            }
        }
    }




/*Movimeta partes do corpo separadamente*/
if(flagShoulderR == 1) {
        if(rotateShoulderRX < 60)
            rotateShoulderRX += 5;
        else
            flagShoulderR = 0;
    }
    if(flagShoulderR == 0) {
        if(rotateShoulderRX > 0)
            rotateShoulderRX -= 5;
    }

     if(flagShoulderL == 1) {
        if(rotateShoulderLX < 60)
            rotateShoulderLX += 5;
        else
            flagShoulderL = 0;
    }
    if(flagShoulderL == 0) {
        if(rotateShoulderLX > 0)
            rotateShoulderLX -= 5;
    }


    if(flagElbowL == 1) {
        if(rotateElbowLX < 60)
            rotateElbowLX += 1;
        else
            flagElbowL = 0;
    }
    if(flagElbowL == 0) {
        if(rotateElbowLX > 0)
            rotateElbowLX -= 1;
    }

    if(flagElbowR == 1) {
        if(rotateElbowRX < 60)
            rotateElbowRX += 1;
        else
            flagElbowR = 0;
    }
    if(flagElbowR == 0) {
        if(rotateElbowRX > 0)
            rotateElbowRX -= 1;
    }

    if(flagLegR == 1 && flagMove == 0) {
        if(rotateLegRX < 60)
            rotateLegRX += 1;
        else
            flagLegR = 0;
    }
    if(flagLegR == 0 && flagMove == 0) {
        if(rotateLegRX > 0)
            rotateLegRX -= 1;
    }

    if(flagLegL == 1 && flagMove == 0) {
        if(rotateLegLX < 60)
            rotateLegLX += 1;
        else
            flagLegL = 0;
    }
    if(flagLegL == 0 && flagMove == 0) {
        if(rotateLegLX > 0)
            rotateLegLX -= 1;
    }

     if(flagKneeL == 1 && flagMove == 0) {
        if(rotateKneeLX > -60)
            rotateKneeLX -= 1;
        else
            flagKneeL = 0;
    }
    if(flagKneeL == 0 && flagMove == 0) {
        if(rotateKneeLX < 0)
            rotateKneeLX += 1;
    }

    if(flagKneeR == 1 && flagMove == 0) {
        if(rotateKneeRX > -60)
            rotateKneeRX -= 1;
        else
            flagKneeR = 0;
    }
    if(flagKneeR == 0 && flagMove == 0) {
        if(rotateKneeRX < 0)
            rotateKneeRX += 1;
    }

    if(flagFinaliza == 1) {
        flagMove = 1;
        if(angy > 0)
            angy -= 1;
        else if(angy < 0)
            angy += 1;

       else {
            if(moveZ > -40)
                moveZ -= 0.01;
            else {
                flagFinaliza = -1;
                exit(0);
            }

        }
    }

    if(flagMove == 1) {
        if(flagMoveRGo == 1) {
            if(rotateLegRX < 60) {
                rotateLegRX += 5;
                if(rotateKneeRX > -30)
                    rotateKneeRX -= 5;
            }
            else {
                flagMoveRGo = 0;
                flagMoveRCome = 1;
            }

        }
        else if(flagMoveRCome == 1) {
            if(rotateLegRX > 0) {
                rotateLegRX -= 5;
                if(rotateKneeRX < 0)
                    rotateKneeRX += 5;
            }
            else {
                flagMoveRCome = 0;
                flagMoveLGo = 1;
            }

        }
        else if(flagMoveLGo == 1) {
             if(rotateLegLX < 60) {
                rotateLegLX += 5;
                if(rotateKneeLX > -30)
                    rotateKneeLX -= 5;
            }
            else {
                flagMoveLGo = 0;
                flagMoveLCome = 1;
            }


        }
        else if(flagMoveLCome == 1) {
             if(rotateLegLX > 0) {
                rotateLegLX -= 5;
                if(rotateKneeLX < 0)
                    rotateKneeLX += 5;
            }
            else {
                flagMoveLCome = 0;
                flagMoveRGo = 1;
            }

        }


    }
glutSwapBuffers();
}

///Rotinas de teclado e mouse///

void MouseInt (int botao, int estado, int coorX, int coorY) {

    switch(botao) {
        case GLUT_LEFT_BUTTON:
        if(estado == GLUT_DOWN) {

         srand( (unsigned)time(NULL) );
         srand( (unsigned)time(NULL) );
         srand( (unsigned)time(NULL) );
         float x = rand() % 101;  /*Calculo da posicao aleatoria*/
         x = x/100;
         int sinal = rand()%2;
         if(sinal == 1)
            x = -x;

         srand( (unsigned)time(NULL) );
         srand( (unsigned)time(NULL) );
         srand( (unsigned)time(NULL) );
         float z = (rand()%3500);
         z = (z/100);
         if(z > 0)
            z = -z;
         if(z > -5.0)
            z = -6.0;

         xClick = x;
         catZ = z;
         flagDrawCat = 1;
         if(catZ > moveZ) {
            flagNeedMoveBack = 1;
            flagNeedMoveOn = 0;
         }
         else {
            flagNeedMoveBack = 0;
            flagNeedMoveOn = 1;
         }
         if(moveX > xClick) {
            flagNeedRotateL = 1;
            flagNeedMoveLeft = 1;
            flagNeedRotateR = 0;
            flagNeedMoveRight = 0;
         }
         else {
            flagNeedRotateL = 0;
            flagNeedMoveLeft = 0;
            flagNeedRotateR = 1;
            flagNeedMoveRight = 1;
         }
        insereElementoFim(&listaPontos, x, z, flagNeedMoveBack, flagNeedMoveLeft, flagNeedMoveOn, flagNeedMoveRight, 0);
        insereElementoFim(&listaPontos, 0.0, -4.0, flagNeedMoveBack, flagNeedMoveLeft, flagNeedMoveOn, flagNeedMoveRight, 1);
        if(firstTime == 0) {
            p = listaPontos.primeiro;
            r = p;
            flagMoveRGo = 1;
            firstTime = 1;
            atualF = 1;
        }
         flagMove = 1;
            break;
        }
}

 Viewing();
 glutPostRedisplay();
}

void keyboard (unsigned char key, int x, int y){
  switch (key) {

   case 'a':
        angCamY -= 1;
        break;
   case 'd':
        angCamY += 1;
        break;
    case 'w':
        angCamX -= 1;
        break;
    case 's':
        angCamX += 1;
        break;
    case 'j':
        camX += 0.1;
        break;
    case 'l':
        camX -= 0.1;
        break;
    case 'i':
        camZ += 0.1;
        break;
    case 'k':
        camZ -= 0.1;
        break;

}


Viewing();
glutPostRedisplay();
}


void menuFunc(GLint opcao) {

    switch(opcao) {
        case 1:
            flagFinaliza = 1;
            flagMove = 1;
            break;
        case 2:
            flagDay = 1;
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHT1);
            glEnable(GL_LIGHT2);
            glEnable(GL_LIGHT3);
            glDisable(GL_LIGHT4);
            glClearColor(0.0, 0.0, 0.0, 0.0);
            break;
        case 3:
            flagDay = 0;
            glDisable(GL_LIGHT0);
            glDisable(GL_LIGHT1);
            glDisable(GL_LIGHT2);
            glDisable(GL_LIGHT3);
            glEnable(GL_LIGHT4);
            glClearColor(1.0, 1.0, 1.0, 1.0);
            break;
        case 4:
            flagShoulderR = 1;
            break;
        case 5:
            flagShoulderL = 1;
            break;
        case 6:
            flagElbowL = 1;
            break;
        case 7:
            flagElbowR = 1;
            break;
        case 8:
            flagLegL = 1;
            break;
        case 9:
            flagLegR = 1;
            break;
        case 10:
            flagKneeL = 1;
            break;
        case 11:
            flagKneeR = 1;
            break;
        case 12:
            if(flagZoom == 0)
                camZ += 3;
            flagZoom = 1;
            break;
        case 13:
            if(flagZoom == 1)
                camZ -= 3;

            flagZoom = 0;
            break;
        case 14:
         //   flagMoveR = 1;
          //  flagLegRGo = 1;
            break;

    }
    glutPostRedisplay();
}

void Timer(int extra) {
     glutPostRedisplay();
     glutTimerFunc(20,Timer,10);
}



int  main ( int argc, char** argv ){
    glutInit  (&argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH  | GLUT_RGBA);
	glutInitWindowSize(800,800);
	glutCreateWindow("Cat Lady");
    CarregaTextura("asfalto.bmp", 0);
	CarregaTextura("calcada2.bmp", 1);
    CarregaTextura("lightpole.bmp", 2);
    CarregaTextura("roof2.bmp", 3);
    CarregaTextura("roof1.bmp", 4);
    CarregaTextura("building1.bmp", 5);
    CarregaTextura("cat1.bmp", 6);
    CarregaTextura("cat2.bmp", 7);
    CarregaTextura("cat4.bmp", 8);
    CarregaTextura("wall1.bmp", 9);
    CarregaTextura("wall2.bmp", 10);
    CarregaTextura("wall3.bmp", 11);
    CarregaTextura("wall4.bmp", 12);
	CarregaTextura("wall5.bmp", 13);
	CarregaTextura("shoes.bmp", 14);
	CarregaTextura("shirt.bmp", 15);
	CarregaTextura("skin.bmp", 16);
	CarregaTextura("palha.bmp", 17);
	CarregaTextura("jeans.bmp", 18);
	CarregaTextura("sky.bmp", 19);
	CarregaTextura("night.bmp", 20);
	CarregaTextura("grama.bmp", 21);
	CarregaTextura("door1.bmp", 22);
	CarregaTextura("door2.bmp", 23);
	CarregaTextura("bag.bmp", 24);
    inicializaLista(&listaPontos);


	init();
	glutDisplayFunc(playGame);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(MouseInt);
    glutKeyboardFunc(keyboard);
    glutCreateMenu(menuFunc);
        glutAddMenuEntry("Finalizar", 1);
        glutAddMenuEntry("Mudar para Noite ", 2);
        glutAddMenuEntry("Mudar para Dia", 3);
        glutAddMenuEntry("Rotacionar Braco Direito", 4);
        glutAddMenuEntry("Rotacionar Braco Esquerdo", 5);
        glutAddMenuEntry("Rotacionar Cotovelo Esquerdo", 6);
        glutAddMenuEntry("Rotacionar Cotovelo Direito", 7);
        glutAddMenuEntry("Rotacionar Perna Esquerda", 8);
        glutAddMenuEntry("Rotacionar Perna Direita", 9);
        glutAddMenuEntry("Rotacionar Joelho Esquerdo", 10);
        glutAddMenuEntry("Rotacionar Joelho Direito", 11);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutTimerFunc(0,Timer,10);
	glutMainLoop();
	if(flagFinaliza == -1)
        return(0);
}
