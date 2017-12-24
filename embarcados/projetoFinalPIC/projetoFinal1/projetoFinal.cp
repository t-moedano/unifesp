#line 1 "C:/Users/aluno/Desktop/projetoFinal.c"
#line 24 "C:/Users/aluno/Desktop/projetoFinal.c"
unsigned int uiValor;

unsigned char ucTexto[10];
unsigned int iLeituraAD = 0;
unsigned char ucMask[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};

void main(){

 TRISD = 0;

 ADCON1 = 0x0F;

 TRISA.RA4 = 0;
 TRISA.RA5 = 0;
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
