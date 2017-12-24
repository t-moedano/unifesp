/*

 CHAVES DE FUNÇÃO:
  --------------------- ----------------------
 |GLCD\LCD ( 1) = ON   |DIS1     ( 1) = OFF   |
 |RX       ( 2) = OFF  |DIS2     ( 2) = OFF   |
 |TX       ( 3) = OFF  |DIS3     ( 3) = OFF   |
 |REL1     ( 4) = OFF  |DIS4     ( 4) = OFF   |
 |REL2     ( 5) = OFF  |INFR     ( 5) = OFF   |
 |SCK      ( 6) = ON   |RESIS    ( 6) = OFF   |
 |SDA      ( 7) = ON   |TEMP     ( 7) = ON    |
 |RTC      ( 8) = ON   |VENT     ( 8) = OFF   |
 |LED1     ( 9) = OFF  |AN0      ( 9) = OFF   |
 |LED2     (10) = OFF  |AN1      (10) = OFF   |
  --------------------- ----------------------
********************************************************************************
OBS:
- HABILITAR BIBLIOTECA LCD.
- HABILITAR BIBLIOTECA I2C.
********************************************************************************
*/
unsigned char ucHora;       // Armazena Hora.
unsigned char ucMinuto;     // Armazena Minuto.
unsigned char ucSegundo;    // Armazena Segundo.

void Display_LCD();
void Grava_RTC();
void Leitura_RTC();
void Converte_BCD(unsigned char ucLinha, unsigned char ucColuna,unsigned char ucValor);
unsigned char ucMask[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

sbit LCD_RS at RE2_bit;
sbit LCD_EN at RE1_bit;
sbit LCD_D7 at RD7_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D4 at RD4_bit;

sbit LCD_RS_Direction at TRISE2_bit;
sbit LCD_EN_Direction at TRISE1_bit;
sbit LCD_D7_Direction at TRISD7_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD4_bit;

char ucContador = 0;
unsigned int iLeituraAD = 0;
unsigned int temp = 0;

void interrupt()
{
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);

    if(INTCON.TMR0IF == 1)
    {
       TMR0H = 0xDB;
       TMR0L = 0x61;

       ucContador++;

       if(ucContador == 16)
       {
          Delay_ms(1000);
          Display_LCD();
          for(ucContador = 2; ucContador < 15; ucContador ++)
          {
               Lcd_Chr(2,ucContador+1,EEPROM_Read(ucContador));
          }
          ucContador = 0;
       }
       else
       {
          iLeituraAD = ADC_Read(2);
          iLeituraAD /= 2;
          Lcd_Out(1,1,"Registrando");
          temp = iLeituraAD;
          EEPROM_Write(ucContador,0x30+(temp%10));
          temp /= 10;
          ucContador++;
          EEPROM_Write(ucContador+1,0x30+(temp%10));
          ucContador++;
       }

       INTCON.TMR0IF = 0;       // Limpa o flag de estouro do timer0 para uma nova contagem de tempo.

    }
}


void main(){

   TRISC.RC5 = 0;
   PORTC.RC5 = 1;
   ADCON1 = 0x0F;

   T0CON.T0CS = 0;
   T0CON.PSA = 0;
   T0CON.T0PS2 = 1;
   T0CON.T0PS1 = 1;
   T0CON.T0PS0 = 0;
   T0CON.T08BIT = 0;

   TMR0H = 0xDB;
   TMR0L = 0x61;
   INTCON.TMR0IE = 1;
   INTCON.TMR0IF = 0;
   T0CON.TMR0ON = 1;
   INTCON.GIE = 1;
   INTCON.PEIE = 1;
   TRISB.RB0=1;
   TRISB.RB1=1;

   Grava_RTC();

   while(1)
   {
        Leitura_RTC();

    }

}

void Converte_BCD(unsigned char ucLinha, unsigned char ucColuna,unsigned char ucValor) {
  unsigned char ucValor1, ucValor2;

  ucValor1 = (ucValor >> 4  ) + '0';
  Lcd_Chr(ucLinha,ucColuna,ucValor1);
  ucValor2 = (ucValor & 0x0F) + '0';
  Lcd_Chr_CP(ucValor2);
}

void Leitura_RTC()
{
   I2C1_Start();
   I2C1_Wr(0xD0);
   I2C1_Wr(0);
   I2C1_Repeated_Start();
   I2C1_Wr(0xD1);
   ucSegundo = I2C1_Rd(1);
   ucMinuto = I2C1_Rd(1);
   ucHora = I2C1_Rd(1);
   I2C1_Stop();
}

void Grava_RTC()
{
   I2C1_Init(100000);
   I2C1_Start();
   I2C1_Wr(0xD0);
   I2C1_Wr(0);
   I2C1_Wr(0x04);
   I2C1_Wr(0x12);
   I2C1_Wr(0x09);
   I2C1_Wr(0x03);
   I2C1_Wr(0x22);
   I2C1_Wr(0x06);
   I2C1_Wr(0x17);
   I2C1_Stop();
}

void Display_LCD()
{

   Lcd_Out(1,1,"(Hora)");
   Converte_BCD(1,7,ucHora);
   Lcd_Chr_CP(':');
   Converte_BCD(1,10,ucMinuto);
   Lcd_Chr_CP(':');
   Converte_BCD(1,13,ucSegundo);
}