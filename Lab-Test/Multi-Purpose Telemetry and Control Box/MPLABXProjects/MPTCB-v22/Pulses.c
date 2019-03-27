 /* 
 * File:   XBeeCore.h
 * Author: C0485763
 *
 * Created on 03 de Agosto de 2017, 17:00
 */

#include "Pulses.h"

void setup_pulsos(void)
{
    TRISDbits.RD0=1;
    dig_1=PORTDbits.RD0;
    TRISDbits.RD1=1;
    dig_2=PORTDbits.RD1;
    TRISDbits.RD2=1;
    dig_3=PORTDbits.RD2;
    TRISDbits.RD3=1;
    dig_4=PORTDbits.RD3;
    freqPulses1=0;
    freqPulses2=0;
    freqPulses3=0;
    freqPulses4=0;
}

uint32_t le_pulsos(uint8_t freqPulses, uint8_t modo)
{
    CCP1IE=0;
    uint32_t freq;
    switch(freqPulses){
        case 1:
            freq = freqPulses1;
            if (modo)
                freqPulses1=0;
            break;
        case 2:
            freq = freqPulses2;
            if (modo)
                freqPulses2=0;
            break;
        case 3:
            freq = freqPulses3;
            if (modo)
                freqPulses3=0;
            break;
        case 4:
            freq = freqPulses4;
            if (modo)
                freqPulses4=0;
            break;
    }
    //freqPulses=0;  // Não acumula pulsos
    CCP1IE=1;
    return freq;
}

