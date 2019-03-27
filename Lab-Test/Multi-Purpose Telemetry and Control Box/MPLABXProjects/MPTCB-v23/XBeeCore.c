/* 
 * File:   XBeeCore.c
 * Author: C0485763
 *
 * Created on 31 de Julho de 2017, 10:00
 */

#include "XBeeCore.h"
#include "timer.h"
#include <ctype.h>

/******************************************************************************
 * AT COMMANDS (FLASH Definitions)
 ******************************************************************************/

/// table_CORE /////////////////////////////////////////////////////////////////
const char get_own_mac_low[]        = {'S','L'}; 	// AT+SL
const char get_own_mac_high[] 		= {'S','H'}; 	// AT+SH
const char gs_pan[]                 = {'I','D'};	// AT+ID
const char gs_channel[]             = {'C','H'};	// AT+CH
const char write_values[]           = {'W','R'};    // AT+WR
const char set_link_key[]           = {'K','Y'};	// AT+KY
const char gs_encryption[]          = {'E','E'};    // AT+EE
const char set_channelmask_900[]    = {'C','M'};    // AT+CM // Novo
const char get_channelmask_900[]    = {'C','M'};    // AT+CM // Novo
const char set_preambleid_900[]     = {'H','P'};    // AT+HP // Novo
const char get_preambleid_900[]     = {'H','P'};    // AT+Hp // Novo

/*
const char get_own_mac_low[]        = "7E00040852534C06"; 	// AT+SL
const char get_own_mac_high[] 		= "7E0004085253480A"; 	// AT+SH
const char set_own_net_address[]    = "7E000608524D59000000";	// AT+MY
const char get_own_net_address[]    = "7E000408524D59FF";		// AT+MY
const char set_baudrate[]           = "7E0005085242440000";	// AT+BD
const char set_api_mode[]           = "7E0005085241500000";	// AT+AP
const char set_api_options[]        = "7E00050852414F0000";	// AT+AO
const char set_pan[]                = "7E000608524944000000";	// AT+ID
const char get_pan[]                = "7E00040852494418";		// AT+ID
const char set_sleep_mode_xbee[]    = "7E00050852534D0000";	// AT+SM
const char get_sleep_mode_xbee[]    = "7E00040852534D05";		// AT+SM
const char set_awake_time[]         = "7E000608525354000000";		// AT+ST
const char set_awake_time_DM[]      = "7E00070852535400000000";	// AT+ST
const char set_sleep_time[]         = "7E000608525350000000";		// AT+SP
const char set_sleep_time_DM[]      = "7E00070852535000000000";	// AT+SP
const char set_channel[]            = "7E0005085243480000";	// AT+CH
const char get_channel[]            = "7E0004085243481A";		// AT+CH
const char get_NI[]                 = "7E000408524E490E";		// AT+NI
const char set_scanning_time[]      = "7E000508524E540000";	// AT+NT
const char set_scanning_time_DM[]   = "7E000608524E54000000";	// AT+NT
const char get_scanning_time[]      = "7E000408524E5403";		// AT+NT
const char set_discov_options[]     = "7E000508524E4F0000";	// AT+NO
const char get_discov_options[]     = "7E000408524E4F08";		// AT+NO
const char write_values[]           = "7E000408525752FC";		// AT+WR
const char set_scanning_channel[]   = "7E000608525343000000";	// AT+SC
const char get_scanning_channel[]   = "7E0004085253430F";		// AT+SC
const char get_duration_energy[]    = "7E0004085253440E";		// AT+SD
const char set_link_key[]           = "7E001408524B590000000000000000000000000000000000";	// AT+KY
const char set_encryption[]         = "7E0005085245450000";	// AT+EE
const char get_encryption[]         = "7E0004085245451B";		// AT+EE
const char set_power_level[]        = "7E00050852504C0000";	// AT+PL
const char get_power_level[]        = "7E00040852504C09";		// AT+PL
const char get_RSSI[]               = "7E0004085244421F";		// AT+DB
const char get_hard_version[]       = "7E00040852485607";		// AT+HV
const char get_soft_version[]       = "7E000408525652FD";		// AT+VR
const char set_RSSI_time[]          = "7E0005085252500000";	// AT+RP
const char get_RSSI_time[] 			= "7E00040852525003";		// AT+RP
const char apply_changes[]          = "7E00040852414321";		// AT+AC
const char reset_xbee[]             = "7E0004085246520D";		// AT+FR
const char reset_defaults_xbee[]    = "7E0004085252450E";		// AT+RE
const char set_sleep_options_xbee[] = "7E00050852534F0000";	// AT+SO
const char get_sleep_options_xbee[] = "7E00040852534F03";	// AT+SO
const char scan_network	[]          = "7E000408524E4413";		// AT+ND
const char set_duration_energy[]    = "7E0005085245440000"; 	// AT+ED
const char set_duration_energy_ZB[] = "7E0005085253440000"; 	// AT+SD
const char get_low_dest_address[]   = "7E00040852444C15"; 	// AT+DL
const char timestamp_packet[]       = "%2u%2u%2u%2u%2u%2u%2u%c%2u%2u";
*/

