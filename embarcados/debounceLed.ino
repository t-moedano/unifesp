/***************************************\
Exercicio 1 - Aplicar o debounce para um botão acender um led
  \***************************************/

const int ledPin = 13; //led no pino 13
const int Botao = 2; //botao no pino 2


int estadoBotaoAtual = LOW;
int estadoLed = HIGH;

unsigned long tempo = 0;
unsigned long tempoDelay = 50;

void setup() {
  pinMode(ledPin, OUTPUT); //Pino do led será saída
  pinMode(Botao, INPUT); //Pino com botão será entrada
}
void loop() {
  //Lê botao e pega a entrada corrente
  int leBotao  = digitalRead(Botao);

  //Se leBotao for diferente do ultimo estado registrado, o tempo é marcado
  if(leBotao != estadoBotaoAtual)
  {
    tempo = millis();
  }

  /*Entao, o tempo é subtraído do tempo atual. Se esse número for maior
  que o tempo de ciclo de delay (problema causado pelo bounce), significa
  que alguém apertou e a lógica do botao é feita novamente*/
   if((millis() - tempo) > tempoDelay)
   {
          if(leBotao == HIGH)
          {
             estadoLed = !estadoLed;
          }    
    }
    digitalWrite(ledPin, estadoLed);
    estadoBotaoAtual = leBotao;
  }