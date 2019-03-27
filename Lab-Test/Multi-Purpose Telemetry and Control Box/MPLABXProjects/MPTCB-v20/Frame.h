/* 
 * File:   Frame.h
 * Author: C0485763
 *
 * Created on 3 de Agosto de 2017, 15:08
 */

#ifndef FRAME_H
#define	FRAME_H

#include "UT.h"

#ifdef	__cplusplus
extern "C" {
#endif

char frameBuffer[300];

void createFrameHeader(const char* WaspID, uint8_t Sequencia);
void addSensorStr(const char* sensor,const char* str);
void addSensorInt(const char* sensor,uint32_t num);
void addSensorFloat(const char* sensor,float num);
void addSensor(const char* sensor, uint8_t nivel1, uint8_t nivel2);
void addValue(uint8_t value, uint8_t type);
//void addSensorPulso(const char* sensor, uint32_t pulso1,uint32_t pulso2, uint32_t pulso3, uint32_t pulso4);

uint8_t NumOfFields=1;
#ifdef	__cplusplus
}
#endif

#endif	/* FRAME_H */

