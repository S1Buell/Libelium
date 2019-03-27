/* 
 * File:   LoRaWanCore.c
 * Author: C0485763
 *
 * Created on 24 de Outubro de 2017, 14:00
 * Updated on 02 de Fevereiro de 2019. 10:00
 */

#include "LoRaWanCore.h"
#include "timer.h"
#include <ctype.h>

const char MAC[] = "mac ";
const char MAC_JOIN_OTAA[] = "join otaa";
const char MAC_TX_CNF[] = "tx cnf";
const char MAC_TX_UNCNF[] = "tx uncnf";
const char MAC_SET_CH_STATUS[] = "set ch status";
const char MAC_SET_SF[] = "radio set sf SF";
const char MAC_SET_BW[] = "radio set bw";
const char MAC_SET_ADR[] = "set adr";
const char MAC_GET_ADR[] = "get adr";
const char MAC_SAVE[] = "save";
const char MAC_SET_DR[] = "set dr";
const char MAC_SET_DEVEUI[] = "set deveui";
const char MAC_SET_APPEUI[] = "set appeui";
const char MAC_SET_APPKEY[] = "set appkey";
const char MAC_GET_DNCTR[] = "get dnctr";

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
uint8_t retornaDado (uint8_t dadoByte,uint8_t dadoBit){
    uint8_t selectDado;
    if (dadoBit){
    selectDado = (dadosRecebidos[dadoByte].data >> dadoBit) & 1;  
    }else{
    selectDado = (dadosRecebidos[dadoByte].data) & 1;}
    return selectDado;
}

uint8_t GetDnctr(void){
    char comando[100];
    
    sprintf(comando, "%s", MAC_GET_DNCTR);
    uint8_t status=enviaComando(comando,CMD_MAC);
    return status;
}

bool SetDevEUI(const char *state)
{
    char comando[32];
    sprintf(comando, "%s %s", MAC_SET_DEVEUI, state ); // set deveui 0004a30b001b7476
    uint8_t status=enviaComando(comando,CMD_MAC);
    return (status==MSG_OK);
}
bool SetAppEUI(const char *state)
{
    char comando[32];
    sprintf(comando, "%s %s", MAC_SET_APPEUI, state ); // set appeui 0000000000000000
    uint8_t status=enviaComando(comando,CMD_MAC);
    return (status==MSG_OK);
}
bool SetAppKey(const char *state)
{
    char comando[50];
    sprintf(comando, "%s %s", MAC_SET_APPKEY,state ); // set appkey 55555555555555555555555555555555
    uint8_t status=enviaComando(comando,CMD_MAC);
    return (status==MSG_OK);
}

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
            return (parseLoRaWan()==MSG_OK);
        default:
            return false;
    }
}

bool SetChannelLoRaWan(uint8_t canal, bool ligado)
{
    char comando[25];
    if (ligado)
        sprintf(comando, "%s %d on", MAC_SET_CH_STATUS, canal); // set ch status xx on
    else
        sprintf(comando, "%s %d off", MAC_SET_CH_STATUS, canal); // set ch status xx off
    uint8_t status=enviaComando(comando,CMD_MAC);
    return (status==MSG_OK);
}

bool SetAdr(const char *state){
    char comando[15];
    
    sprintf(comando, "%s %s", MAC_SET_ADR, state); // set adr off
    uint8_t status=enviaComando(comando,CMD_MAC);
    return (status==MSG_OK);
}

bool GetAdr(void){
    char comando[10];
    
    sprintf(comando, "%s", MAC_GET_ADR); // get adr
    uint8_t status=enviaComando(comando,CMD_MAC); 
    return status;
}

bool MacSave(void){
    char comando[7];
    
    sprintf(comando, "%s", MAC_SAVE); // save
    uint8_t status=enviaComando(comando,CMD_MAC);
    return (status==MSG_OK);
}

