/*
 * File:   EEPROM.c
 * Author: 1622812
 *
 * Created on January 21, 2019, 2:12 PM
 */

#include "EEPROM.h"
void WriteEEPROM(uint8_t address, uint8_t data)
{
   EEADR = (address & 0x0ff); // Segura o endereço da localização da eeprom que esta sendo acessada
   EEDATA = data; // Segura 8bits data para read/write    
   EECON1bits.EEPGD = 0; // Acessa os dados da memoria EEPROM
   EECON1bits.CFGS = 0; // Acessa os dados da memoria EEPROM 
   EECON1bits.WREN = 1; // Permite escrita na EEPROM   
   INTCONbits.GIE = 0; // Desabilita interrupts que são criticos para escrita da EEPROM
   EECON2 = 0x55;     
   EECON2 = 0xAA;     
   EECON1bits.WR = 1; // Inicializa a escrita/apaga os dados na eeprom
   while(EECON1bits.WR); // Escreve na EEPROM até que a escrita se complete
   INTCONbits.GIE = 1; // Habilita interrupts que são criticos para escrita da EEPROM   
   EECON1bits.WREN = 0; //Desabilita escrita na EEPROM  
}

uint8_t ReadEEPROM( uint8_t address ) 
{     
   EEADR = (address & 0x0ff);       
   EECON1bits.CFGS = 0;     
   EECON1bits.EEPGD = 0;     
   EECON1bits.RD = 1;     
   return ( EEDATA ); // return with read byte
}