void resetXBee(void)
{
    PORTCbits.RC0=0;
    NOP();
    TRISCbits.RC0=0;
    __delay_ms(100);
    TRISCbits.RC0=1;
    NOP();
    __delay_ms(100);
}

/*
 * Function: It initalizes all the necessary variables including its parent's 
 * variables
 * 
 * Parameters:
 * 'protocol_used' : specifies the protocol used in the XBee module 
 * 'uart_used' : specifies the UART where the data are sent to (SOCKET0 or SOCKET1)
 * Returns: void
*/
void init_XBee(void)
{	
    resetXBee();
	protocol=XBEE_900HP;
	
	error_AT=2;
	error_RX=2;
}

/*
 * Function: Get the 32 lower bits of my MAC address
 * 
 * Returns: Integer that determines if there has been any error 
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
 * 	Values: When it is executed stores the returned value by SL command in the 
 *			global "sourceMacLow[4]" variable
 */
uint8_t getOwnMacLow(void)
{
    uint8_t error=2;     
    error_AT=2;
    
    gen_data(get_own_mac_low,0,0);
    error=gen_send();
    
    if(error==0)
    {
		sourceMacLow[0]=response.ATCommandResponse.commandData[0];
		sourceMacLow[1]=response.ATCommandResponse.commandData[1];
		sourceMacLow[2]=response.ATCommandResponse.commandData[2];
		sourceMacLow[3]=response.ATCommandResponse.commandData[3];
    }
    return error; 
}

/*
 Function: Get the 32 higher bits of my MAC address
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: When it is executed stores the returned value by SH in the global 
         "sourceMacHigh[4]" variable
*/
uint8_t getOwnMacHigh(void)
{
    uint8_t error=2;     
    error_AT=2;

    gen_data(get_own_mac_high,0,0);
    error=gen_send();
    
    if(error==0)
    {
		sourceMacHigh[0]=response.ATCommandResponse.commandData[0];
		sourceMacHigh[1]=response.ATCommandResponse.commandData[1];
		sourceMacHigh[2]=response.ATCommandResponse.commandData[2];
		sourceMacHigh[3]=response.ATCommandResponse.commandData[3];
    }
    return error;
}

/*
 Function: Get the 64 bits of my MAC address
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes functions getOwnMacLow() and getOwnMacHigh()
*/
 uint8_t getOwnMac(void)
{
    uint8_t error=2;
    error=getOwnMacLow();
    if(error==0)
    {
        error=getOwnMacHigh();  
    }
    return error;
}

void processaPacote(void)
{
    // Não aceita broadcast
    if (receivePacket.receivePacketAO0.receiveOptions==0x02)
        return;
    if (receivePacket.receivePacketAO0.sizeData!=1)
        return;
    
    if (receivePacket.receivePacketAO0.receivedData[0]==0x55)
        PORTDbits.RD4=0;
    if (receivePacket.receivePacketAO0.receivedData[0]==0xAA)
        PORTDbits.RD4=1;

}

