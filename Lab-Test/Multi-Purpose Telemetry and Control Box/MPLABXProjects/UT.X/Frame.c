/* 
 * File:   XBeeCore.h
 * Author: C0485763
 *
 * Created on 03 de Agosto de 2017, 15:00
 */

#include "Frame.h"


void createFrame(const char* ID)
{
    sprintf(frameBuffer, "<=>\x80N#%ld#%s#%d#" , ID_DEVICE, ID, numPacote++);
    frameBuffer[4]=0;
}

void addSensorStr(const char* sensor,const char* str)
{
    char f[30];
    frameBuffer[4]++;
    sprintf(f, "%s:%s#", sensor, str);
    strcat(frameBuffer, (const char*) f);
}

void addSensorInt(const char* sensor,uint32_t num)
{
    char f[30];
    frameBuffer[4]++;
    sprintf(f, "%s:%lu#", sensor, num);
    strcat(frameBuffer, (const char*) f);
}

void addSensorFloat(const char* sensor,float num)
{
    char f[30];
    frameBuffer[4]++;
    sprintf(f, "%s:%f#", sensor, num);
    strcat(frameBuffer, (const char*) f);
}


