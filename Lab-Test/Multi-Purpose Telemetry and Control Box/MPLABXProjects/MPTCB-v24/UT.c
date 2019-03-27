/* 
 * File:   newmain.c
 * Author: C0485763
 *
 * Created on 13 de Julho de 2017, 14:26
 * Updated on 02 de Dezembro de 2018. 10:00
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

void main(void) {
    uint8_t contador;
    uint8_t pisca=0;
    
    TRISEbits.RE2=0; // Define como saída o pino de led
    PORTDbits.RD4=0; // e seta a saida como LOW
    TRISDbits.RD4=0; // Define como saída o pino de relé 1
    PORTDbits.RD5=0; // e seta a saida como LOW
    TRISDbits.RD5=0; // Define como saída o pino de relé 2
    PORTDbits.RD6=0; // e seta a saida como LOW
    TRISDbits.RD6=0; // Define como saída o pino de relé 3
    PORTDbits.RD7=0; // e seta a saida como LOW
    TRISDbits.RD7=0; // Define como saída o pino de relé 4
    // Led pisca 13 vezes antes de entrar no Loop
    
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
    SetAdr(STATE_ON);
    MacSave();
   */
#ifdef XBEE
    setup_uart(115200);
    init_XBee();
   
    setPAN(panID);
    setChannelMask(Mask);
    setPreambleID(preambleID);
    setEncryptionMode(encryptEnable);
    setLinkKey(encryptKey);
#endif    
    
#ifdef LORAWAN 
    struct
    {
        uint8_t feedback1;
        uint8_t feedback2;
        uint16_t nivel1; 
        uint16_t nivel2;  
        uint32_t pulsos1; 
        uint32_t pulsos2; 
        uint32_t pulsos3; 
        uint32_t pulsos4; 
    } dadoPoco;
   
    putch(0x34); //Sync do auto-baud rate // 0x55 anteriormente
    
    for (uint8_t i=0; i<48; i++){
        SetChannelLoRaWan (i,0);
    } 
    for (uint8_t i=48; i<=63; i++){
        SetChannelLoRaWan (i,1);
    }
    
    DataRate(1);
    SetAdr(STATE_OFF);
    SetDevEUI();
    SetAppEUI();
    SetAppKey();
    MacSave();
