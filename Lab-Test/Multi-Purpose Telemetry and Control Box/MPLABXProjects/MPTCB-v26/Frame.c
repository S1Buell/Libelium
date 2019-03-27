/* 
 * File:   XBeeCore.h
 * Author: C0485763
 *
 * Created on 03 de Agosto de 2017, 15:00
 */

#include "Frame.h"
//uint8_t frame[] = {'<','=','>',128,1,'#','1','4','2','#','t','e','s','t','e','a','u','g','u','s','t','o','#','2','0','0','#','T','C','A',':','2','8','#'}; //Testar com calma
//-------------------------------------------------Frame format-----------------------------------------------------
// |     |             |                  |   |           |   |             |   |          |   |           |   |           |   |     |            |   |
// | <=> | Frame type  | Number of fields | # | Serial ID | # | Waspmote ID | # | Sequence | # | Sensor_1  | # | Sensor_2  | # | ... | Sensor_n   | # |
// |     |             |                  |   |           |   |             |   |          |   | TC:95     |   | SOIL_C:22 |   |     | SOIL_F: 10 |   |

void createFrameHeader(const char* WaspID, uint8_t Sequencia)
{   
    sprintf(frameBuffer, "<=>\x80N#%ld#%s#%u#", SerialID, WaspID, Sequencia);
    frameBuffer[4]=0;
}

void addSensorNivel(const char* sensor, uint16_t nivel1,uint16_t nivel2)
{
    frameBuffer[4]++;
    char f[18];
    sprintf(f,"%s:%u;%u#", sensor,nivel1,nivel2);
    strcat(frameBuffer, (const char*) f);
}
void addSensorPulso(const char* sensor, uint32_t pulso1,uint32_t pulso2, uint32_t pulso3, uint32_t pulso4)
{
    frameBuffer[4]++;
    char f[50];
    sprintf(f, "%s:%lu;%lu;%lu;%lu#",sensor, pulso1, pulso2, pulso3, pulso4);
    strcat(frameBuffer, (const char*) f);
}
void addSensorStr(const char* sensor,const char* str)
{
    char f[30];
    frameBuffer[4]++;
    sprintf(f, "%s:%s#", sensor, str);
    strcat(frameBuffer, (const char*)f);
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
    //strcat(frameBuffer,  f);
}
void sendError(const char* WaspID,const char* name, uint8_t codeError)
{
    
    memset(frameBuffer, 0, 255);
    createFrameHeader(WaspID,0);
    char f[30];
    frameBuffer[4]++;
    sprintf(f, "%s:%d#", name, codeError);
    strcat(frameBuffer, (const char*) f);
}

