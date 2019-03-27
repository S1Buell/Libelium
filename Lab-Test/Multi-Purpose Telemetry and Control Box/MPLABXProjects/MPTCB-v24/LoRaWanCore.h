/* 
 * File:   LoRaWanCore.h
 * Author: 1398236
 *
 * Created on 24 de Outubro de 2017, 14:18
 */
#ifndef LORAWANCORE_H
#define	LORAWANCORE_H

#include "UT.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
#define LF 0x0A
#define CR 0x0D
    
#define MAX_DADOS_RECEBIDOS 10
    
#define MSG_OK                  0
#define MSG_INVALID_PARAM       1
#define MSG_NOT_JOINED          2
#define MSG_NO_FREE_CH          3
#define MSG_SILENT              4
#define MSG_FRAME_COUNTER_ERR   5
#define MSG_BUSY                6
#define MSG_MAC_PAUSED          7
#define MSG_INVALID_DATA_LEN    8
#define MSG_MAC_TX_OK           9
#define MSG_MAC_RX              10
#define MSG_MAC_ERR             11
#define MSG_KEYS_NOT_INIT       12
#define MSG_DENIED              13
#define MSG_ACCEPTED            14
#define MSG_RN2903              15
#define SEM_RESPOSTA            0xFF // TESTE

#define CMD_MAC 0
#define CMD_SYS 1

    
volatile struct
{
    uint8_t port;
    uint8_t data;
} dadosRecebidos[MAX_DADOS_RECEBIDOS];
    
volatile uint8_t responseLoRaWan;
volatile uint8_t tamDadosRecebidos;
volatile uint8_t tamFrame;
volatile bool novaMsgLoRaWan;
const char STATE_ON[] = "on";
const char STATE_OFF[] = "off";

uint8_t retornaDado (uint8_t dadoByte,uint8_t dadoBit);  
uint8_t GetDnctr(void);
bool SetDevEUI();
bool SetAppEUI();
bool SetAppKey();
uint8_t JoinLoRaWan(void);
uint8_t TxLoRaWan(bool conf, uint8_t porta, const uint8_t* data, uint8_t tamData);
uint8_t enviaComando(const char *cmd, uint8_t tipoComando);
uint8_t parseLoRaWan(void);
void initRecebeDados(void);
void recebeByteLoRaWan(int8_t b);
bool SetChannelLoRaWan(uint8_t canal, bool ligado);
bool SetSpreadingFactor(uint8_t sf);
bool MacSave(void);
bool SetAdr(const char *state);
bool GetAdr(void);
bool SetBandWidth (uint16_t bw);
bool DataRate (uint16_t dr);
bool ResetModuloLoRaWan(void);




#ifdef	__cplusplus
}
#endif

#endif	/* LORAWANCORE_H */

