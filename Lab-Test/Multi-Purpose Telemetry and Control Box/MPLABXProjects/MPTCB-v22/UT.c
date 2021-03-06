/* 
 * File:   newmain.c
 * Author: C0485763
 *
 * Created on 13 de Julho de 2017, 14:26
 * Updated on 02 de Fevereiro de 2019. 10:00
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
    
    TRISEbits.RE2=0; // Define como sa�da o pino de led
    PORTDbits.RD4=0;
    TRISDbits.RD4=0; // Define como sa�da o pino de rel� 1
    PORTDbits.RD5=0;
    TRISDbits.RD5=0; // Define como sa�da o pino de rel� 2
    PORTDbits.RD6=0;
    TRISDbits.RD6=0; // Define como sa�da o pino de rel� 3
    PORTDbits.RD7=0;
    TRISDbits.RD7=0; // Define como sa�da o pino de rel� 4
    
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
    
    /*
    SetBandWidth(500);
    SetSpreadingFactor(8);
    DataRate (3);
    AdaptiveDataRate(STATE_ON);
    MacSave();
   */
#ifdef XBEE
    init_XBee();
   
    teste = setPAN(panID);
    //teste1 = setChannelMask(Mask);
    //teste2 = setPreambleID(preambleID);
    teste3 = setLinkKey(encryptKey);
    teste4 = setEncryptionMode(encryptEnable);
     
  
#endif    
    
#ifdef LORAWAN
    struct
    {
        //uint8_t id; FUN�AO DESATIVADA, usando o EUI device do lora para identifica��o
        uint8_t feedback;
        uint16_t nivel1; 
        uint16_t nivel2;  
        uint32_t pulsos1; 
        uint32_t pulsos2; 
        uint32_t pulsos3; 
        uint32_t pulsos4; 
    } dadoPoco;
    //dadoPoco.id = ReadEEPROM(0x0069); FUN�AO DESATIVADA, usando o EUI device do lora para identifica��o

    //dadoPoco.numPacote=0;
    putch(0x34); //Sync do auto-baud rate // 0x55 anteriormente
    
    
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
    
#endif
    
    
    while (true)
    {
        uint32_t tempo=millis();
        pisca ^= 1;
        PORTEbits.RE2 = pisca;
        
#ifdef XBEE
        createFrameHeader("UT_Poco");
        addSensorFloat("NIVEL",le_AD(0)*1000.0);
        addSensorInt("LITROS",le_pulsos(1,retornaDado(4,0)));
        uint8_t resp=send(RX_ADDRESS, (uint8_t*)frameBuffer, strlen((const char*) frameBuffer));
        //teste1 = numPacote;
#endif

#ifdef LORAWAN        
        //dadoPoco.numPacote++;
        /* FUN�AO DESATIVADA, usando o EUI device do lora para identifica��o
        if (((dadosRecebidos[1].data & 0b10000000)   == 0b10000000) && (dadosRecebidos[2].data != 0)){
            dadoPoco.id = dadosRecebidos[2].data;
            WriteEEPROM(0x0069,dadosRecebidos[2].data);
        }*/
        
        dadoPoco.feedback=dadosRecebidos[1].data; // A gosto do usuario
        dadoPoco.nivel1  =(uint16_t)(le_AD(0)*1000.0);
        dadoPoco.nivel2  =(uint16_t)(le_AD(1)*1000.0);
        dadoPoco.pulsos1 =le_pulsos(1,retornaDado(4,0)); 
        dadoPoco.pulsos2 =le_pulsos(2,retornaDado(4,1));
        dadoPoco.pulsos3 =le_pulsos(3,retornaDado(4,2)); 
        dadoPoco.pulsos4 =le_pulsos(4,retornaDado(4,3));      
        
        LATDbits.LATD4 = retornaDado(0,0); 
        LATDbits.LATD5 = retornaDado(0,3); 
        LATDbits.LATD6 = retornaDado(0,2); 
        LATDbits.LATD7 = retornaDado(0,1); 
        
        if (retornaDado(1,6) == 1){
            uint8_t Icanal = retornaDado(6,6)<<6 | retornaDado(6,5)<<5 | retornaDado(6,4)<<4 | retornaDado(6,3)<<3 | retornaDado(6,2)<<2 | retornaDado(6,1)<<1 | retornaDado(6,0);
            uint8_t Fcanal = retornaDado(7,6)<<6 | retornaDado(7,5)<<5 | retornaDado(7,4)<<4 | retornaDado(7,3)<<3 | retornaDado(7,2)<<2 | retornaDado(7,1)<<1 | retornaDado(7,0);
            for (uint8_t i=0; i<Fcanal; i++){
                SetChannelLoRaWan (i,0);
            } 
            for (uint8_t i=Icanal; i<=Fcanal; i++){
                SetChannelLoRaWan (i,1);
            }
            if (retornaDado(3,1) == 1){
                AdaptiveDataRate(STATE_OFF);
                uint8_t dr = retornaDado(2,3)<<3 | retornaDado(2,2)<<2 | retornaDado(2,1)<<1 | retornaDado(2,0);
                if (sizeof(dadoPoco)<11 && dr==0)
                    dr++; // Mudar essa linha pata dr=3 quando o modelo australiano atualizar
                DataRate(dr);
                if (retornaDado(1,7) == 1){
                    uint8_t sf = retornaDado(2,7)<<3 | retornaDado(2,6)<<2 | retornaDado(2,5)<<1 | retornaDado(2,4);
                    SetSpreadingFactor (sf);
                    if (retornaDado(3,0) == 0)
                        SetBandWidth (125);
                    else
                        SetBandWidth (500);
                }}
            else 
                AdaptiveDataRate(STATE_ON);
            MacSave();
        }
         
        uint8_t resp=TxLoRaWan(true, 3, (const uint8_t*)&dadoPoco, sizeof(dadoPoco)); // Confirmado
        //uint8_t resp=TxLoRaWan(false, 3, (const uint8_t*)&dadoPoco, sizeof(dadoPoco)); // N�o confirmado
               
#endif
        
       
        if (verificaUSB() && USBUSARTIsTxTrfReady())
        {
            char data[150];
            sprintf(data,"resposta: %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d \n\r",
                    dadosRecebidos[0].data,
                    dadosRecebidos[1].data,
                    dadosRecebidos[2].data,
                    dadosRecebidos[3].data,
                    dadosRecebidos[4].data,
                    dadosRecebidos[5].data,
                    dadosRecebidos[6].data,
                    dadosRecebidos[7].data,
                    dadosRecebidos[8].data,
                    dadosRecebidos[9].data,
                    dadosRecebidos[0].port,
                    dadosRecebidos[1].port,
                    dadosRecebidos[2].port,
                    dadosRecebidos[3].port,
                    dadosRecebidos[4].port,
                    dadosRecebidos[5].port,
                    dadosRecebidos[6].port,
                    dadosRecebidos[7].port,
                    dadosRecebidos[8].port,
                    dadosRecebidos[9].port);
            putsUSBUSART(data);
        }
        uint32_t deltaTempo=(millis()-tempo);
        if (deltaTempo<TEMPO_TRANSMISSAO)
        {
            uint32_t tempoTimeOut=TEMPO_TRANSMISSAO-deltaTempo;
            delay(tempoTimeOut);
        }
    }
    return;
}