
_interrupt:

;projetoFinal2.c,50 :: 		void interrupt()
;projetoFinal2.c,52 :: 		Lcd_Init();
	CALL        _Lcd_Init+0, 0
;projetoFinal2.c,53 :: 		Lcd_Cmd(_LCD_CLEAR);
	MOVLW       1
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;projetoFinal2.c,54 :: 		Lcd_Cmd(_LCD_CURSOR_OFF);
	MOVLW       12
	MOVWF       FARG_Lcd_Cmd_out_char+0 
	CALL        _Lcd_Cmd+0, 0
;projetoFinal2.c,56 :: 		if(INTCON.TMR0IF == 1)
	BTFSS       INTCON+0, 2 
	GOTO        L_interrupt0
;projetoFinal2.c,58 :: 		TMR0H = 0xDB;
	MOVLW       219
	MOVWF       TMR0H+0 
;projetoFinal2.c,59 :: 		TMR0L = 0x61;
	MOVLW       97
	MOVWF       TMR0L+0 
;projetoFinal2.c,61 :: 		ucContador++;
	INCF        _ucContador+0, 1 
;projetoFinal2.c,63 :: 		if(ucContador == 16)
	MOVF        _ucContador+0, 0 
	XORLW       16
	BTFSS       STATUS+0, 2 
	GOTO        L_interrupt1
;projetoFinal2.c,65 :: 		Delay_ms(1000);
	MOVLW       11
	MOVWF       R11, 0
	MOVLW       38
	MOVWF       R12, 0
	MOVLW       93
	MOVWF       R13, 0
L_interrupt2:
	DECFSZ      R13, 1, 1
	BRA         L_interrupt2
	DECFSZ      R12, 1, 1
	BRA         L_interrupt2
	DECFSZ      R11, 1, 1
	BRA         L_interrupt2
	NOP
	NOP
;projetoFinal2.c,66 :: 		Display_LCD();
	CALL        _Display_LCD+0, 0
;projetoFinal2.c,67 :: 		for(ucContador = 2; ucContador < 15; ucContador ++)
	MOVLW       2
	MOVWF       _ucContador+0 
L_interrupt3:
	MOVLW       15
	SUBWF       _ucContador+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_interrupt4
;projetoFinal2.c,69 :: 		Lcd_Chr(2,ucContador+1,EEPROM_Read(ucContador));
	MOVF        _ucContador+0, 0 
	MOVWF       FARG_EEPROM_Read_address+0 
	CALL        _EEPROM_Read+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_Lcd_Chr_out_char+0 
	MOVLW       2
	MOVWF       FARG_Lcd_Chr_row+0 
	MOVF        _ucContador+0, 0 
	ADDLW       1
	MOVWF       FARG_Lcd_Chr_column+0 
	CALL        _Lcd_Chr+0, 0
;projetoFinal2.c,67 :: 		for(ucContador = 2; ucContador < 15; ucContador ++)
	INCF        _ucContador+0, 1 
;projetoFinal2.c,70 :: 		}
	GOTO        L_interrupt3
L_interrupt4:
;projetoFinal2.c,71 :: 		ucContador = 0;
	CLRF        _ucContador+0 
;projetoFinal2.c,72 :: 		}
	GOTO        L_interrupt6
L_interrupt1:
;projetoFinal2.c,75 :: 		iLeituraAD = ADC_Read(2);
	MOVLW       2
	MOVWF       FARG_ADC_Read_channel+0 
	CALL        _ADC_Read+0, 0
	MOVF        R0, 0 
	MOVWF       _iLeituraAD+0 
	MOVF        R1, 0 
	MOVWF       _iLeituraAD+1 
;projetoFinal2.c,76 :: 		iLeituraAD /= 2;
	MOVF        R0, 0 
	MOVWF       _iLeituraAD+0 
	MOVF        R1, 0 
	MOVWF       _iLeituraAD+1 
	RRCF        _iLeituraAD+1, 1 
	RRCF        _iLeituraAD+0, 1 
	BCF         _iLeituraAD+1, 7 
