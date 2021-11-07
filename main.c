#pragma config DEBUG = 1
#pragma config LVP = 0
#pragma config FCMEN = 0
#pragma config IESO = 0
#pragma config BOREN = 00
#pragma config CPD = 0
#pragma config CP = 0
#pragma config MCLRE = 0
#pragma config PWRTE = 1
#pragma config WDTE = 0
#pragma config FOSC = 101

#include <stdint.h>
#include "lcd.h"
#include "keypad.h"

#define TMR1H_VAL 0x9E
#define TMR1L_VAL 0x57

uint16_t centi_seconds = 0;
uint8_t counter = 0;
uint16_t interval = 0;

void main(void) {
    OSCCON = 0x70;
    while (OSCCONbits.HTS == 0);
    
    TRISC = 0x00;
    T2CON = 0x00;
    PR2 = 0x65;
    CCP1CON = 0x0C;
    CCPR1L = 0x80;
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.TMR1IE = 1;
    PIE1bits.TMR2IE = 1;
    
    
    lcd_init(true, false, false);
    lcd_write_string("Tiempo arranque:");
    lcd_move_cursor(0x47);
    
    keypad_init();
    
    while (1);
}

void __interrupt() handle_interrupt() {
    if (PIR1bits.TMR1IF == 1) {
        T1CONbits.TMR1ON = 0;
        centi_seconds++;
        TMR1H = TMR1H_VAL;
        TMR1L = TMR1L_VAL;
        PIR1bits.TMR1IF = 0;
        T1CONbits.TMR1ON = 1;
    }
}