void recebeByte(int8_t b)
{
    static uint8_t estadoRecepcao=0;
    static bool escapeCaracter=false;
    static uint16_t tamanhoMensagem;
    static uint8_t checksumRecebimento;
    static uint16_t sizeData;
    static uint8_t frameData[MAX_DATA_RECEPCAO];

    if (b==0x7D) // Recebeu escape caracter
    {
        escapeCaracter=true;
        return;
    }

    if (escapeCaracter) // Trata escape caracter
    {
       b^=0x20;
    }

    switch(b) // Verifica se é um escape caracter
    {
        case 0x11 :
        case 0x13 :
        case 0x7D :
        case 0x7E : 
            if (!escapeCaracter)
                estadoRecepcao=0;
            break;
        default:
            if (escapeCaracter)
            {
                b^=0x20;
                estadoRecepcao=0;
            }
            break;

    }

    escapeCaracter=false;

    checksumRecebimento+=b;
    switch (estadoRecepcao)
    {
        case 0: 
            if (b==0x7E)    // Verificar Start Delimiter
            {
                estadoRecepcao++;
                tamanhoMensagem=0;
            }
            break;
        case 1: // MSB Length
            tamanhoMensagem=b;
            tamanhoMensagem<<=8;
            estadoRecepcao++;
            break;
        case 2: // LSB Length
            tamanhoMensagem|=b;
            sizeData=2; // Deixa espaço para o tamanho da mensagem
            tamanhoMensagem+=2;
            checksumRecebimento=0;
            estadoRecepcao++;
            break;
        case 3:
            frameData[sizeData++]=b;
            if (sizeData>=tamanhoMensagem)
                estadoRecepcao++;
            else if (sizeData==MAX_DATA_RECEPCAO)
                estadoRecepcao=0;
            break;
        case 4:
            estadoRecepcao=0;
            if (checksumRecebimento!=255)
                return;
            
            switch (frameData[2])
            {
                case AT_COMMAND_RESPONSE: // AT Command Response
                    memcpy(response.frameData, frameData, sizeData);
                    response.ATCommandResponse.sizeData=tamanhoMensagem-7;
                    break;
                case TRANSMIT_STATUS: // Trasmit Status
                    memcpy(response.frameData, frameData, sizeData);
                    response.transmitStatus.sizeData=tamanhoMensagem-9;
                    break;
                case RECEIVE_PACKET_AO0: // Received packet AO=0
                    memcpy(receivePacket.frameData, frameData, sizeData);
                    receivePacket.receivePacketAO0.sizeData=tamanhoMensagem-14;
                    processaPacote();
                    break;
                case RECEIVE_PACKET_AO1: // Received packet AO=1
                    memcpy(receivePacket.frameData, frameData, sizeData);
                    receivePacket.receivePacketAO1.sizeData=tamanhoMensagem-20;
                    break;
            }
            
            break;

    }
}
 
uint16_t tamanhoCommand=0;
uint8_t cs;
void addByteCommand(int8_t b, bool calcChecksum)
{
    
    if (calcChecksum)
        cs-=b;
    
    if (tamanhoCommand>0)
    {
        switch(b)
        {
            case 0x11 :
            case 0x13 :
            case 0x7D :
            case 0x7E : 
                command[tamanhoCommand++]=0x7D;
                b^=0x20;
                break;
        }
    }
    else
    {
        cs=255;
    }

    command[tamanhoCommand++]=b;
    
}

 /*
 Function: Generates the API frame to send to the XBee module
 Parameters:
 	data : The string that contains part of the API frame
 Returns: Nothing
 Values: Stores in 'command' variable the API frame to send to the XBee module
*/
void gen_data(const uint8_t* data, uint8_t* param, uint8_t sizeParam)
{
    int16_t size=sizeParam + 4; // Adiciona quatro devido aos campso Frame Type (0x08), FrameID e data
	tamanhoCommand=0;
    addByteCommand(0x7E,false);       // Start Delimiter
    addByteCommand(size >> 8,false);  // size high
    addByteCommand(size,false);       // size low
    addByteCommand(0x08,true);       // Frame Type (AT Command = 0x08)
    addByteCommand(0x52,true);       // Frame ID
    addByteCommand(data[0],true);
    addByteCommand(data[1],true);    
    
    for (uint8_t i=0 ; i<sizeParam ; i++)
    {
        addByteCommand(param[i],true);
    }
    
    addByteCommand(cs,false);
}

/*
 * Function: Generates a decimal number from two ASCII characters which were numbers
 * Returns: The generated number
 * 
 */
uint8_t converter(uint8_t conv1, uint8_t conv2)
{
	uint8_t aux=0;
	uint8_t aux2=0;
	uint8_t resul=0;

    
    conv1=toupper(conv1);
    conv2=toupper(conv2);
    
    if ((conv1>='0') && (conv1<='9'))
    {
        aux=conv1-'0';
    }
    else if ((conv1>='A') && (conv1<='F'))
    {
        aux=conv1-'A'+10;
    }
        
    if ((conv2>='0') && (conv2<='9'))
    {
        aux2=conv2-'0';
    }
    else if ((conv2>='A') && (conv2<='F'))
    {
        aux2=conv2-'A'+10;
    }
    else
    {
        aux2=100;
    }

	if(aux2==100) // Only one character but we have treated two, so We have to fix it
	{
		resul=aux;
	}
	else
	{
		resul=(uint8_t)((aux*16)+aux2);
	}
	return resul;
}

