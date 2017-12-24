
/*Sensor de vaga de estacionamento e sensor de ré
 * Thauany Moedano
 */

/*Bibliotecas necessárias*/
#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

/*Constantes para o bip do buzzer*/
#define frequency 2000
#define duration 50

/*Echo e trigger do módulo I2C acoplado ao display LCD*/
const int trigger = 40;
const int echo = 41;

const int buzzer = 13;
const int R = 2;
const int G = 3;
const int B = 4;
const int button = 7;
const int ldr = 0;
const int redLed = 10;
const int greenLed = 11;
const int bargraph[] = {
  22, 23, 24, 25, 26, 27, 28}; 

/*Variáveis utilizadas no programa*/
int actualButtonState = 0;
int lastButtonState = LOW;
unsigned long actualTime = 0;
unsigned long delayTime = 500;
int activateSensor = false; 
int endereco = 0;
long delayBuzzer = 1000;
long redValue = 0, blueValue = 0, greenValue = 100;
long ldrValue, redLedValue = 150, greenLedValue = 150;  

Ultrasonic ultrasonic(trigger, echo);
LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7,3, POSITIVE);

void setup()
{
  Serial.begin(9600); 

  lcd.begin (16,2);
  lcd.setBacklight(HIGH);

  for(int b = 0; b < 10; ++b)
  {
    pinMode(bargraph[b], OUTPUT); 
    digitalWrite(bargraph[b], LOW);
  }

  pinMode(buzzer, OUTPUT);
  pinMode(R, OUTPUT); 
  pinMode(G, OUTPUT); 
  pinMode(B, OUTPUT); 
  pinMode(button, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);



}

void loop()
{
  /*Lê distancia do sensor ultrassonico*/
  float distanceInMeters;
  long microsec = ultrasonic.timing();

  /*Faz o debounce do botão que troca as funções do programa. 
   *Isto só fica disponível a cada 5 segundos
   */
  int buttonRead = digitalRead(button);

  if(buttonRead != lastButtonState)
  {
    actualTime = millis();
  }

  if((millis() - actualTime) > delayTime)
  {
    if(buttonRead != actualButtonState)
    {
      actualButtonState = buttonRead;
    }   

  }

  if(buttonRead == HIGH && lastButtonState == LOW)
  {
    if(activateSensor == true)
      activateSensor = false; 
    else 
      activateSensor = true;
  }

  lastButtonState = buttonRead;

  /*Transforma a distancia lida para metros*/
  distanceInMeters = ultrasonic.convert(microsec, Ultrasonic::CM);
  distanceInMeters /= 100;

  /*Se o sensor de ré estiver ativado, liga os componentes esperados*/
  if(activateSensor == true)
  {
    /*Apaga os componentes do sensor de vaga*/
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, LOW);

    /*Escreve no lcd. A máxima distancia capturada é 1m*/
    lcd.setCursor(0,0);
    lcd.print("Distancia:" );

    if(distanceInMeters > 1)
      lcd.print(1.00);
    else
      lcd.print(distanceInMeters);

    lcd.print(" m");

    /*Se a distancia for maior que 1m, entra no modo distância segura e não ativa os componentes*/
    if(distanceInMeters >= 1)
    {
      digitalWrite(buzzer,LOW);
      delayBuzzer = 1000;
      for(int b = 0; b < 10; ++b)
        digitalWrite(bargraph[b], LOW);

      greenValue = 100;
      redValue = 0; 
    }
    else
      tone(buzzer,frequency,duration); //bip no buzzer

    /*Lógica para acender os leds do bargraph, mudar o RGB por PWM e aumentar ou diminuir o delay entre cada bip*/
    if(distanceInMeters <= 0.90)
    {
      delayBuzzer = 900;
      greenValue = 90;
      redValue = 10; 
    }


    if(distanceInMeters <= 0.80)
    {
      delayBuzzer = 800;
      greenValue = 80;
      redValue = 20;
    }


    if(distanceInMeters <= 0.70)
    {
      delayBuzzer = 700;
      greenValue = 70;
      redValue = 30;
    }

    if(distanceInMeters <= 0.60)
    {
      delayBuzzer = 600;
      digitalWrite(bargraph[0], HIGH); 
      greenValue = 60;
      redValue = 40;
    }
    else
      digitalWrite(bargraph[0], LOW);

    if(distanceInMeters <= 0.50)
    {
      delayBuzzer = 500;
      digitalWrite(bargraph[1], HIGH);
      greenValue = 50;
      redValue = 50;
    }
    else
      digitalWrite(bargraph[1], LOW);

    if(distanceInMeters <= 0.4)
    {
      delayBuzzer = 400;
      digitalWrite(bargraph[2], HIGH);
      greenValue = 40;
      redValue = 60;
    }
    else
      digitalWrite(bargraph[2], LOW);

    if(distanceInMeters <= 0.40)
    {
      delayBuzzer = 400;
      digitalWrite(bargraph[3], HIGH);
      greenValue = 30;
      redValue = 70;
    }
    else
      digitalWrite(bargraph[3], LOW);

    if(distanceInMeters <= 0.30)
    {
      delayBuzzer = 300;
      digitalWrite(bargraph[4], HIGH);
      greenValue = 20;
      redValue = 80;
    }
    else
      digitalWrite(bargraph[4], LOW);


    if(distanceInMeters <= 0.20)
    {
      delayBuzzer = 200;
      digitalWrite(bargraph[5], HIGH);
      greenValue = 10;
      redValue = 90;
    }
    else
      digitalWrite(bargraph[5], LOW);


    if(distanceInMeters <= 0.10)
    {
      delayBuzzer = 100;
      digitalWrite(bargraph[6], HIGH);
      greenValue = 0;
      redValue = 100;
    }
    else
      digitalWrite(bargraph[6], LOW);

    analogWrite(G, greenValue);
    analogWrite(B, blueValue);
    analogWrite(R, redValue);
  }
  /*Caso o sensor de vaga esteja acionado*/
  else
  {
    lcd.clear();
    analogWrite(G, 0);
    analogWrite(B, 0);
    analogWrite(R, 0);

    ldrValue = analogRead(ldr); //Controla o brilho dos leds por PWM utilizando o sensor de luminosidade

    for(int i = 0; i < 10; ++i)
      digitalWrite(bargraph[i], LOW);

    if(distanceInMeters < 0.5)
    {
      EEPROM.write(endereco, 0);
      analogWrite(redLed, redLedValue);
      analogWrite(greenLed, LOW);
      lcd.setCursor(0,0);
      lcd.print("Ocupado" );
    }
    else
    {
      EEPROM.write(endereco, 1); /*Grava o valor da EEPROM*/
      analogWrite(redLed, LOW);
      analogWrite(greenLed, greenLedValue);
      lcd.setCursor(0,0);
      lcd.print("Livre" );
    }

    /*Controla o brilho dos leds*/
    if(ldrValue < 380)
    {
      redLedValue += 40;
      greenLedValue += 40;

      if(redLedValue > 255 || greenLedValue > 255)
      {
        redLedValue = 255;
        greenLedValue = 255;
      }
    }
    else
    {
      redLedValue -= 40;
      greenLedValue -= 40;

      if(redLedValue < 10 || greenLedValue < 10)
      {
        redLedValue = 10;
        greenLedValue = 10;
      }
    }   
  }  
  /*Le valor da EEPROM*/
  Serial.print("Valor lido da EEPROM: ");
  Serial.println(EEPROM.read(endereco));
  delay(delayBuzzer);
}



