/* 
 * File:   AD.h
 * Author: C0485763
 *
 * Created on 3 de Agosto de 2017, 17:18
 */

#ifndef AD_H
#define	AD_H

#include "UT.h"

#ifdef	__cplusplus
extern "C" {
#endif

void setup_AD(void);
float le_AD(uint8_t AnalogPort);


#ifdef	__cplusplus
}
#endif

#endif	/* AD_H */

