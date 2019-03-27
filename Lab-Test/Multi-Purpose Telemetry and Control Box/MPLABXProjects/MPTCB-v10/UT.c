/* 
 * File:   newmain.c
 * Author: C0485763
 *
 * Created on 13 de Julho de 2017, 14:26
 */
#pragma warning disable 520

#include "UT.h"



bool verificaUSB(void)
{
    if ((USBDeviceState == DETACHED_STATE) && (USB_BUS_SENSE == 1))
    {
        USBDeviceAttach();
    }
    else if ((USBDeviceState == ATTACHED_STATE) && (USB_BUS_SENSE != 1))
    {
        USBDeviceDetach();
    }

    if ((USBGetDeviceState() < CONFIGURED_STATE) || (USBIsDeviceSuspended()))
    {
        return false;
    }

    CDCTxService();
    return true;
    
}

void delay(uint32_t time)
{
    uint32_t to=millis();
    while ((millis()-to)<time)
    {
        verificaUSB();
    }    
}



/*
 * 
 */
//int main(int argc, char** argv) {

void main(void) {
    uint8_t pisca=0;
    
    TRISEbits.RE2=0; // Define como saída o pino de led
    PORTDbits.RD4=0;
    TRISDbits.RD4=0; // Define como saída o pino de relé
    
    for (int i=0;i<25;i++)
    {
        pisca ^= 1;
        PORTEbits.RE2 = pisca;
        __delay_ms(200);
    }
#ifdef XBEE
    setup_uart(115200);
#endif    
    
#ifdef LORAWAN    
    setup_uart(57600);
#endif    
    
    USBDeviceInit();
    setup_AD();
    setup_pulsos();
    setup_ccp1();
                
    verificaUSB();
    
#ifdef XBEE
    init_XBee();
    
    setPAN(panID);
    
    setLinkKey(encryptKey);
    setEncryptionMode(encryptEnable);
#endif    
    
#ifdef LORAWAN
    struct
    {
        //uint8_t numPacote;
        uint16_t nivel;
        uint32_t pulsos;
    } dadoPoco;

    //dadoPoco.numPacote=0;
    putch(0x55); //Sync do auto-baud rate
    
    
    // *******************************************************
#ifdef CONVERSOR_RS232
    RCIE=0;
    while (true)
    {
        uint8_t buf[USB_EP0_BUFF_SIZE];

        verificaUSB();
        uint8_t numBytes = getsUSBUSART(buf,USB_EP0_BUFF_SIZE); //until the buffer is free.
        for (int i=0;i<numBytes;i++)
        {
            putch(buf[i]);
        }

        char bufSerial[100];
        uint8_t bytesLidos=0;
        while (kbhit())
        {
            pisca ^= 1;
            PORTEbits.RE2 = pisca;
            if (bytesLidos>=sizeof(bufSerial))
                break;
            bufSerial[bytesLidos++]=getch();
        }

        if (bytesLidos > 0)
        {
            putUSBUSART(bufSerial,bytesLidos);
            while (!USBUSARTIsTxTrfReady())
                verificaUSB();
        }

    }
#endif
    // *******************************************************
    
    uint8_t statusLoRaWan=JoinLoRaWan();
#endif

   
    while (true)
    {
        uint32_t tempo=millis();
        pisca ^= 1;
        PORTEbits.RE2 = pisca;
        
#ifdef XBEE
        createFrame("UT_Poco");
        addSensorFloat("NIVEL",le_AD());
        addSensorInt("LITROS",le_pulsos());
        uint8_t resp=send(RX_ADDRESS, (uint8_t*)frameBuffer, strlen((const char*) frameBuffer));
#endif

#ifdef LORAWAN        
        //dadoPoco.numPacote++;
        dadoPoco.nivel=(uint16_t)(le_AD()*1000.0);
        dadoPoco.pulsos=le_pulsos();
        
        
        for (uint8_t canal=0;canal<8;canal++)
        {
            SetChannelLoRaWan(canal, true);
        }
        for (uint8_t canal=8;canal<72;canal++)
        {
            SetChannelLoRaWan(canal, false);
        }
        SetChannelLoRaWan(64, true);
        
        
        uint8_t resp=TxLoRaWan(true, 1, (const uint8_t*)&dadoPoco, sizeof(dadoPoco)); // Confirmado
        //uint8_t resp=TxLoRaWan(false, 1, (const uint8_t*)&dadoPoco, sizeof(dadoPoco)); // Não confirmado
#endif
        
        
        if (verificaUSB() && USBUSARTIsTxTrfReady())
        {
            /*
            char data[150];
            if (statusLoRaWan)
                sprintf(data,"[%ld] CMD: %sResp: %d\n\r\n\r",millis(),testeUSB,responseLoRaWan);
            else
                sprintf(data,"[%ld] ECMD: %sResp: %d\n\r\n\r",millis(),testeUSB,responseLoRaWan);
            
            //sprintf(data,"resposta: %d %d %2X %2X",responseLoRaWan,dadosRecebidos[tamDadosRecebidos-2].port,dadosRecebidos[tamDadosRecebidos-2].data,dadosRecebidos[tamDadosRecebidos-1].data);
            putsUSBUSART(data);
            */
            putsUSBUSART(frameBuffer);
            
        }
        
            
        uint32_t deltaTempo=(millis()-tempo);
        if (deltaTempo<TEMPO_TRANSMISSAO)
        {
            uint32_t tempoTimeOut=TEMPO_TRANSMISSAO-deltaTempo;
            delay(tempoTimeOut);
        }

        //delay(TEMPO_TRANSMISSAO);
    }
    return;
}





/*
void main(void) {
    uint8_t pisca=0;
    
    TRISEbits.RE2=0; // Define como saída o pino de led
    PORTDbits.RD4=0;
    TRISDbits.RD4=0; // Define como saída o pino de relé
    
    for (int i=0;i<10;i++)
    {
        pisca ^= 1;
        PORTEbits.RE2 = pisca;
        __delay_ms(200);
    }
    
    setup_uart(115200);
    USBDeviceInit();
    setup_AD();
    setup_pulsos();
    setup_ccp1();
    init_XBee();
    
    setPAN(panID);
    
    setLinkKey(encryptKey);
    setEncryptionMode(encryptEnable);
                
    verificaUSB();
    while (true)
    {
        createFrame("UT_Poco");
        //addSensorStr("STR","TESTE");
        addSensorFloat("NIVEL",le_AD());
        addSensorInt("LITROS",le_pulsos());
        pisca ^= 1;
        PORTEbits.RE2 = pisca;
        
        uint8_t resp=send(RX_ADDRESS, (uint8_t*)frameBuffer, strlen((const char*) frameBuffer));
        //uint8_t resp=getPAN();
        
        if (verificaUSB() && USBUSARTIsTxTrfReady())
        {
            char linha[50];
            sprintf(linha, "[%ld]: F:%d R:%d\n", millis(), numPacote-1, resp); 
            putsUSBUSART(linha);
        }
        delay(TEMPO_TRANSMISSAO);
    }
    return;
}
*/
