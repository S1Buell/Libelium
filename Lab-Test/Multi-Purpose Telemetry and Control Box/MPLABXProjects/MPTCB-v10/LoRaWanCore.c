/* 
 * File:   LoRaWanCore.c
 * Author: C0485763
 *
 * Created on 24 de Outubro de 2017, 14:00
 */

#include "LoRaWanCore.h"
#include "timer.h"
#include <ctype.h>

const char MAC[] = "mac ";
const char MAC_JOIN_OTAA[] = "join otaa";
const char MAC_TX_CNF[] = "tx cnf";
const char MAC_TX_UNCNF[] = "tx uncnf";
const char MAC_SET_CH_STATUS[] = "set ch status";

const char SYS[] = "sys ";
const char SYS_RESET[] = "reset";

const char *MSG_LORAWAN[] = 
{
    "ok",                               // 0
    "invalid_param",                    // 1
    "not_joined",                       // 2
    "no_free_ch",                       // 3
    "silent",                           // 4
    "frame_counter_err_rejoin_needed",  // 5
    "busy",                             // 6
    "mac_paused",                       // 7
    "invalid_data_len",                 // 8
    "mac_tx_ok",                        // 9
    "mac_rx ",                          // 10
    "mac_err",                          // 11
    "keys_not_init",                    // 12
    "denied",                           // 13
    "accepted"                          // 14
    "RN2903 "                           // 15
};

bool ResetModuloLoRaWan(void)
{
    uint8_t status;
    
    status=enviaComando(SYS_RESET,CMD_SYS);
    return (status==MSG_RN2903);
}

bool JoinLoRaWan(void)
{
    uint8_t status;
    
    status=enviaComando(MAC_JOIN_OTAA,CMD_MAC);
    switch (status)
    {
        case MSG_OK:
            return (parseLoRaWan()==MSG_ACCEPTED);
        
        default:
            return false;

    }
}

bool SetChannelLoRaWan(uint8_t canal, bool ligado)
{
    char comando[200];
    
    if (ligado)
        sprintf(comando, "%s %d on", MAC_SET_CH_STATUS, canal);
    else
        sprintf(comando, "%s %d off", MAC_SET_CH_STATUS, canal);

    uint8_t status=enviaComando(comando,CMD_MAC);

    return (status==MSG_OK);
}

bool TxLoRaWan(bool conf, uint8_t porta, const uint8_t* data, uint8_t tamData)
{
    char comando[200];
    char hex[4];
    
    if (conf)
        sprintf(comando, "%s %d ", MAC_TX_CNF, porta);
    else
        sprintf(comando, "%s %d ", MAC_TX_UNCNF, porta);

    for (uint8_t i=0;i<tamData;i++)
    {
        sprintf(hex, "%02X", data[i]);
        strcat(comando,hex);
    }
    
    while (true)
    {
        uint8_t status=enviaComando(comando,CMD_MAC);
        switch (status)
        {
            case MSG_OK:
                return (parseLoRaWan()==MSG_MAC_TX_OK);
            case MSG_NOT_JOINED:
            case MSG_FRAME_COUNTER_ERR:
            {
                if (!JoinLoRaWan())
                    return false;
                break;
            }
            case MSG_BUSY:
            {
                if (!ResetModuloLoRaWan())
                    return false;
                break;
            }

            default:
                return false;
        }
    }
    return false;
}


uint8_t enviaComando(const char *cmd, uint8_t tipoComando)
{
    initRecebeDados();
    
    switch (tipoComando)
    {
        case CMD_MAC:
        {
            for (uint16_t i = 0; i < strlen(MAC); i++)
            {
                putch((char)MAC[i]);
            }
        } break;
        case CMD_SYS:
        {
            for (uint16_t i = 0; i < strlen(SYS); i++)
            {
                putch((char)SYS[i]);
            }
        } break;
        
    }
    
    for (uint16_t i = 0; i < strlen(cmd); i++)
	{
        putch((char)cmd[i]);
    }
    putch(CR);
    putch(LF);
    
    return parseLoRaWan();
}

uint8_t parseLoRaWan(void)
{
    uint8_t status=SEM_RESPOSTA;
    uint16_t intervalMAX=60000;
    bool timeout=false;
    uint32_t previous=millis();
    
    while ((!timeout) && (!novaMsgLoRaWan))
    {	
        if ((millis()-previous) > intervalMAX)
        {
			timeout=true;
		}  	  
    }
    
    if (novaMsgLoRaWan)
    {
      status=responseLoRaWan;
      novaMsgLoRaWan=false;
    }
    
    return status;
}

void initRecebeDados(void)
{
    RCIE=0;
    responseLoRaWan=SEM_RESPOSTA;
    tamFrame=0;
    tamDadosRecebidos=0;
    novaMsgLoRaWan=false;
    RCIE=1;
}



void recebeByteLoRaWan(int8_t b)
{
    static uint8_t frameData[MAX_DATA_RECEPCAO];
    
    frameData[tamFrame++]=b;
    if ((b==LF) && (tamFrame>2))
    {
        frameData[tamFrame]=0x00; // TESTE
        strcpy(frameBuffer,frameData); // TESTE
        
        frameData[tamFrame-2]=0x00;
        tamFrame=0;
        uint8_t len = LENGTH(MSG_LORAWAN);
        responseLoRaWan=SEM_RESPOSTA;
        for (uint8_t i=0;i<len;i++)
        {
            if (strcmp(frameData,MSG_LORAWAN[i])==0)
            {
                responseLoRaWan=i;
                novaMsgLoRaWan=true;
                return;
            }
        }

        uint8_t tamMsgRx=strlen(MSG_LORAWAN[MSG_RN2903]);
        if (strncmp(frameData,MSG_LORAWAN[MSG_RN2903],tamMsgRx)==0)
        {
                responseLoRaWan=MSG_RN2903;
                novaMsgLoRaWan=true;
                return;
        }
        
        // mac rx 123 AABBCCDD
        // Verifica recebimento de dados
        tamMsgRx=strlen(MSG_LORAWAN[MSG_MAC_RX]);
        if (strncmp(frameData,MSG_LORAWAN[MSG_MAC_RX],tamMsgRx)==0)
        {
            //responseLoRaWan=MSG_MAC_RX;
            
            uint8_t i=tamMsgRx;
            uint8_t port=0;
            // Le portno do mac_rx
            for (;i<strlen(frameData);i++)
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
        }
    }
    
    if ((tamFrame>=MAX_DATA_RECEPCAO) || (b==LF))
    {
        tamFrame=0;
    }
   
        
}
