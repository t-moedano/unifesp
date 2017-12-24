#include <stdio.h>
#include <stdlib.h>

int main()
{

    FILE *analise;
    analise = fopen("analise.txt", "w");

    //Parâmetros para a samambaia
    float samambaia = 100;
    float fotossintese = 2.0;
    float sol_forte = 0.03;

    //Valores iniciais dos dinossauros
    float aelossauro = 15.0;
    float triceratops = 15.0;
    float espinossauro = 15.0;
    float t_rex = 15.0;

    //Taxa de infecção do T-Rex
    float intoxicacao = 1.9;

    float v[14]; //Definindo vetor que armazena os parâmetros
    float deltaT = 0.01; //Variação de deltaT
    int i;
    float tempo;
    float dSamambaia, dAelossauro, dTriceratops, dEspinossauro, dT_Rex;
    float K = 100.0; //Capacidade de suporte ao meio

    v[0] = 0.02;
    v[1] = 0.01;
    v[2] = 0.094;
    v[3] = 0.01;
    v[4] = 0.01;
    v[5] = 0.09;
    v[6] = 0.01;
    v[7] = 0.01;
    v[8] = 0.04;
    v[9] = 0.06;
    v[10] = 0.01;
    v[11] = 0.02;
    v[12] = 0.03;
    v[13] = 0.009;

      fprintf(analise, "Tempo Samambaia Aelossauro Triceratops Espinossauro T-Rex \n", tempo, samambaia, aelossauro, triceratops, espinossauro, t_rex);
     fprintf(analise, "%.2f  %f   %f  %f  %f  %f\n", tempo, samambaia, aelossauro, triceratops, espinossauro, t_rex);


    for(tempo = 0.0; tempo < 300; tempo+=deltaT){
        //Taxa de variação de cada em espécie em função das equações de Lotka-Volterra
        dSamambaia = samambaia * (fotossintese - fotossintese*samambaia/K - v[0]*aelossauro - v[1]*triceratops - sol_forte) * deltaT;
        dAelossauro = aelossauro * (v[2]*samambaia - v[3]*espinossauro - v[4]*t_rex) * deltaT;
        dTriceratops = triceratops * (v[5]*samambaia - v[6]*espinossauro - v[7]*t_rex) * deltaT;
        dEspinossauro = espinossauro * (v[8]*aelossauro + v[9]*triceratops - v[10]*t_rex) * deltaT;
        dT_Rex = t_rex * (v[11]*aelossauro + v[12]*triceratops + v[13]*espinossauro - intoxicacao) * deltaT;


	espinossauro += dEspinossauro;
	aelossauro += dAelossauro;
	triceratops += dTriceratops;
	t_rex += dT_Rex;
	samambaia += dSamambaia;

        fprintf(analise, "%.2f  %f   %f  %f  %f  %f\n", tempo, samambaia, aelossauro, triceratops, espinossauro, t_rex);

    }



    return 0;
}