;projetoFinal2.c,77 :: 		Lcd_Out(1,1,"Registrando");
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       ?lstr1_projetoFinal2+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(?lstr1_projetoFinal2+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;projetoFinal2.c,78 :: 		temp = iLeituraAD;
	MOVF        _iLeituraAD+0, 0 
	MOVWF       _temp+0 
	MOVF        _iLeituraAD+1, 0 
	MOVWF       _temp+1 
;projetoFinal2.c,79 :: 		EEPROM_Write(ucContador,0x30+(temp%10));
	MOVF        _ucContador+0, 0 
	MOVWF       FARG_EEPROM_Write_address+0 
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        _iLeituraAD+0, 0 
	MOVWF       R0 
	MOVF        _iLeituraAD+1, 0 
	MOVWF       R1 
	CALL        _Div_16X16_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVF        R0, 0 
	ADDLW       48
	MOVWF       FARG_EEPROM_Write_data_+0 
	CALL        _EEPROM_Write+0, 0
;projetoFinal2.c,80 :: 		temp /= 10;
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        _temp+0, 0 
	MOVWF       R0 
	MOVF        _temp+1, 0 
	MOVWF       R1 
	CALL        _Div_16X16_U+0, 0
	MOVF        R0, 0 
	MOVWF       _temp+0 
	MOVF        R1, 0 
	MOVWF       _temp+1 
;projetoFinal2.c,81 :: 		ucContador++;
	INCF        _ucContador+0, 1 
;projetoFinal2.c,82 :: 		EEPROM_Write(ucContador+1,0x30+(temp%10));
	MOVF        _ucContador+0, 0 
	ADDLW       1
	MOVWF       FARG_EEPROM_Write_address+0 
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16X16_U+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVF        R0, 0 
	ADDLW       48
	MOVWF       FARG_EEPROM_Write_data_+0 
	CALL        _EEPROM_Write+0, 0
;projetoFinal2.c,83 :: 		ucContador++;
	INCF        _ucContador+0, 1 
;projetoFinal2.c,84 :: 		}
L_interrupt6:
;projetoFinal2.c,86 :: 		INTCON.TMR0IF = 0;       // Limpa o flag de estouro do timer0 para uma nova contagem de tempo.
	BCF         INTCON+0, 2 
;projetoFinal2.c,88 :: 		}
L_interrupt0:
;projetoFinal2.c,89 :: 		}
L_end_interrupt:
L__interrupt10:
	RETFIE      1
; end of _interrupt

_main:

;projetoFinal2.c,92 :: 		void main(){
;projetoFinal2.c,94 :: 		TRISC.RC5 = 0;
	BCF         TRISC+0, 5 
;projetoFinal2.c,95 :: 		PORTC.RC5 = 1;
	BSF         PORTC+0, 5 
;projetoFinal2.c,96 :: 		ADCON1 = 0x0F;
	MOVLW       15
	MOVWF       ADCON1+0 
;projetoFinal2.c,98 :: 		T0CON.T0CS = 0;
	BCF         T0CON+0, 5 
;projetoFinal2.c,99 :: 		T0CON.PSA = 0;
	BCF         T0CON+0, 3 
;projetoFinal2.c,100 :: 		T0CON.T0PS2 = 1;
	BSF         T0CON+0, 2 
;projetoFinal2.c,101 :: 		T0CON.T0PS1 = 1;
	BSF         T0CON+0, 1 
;projetoFinal2.c,102 :: 		T0CON.T0PS0 = 0;
	BCF         T0CON+0, 0 
;projetoFinal2.c,103 :: 		T0CON.T08BIT = 0;
	BCF         T0CON+0, 6 
;projetoFinal2.c,105 :: 		TMR0H = 0xDB;
	MOVLW       219
	MOVWF       TMR0H+0 
;projetoFinal2.c,106 :: 		TMR0L = 0x61;
	MOVLW       97
	MOVWF       TMR0L+0 
;projetoFinal2.c,107 :: 		INTCON.TMR0IE = 1;
	BSF         INTCON+0, 5 
;projetoFinal2.c,108 :: 		INTCON.TMR0IF = 0;
	BCF         INTCON+0, 2 
;projetoFinal2.c,109 :: 		T0CON.TMR0ON = 1;
	BSF         T0CON+0, 7 
;projetoFinal2.c,110 :: 		INTCON.GIE = 1;
	BSF         INTCON+0, 7 
;projetoFinal2.c,111 :: 		INTCON.PEIE = 1;
	BSF         INTCON+0, 6 
;projetoFinal2.c,112 :: 		TRISB.RB0=1;
	BSF         TRISB+0, 0 
;projetoFinal2.c,113 :: 		TRISB.RB1=1;
	BSF         TRISB+0, 1 
;projetoFinal2.c,115 :: 		Grava_RTC();
	CALL        _Grava_RTC+0, 0
;projetoFinal2.c,117 :: 		while(1)
L_main7:
;projetoFinal2.c,119 :: 		Leitura_RTC();
	CALL        _Leitura_RTC+0, 0
;projetoFinal2.c,121 :: 		}
	GOTO        L_main7
