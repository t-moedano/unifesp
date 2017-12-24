#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *analise;
    analise = fopen("analise.txt", "w");
    int opcao;
    float v[22];
    float fito = 200;
    float krill = 100;
    float peixes = 100;
    float pinguins = 100;
    float albatrozes = 100;
    float focas = 100;
    float polar = 100;
    float fotossintese = 2.0;
    float mancha_oleo = 0.03;
    float polar_gelo = 1.9;

    float deltaT = 0.01;
    float tempo = 0.0;
    float dFito, dKrill, dPeixes, dPinguin, dAlbatroz, dFoca, dPolar;
    float K = 100.0;
    float caca = 0;
    int albatrozesExtincao = 0;
    int poluicao = 0;
    int poluicaoTerra = 0;
    int aumentaFoca = 0;

    v[0] = 0.01;
    v[1] = 0.02;
    v[2] = 0.01;
    v[3] = 0.03;
    v[4] = 0.02;
    v[5] = 0.03;
    v[6] = 0.01;
    v[7] = 0.04;
    v[8] = 0.04;
    v[9] = 0.02;
    v[10] = 0.04;
    v[11] = 0.05;
    v[12] = 0.01;
    v[13] = 0.03;
    v[14] = 0.02;
    v[15] = 0.04;
    v[16] = 0.07;
    v[17] = 0.06;
    v[18] = 0.07;
    v[19] = 0.03;
    v[20] = 0.03;
    v[21] = 0.05;
    v[22] = 0.07;
    printf("Fazer analise: 1  sim <---> 2 -nao");
    scanf("%d", &opcao);

    if(opcao==1){
        printf("Escolha a analise:\n1-Caça os peixes\n2-Fim dos albatrozes\n\n3 - Poluição Terra4-Poluicao Mares\n5-Super populacao de focas");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                caca = 2;
                break;
            case 2:
                albatrozesExtincao = 1;
                break;
            case 3:
                poluicaoTerra = 1;
                break;
            case 4:
                poluicao = 1;
                break;
            case 5:
                aumentaFoca = 1;
                break;
            case 6:
                poluicaoTerra = 1;
                break;
        }

    }


      fprintf(analise, "Tempo Fito Krill Peixes Pinguin Albatroz Foca Urso  \n");
      fprintf(analise, "%.2f  %f   %f  %f  %f  %f %f %f\n", tempo, fito, krill, peixes, pinguins, albatrozes, focas, polar);


    int fim = 500;

    for(tempo = 0.0; tempo < fim; tempo += deltaT){

        if(opcao == 1 && (tempo > (fim*0.5) && tempo < (fim*0.75)))
            caca = 0.0;

        if(albatrozesExtincao && tempo >(fim/ 2))
            albatrozes = 0;

        if(poluicao && tempo >(fim/ 2)){
            fito -= fito * 0.5;
            peixes -= peixes * 0.3;
            krill -= 0.7*krill;
        }

        if(poluicaoTerra && tempo >(fim/ 2)){
            polar -= polar * 0.5;
            pinguins -= pinguins * 0.3;
            albatrozes -= albatrozes*0.7;
            focas -= focas * 0.2;
        }

        if(aumentaFoca && tempo > (fim/ 2)){
            focas *= 2;
        }


        dFito = fito * (fotossintese - fotossintese*fito/K - v[0]*krill - v[1]*peixes - sol_forte) * deltaT;
        dKrill = krill * (v[2]*fito - v[3]*pinguins) * deltaT;
        dPeixes = peixes * (v[5]*fito - v[6]*pinguins - v[7]*albatrozes  - caca) * deltaT;
        dPinguin = pinguins * (v[8]*peixes + v[9]*krill - v[10]*focas - v[11]*polar - v[19]*albatrozes) * deltaT;
        dFoca = focas * (v[12]*pinguins + v[13]*albatrozes - v[14]*polar) * deltaT;
        dAlbatroz = albatrozes * (v[15]*peixes - v[16]*focas + v[20] *pinguins +v[21] * albatrozes  - v[22]*albatrozes  ) * deltaT;
        dPolar = polar * (v[17]*focas + v[18]*pinguins - polar_gelo) * deltaT;

        fito += dFito;
        krill += dKrill;
        peixes += dPeixes;
        pinguins += dPinguin;
        focas += dFoca;
        albatrozes += dAlbatroz;
        polar += dPolar;


        fprintf(analise, "%.2f  %f  %f %f  %f  %f  %f  %f\n", tempo, fito, krill, peixes, pinguins, albatrozes, focas, polar);

    }



    return 0;
}
