///Projeto 01 - Simulação de lançamento com atrito
///Bruna Gabriela de Siqueira RA: 92380
///Kaio Dantas Maia RA: 92420
///Thauany Moedano RA: 92486

#include <stdio.h>
#include <stdlib.h>
#include <math.h> //Biblioteca utilizada para cacular seno e cosseno

int main()
{   //Declarando variáveis
    float m, theta, V, g, k, deltaT, Vox, Voy, x, y, t, Vx, Vy, Ec, Ep, g1, Et, Q;
    FILE *resultados;

    resultados = fopen("projeto01.txt", "w"); //Abrindo o arquivo-texto

    //Definindo parâmetros
    m = 16.0; //Massa
    theta = 1.047197551; //60 graus - o C calcula em radianos por isso a medida foi transformada
    V = 100.0; //Velocidade inicial
    g = -9.81; //Gravidade
    g1 = 9.81;
    k = 0.4; //Constante de atrito
    deltaT = 1.35; //Variação do tempo

    //Definindo parâmetros para t = 0
    Vox = V * cos(theta); //Velocidade no eixo X
    Voy = V * sin(theta); //Velocidade no eixo Y
    x = 0.0; //Posição em x (deslocamento)
    y = 0.0; //Posição em y (altura)
    t = 0; //Tempo
    Ec = 0.5 * m * V * V; //Energia Cinética
    Et = Ec; //Energia térmica

    //Printando os resultados no arquivo texto
    fprintf(resultados, "Tempo | Velocidade | Altura | Deslocamento | E. Cinetica |     E. Potencial |     E. Térmica | E. Total\n");
    fprintf(resultados, "%.2f      %.2f         %.2f        %.2f          %.2f        0.00                0.00         %.2f\n", t, V, y, x, Ec, Et);

    //Atribuindo velocidades
    Vx = Vox;
    Vy = Voy;

    //Simulando o lançamento em 20 segundos
    for (t = 1.35; t < 20; t+=1.35) {
        Vx = Vx - (k * Vx * deltaT)/m; //Calculando velocidade em X
        Vy = Vy + (g - (k * Vy)/m) * deltaT; //Calculando velocidade em Y
        x = x + Vx*deltaT - (k*Vx*deltaT*deltaT)/m; //Calculando posição em X
        y = y + Vy*deltaT + (g - (k * Vy)/m)*deltaT*deltaT; //Calculando posição em Y
        V = sqrt((Vx*Vx)+(Vy*Vy)); //Calculando a velocidade final (união das velocidades nos dois eixos)
        Ec = 0.5 * m * V * V; //Calculando energia cinética
        Ep = m * g1 * y; //Calculado energia potencial
        Q = Et - (Ec + Ep); //Calculando energia térmica
        Et = Ec + Ep + Q; //Calculando energia total do sistema

        //Se a altura chegar a zero significa que o objeto tocou o solo e a simulação é parada
        if (y < 0) {
            fprintf(resultados, "%.2f     %.2f        0.00        %.2f          %.2f          0.00          %.2f          %.2f\n", t, V, x, Ec, Q, Et);
            break; //Printando resultados e parando simulação
        }
        fprintf(resultados, "%.2f      %.2f         %.2f        %.2f          %.2f          %.2f          %.2f          %.2f\n", t, V, y, x, Ec, Ep, Q, Et);
      }

    return 0;
}