;projetoFinal2.c,123 :: 		}
L_end_main:
	GOTO        $+0
; end of _main

_Converte_BCD:

;projetoFinal2.c,125 :: 		void Converte_BCD(unsigned char ucLinha, unsigned char ucColuna,unsigned char ucValor) {
;projetoFinal2.c,128 :: 		ucValor1 = (ucValor >> 4  ) + '0';
	MOVF        FARG_Converte_BCD_ucValor+0, 0 
	MOVWF       FARG_Lcd_Chr_out_char+0 
	RRCF        FARG_Lcd_Chr_out_char+0, 1 
	BCF         FARG_Lcd_Chr_out_char+0, 7 
	RRCF        FARG_Lcd_Chr_out_char+0, 1 
	BCF         FARG_Lcd_Chr_out_char+0, 7 
	RRCF        FARG_Lcd_Chr_out_char+0, 1 
	BCF         FARG_Lcd_Chr_out_char+0, 7 
	RRCF        FARG_Lcd_Chr_out_char+0, 1 
	BCF         FARG_Lcd_Chr_out_char+0, 7 
	MOVLW       48
	ADDWF       FARG_Lcd_Chr_out_char+0, 1 
;projetoFinal2.c,129 :: 		Lcd_Chr(ucLinha,ucColuna,ucValor1);
	MOVF        FARG_Converte_BCD_ucLinha+0, 0 
	MOVWF       FARG_Lcd_Chr_row+0 
	MOVF        FARG_Converte_BCD_ucColuna+0, 0 
	MOVWF       FARG_Lcd_Chr_column+0 
	CALL        _Lcd_Chr+0, 0
;projetoFinal2.c,130 :: 		ucValor2 = (ucValor & 0x0F) + '0';
	MOVLW       15
	ANDWF       FARG_Converte_BCD_ucValor+0, 0 
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	MOVLW       48
	ADDWF       FARG_Lcd_Chr_CP_out_char+0, 1 
;projetoFinal2.c,131 :: 		Lcd_Chr_CP(ucValor2);
	CALL        _Lcd_Chr_CP+0, 0
;projetoFinal2.c,132 :: 		}
L_end_Converte_BCD:
	RETURN      0
; end of _Converte_BCD

_Leitura_RTC:

;projetoFinal2.c,134 :: 		void Leitura_RTC()
;projetoFinal2.c,136 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;projetoFinal2.c,137 :: 		I2C1_Wr(0xD0);
	MOVLW       208
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;projetoFinal2.c,138 :: 		I2C1_Wr(0);
	CLRF        FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;projetoFinal2.c,139 :: 		I2C1_Repeated_Start();
	CALL        _I2C1_Repeated_Start+0, 0
;projetoFinal2.c,140 :: 		I2C1_Wr(0xD1);
	MOVLW       209
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;projetoFinal2.c,141 :: 		ucSegundo = I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       _ucSegundo+0 
;projetoFinal2.c,142 :: 		ucMinuto = I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       _ucMinuto+0 
;projetoFinal2.c,143 :: 		ucHora = I2C1_Rd(1);
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVF        R0, 0 
	MOVWF       _ucHora+0 
;projetoFinal2.c,144 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;projetoFinal2.c,145 :: 		}
L_end_Leitura_RTC:
	RETURN      0
