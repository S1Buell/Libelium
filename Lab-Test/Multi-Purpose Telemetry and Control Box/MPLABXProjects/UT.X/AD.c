/* 
 * File:   XBeeCore.h
 * Author: C0485763
 *
 * Created on 03 de Agosto de 2017, 17:00
 */

#include "AD.h"

void setup_AD(void)
{
    ADON=0;
    ADCON1=0b00001110; // AN0 Analógico
    ADCON0=0b00000000;
    ADCON2=0b10111110; // TAD=20 e ADC=Fosc/64
    ADON=1;
    ADIF=0;
    ADIE=0;
}
/*
float le_AD(void)
{
// 979 ---- 20mA
// 195 ---- 4mA
    
//    (AD-195)    (C-4)
//   --------- = -------  => C=(AD-195)*(20-4)/(979-195)+4
//   (979-195)   (20 - 4)

    float corrente;
    
    uint16_t leituraAux;
    uint32_t leitura=0;
    
    for (int i=0;i<128;i++)
    {
        GO_DONE=1;
        NOP();
        while (GO_DONE);

        leituraAux=ADRESH;
        leituraAux=(leituraAux << 8) | ADRESL;
        leitura+=leituraAux;
        
    }
    
    leitura>>=7;
    
    if (leitura==0)
        corrente=0;
    else
        corrente=((int16_t) leitura-195.0)*16.0/784.0+4.0;
                
    return corrente;
}
*/


uint16_t leAD(void)
{
// 979 ---- 20mA
// 195 ---- 4mA
    
//    (AD-195)    (C-4)
//   --------- = -------  => C=(AD-195)*(20-4)/(979-195)+4
//   (979-195)   (20 - 4)

   
    uint16_t leituraAux;
    uint32_t leitura=0;
    
    for (uint16_t i=0;i<1024;i++)
    {
        GO_DONE=1;
        NOP();
        while (GO_DONE);

        leituraAux=ADRESH;
        leituraAux=(leituraAux << 8) | ADRESL;
        leitura+=leituraAux;
        
    }
    
    leitura>>=10;
                
    return leitura;
}

float le4a20(void)
{
    float corrente;
    uint32_t to=millis();
    uint32_t ad = 0;
    uint8_t cnt = 0;
    //verificaUSB();
    while ((millis()-to)<1000)
    {
        ad += leAD();
        cnt++;
        //verificaUSB();
        __delay_ms(10);
    }
    if (ad==0)
        return 0.00;
    
    corrente = ad / (float)cnt;
    corrente=(corrente-195.0)*16.0/784.0+4.0;
    
    return corrente;
    
}

