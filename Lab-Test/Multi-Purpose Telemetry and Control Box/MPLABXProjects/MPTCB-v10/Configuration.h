/* 
 * File:   Configuration.h
 * Author: 1398236
 *
 * Created on 27 de Outubro de 2017, 13:28
 */

#ifndef CONFIGURATION_H
#define	CONFIGURATION_H
#include <stdint.h>
#include <stdbool.h>


// *************************************************************
// *************** Par�metros de configura��o ******************
// *************************************************************

#define ID_DEVICE 100000001U

//#define CONVERSOR_RS232
#define LORAWAN
//#define XBEE


#define TEMPO_TRANSMISSAO   30000 // em milisegundos

#ifdef XBEE
uint8_t panID[2] = {0x12,0x34}; // Gateway telhado
char RX_ADDRESS[] = "0013A200408DE1A8"; // Gateway telhado
const char encryptKey[] = "ValeiiotLinkKey!"; // Gateway telhado
bool encryptEnable = true;
//uint8_t panID[2] = {0x22,0x22}; // Gateway laborat�rio
//char RX_ADDRESS[] = "0013A200408DE1AF"; // Gateway laborat�rio
//const char encryptKey[] = "ValeTESTE2017SLZ"; // Gateway laborat�rio
//char RX_ADDRESS[] = "000000000000FFFF";  // Broadcast
#endif
// *************************************************************
// *************************************************************
// *************************************************************





#if defined(LORAWAN) && defined(XBEE)
#error "Escolha somente um radio (LORAWAN ou XBEE)"
#endif

#if !defined(LORAWAN) && !defined(XBEE)
#error "Escolha um radio (LORAWAN ou XBEE)"
#endif


#endif	/* CONFIGURATION_H */

