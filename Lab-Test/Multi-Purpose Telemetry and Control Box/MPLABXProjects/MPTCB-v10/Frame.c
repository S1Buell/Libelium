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
//Exemplo
void recebeByteLoRaWan(int8_t b)
{
    static uint8_t frameData[MAX_DATA_RECEPCAO]; // frameData[100]
    frameData[tamFrame++]=b; // frameData[100] = {x,x,x,...,x,LF,0}
    if ((b==LF) && (tamFrame>2))
    {
        frameData[tamFrame]=0x00; // frameData[100] = {x,x,x,...,x,LF,0x00}
        strcpy(frameBuffer,frameData); // frameBuffer[200] = {x,x,x,...,x,LF,0x00}
        
        frameData[tamFrame-2]=0x00; // frameData[100] = {x,x,x,...,0x00,LF,0x00}
        tamFrame=0;
		
        uint8_t len = LENGTH(MSG_LORAWAN); // len = 16
        responseLoRaWan=SEM_RESPOSTA; // responseLoRaWan = 0xFF
        for (uint8_t i=0;i<len;i++)
        {
            if (strcmp(frameData,MSG_LORAWAN[i])==0) // mac_tx_ok (ack)
            {
                responseLoRaWan=i; // responseLoRaWan = 9
                novaMsgLoRaWan=true; // novaMsgLoRaWan = 1
                return;
            }
        }
		
        uint8_t tamMsgRx=strlen(MSG_LORAWAN[MSG_RN2903]); // tamMsgRx = 7 ("RN2903 ")
        if (strncmp(frameData,MSG_LORAWAN[MSG_RN2903],tamMsgRx)==0)
        {
                responseLoRaWan=MSG_RN2903; // responseLoRaWan = 15
                novaMsgLoRaWan=true; // novaMsgLoRaWan = 1
                return;
        } 
        // mac rx 123 AABBCCDD
        // Verifica recebimento de dados
        tamMsgRx=strlen(MSG_LORAWAN[MSG_MAC_RX]); //"mac rx " lenght 7
        if (strncmp(frameData,MSG_LORAWAN[MSG_MAC_RX],tamMsgRx)==0)
        {
            //responseLoRaWan=MSG_MAC_RX;
            
            uint8_t i=tamMsgRx;
            uint8_t port=0;
            // Le portno do mac_rx
            for (;i<strlen(frameData);i++) // Ex: mac rx 1 AB
            {
                if ((frameData[i]<'0') || (frameData[i]>'9'))
                    break;
           
                port*=10;
                port+=frameData[i]-'0';
            }
            i++;
            // Le data do mac_rx
            for (;i<strlen(frameData);i+=2)
            {  
                dadosRecebidos[tamDadosRecebidos].port=port;
                dadosRecebidos[tamDadosRecebidos++].data=converter(frameData[i],frameData[i+1]);
                if (tamDadosRecebidos>=MAX_DADOS_RECEBIDOS)
                    return;
            }
            
            if (i>=strlen(frameData)){
                    for (; tamDadosRecebidos<=MAX_DADOS_RECEBIDOS;tamDadosRecebidos++){
                        dadosRecebidos[tamDadosRecebidos].data = 0;
                    }
               }
            
        }
    }
    if ((tamFrame>=MAX_DATA_RECEPCAO) || (b==LF))
    {
        tamFrame=0;
    }      
}

