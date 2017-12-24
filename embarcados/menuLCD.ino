#include <LiquidCrystal.h> 
 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
const int buttonBack = 6;
const int buttonLeft = 8;
const int buttonTop = 7;
const int buttonRight = 9;

int estadoButtonBack = 0;
int estadoButtonLeft = 0;
int estadoButtonTop = 0;
int estadoButtonRight = 0;

int leButtonBack;
int leButtonLeft;
int leButtonRight;
int leButtonTop;

int lastEstadoBack = LOW;
int lastEstadoRight = LOW;
int lastEstadoTop = LOW;
int lastEstadoLeft = LOW;

int timeBack;
int timeTop;
int timeRight;
int timeLeft;

int timeBackDelay = 50;
int timeTopDelay = 50;
int timeRightDelay = 50;
int timeLeftDelay = 50;

bool apertou;

int i = 0;
int j = 0;

int caseOpcao = 0;
int caseSubOpcao = 0;
boolean subOpcaoON = false;

void setup() 
{   
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Opcao 1*");
  lcd.setCursor(0,1);
  lcd.print("Opcao 2");


  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);
  pinMode(buttonTop, INPUT);
  pinMode(buttonBack, INPUT);
   
} 
void loop() 
{   
  apertou = false; 
  leButtonBack  = digitalRead(buttonBack);
  leButtonLeft  = digitalRead(buttonLeft);
  leButtonTop  = digitalRead(buttonTop);
  leButtonRight  = digitalRead(buttonRight);
  
  /////////////////////////////////////////////DEBOUNCE
  
   if(leButtonBack != lastEstadoBack)
  {
    timeBack = millis();
  }

   if((millis() - timeBack) > timeBackDelay)
   {
      if (leButtonBack != estadoButtonBack)
      {
          estadoButtonBack = leButtonBack;
               apertou = true;
      }
    }
    
    
   if(leButtonTop != lastEstadoTop)
   {
    timeTop = millis();
   }

   if((millis() - timeTop) > timeTopDelay)
   {
      if (leButtonTop != estadoButtonTop)
      {
          estadoButtonTop = leButtonTop;
               apertou = true;
     
        
      }
    }
   
   if(leButtonTop != lastEstadoTop)
   {
    timeTop = millis();
   }

   if((millis() - timeTop) > timeTopDelay)
   {
      if (leButtonTop != estadoButtonTop)
      {
          estadoButtonTop = leButtonTop;
               apertou = true;
       
        
      }
    }
    
   if(leButtonLeft != lastEstadoLeft)
   {
    timeLeft = millis();
   }

   if((millis() - timeLeft) > timeLeftDelay)
   {
      if (leButtonLeft != estadoButtonLeft)
      {
          estadoButtonLeft = leButtonLeft;
               apertou = true;
         
        
      }
    }
  
   if(leButtonRight != lastEstadoRight)
   {
    timeRight = millis();
   }

   if((millis() - timeRight) > timeRightDelay)
   {
      if (leButtonRight != estadoButtonRight)
      {
          estadoButtonRight = leButtonRight;
          apertou = true;
      }
    }
    
    ////////////////////////////////////////////
    
    if(leButtonBack == HIGH && lastEstadoBack == LOW)
    {
      
         
         if(subOpcaoON)
         {
            caseSubOpcao += 1;
            if(caseSubOpcao > 3)
                caseSubOpcao = 3;
         }
         else
         {
             caseOpcao += 1;
             if(caseOpcao > 3)
                caseOpcao = 3;
         } 
    }
    
    if(leButtonTop == HIGH && lastEstadoTop == LOW)
    {
    
       
            
         if(subOpcaoON)
         {
            caseSubOpcao -= 1;
            if(caseSubOpcao < 0)
                caseSubOpcao = 0;
         }
         else
         {
             caseOpcao -= 1;
             if(caseOpcao < 0)
                caseOpcao = 0;
         } 
    }
    
    if(leButtonRight == HIGH && lastEstadoRight == LOW)
    {
        subOpcaoON = true;
        caseSubOpcao = 0;     
    }
    
    if(leButtonLeft == HIGH && lastEstadoLeft == LOW)
    {
        subOpcaoON = false;
        caseSubOpcao = 0;        
    }
    
    
    /////////////////////////////////////////////
    

        if((caseOpcao == 0 || caseOpcao == 2) && apertou == true)
        {
          lcd.begin(16,2);
          lcd.setCursor(0,0);
          lcd.print("Opcao ");
          lcd.print(caseOpcao+1);
          lcd.print("*");
          lcd.setCursor(0,1);
          lcd.print("Opcao ");
          lcd.print(caseOpcao+2);
        }
        else if((caseOpcao == 1 || caseOpcao == 3) && apertou == true)
        {
          lcd.begin(16,2);
          lcd.setCursor(0,0);
          lcd.print("Opcao ");
          lcd.print(caseOpcao);
          lcd.setCursor(0,1);
          lcd.print("Opcao ");
          lcd.print(caseOpcao+1);
          lcd.print("*");
        }

        if(subOpcaoON)
        {
          if((caseSubOpcao == 0 || caseSubOpcao == 2) && apertou == true)
        {

           lcd.begin(16,2);
          lcd.setCursor(0,0);
          lcd.print("Opcao ");
          lcd.print(caseOpcao+1);
          lcd.print("*");
          lcd.setCursor(0,1);
          lcd.print("Opcao ");
          lcd.print(caseOpcao+1);
          
          lcd.setCursor(7,0);
          lcd.print(".");
          lcd.print(caseSubOpcao+1);
          lcd.print("*");
          lcd.setCursor(7,1);
          lcd.print(".");
          lcd.print(caseSubOpcao+2);
        }
        else if((caseSubOpcao == 1 || caseSubOpcao == 3) && apertou == true)
        {

           lcd.begin(16,2);
          lcd.setCursor(0,0);
          lcd.print("Opcao ");
          lcd.print(caseOpcao+1);
          lcd.setCursor(0,1);
          lcd.print("Opcao ");
          lcd.print(caseOpcao+1);
          lcd.print("*");
          
          lcd.setCursor(7,0);
          lcd.print(".");
          lcd.print(caseSubOpcao);
          lcd.setCursor(7,1);
          lcd.print(".");
          lcd.print(caseSubOpcao+1);
          lcd.print("*");
        }
        
        }
    
        
        

    Serial.print("caseOpcao: ");
    Serial.print(caseOpcao);
    Serial.print(" ");
    Serial.print("caseSubOpcao: ");
    Serial.print(caseSubOpcao);
     Serial.print(" ");
      Serial.print("opcaonON: ");
    Serial.println(subOpcaoON);

    
    /////////////////////////////////////////
    
    
    lastEstadoTop = leButtonTop;
    lastEstadoBack = leButtonBack;
    lastEstadoRight = leButtonRight;
    lastEstadoLeft = leButtonLeft;
  
} 