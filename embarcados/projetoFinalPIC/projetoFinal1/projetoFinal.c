/*

Thauany Moedano
PIC - Parte 1

************************ Configurações do KIT Picgenios ************************
 CRISTAL: 8Mhz.

 CHAVES DE FUNÇÃO:
  --------------------- ----------------------
 |GLCD\LCD ( 1) = OFF  |DIS1     ( 1) = OFF   |
 |RX       ( 2) = OFF  |DIS2     ( 2) = OFF   |
 |TX       ( 3) = OFF  |DIS3     ( 3) = ON    |
 |REL1     ( 4) = OFF  |DIS4     ( 4) = ON    |
 |REL2     ( 5) = OFF  |INFR     ( 5) = OFF   |
 |SCK      ( 6) = OFF  |RESIS    ( 6) = ON    |
 |SDA      ( 7) = OFF  |TEMP     ( 7) = ON    |
 |RTC      ( 8) = OFF  |VENT     ( 8) = ON    |
 |LED1     ( 9) = OFF  |AN0      ( 9) = OFF   |
 |LED2     (10) = OFF  |AN1      (10) = OFF   |
  --------------------- ----------------------
*/

unsigned int  uiValor;

unsigned char ucTexto[10];
unsigned int iLeituraAD = 0;
unsigned char ucMask[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void main(){

   TRISD = 0;

   ADCON1 = 0x0F;

   TRISA.RA4 = 0;      //Display 3
   TRISA.RA5 = 0;     // Display 4
   TRISC.RC5 = 0;
   PORTC.RC5 = 1;
   while(1)
   {

       iLeituraAD= ADC_Read(2);
        iLeituraAD/=2;
      
      Delay_ms(2);

      if(iLeituraAD >= 30)
      {
         PWM1_Init(5000);
         PWM1_Set_Duty(iLeituraAD * 5);
         PWM1_Start();
      }
      else
      {
          PWM1_Stop();
      }

      uiValor = iLeituraAD;
      Delay_ms(2);
      PORTD = ucMask[uiValor%10];
      PORTA.RA5 = 1;
      Delay_ms(2);
      PORTA.RA5 = 0;
      uiValor/=10;
      PORTD = ucMask[uiValor%10];
      PORTA.RA4 = 1;
      Delay_ms(2);
      PORTA.RA4 = 0;
      Delay_ms(2);

    }
}