; end of _Leitura_RTC

_Grava_RTC:

;projetoFinal2.c,147 :: 		void Grava_RTC()
;projetoFinal2.c,149 :: 		I2C1_Init(100000);
	MOVLW       20
	MOVWF       SSPADD+0 
	CALL        _I2C1_Init+0, 0
;projetoFinal2.c,150 :: 		I2C1_Start();
	CALL        _I2C1_Start+0, 0
;projetoFinal2.c,151 :: 		I2C1_Wr(0xD0);
	MOVLW       208
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;projetoFinal2.c,152 :: 		I2C1_Wr(0);
	CLRF        FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;projetoFinal2.c,153 :: 		I2C1_Wr(0x04);
	MOVLW       4
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;projetoFinal2.c,154 :: 		I2C1_Wr(0x12);
	MOVLW       18
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;projetoFinal2.c,155 :: 		I2C1_Wr(0x09);
	MOVLW       9
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;projetoFinal2.c,156 :: 		I2C1_Wr(0x03);
	MOVLW       3
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;projetoFinal2.c,157 :: 		I2C1_Wr(0x22);
	MOVLW       34
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;projetoFinal2.c,158 :: 		I2C1_Wr(0x06);
	MOVLW       6
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;projetoFinal2.c,159 :: 		I2C1_Wr(0x17);
	MOVLW       23
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
;projetoFinal2.c,160 :: 		I2C1_Stop();
	CALL        _I2C1_Stop+0, 0
;projetoFinal2.c,161 :: 		}
L_end_Grava_RTC:
	RETURN      0
; end of _Grava_RTC

_Display_LCD:

;projetoFinal2.c,163 :: 		void Display_LCD()
;projetoFinal2.c,166 :: 		Lcd_Out(1,1,"(Hora)");
	MOVLW       1
	MOVWF       FARG_Lcd_Out_row+0 
	MOVLW       1
	MOVWF       FARG_Lcd_Out_column+0 
	MOVLW       ?lstr2_projetoFinal2+0
	MOVWF       FARG_Lcd_Out_text+0 
	MOVLW       hi_addr(?lstr2_projetoFinal2+0)
	MOVWF       FARG_Lcd_Out_text+1 
	CALL        _Lcd_Out+0, 0
;projetoFinal2.c,167 :: 		Converte_BCD(1,7,ucHora);
	MOVLW       1
	MOVWF       FARG_Converte_BCD_ucLinha+0 
	MOVLW       7
	MOVWF       FARG_Converte_BCD_ucColuna+0 
	MOVF        _ucHora+0, 0 
	MOVWF       FARG_Converte_BCD_ucValor+0 
	CALL        _Converte_BCD+0, 0
;projetoFinal2.c,168 :: 		Lcd_Chr_CP(':');
	MOVLW       58
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	CALL        _Lcd_Chr_CP+0, 0
;projetoFinal2.c,169 :: 		Converte_BCD(1,10,ucMinuto);
	MOVLW       1
	MOVWF       FARG_Converte_BCD_ucLinha+0 
	MOVLW       10
	MOVWF       FARG_Converte_BCD_ucColuna+0 
	MOVF        _ucMinuto+0, 0 
	MOVWF       FARG_Converte_BCD_ucValor+0 
	CALL        _Converte_BCD+0, 0
;projetoFinal2.c,170 :: 		Lcd_Chr_CP(':');
	MOVLW       58
	MOVWF       FARG_Lcd_Chr_CP_out_char+0 
	CALL        _Lcd_Chr_CP+0, 0
;projetoFinal2.c,171 :: 		Converte_BCD(1,13,ucSegundo);
	MOVLW       1
	MOVWF       FARG_Converte_BCD_ucLinha+0 
	MOVLW       13
	MOVWF       FARG_Converte_BCD_ucColuna+0 
	MOVF        _ucSegundo+0, 0 
	MOVWF       FARG_Converte_BCD_ucValor+0 
	CALL        _Converte_BCD+0, 0
;projetoFinal2.c,172 :: 		}
L_end_Display_LCD:
	RETURN      0
; end of _Display_LCD