#endif  
    while (true)
    {
        uint32_t tempo=millis();
        pisca ^= 1;
        PORTEbits.RE2 = pisca;
        
#ifdef XBEE
        createFrameHeader("UT_Poco");
        addSensorFloat("NIVEL",123);
        addSensorInt("LITROS",456);
        uint8_t resp=send(RX_ADDRESS, (uint8_t*)frameBuffer, strlen((const char*) frameBuffer));
        //teste1 = numPacote;
#endif

#ifdef LORAWAN 
        
        dadoPoco.nivel1  =(uint16_t)(le_AD(0)*1000.0);
        dadoPoco.nivel2  =(uint16_t)(le_AD(1)*1000.0);
        dadoPoco.pulsos1 =le_pulsos(1,retornaDado(1,0)); 
        dadoPoco.pulsos2 =le_pulsos(2,retornaDado(1,1));
        dadoPoco.pulsos3 =le_pulsos(3,retornaDado(1,2)); 
        dadoPoco.pulsos4 =le_pulsos(4,retornaDado(1,3));  
        
        nivel1  = dadoPoco.nivel1;
        nivel2  = dadoPoco.nivel2;
        pulsos1 = dadoPoco.pulsos1;
        pulsos2 = dadoPoco.pulsos2;
        pulsos3 = dadoPoco.pulsos3;
        pulsos4 = dadoPoco.pulsos4;   
        
        LATDbits.LATD4 = retornaDado(0,0); 
        LATDbits.LATD5 = retornaDado(0,3); 
        LATDbits.LATD6 = retornaDado(0,2); 
        LATDbits.LATD7 = retornaDado(0,1); 
        
        feedback1 = (feedback1 & (~(1))) | (retornaDado(0,0));
        feedback1 = (feedback1 & (~(1<<1))) | (retornaDado(0,3)<<1);
        feedback1 = (feedback1 & (~(1<<2))) | (retornaDado(0,2)<<2);
        feedback1 = (feedback1 & (~(1<<3))) | (retornaDado(0,1)<<3);
        feedback1 = (feedback1 & (~(1<<4))) | (retornaDado(1,4)<<4);
        feedback1 = (feedback1 & (~(1<<5))) | (retornaDado(1,5)<<5);
        feedback2 = (feedback2 & (~(1)))    | (retornaDado(5,6));
        feedback2 = (feedback2 & (~(1<<1))) | (retornaDado(5,7)<<1);
        feedback2 = (feedback2 & (~(1<<2))) | (retornaDado(5,4)<<2);
        feedback2 = (feedback2 & (~(1<<3))) | (retornaDado(5,5)<<3);
        feedback2 = (feedback2 & (~(1<<4))) | (retornaDado(5,2)<<4);
        feedback2 = (feedback2 & (~(1<<5))) | (retornaDado(5,3)<<5);
        feedback2 = (feedback2 & (~(1<<6))) | (retornaDado(5,0)<<6);
        feedback2 = (feedback2 & (~(1<<7))) | (retornaDado(5,1)<<7);
          
        if (retornaDado(0,4) == 1){
            uint8_t Icanal = retornaDado(6,6)<<6 | retornaDado(6,5)<<5 | retornaDado(6,4)<<4 | retornaDado(6,3)<<3 | retornaDado(6,2)<<2 | retornaDado(6,1)<<1 | retornaDado(6,0);
            uint8_t Fcanal = retornaDado(7,6)<<6 | retornaDado(7,5)<<5 | retornaDado(7,4)<<4 | retornaDado(7,3)<<3 | retornaDado(7,2)<<2 | retornaDado(7,1)<<1 | retornaDado(7,0);
            for (uint8_t i=0; i<Fcanal; i++){
                SetChannelLoRaWan (i,0);
            } 
            for (uint8_t i=Icanal; i<=Fcanal; i++){
                SetChannelLoRaWan (i,1);
            }
            if (retornaDado(0,7) == 1){
                SetAdr(STATE_OFF);
                uint8_t dr = retornaDado(2,3)<<3 | retornaDado(2,2)<<2 | retornaDado(2,1)<<1 | retornaDado(2,0);
                if (sizeof(dadoPoco)<11 && dr==0)
                    dr++; // Mudar essa linha pata dr=3 quando o modelo australiano atualizar
                DataRate(dr);
                if (retornaDado(0,5) == 1){
                    uint8_t sf = retornaDado(2,7)<<3 | retornaDado(2,6)<<2 | retornaDado(2,5)<<1 | retornaDado(2,4);
                    SetSpreadingFactor (sf);
                    if (retornaDado(0,6) == 0)
                        SetBandWidth (125);
                    else
                        SetBandWidth (500);
                }}
            else 
                SetAdr(STATE_ON);
            MacSave();
        }
         
        dadoPoco.feedback1=feedback1;
        dadoPoco.feedback2=feedback2;    
        //if ()
        uint8_t resp=TxLoRaWan(true, 3, (const uint8_t*)&dadoPoco, sizeof(dadoPoco)); // Confirmado
        
        if (resp == 0){
            contador++;
            if (contador > 2 ){
                SetAdr(STATE_OFF);
                DataRate(1);
                MacSave();
                contador=0;
            }
        }
        
        //uint8_t resp=TxLoRaWan(false, 3, (const uint8_t*)&dadoPoco, sizeof(dadoPoco)); // Não confirmado
               
#endif
        
        if (verificaUSB() && USBUSARTIsTxTrfReady())
        {
            char data[150];
            
            sprintf(data,"resposta: %2X %2X %2X %2X %2X %2X %2X %2X %2X %2X  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d  %d \n\r",
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
                pulsos1);
            
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