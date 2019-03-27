/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

To request to license the code under the MLA license (www.microchip.com/mla_license), 
please contact mla_licensing@microchip.com
*******************************************************************************/

#ifndef SYSTEM_H
#define SYSTEM_H

#include "UT.h"

//#define _XTAL_FREQ 20000000
#define _XTAL_FREQ 48000000

//***** Configurado para PIC18F4550
#define FIXED_ADDRESS_MEMORY

#define IN_DATA_BUFFER_ADDRESS (USB_BDT_ADDRESS + 0x100)
#define OUT_DATA_BUFFER_ADDRESS (IN_DATA_BUFFER_ADDRESS + CDC_DATA_IN_EP_SIZE)
#define CONTROL_BUFFER_ADDRESS (OUT_DATA_BUFFER_ADDRESS + CDC_DATA_OUT_EP_SIZE)

#define IN_DATA_BUFFER_ADDRESS_TAG @IN_DATA_BUFFER_ADDRESS
#define OUT_DATA_BUFFER_ADDRESS_TAG @OUT_DATA_BUFFER_ADDRESS
#define CONTROL_BUFFER_ADDRESS_TAG @CONTROL_BUFFER_ADDRESS
// *******************************************************

/*** System States **************************************************/
typedef enum
{
    SYSTEM_STATE_USB_START,
    SYSTEM_STATE_USB_SUSPEND,
    SYSTEM_STATE_USB_RESUME
} SYSTEM_STATE;

volatile uint32_t ticks;
volatile uint32_t tempoHorimetro;
volatile bool horimetroLigado;
volatile uint16_t tempoSemVazao;
volatile uint16_t tempoRegistroHorimetro;

volatile uint16_t tempoVazaoInstantanea;
volatile uint32_t freqPulsesAnterior;
volatile uint16_t vazaoInstantanea;



#endif //SYSTEM_H
