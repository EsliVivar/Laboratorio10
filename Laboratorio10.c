/* 
 * File:   Laboratorio10.c
 * Author: Esli Vivar. 
 *Descripcion:Realice una subrutina que envíe una cadena de caracteres utilizando la
comunicación serial.

 */

// Configuracion 1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <stdint.h>  // Para poder usar los int de 8 bits

#define _XTAL_FREQ 1000000
 

void pal(char txt[]);
void setup(void);

void __interrupt() isr (void){
    if(PIR1bits.RCIF){          // Hay datos recibidos?
       PORTB = RCREG;     // Mostramos valor recibido en el PORTD
    }
    return;
}

void main(void) {
   
    setup();
    while(1){
    pal("Hola ");
    pal("mundo, ");
    pal("soy ");
    pal("Esli ");
     }
}

void setup(void){
    ANSEL = 0;
    ANSELH = 0;                 // I/O digitales
    
    TRISB = 0;
    PORTB = 0;                  // PORTD como salida
    
    OSCCONbits.IRCF = 0b100;    // 1MHz
    OSCCONbits.SCS = 1;         // Oscilador interno
    TXSTAbits.SYNC = 0;         // Comunicación ascincrona (full-duplex)
    TXSTAbits.BRGH = 1;         // Baud rate de alta velocidad 
    BAUDCTLbits.BRG16 = 1;      // 16-bits para generar el baud rate
    
    SPBRG = 25;
    SPBRGH = 0;                 // Baud rate ~9600, error -> 0.16%
    
    RCSTAbits.SPEN = 1;         // Habilitamos comunicación
    TXSTAbits.TX9 = 0;          // Utilizamos solo 8 bits
    TXSTAbits.TXEN = 1;         // Habilitamos transmisor
    RCSTAbits.CREN = 1;         // Habilitamos receptor
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones globales
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones de perifericos
    PIE1bits.RCIE = 1;          // Habilitamos Interrupciones de recepción
}

void pal(char txt[]){
    uint8_t i=0;
        while(txt[i]!=' '){                 // Incrementamos indice para enviar sigiente caracter
            TXREG = txt[i];    // Cargamos caracter a enviar
            i++;
            __delay_ms(100);
            } 
        return;
    
       
}