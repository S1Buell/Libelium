/* 
 * File:   uart.c
 * Author: C0485763
 *
 * Created on 28 de Julho de 2017, 12:16
 */

#include "uart.h"

/*
 * 
 */
void setup_uart(uint32_t baudRate)
{
    uint32_t brg;

    PORTCbits.RC6=1;
    TRISCbits.RC6=0;
    
    PORTCbits.RC7=1;
    TRISCbits.RC7=1;

    TXSTAbits.BRGH=1;
    BAUDCONbits.BRG16=1;
    brg = ((_XTAL_FREQ*10/4)/(baudRate)-5);
    brg /= 10;
    SPBRG=(uint8_t)brg;
    SPBRGH=(uint8_t)(brg >> 8);

    TXSTAbits.SYNC=0;
    TXSTAbits.SENDB=0;
    RCSTAbits.SPEN=1;
    
    BAUDCONbits.TXCKP=0;
    BAUDCONbits.RXDTP=0;
    BAUDCONbits.ABDEN=0;
    TXSTAbits.TX9=0;
    RCSTAbits.RX9=0;
    
    RCSTAbits.CREN=1;
    TXSTAbits.TXEN=1;
    
    RCIE=1;
}

void putch(char data)
{
    while (!TXIF);
    TXREG=data;
}

char getch(void)
{
    uint8_t RC;
    char data;
    
    if (!RCIF)
        return 0;
    
    RC=RCSTA;
    data=RCREG;
    
    //if ((RCSTAbits.FERR) || (RCSTAbits.OERR))
    if ((RC & 0x06)!=0)
    {
        RCSTAbits.CREN=0;
        NOP();
        RCSTAbits.CREN=1;
    }
    
    return data;
}

 __bit kbhit(void)
 {
    return RCIF;
 }
 
 void flush(void)
 {
     while (kbhit())
         getch();
 }
 