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

void createFrameHeader(const char* ID)
{
    //sprintf(frameBuffer, "<=>\x80N#%ld#%s#%d#" , ID_DEVICE, ID, numPacote++);
    //sprintf(frameBuffer, "<=>\x80N#%ld#%s#%d#" , ID_DEVICE, ID, numPacote++);
    sprintf(frameBuffer, "%x%x", 0,0);
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


