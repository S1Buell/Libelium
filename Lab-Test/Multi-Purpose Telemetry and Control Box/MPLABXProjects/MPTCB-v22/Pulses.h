/* 
 * File:   Pulses.h
 * Author: C0485763
 *
 * Created on 3 de Agosto de 2017, 17:27
 */

#ifndef PULSES_H
#define	PULSES_H

#include "UT.h"

volatile int dig_1,dig_2,dig_3,dig_4;
volatile uint32_t freqPulses1;
volatile uint32_t freqPulses2;
volatile uint32_t freqPulses3;
volatile uint32_t freqPulses4;

#ifdef	__cplusplus
extern "C" {
#endif

void setup_pulsos(void);
uint32_t le_pulsos(uint8_t freqPulses, uint8_t modo);


#ifdef	__cplusplus
}
#endif

#endif	/* PULSES_H */

