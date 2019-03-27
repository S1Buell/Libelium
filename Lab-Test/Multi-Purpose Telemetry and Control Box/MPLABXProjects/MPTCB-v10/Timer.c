/* 
 * File:   uart.c
 * Author: C0485763
 *
 * Created on 31 de Julho de 2017, 16:00
 */


#include "Timer.h"

void setup_timer1(void)
{
    T1CON=0b11110001;
    ticks=0;
    TMR1IE=1;
    GIEH = 1;
}

void setup_timer0(void)
{
    T0CON=0b10000100;  // Prescaler 32 / 16-bits
    ticks=0;
    TMR0IE=1;
    GIEH = 1;
}

void setup_ccp1(void)
{
    GIEH = 0;
    T3CON=0b10111000; // CCP1 no TIMER1
    TMR1H=0x00;
    TMR1L=0x00;
    CCPR1H=0x05;
    CCPR1L=0xDC;
    ticks=0;
    
    CCP1IF=0;
    T1CON=0b11110001; //    Prescale 8
    CCP1CON = 0b00001011;
    CCP1IE=1;
    IPR1bits.CCP1IP=1;
    RCONbits.IPEN = 1;
    GIEH = 1;
}


uint32_t millis()
{
    CCP1IE=0;
    uint32_t m=ticks;
    CCP1IE=1;
   
    return m;
}

