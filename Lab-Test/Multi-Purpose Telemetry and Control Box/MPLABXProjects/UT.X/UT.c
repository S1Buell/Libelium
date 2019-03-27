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
    gravaDadosEeprom();
    verificaUSB();
    while ((millis()-to)<time)
    {
        gravaDadosEeprom();
        verificaUSB();
    }    
}



/*
 * 
 */
void main(void) {
    uint8_t pisca=0;
    
    TRISEbits.RE2=0; // Define como saída o pino de led
    PORTDbits.RD4=0;
    TRISDbits.RD4=0; // Define como saída o pino de relé
    TRISAbits.RA0=1; // Define como entrada o pino de analógico
    TRISAbits.RA1=1; // Define como entrada o pino de analógico
    
    
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
    inicializaVariaveis();    
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
        uint8_t nivelL              :8;
        uint8_t nivelH              :7;
        uint8_t horimetroLigado     :1;
        uint8_t vazaoAcumuladaB0;
        uint8_t vazaoAcumuladaB1;
        uint8_t vazaoAcumuladaB2;
        uint8_t horimetroB0;
        uint8_t horimetroB1;
        uint8_t horimetroB2;
        uint8_t  vazaoInstantanea;
    } dadoPoco;
    
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

    //writeEeprom(0,123);
   
    while (true)
    {
        uint32_t tempo=millis();
        pisca ^= 1;
        PORTEbits.RE2 = pisca;
        uint16_t nivelPoco=(uint16_t)(le4a20()*1000.0);
        leMedidas();
        
#ifdef XBEE
        createFrame("UT_Poco");
        addSensorFloat("NIVEL",nivelPoco);
        addSensorInt("LITROS",pulsosMedido);
        uint8_t resp=send(RX_ADDRESS, (uint8_t*)frameBuffer, strlen((const char*) frameBuffer));
#endif

#ifdef LORAWAN        
        dadoPoco.nivelL=nivelPoco;
        dadoPoco.nivelH=nivelPoco>>8;
        dadoPoco.horimetroLigado=horimetroLigadoMedido;
        dadoPoco.vazaoAcumuladaB0=vazaoAcumuladaMedido;
        dadoPoco.vazaoAcumuladaB1=vazaoAcumuladaMedido >> 8;
        dadoPoco.vazaoAcumuladaB2=vazaoAcumuladaMedido >> 16;
        dadoPoco.horimetroB0=horimetroMedido;
        dadoPoco.horimetroB1=horimetroMedido >> 8;
        dadoPoco.horimetroB2=horimetroMedido >> 16;
        dadoPoco.vazaoInstantanea=vazaoInstantaneaMedido;
        
        /*
        for (uint8_t canal=0;canal<8;canal++)
        {
            SetChannelLoRaWan(canal, true);
        }
        for (uint8_t canal=8;canal<72;canal++)
        {
            SetChannelLoRaWan(canal, false);
        }
        SetChannelLoRaWan(64, true);
        */
        
        //uint8_t resp=TxLoRaWan(true, 1, (const uint8_t*)&dadoPoco, sizeof(dadoPoco)); // Confirmado
        uint8_t resp=TxLoRaWan(false, 1, (const uint8_t*)&dadoPoco, sizeof(dadoPoco)); // Não confirmado
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
            //putsUSBUSART(frameBuffer);
            */
            
            /*************** TESTE ***************
            char data[150];
            uint16_t nivel=(uint16_t)(le_AD()*1000.0);
            uint32_t pulsos=le_pulsos();

            sprintf(data,"[%lu] N:%u P:%lu\n\r",millis(),nivel,pulsos);
            putsUSBUSART(data);
            */
            
            /*
            char data[150];
            sprintf(data,"[%ld] Ret: %d Resp: %d\n\r\n\r",millis(),resp,responseLoRaWan);
            
            //sprintf(data,"resposta: %d %d %2X %2X",responseLoRaWan,dadosRecebidos[tamDadosRecebidos-2].port,dadosRecebidos[tamDadosRecebidos-2].data,dadosRecebidos[tamDadosRecebidos-1].data);
            putsUSBUSART(data);
            */

        }
        
            
        uint32_t deltaTempo=(millis()-tempo);
        uint32_t tempoTimeOut=TEMPO_TRANSMISSAO-deltaTempo;
        if (deltaTempo>TEMPO_TRANSMISSAO)
        {
            tempoTimeOut=0;
        }
        
        delay(tempoTimeOut);

        //delay(TEMPO_TRANSMISSAO);
    }
    return;
}
