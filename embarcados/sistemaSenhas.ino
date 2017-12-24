/***************************************\
** ROBOCORE ARDUINO KIT INICIANTE **
* *
** Módulo Amarelo **
\***************************************/
const int ledPinVermelho = 13;  //vermelho
const int ledPinAmarelo = 12; //amarelo
const int ledPinVerde = 11;  //verde
 
const int BotaoVermelho = 2;
const int BotaoAmarelo = 3;
const int BotaoVerde = 4;

//Sequencia: verde vermelho amarelo
int estadoBotaoVermelho = 0;
int estadoBotaoAmarelo = 0;
int estadoBotaoVerde = 0;

int leBotaoVermelho;
int leBotaoAmarelo;
int leBotaoVerde;

int ultimoEstadoBotaoVermelho = LOW;
int ultimoEstadoBotaoAmarelo = LOW;
int ultimoEstadoBotaoVerde = LOW;

int estadoLedVermelho = LOW;
int estadoLedAmarelo = LOW;
int estadoLedVerde = LOW;

int tempoDelay = 50;
int tempoVermelho = 0;
int tempoAmarelo = 0;
int tempoVerde = 0;

int estadoSenha = 0;

void setup(){
pinMode(ledPinVermelho, OUTPUT);
pinMode(BotaoVermelho, INPUT);
pinMode(ledPinAmarelo, OUTPUT);
pinMode(BotaoAmarelo, INPUT);
pinMode(ledPinVerde, OUTPUT);
pinMode(BotaoVerde, INPUT);
}
void loop(){

  int leBotaoVermelho  = digitalRead(BotaoVermelho);
  int leBotaoAmarelo  = digitalRead(BotaoAmarelo);
  int leBotaoVerde  = digitalRead(BotaoVerde);

  //Se leBotao for diferente do ultimo estado registrado, o tempo é marcado
  if(leBotaoVermelho != ultimoEstadoBotaoVermelho)
  {
    tempoVermelho = millis();
  }

  /*Entao, o tempo é subtraído do tempo atual. Se esse número for maior
  que o tempo de ciclo de delay (problema causado pelo bounce), significa
  que alguém apertou e a lógica do botao é feita novamente*/
   if((millis() - tempoVermelho) > tempoDelay)
   {
      if (leBotaoVermelho != estadoBotaoVermelho)
      {
          estadoBotaoVermelho = leBotaoVermelho;

        
      }
    }
   
   
    //////////////////////////////////////
   
    if(leBotaoAmarelo != ultimoEstadoBotaoAmarelo)
  {
    tempoAmarelo = millis();
  }

  /*Entao, o tempo é subtraído do tempo atual. Se esse número for maior
  que o tempo de ciclo de delay (problema causado pelo bounce), significa
  que alguém apertou e a lógica do botao é feita novamente*/
   if((millis() - tempoAmarelo) > tempoDelay)
   {
      if (leBotaoAmarelo != estadoBotaoAmarelo)
      {
          estadoBotaoAmarelo = leBotaoAmarelo;

         
      }
    }
   
    //////////////////////////////////////
   
    if(leBotaoVermelho != ultimoEstadoBotaoVermelho)
    {
    tempoVermelho = millis();
    }

  /*Entao, o tempo é subtraído do tempo atual. Se esse número for maior
  que o tempo de ciclo de delay (problema causado pelo bounce), significa
  que alguém apertou e a lógica do botao é feita novamente*/
   if((millis() - tempoVerde) > tempoDelay)
   {
      if (leBotaoVerde != estadoBotaoVerde)
      {
          estadoBotaoVerde = leBotaoVerde;

         
      }
    }
   
    if(leBotaoVermelho == HIGH && ultimoEstadoBotaoVermelho == LOW)
    {
        if(estadoSenha == 1) //Sequencia: Verde
        {
            estadoSenha = 2;  //Sequencia: Verde - Vermelho
        }
        else
        {
            estadoSenha = 0; //Sequencia: -
        }       
    }
       
   if(leBotaoVerde == HIGH && ultimoEstadoBotaoVerde == LOW)
    {
        estadoSenha = 1;
    }
       
    if(leBotaoAmarelo == HIGH && ultimoEstadoBotaoAmarelo == LOW)
    {
       
        if(estadoSenha == 2)
        {
               
            digitalWrite (ledPinAmarelo, HIGH);
            digitalWrite (ledPinVermelho, HIGH);
            digitalWrite (ledPinVerde, HIGH);
            delay (100);
            digitalWrite (ledPinAmarelo, LOW);
            digitalWrite (ledPinVermelho, LOW);
            digitalWrite (ledPinVerde, LOW);
            delay (100);
            estadoLedVerde = LOW;
            estadoLedAmarelo = LOW;
            estadoLedVermelho = LOW;
            leBotaoVermelho = LOW;
            leBotaoAmarelo = LOW;
            leBotaoVerde = LOW;
               
        }
        estadoSenha = 0;        
    }
   
   
    ultimoEstadoBotaoVermelho = leBotaoVermelho;
   
   
    ultimoEstadoBotaoAmarelo = leBotaoAmarelo;
   
   
    ultimoEstadoBotaoVerde = leBotaoVerde;
   
       
}