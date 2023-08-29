#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "usart.h"

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT   = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ      20000000

#define _RXB0D0         0b01100110

/*--Prtotype--*/
void CONFIG();
void interrupt rx_uart0(void);

/*--Grobal Variables--*/
char rx_data;
//unsigned char tx_data = '2';
char s[10];
char rx;
int rx_flag = 0;
volatile int i = 0;

void main(void)
{ 
    CONFIG();
    _usart_init();
    __delay_ms(100);
    
    while(1)
    { 
        /*　送信のみ　*/
        //RC6 = 1;
        __delay_ms(1000);
        TXREG = '2';
        //TXREG = 0b00110000;   //ASCII
        while(!TXSTAbits.TRMT);
        
        
        
        /*　送受信　
        while(!RCIF);
        rx_data = RCREG;
        RCIF = 0;
        
         __delay_ms(1000);
        TXREG = rx_data;
        while(!TXSTAbits.TRMT);
        */
       
    }
}

void CONFIG()
{
    OSCCON = 0b01101000;
    ANSEL  = 0b00000000;
    ANSELH = 0b00000000;
    TRISC  = 0b10000000;                                                        //RC7/RXを入力(1)に設定
    TRISA  = 0b00000000;
    PORTA  = 0b00000000;
    PORTC  = 0b00000000;
    
}

/*
void interrupt rx_uart0(void)
{
    if(PIR1bits.RCIF == 1)
    {
        rx = RCREG;
        
        if(rx == '1')
        {
            RA0 = 1;
            RA1 = 1;
            RA2 = 1;
            RA3 = 1;
            __delay_ms(1000);
            RA0 = 0;
            RA1 = 0;
            RA2 = 0;
            RA3 = 0;
        }
        
        
        /*
        RC0 = 1;
        __delay_ms(100);
        RC0 = 0;
        
        
        PIR1bits.RCIF = 0;
         
    }
}
*/