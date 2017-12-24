-- /*
 * EEPROM Write
 *
 */

#include <EEPROM.h>

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
const int LM35 = 0; 
float temperatura = 0;
int ADClido = 0; 
int mode = 0;
int addr = 0;

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL1V1);
  
  /** Empty setup. **/
}

void loop() {

  if(mode == 0) //LEITURA DA TEMPERATURA
  {
    for(int i = 0; i < 20; ++i)
    {
      delay(500);
      ADClido = analogRead(LM35);
      temperatura = ADClido * 0.1075268817204301;
     
      int temp100 = (int) (temperatura*100.00);
      int parteInteira = temp100/100;
      int parteDecimal = temp100%100;
      Serial.print("Temperatura em tempo real  ");
      Serial.print("[ ");
      Serial.print(i+1);
      Serial.print(" ]: ");
      Serial.print(parteInteira);
      Serial.print(".");
       if(parteDecimal < 10)
        {
          Serial.print("0");
        }
      Serial.println(parteDecimal);
      EEPROM.write(addr, parteInteira);
      ++addr;
      EEPROM.write(addr, parteDecimal);
      ++addr;
    }  
    mode = 1;
  }

  if(mode == 1) //RECUPERA DA MEMÓRIA
  {
    int cont = 0;
    for(int i = 0; i < 39; i+=2)
    {
        Serial.print("Temperatura gravada no EEPROM:  ");
        Serial.print("[ ");
         
        if(i%2 == 0)
        {
          Serial.print(cont+1);
          } 
        ++cont;
         
         Serial.print(" ]: ");
        int tempInteira = EEPROM.read(i);
        int tempDecimal = EEPROM.read(i+1);
        Serial.print(tempInteira);
        Serial.print(".");
        if(tempDecimal < 10)
        {
          Serial.print("0");
        }
        Serial.println(tempDecimal);
        
        
    }
    mode = 3;
  }

}