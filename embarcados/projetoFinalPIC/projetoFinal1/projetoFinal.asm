
_main:

;projetoFinal.c,30 :: 		void main(){
;projetoFinal.c,32 :: 		TRISD = 0;
	CLRF        TRISD+0 
;projetoFinal.c,34 :: 		ADCON1 = 0x0F;
	MOVLW       15
	MOVWF       ADCON1+0 
;projetoFinal.c,36 :: 		TRISA.RA4 = 0;      //Display 3
	BCF         TRISA+0, 4 
;projetoFinal.c,37 :: 		TRISA.RA5 = 0;     // Display 4
	BCF         TRISA+0, 5 
;projetoFinal.c,38 :: 		TRISC.RC5 = 0;
	BCF         TRISC+0, 5 
;projetoFinal.c,39 :: 		PORTC.RC5 = 1;
	BSF         PORTC+0, 5 
;projetoFinal.c,40 :: 		while(1)
L_main0:
;projetoFinal.c,43 :: 		iLeituraAD= ADC_Read(2);
	MOVLW       2
	MOVWF       FARG_ADC_Read_channel+0 
	CALL        _ADC_Read+0, 0
	MOVF        R0, 0 
	MOVWF       _iLeituraAD+0 
	MOVF        R1, 0 
	MOVWF       _iLeituraAD+1 
;projetoFinal.c,44 :: 		iLeituraAD/=2;
	MOVF        R0, 0 
	MOVWF       _iLeituraAD+0 
	MOVF        R1, 0 
	MOVWF       _iLeituraAD+1 
	RRCF        _iLeituraAD+1, 1 
	RRCF        _iLeituraAD+0, 1 
	BCF         _iLeituraAD+1, 7 
;projetoFinal.c,46 :: 		Delay_ms(2);
	MOVLW       6
	MOVWF       R12, 0
	MOVLW       48
	MOVWF       R13, 0
L_main2:
	DECFSZ      R13, 1, 1
	BRA         L_main2
	DECFSZ      R12, 1, 1
	BRA         L_main2
	NOP
;projetoFinal.c,48 :: 		if(iLeituraAD >= 30)
	MOVLW       0
	SUBWF       _iLeituraAD+1, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main10
	MOVLW       30
	SUBWF       _iLeituraAD+0, 0 
L__main10:
	BTFSS       STATUS+0, 0 
	GOTO        L_main3
;projetoFinal.c,50 :: 		PWM1_Init(5000);
	BSF         T2CON+0, 0, 0
	BCF         T2CON+0, 1, 0
	MOVLW       99
	MOVWF       PR2+0, 0
	CALL        _PWM1_Init+0, 0
;projetoFinal.c,51 :: 		PWM1_Set_Duty(iLeituraAD * 5);
	MOVLW       5
	MULWF       _iLeituraAD+0 
	MOVF        PRODL+0, 0 
	MOVWF       FARG_PWM1_Set_Duty_new_duty+0 
	CALL        _PWM1_Set_Duty+0, 0
;projetoFinal.c,52 :: 		PWM1_Start();
	CALL        _PWM1_Start+0, 0
;projetoFinal.c,53 :: 		}
	GOTO        L_main4
L_main3:
;projetoFinal.c,56 :: 		PWM1_Stop();
	CALL        _PWM1_Stop+0, 0
;projetoFinal.c,57 :: 		}
L_main4:
;projetoFinal.c,59 :: 		uiValor = iLeituraAD;
	MOVF        _iLeituraAD+0, 0 
	MOVWF       _uiValor+0 
	MOVF        _iLeituraAD+1, 0 
	MOVWF       _uiValor+1 
;projetoFinal.c,60 :: 		Delay_ms(2);
	MOVLW       6
	MOVWF       R12, 0
	MOVLW       48
	MOVWF       R13, 0
L_main5:
	DECFSZ      R13, 1, 1
	BRA         L_main5
	DECFSZ      R12, 1, 1
	BRA         L_main5
	NOP
;projetoFinal.c,61 :: 		PORTD = ucMask[uiValor%10];
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        _uiValor+0, 0 
	MOVWF       R0 
	MOVF        _uiValor+1, 0 
	MOVWF       R1 
	CALL        _Div_16X16_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVLW       _ucMask+0
	ADDWF       R0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(_ucMask+0)
	ADDWFC      R1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       PORTD+0 
;projetoFinal.c,62 :: 		PORTA.RA5 = 1;
	BSF         PORTA+0, 5 
;projetoFinal.c,63 :: 		Delay_ms(2);
	MOVLW       6
	MOVWF       R12, 0
	MOVLW       48
	MOVWF       R13, 0
L_main6:
	DECFSZ      R13, 1, 1
	BRA         L_main6
	DECFSZ      R12, 1, 1
	BRA         L_main6
	NOP
;projetoFinal.c,64 :: 		PORTA.RA5 = 0;
	BCF         PORTA+0, 5 
;projetoFinal.c,65 :: 		uiValor/=10;
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        _uiValor+0, 0 
	MOVWF       R0 
	MOVF        _uiValor+1, 0 
	MOVWF       R1 
	CALL        _Div_16X16_U+0, 0
	MOVF        R0, 0 
	MOVWF       _uiValor+0 
	MOVF        R1, 0 
	MOVWF       _uiValor+1 
;projetoFinal.c,66 :: 		PORTD = ucMask[uiValor%10];
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16X16_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVLW       _ucMask+0
	ADDWF       R0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(_ucMask+0)
	ADDWFC      R1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       PORTD+0 
;projetoFinal.c,67 :: 		PORTA.RA4 = 1;
	BSF         PORTA+0, 4 
;projetoFinal.c,68 :: 		Delay_ms(2);
	MOVLW       6
	MOVWF       R12, 0
	MOVLW       48
	MOVWF       R13, 0
L_main7:
	DECFSZ      R13, 1, 1
	BRA         L_main7
	DECFSZ      R12, 1, 1
	BRA         L_main7
	NOP
;projetoFinal.c,69 :: 		PORTA.RA4 = 0;
	BCF         PORTA+0, 4 
;projetoFinal.c,70 :: 		Delay_ms(2);
	MOVLW       6
	MOVWF       R12, 0
	MOVLW       48
	MOVWF       R13, 0
L_main8:
	DECFSZ      R13, 1, 1
	BRA         L_main8
	DECFSZ      R12, 1, 1
	BRA         L_main8
	NOP
;projetoFinal.c,72 :: 		}
	GOTO        L_main0
;projetoFinal.c,73 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
