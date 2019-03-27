/* 
 * File:   eeprom.h
 * Author: 1398236
 *
 * Created on 28 de Fevereiro de 2018, 10:12
 */

#ifndef EEPROM_H
#define	EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

void writeEeprom(uint8_t end, uint8_t b);
uint8_t readEeprom(uint8_t end);
void gravaDadosEeprom(void);
void retornaDadosEeprom(void);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_H */