/*
 Function: Sends the API frame stored in 'command' variable to the XBee module
 Parameters:
 	data : The string that contains part of the API frame
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
*/
uint8_t gen_send(void)
{
    uint8_t error_int=2;

    for (uint16_t i = 0; i < tamanhoCommand; i++)
	{
        putch((char)command[i]);
	}
	
    //error_int = parse_message();

    return error_int;
}

/*
 * Function: Parses the answer received by the XBee module, calling the 
 * appropriate function
 * 
 * Parameters:
 * 	frame : an array that contains the API frame that is expected to receive 
 * 			answer from if it is an AT command
 * 
 * Returns: Integer that determines if there has been any error 
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
*/
uint8_t parse_message(void)
{
    uint16_t intervalMAX=40000;
    bool timeout=false;
    uint32_t previous=millis();
    
    response.ATCommandResponse.frameType=0;
    
    
    while ((!timeout) && (response.ATCommandResponse.frameType!=AT_COMMAND_RESPONSE))
    {	
        /*
		if (kbhit())
		{
            recebeByte(getch());
		}
		
        */
        if ((millis()-previous) > intervalMAX)
        {
			timeout=true;
		}  	  
    }     
       
    if (response.ATCommandResponse.frameType==AT_COMMAND_RESPONSE)
        error_AT=0;
    else
        error_AT=1;
    
    return error_AT;
}

/*
 Function: Set the network identifier
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Parameters: 
   PANID: Array of integers than contains the 16b or 64b PAN ID
 Values: Stores in global "PAN_ID" variable the recent set PAN ID value
 */
uint8_t setPAN(uint8_t* PANID)
{
    int8_t error=2;
        
    error_AT=2;

    gen_data(gs_pan,PANID,2);
    error=gen_send();

    if(!error)
    {
        PAN_ID[0] = PANID[0];
        PAN_ID[1] = PANID[1];           
    } 
    return error;
}

/*
 Function: Get Network ID
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores in global "error" variable any error happened while execution
	 Stores in global "PAN_ID" variable the 16b or 64b network PAN ID
*/
uint8_t getPAN()
{
    int8_t error=2;
     
    error_AT=2;

    gen_data(gs_pan,0,0);
    error=gen_send();

    if (!error)
    {
        PAN_ID[0] = response.ATCommandResponse.commandData[0];
        PAN_ID[1] = response.ATCommandResponse.commandData[1];
    } 
    return error;
}

/*
 Function: Write the current parameters to a non volatil memory
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Executes the WR command
*/
uint8_t writeValues()
{
    int8_t error=2;
    error_AT=2;

    gen_data(write_values,0,0);
    error=gen_send();
    
    return error;
}

/*
 Function: Set the channel frequency where the module is going to work 
 Returns: Integer that determines if there has been any error 
   error=2  --> The command has not been executed
   error=1  --> There has been an error while executing the command
   error=0  --> The command has been executed with no errors
   error=-1 --> Forbidden command for this protocol
 Values: Stores the selected channel in the global "channel" variable
 Parameters:
   _channel: Channel used to transmit (0x0B-0x1A)
*/
uint8_t setChannel(uint8_t _channel)
{
    int8_t error=2;
    error_AT=2;

    gen_data(gs_channel,&_channel,1);
    error=gen_send();
    
    if(!error)
    {
        channel=_channel;
    }

    return error;
}

/*
 Function: Get the actual frequency channel 
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Stores the frequency channel in the global "channel" variable
*/
uint8_t getChannel(void)
{
    int8_t error=2;
    error_AT=2;
	
    gen_data(gs_channel,0,0);
    error=gen_send();
    
    if(!error)
    {
        channel=response.ATCommandResponse.commandData[0];
    }
    return error;
}

/*
 * Function: Send a packet from one XBee to another XBee in API mode
 * This function performs application-level retries.
 * This function is only used for 64-bit addressing.
 * 
 * 
 * Return:
 * 	'0' OK
 * 	'1' error
 */
