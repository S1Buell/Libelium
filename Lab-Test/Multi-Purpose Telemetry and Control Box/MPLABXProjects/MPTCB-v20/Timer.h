/* 
 * File:   Timer.h
 * Author: C0485763
 *
 * Created on 31 de Julho de 2017, 16:27
 */


#ifndef TIMER_H
#define	TIMER_H

#include "UT.h"

#ifdef	__cplusplus
extern "C" {
#endif

void setup_timer1(void);
void setup_timer0(void);
void setup_ccp1(void);
uint32_t millis();
uint8_t aaa;

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

