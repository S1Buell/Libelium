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

float le_AD(void)
{
// 979 ---- 20mA
// 195 ---- 4mA
    
//    (AD-195)    (C-4)
//   --------- = -------  => C=(AD-195)*(20-4)/(979-195)+4
//   (979-195)   (20 - 4)

    float corrente;
    
    uint16_t leituraAux;
    uint16_t leitura=0;
    
    for (int i=0;i<32;i++)
    {
        GO_DONE=1;
        NOP();
        while (GO_DONE);
//        verificaUSB();

        leituraAux=ADRESH;
        leituraAux=(leituraAux <<8) | ADRESL;
        leitura+=leituraAux;
        
    }
    
    leitura>>=5;
    
    if (leitura==0)
        corrente=0;
    else
        corrente=((int16_t) leitura-195.0)*16.0/784.0+4.0;
                
    return corrente;
}