/**********************************************************************
		 *  Call parsing function depending on the Frame Type
		 *  _______________________________________________
		 * |      |     |     |    		   |			   |
		 * | 0x7E | MSB | LSB | Frame Type |    ......     |
		 * |______|_____|_____|____________|_______________|
		 * 	  0	     1     2        3          variable
		 **********************************************************************/
uint8_t send(char* macAddress, uint8_t* pointer, uint16_t length)
{	
    const uint8_t MAX_RETRIES = _send_retries;
    uint16_t maxPayload=0;

	// set maximum payload depending on the 
	// protocol, encryption mode, addressing mode
	switch (protocol)
	{		

		case DIGIMESH: 	maxPayload=73;
						break;
		
		case XBEE_900:  if(encryptMode) maxPayload=80;
						else maxPayload=100;
						break;
        case XBEE_900HP:maxPayload=0xFF;
						break;
		default:		break;
		
	}  
   
    // Check if fragmentation is necessary due to packet length 
    // is greater than maximum payload 
    if(length > maxPayload)
    {	
		// Truncation needed
        length=maxPayload;
    }
    
    int16_t size=length + 14;
    
	tamanhoCommand=0;
    addByteCommand(0x7E,false);       // Start Delimiter
    addByteCommand(size >> 8,false);  // size high
    addByteCommand(size,false);       // size low
    addByteCommand(0x10,true);       // Frame Type (Transmit request = 0x10)
    addByteCommand(0x01,true);       // Frame ID
    for (uint8_t i=0;i<8;i++)
    {
        addByteCommand(converter(macAddress[i*2],macAddress[i*2+1]),true);    // Destination address
    }
    addByteCommand(0xFF,true);       // Reserved
    addByteCommand(0xFE,true);       // Reserved
    addByteCommand(0x00,true);       // Broadcast radius
    addByteCommand(0x00,true);       // Transmit Options
    
    for (uint16_t i=0;i<length;i++)
    {
        addByteCommand(pointer[i],true);
    }
    
    addByteCommand(cs,false);
    
    for (uint8_t i=0;i<=MAX_RETRIES;i++)
    {
        sendXBeePriv();
		
		// Check TX flag
		if( error_TX == 0 )
		{
			// Send successful, exit the while loop
			return 0;
		}
		else
		{			
			// Error transmitting the packet
			// wait for a random delay between 100 and 500 ms
			//__delay_ms( (unsigned long)rand()%400LU + 100LU);
            unsigned long r=(unsigned long)60LU;
            for (unsigned long i=0;i<r;i++)
            {
                __delay_ms(1);
            }
		}
    }
	
	return 1;
}

/*
 * Function: Send a packet from one XBee to another XBee in API mode
 * 
 * Parameters: 
 *   packet :	A struct of packetXBee type
 * 
 * Returns: Integer that determines if there has been any error 
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
 * 
 * --> DIGI's XBee Packet inner structure:
 * 
 * StartDelimiter(1B) + Length(2B) +  Frame Data(variable) + Checksum(1B)
 *  ______________     ___________     __________________     __________
 * |              |   |     |     |   |					 |   |			|
 * |	0x7E	  | + | MSB | LSB | + |    Frame Data    | + |	1 Byte	|
 * |______________|   |_____|_____|   |__________________|   |__________|
 * 
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * 
 * name: setChannelMask
 * @param void
 * @return '0' if ok, '1' otherwise
 * 
 */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t setChannelMask( uint8_t* mask )
{
	int8_t error=2;     
    error_AT=2;
    char buffer[50];
    
    // set_channelmask_900
    //strcpy_P(buffer, (char*)pgm_read_word(&(table_900HP[4])));
	//gen_data(buffer, mask);
	//gen_checksum(buffer); 
    
    //error = gen_send(buffer);
    
    gen_data(set_channelmask_900, mask,0);
    error = gen_send();
    
    if( error == 0 )
    {     
		_channelMask[0] = mask[0];
		_channelMask[1] = mask[1];
		_channelMask[2] = mask[2];
		_channelMask[3] = mask[3];
		_channelMask[4] = mask[4];
		_channelMask[5] = mask[5];
		_channelMask[6] = mask[6];
		_channelMask[7] = mask[7];
    }
    return error;    
}

/*
 * 
 * name: getChannelMask
 * @param void
 * @return '0' if ok, '1' otherwise
 * 
 */
