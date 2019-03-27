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

char frameBuffer[150];

void createFrameHeader(const char* WaspID, uint8_t Sequencia);
void addSensorStr(const char* sensor,const char* str);
void addSensorInt(const char* sensor,uint32_t num);
void addSensorFloat(const char* sensor,float num);
void addSensorNivel(const char* sensor, uint16_t nivel1, uint16_t nivel2);
void addSensorPulso(const char* sensor, uint32_t pulso1,uint32_t pulso2, uint32_t pulso3, uint32_t pulso4);
void sendError(const char* WaspID,const char* name, uint8_t codeError);


#ifdef	__cplusplus
}
#endif

#endif	/* FRAME_H */

