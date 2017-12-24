/***************************************\
** ROBOCORE ARDUINO KIT INICIANTE **
* *
** Display 7 Segmentos 2 **
\***************************************/
const int a = 4;
const int b = 5;
const int c = 6;
const int d = 7;
const int botaoMais = 13;
const int botaoMenos = 12;

int estadoButtonMais = 0;
int estadoButtonMenos = 0;

int leButtonMais;
int leButtonMenos;


int lastEstadoMais = LOW;
int lastEstadoMenos = LOW;

int timeMais;
int timeMenos;

int timeMaisDelay = 50;
int timeMenosDelay = 50;

int digito = 0;

void setup(){
pinMode(a, OUTPUT);
pinMode(b, OUTPUT);
pinMode(c, OUTPUT);
pinMode(d, OUTPUT);
pinMode(botaoMais, INPUT);
pinMode(botaoMenos, INPUT);
 Serial.begin(9600);
}

 
void digitos(int digito)
{
  
     if(digito == 0)
     {     
       digitalWrite(a, LOW);//DIGITO 0
       digitalWrite(b, LOW);
       digitalWrite(c, LOW);
       digitalWrite(d, LOW);
       
     }
     if(digito == 1)
     {
       digitalWrite(a, HIGH);//DIGITO 1
       digitalWrite(b, LOW);
       digitalWrite(c, LOW);
       digitalWrite(d, LOW);

     }
     if(digito == 2)
     {
       digitalWrite(a, LOW);//DIGITO 2
       digitalWrite(b, HIGH);
       digitalWrite(c, LOW);
       digitalWrite(d, LOW);
     
     }
     if(digito == 3)
     {
       digitalWrite(a, HIGH);//DIGITO 3
       digitalWrite(b, HIGH);
       digitalWrite(c, LOW);
       digitalWrite(d, LOW);
   
     }
     if(digito == 4)
     {
       digitalWrite(a, LOW);//DIGITO 4
       digitalWrite(b, LOW);
       digitalWrite(c, HIGH);
       digitalWrite(d, LOW);
     
     }
     if(digito == 5)
     {
       digitalWrite(a, HIGH);//DIGITO 5
       digitalWrite(b, LOW);
       digitalWrite(c, HIGH);
       digitalWrite(d, LOW);
      
     }
     if(digito == 6)
     {
       digitalWrite(a, LOW);//DIGITO 6
       digitalWrite(b, HIGH);
       digitalWrite(c, HIGH);
       digitalWrite(d, LOW);
    
     }
     if(digito == 7)
     {
       digitalWrite(a, HIGH);//DIGITO 7
       digitalWrite(b, HIGH);
       digitalWrite(c, HIGH);
       digitalWrite(d, LOW);
  
     }
     if(digito == 8)
     {
       digitalWrite(a, LOW);//DIGITO 8
       digitalWrite(b, LOW);
       digitalWrite(c, LOW);
       digitalWrite(d, HIGH);

     }
     if(digito == 9)
     {
       digitalWrite(a, HIGH); //DIGITO 9
       digitalWrite(b, LOW);
       digitalWrite(c, LOW);
       digitalWrite(d, HIGH);
      
     }
  
}
void loop()
{
    leButtonMais  = digitalRead(botaoMais);
    leButtonMenos  = digitalRead(botaoMenos); 

  if(leButtonMais != lastEstadoMais)
  {
    timeMais = millis();
  }

  if(leButtonMenos != lastEstadoMenos)
  {
    timeMenos = millis();
  }
  

   if((millis() - timeMenos) > timeMenosDelay)
   {
      if (leButtonMenos != estadoButtonMenos)
      {
          estadoButtonMenos = leButtonMenos;
          
         
         
      }
    }

     if((millis() - timeMais) > timeMaisDelay)
   {
      if (leButtonMais != estadoButtonMais)
      {
          estadoButtonMais = leButtonMais;
          
      
      }
    }


     if(leButtonMais == HIGH && lastEstadoMais == LOW)
     {
        digito++;
        if(digito > 9)
          digito = 0;  
     }

     if(leButtonMenos == HIGH && lastEstadoMenos == LOW)
     {
        digito--;
        if(digito < 0)
          digito = 9;  
     }
    lastEstadoMais = leButtonMais;
    lastEstadoMenos = leButtonMenos;
    Serial.print(digito);
    
    digitos(digito);
 
} 