uint8_t getChannelMask()
{
	int8_t error=2;     
    error_AT=2;
    char buffer[20];

    gen_data(get_channelmask_900,0,0);
    error = gen_send();
    
    if( error == 0 )
    {
		// module provides a 9-byte payload
		// the first byte is 0x00
		// the rest of the bytes are the contents of the command answer:
		_channelMask[0] = data[1];
		_channelMask[1] = data[2];
		_channelMask[2] = data[3];
		_channelMask[3] = data[4];
		_channelMask[4] = data[5];
		_channelMask[5] = data[6];
		_channelMask[6] = data[7];
		_channelMask[7] = data[8];
    }
    return error;    
}

uint8_t setPreambleID( uint8_t preambleID )
{
	int8_t error=2;     
    error_AT=2;
    char buffer[20];
    
    gen_data(set_preambleid_900, (uint8_t*)preambleID,0);
    error = gen_send();
    
    if( error == 0 )
    {  
            _preambleID = preambleID;   
    }
    return error;    
}

/*
 * 
 * name: getPreambleID
 * @param void
 * @return '0' if ok, '1' otherwise
 * 
 */
uint8_t getPreambleID()
{
	int8_t error=2;     
    error_AT=2;
    char buffer[20];

    gen_data(get_preambleid_900,0,0);
    error = gen_send();
    
    if( error == 0 )
    {
		_preambleID = data[0];	
    }
    return error;    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
uint8_t sendXBeePriv(void)
{
    for (uint16_t i = 0; i < tamanhoCommand; i++)
    {
        putch((char)command[i]);
    }
    
	// read XBee's answer to TX request
	error_TX=txZBStatusResponse();
    
    return error_TX;
}

/*
 * Function: Parses the ZB TX Status message received by the XBee module
 * 
 * Parameters:
 * 	data_in : the answer received by the module
 * 	end : the end of the frame
 * 	start : the start of the frame
 * 
 * Returns: Integer that determines if there has been any error 
 * 	error=2 --> The command has not been executed
 * 	error=1 --> There has been an error while executing the command
 * 	error=0 --> The command has been executed with no errors
*/
uint8_t txZBStatusResponse(void)
{
    uint16_t intervalMAX=40000;
    bool timeout=false;
    uint32_t previous=millis();
    
    response.transmitStatus.frameType=0;
    
    
    while ((!timeout) && (response.transmitStatus.frameType!=TRANSMIT_STATUS))
    {	
        /*
		if (kbhit())
		{
            recebeByte(getch());
		}
		*/
        
        if ((millis()-previous) > intervalMAX)
        {
			timeout=true;
		}  	  
    }     
       
    error_TX=1;
    if (response.transmitStatus.frameType==TRANSMIT_STATUS)
    {
        retries_sending=response.transmitStatus.transmitRetryCount;
        discovery_status=response.transmitStatus.discoveryStatus;
        delivery_status=response.transmitStatus.deliveryStatus;
        if (delivery_status==0) 
            error_TX=0;
    }
    
    return error_TX;
}

/*
 Function: Sets the encryption key to be used in the 128b AES algorithm
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the KY command. Stores in global "linkKey" variable the key has been set
 Parameters:
   key: 16 byte array of chars that specifies the 128b AES key
*/
uint8_t setLinkKey(const char* key)
{
    int8_t error=2;
    error_AT=2;

	// set_link_key
    gen_data(set_link_key,(uint8_t*) key,16);
    error=gen_send();

    return error;
}

/*
 Function: Sets the encryption mode on/off
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the EE command. Stores in global "encryptMode" variable the encryption mode
 Parameters:
   mode: on/off the encryption mode (1/0)
*/
uint8_t setEncryptionMode(bool mode)
{
    int8_t error=2;
    error_AT=2;

    if (mode)
        mode=1;

	// set_encryption
    gen_data(gs_encryption,&mode,1);
    error=gen_send();
    
    if(!error)
    {
        encryptMode=mode;
    }
    return error;
}

/*
 Function: Gets the encryption mode on/off
 Returns: Integer that determines if there has been any error 
   error=2 --> The command has not been executed
   error=1 --> There has been an error while executing the command
   error=0 --> The command has been executed with no errors
 Values: Change the EE command. Stores in global "encryptMode" variable the encryption mode
 Parameters:
   mode: on/off the encryption mode (1/0)
*/
uint8_t getEncryptionMode()
{	
	int8_t error=2;
	error_AT=2;

    gen_data(gs_encryption,0,0);
    error=gen_send();

    if(!error)
    {
        encryptMode=response.ATCommandResponse.commandData[0];
    }
    return error;
}
