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

char frameBuffer[200];

void createFrameHeader(const char* ID);
void addSensorStr(const char* sensor,const char* str);
void addSensorInt(const char* sensor,uint32_t num);
void addSensorFloat(const char* sensor,float num);

uint8_t numPacote=0;

#ifdef	__cplusplus
}
#endif

#endif	/* FRAME_H */

