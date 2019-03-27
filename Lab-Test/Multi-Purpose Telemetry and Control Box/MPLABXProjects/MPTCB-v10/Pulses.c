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
    freqPulses=0;
}

uint32_t le_pulsos(void)
{
    CCP1IE=0;
    uint32_t freq=freqPulses;
    //freqPulses=0;  // Não acumula pulsos
    CCP1IE=1;
    return freq;
}