bool SetSpreadingFactor(uint8_t sf){
    char comando[20];
    
    sprintf(comando, "%s%d", MAC_SET_SF, sf); // radio set sf SF12
    uint8_t status=enviaComando(comando,CMD_MAC);
    return (status==MSG_OK);
}

bool SetBandWidth (uint16_t bw){
    char comando[20];
    
    sprintf(comando, "%s %d", MAC_SET_BW, bw); // radio set bw 500
    uint16_t status=enviaComando(comando,CMD_MAC);
    return (status==MSG_OK);
}

bool DataRate (uint16_t dr){
    char comando[12];
    
    sprintf(comando, "%s %d", MAC_SET_DR, dr); // set dr 15
    uint16_t status=enviaComando(comando,CMD_MAC);
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
        if (i == 2 || i == 3) { // nivel1
            if (retornaDado(1,4) == 1 || nivel1 == 0) {
                continue;}}
        else if (i == 4 || i == 5 ){ // nivel2
            if (retornaDado(1,5) == 1 || nivel2 == 0) {
                continue;}}
       
        else if (i == 9){// Pulsos1 4 bytes
            if((retornaDado(5,0) == 1) || (retornaDado(5,1) == 1) || pulsos1== 0){
                continue;}}
        else if (i == 8){// Pulsos1 2 byte
            if((retornaDado(5,0) == 1) || (retornaDado(5,1) == 1) || pulsos1 == 0){
                continue;}}
        else if (i == 7){// Pulsos1 1 bytes
            if((retornaDado(5,0) == 1) || pulsos1 == 0){
                continue;}}
        else if (i == 6){// Pulsos1 0 bytes
            if((retornaDado(5,0) == 1) && (retornaDado(5,1) == 1) || pulsos1 == 0){
                continue;}}
        
        else if (i == 13){// Pulsos2 4 bytes
            if((retornaDado(5,2) == 1) || (retornaDado(5,3) == 1) || pulsos2 == 0){
                continue;}}
        else if (i == 12){// Pulsos2 2 byte
            if((retornaDado(5,2) == 1) || (retornaDado(5,3) == 1) || pulsos2 == 0){
                continue;}}
        else if (i == 11){// Pulsos2 1 bytes
            if((retornaDado(5,2) == 1) || pulsos2 == 0){
                continue;}}
        else if (i == 10){// Pulsos2 0 bytes
            if((retornaDado(5,2) == 1) && (retornaDado(5,3) == 1) || pulsos2 == 0){
                continue;}}
        
        else if (i == 17){// Pulsos3 4 bytes
            if((retornaDado(5,4) == 1) || (retornaDado(5,5) == 1) || pulsos3 == 0){
                continue;}}
        else if (i == 16){// Pulsos3 2 byte
            if((retornaDado(5,4) == 1) || (retornaDado(5,5) == 1) || pulsos3 == 0){
                continue;}}
        else if (i == 15){// Pulsos3 1 bytes
            if((retornaDado(5,4) == 1) || pulsos3 == 0){
                continue;}}
        else if (i == 14){// Pulsos3 0 bytes
            if((retornaDado(5,4) == 1) && (retornaDado(5,5) == 1) || pulsos3 == 0){
                continue;}}
        
        else if (i == 21){// Pulsos4 4 bytes
            if((retornaDado(5,6) == 1) || (retornaDado(5,7) == 1) || pulsos4 == 0){
                continue;}}
        else if (i == 20){// Pulsos4 2 byte
            if((retornaDado(5,6) == 1) || (retornaDado(5,7) == 1) || pulsos4 == 0){
                continue;}}
        else if (i == 19){// Pulsos4 1 bytes
            if((retornaDado(5,6) == 1) || pulsos4 == 0){
                continue;}}
        else if (i == 18){// Pulsos4 0 bytes
            if((retornaDado(5,6) == 1) && (retornaDado(5,7) == 1) || pulsos4 == 0){
                continue;}}
        
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