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

#define SerialID 100000001U
#define FrameType 128

//#define CONVERSOR_RS232
//#define LORAWAN
#define XBEE

#define TEMPO_TRANSMISSAO   30000 // em milisegundos

#ifdef XBEE
uint8_t panID[2] = {0x7F,0xFF}; // Gateway telhado
//char RX_ADDRESS[] = "0013A20041741FA7"; // EMWQ_1
char RX_ADDRESS[] = "0013A200410ACE69"; // modem azul
//char RX_ADDRESS[] = "0013A200416463E2"; // Gateway CPD
//char RX_ADDRESS[] = "0013A200418977FD"; // Vitor1
//FFFFFFFE00000FFF
uint8_t Mask[8] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xF7,0xFF,0xC0}; // Gateway CPD
uint8_t preambleID = 0;
bool encryptEnable = true;
const char encryptKey[] = "M6j3b456IIOTKey!"; // Gateway telhado 4d366a336234353649494f544b657921


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

