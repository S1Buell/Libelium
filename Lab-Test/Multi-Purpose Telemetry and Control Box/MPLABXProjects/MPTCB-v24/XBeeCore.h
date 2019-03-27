/* 
 * File:   XBeeCore.h
 * Author: C0485763
 *
 * Created on 31 de Julho de 2017, 10:03
 * Updated on 02 de Fevereiro de 2019. 10:00
 */

#ifndef XBEECORE_H
#define	XBEECORE_H

#include "UT.h"

#define AT_COMMAND_RESPONSE 0x88
#define TRANSMIT_STATUS 0x8B
#define RECEIVE_PACKET_AO0 0x90
#define RECEIVE_PACKET_AO1 0x91


//Different protocols used in the libraries
//#define XBEE_802_15_4 	1
//#define	ZIGBEE 			2
#define	DIGIMESH 		3
#define XBEE_900 		4
//#define XBEE_868 		5
#define XBEE_900HP 		6
//#define XBEE_868LP 		7
#define MAX_DATA    1
//#define	MAX_PARSE   150
#define MAX_DATA_RECEPCAO 100

#ifdef	__cplusplus
extern "C" {
#endif

//! It initializes the necessary variables
/*!
It initalizes all the necessary variables
\param uint8_t protocol_used : specifies the protocol used in the XBee 
        module (depends on the XBee module)
\param uint8_t uart_used : specifies the UART where the data are sent to,
        (SOCKET0 or SOCKET1)
\return void
 */
void init_XBee(void);	
    
//! It gets the own lower 32b MAC
/*!
It stores in global 'sourceMacLow' variable the own lower 32b MAC
\return '0' on success, '1' otherwise
 */
uint8_t getOwnMacLow(void);

//! It gets the own higher 32b MAC
/*!
It stores in global 'sourceMacHigh' variable the own higher 32b MAC
\return '0' on success, '1' otherwise
 */
uint8_t getOwnMacHigh(void);

//! It gets the own MAC
/*!
It stores in global 'sourceMacHigh' and 'sourceMacLow' variables the 64b MAC
\return '0' on success, '1' otherwise
*/
uint8_t getOwnMac(void);
    
//! It generates the API frame to send to the XBee module
/*!
\param const char* data : the string that contains part of the API frame
\return void
*/
void gen_data(const uint8_t* data, uint8_t* param, uint8_t sizeParam);

/*
 Function: Clears the variable 'command'
*/
void clearCommand(void);

/*
 * Function: Generates a decimal number from two ASCII characters which were numbers
 * Returns: The generated number
 * 
 */
uint8_t converter(uint8_t conv1, uint8_t conv2);

//! It sends the API frame stored in 'command' variable to the XBee module
/*!
\param const char* data : the string that contains part of the API frame
\return '0' if no error, '1' if error
*/
uint8_t gen_send(void);

//! It parses the answer received by the XBee module, calling the appropriate function
/*!
\param uint8_t* frame : an array that contains the API frame that is expected to receive answer from if it is an AT command
\return '0' if no error, '1' if error
   */
//uint8_t parse_message(uint8_t* frame);
uint8_t parse_message(void); // TESTE



//! It parses the Modem Status message received by the XBee module
/*!
\param uint8_t* data_in : the string that contains the eschaped API frame AT command
\param uint16_t end : the end of the frame
\param uint16_t start : the start of the frame
\return '0' if no error, '1' if error
*/
uint8_t modemStatusResponse(uint8_t* data_in, uint16_t end, uint16_t start);

//! It sets the PAN ID
/*!
\param uint8_t* PANID : the PAN ID (64b - ZigBee ; 16b - Other protocols)
\return '0' on success, '1' otherwise
 */
uint8_t setPAN(uint8_t* PANID);

//! It gets the PAN ID
/*!
It stores in global 'PAN_ID' the PAN ID
\return '0' on success, '1' otherwise
 */
uint8_t getPAN();

//! It sets the channel frequency where module is working on
/*!
\param uint8_t _channel : the channel frequency where module is working on (range depends on the XBee module)
\return '0' on success, '1' otherwise
 */
uint8_t setChannel(uint8_t _channel);

//! It gets the channel frequency where module is working on
/*!
It stores in global 'channel' the channel frequency where module is working on
\return '0' on success, '1' otherwise
 */
uint8_t getChannel();

//! It writes the parameters changed into non-volatil memory, being applied 
//! when the XBee is set OFF
/*!
\return '0' on success, '1' otherwise
 */
uint8_t writeValues();

    
//! It sends a packet from one XBee to another XBee in API mode
/*! This function performs application-level retries.
 * 	This function is only used for 64-bit addressing.
/*!
\param char* macAddress : destination MAC address
\param char* data : data to be sent (as string)
\return '0' on success, '1' error
 */
uint8_t send(char* macAddress, uint8_t* pointer, uint16_t length);
//uint8_t send( char* macAddress, char* data );

uint8_t setChannelMask( uint8_t* mask );
uint8_t getChannelMask();
uint8_t setPreambleID( uint8_t preambleID );
uint8_t getPreambleID();
//! It sends a packet to other XBee modules
/*!
\param struct packetXBee* packet : the function gets the needed information 
        to send the packet from it
\return '0' on success, '1' otherwise
*/
//uint8_t sendXBeePriv(struct packetXBee* packet); 
uint8_t sendXBeePriv(void); // TESTE

//! It parses the ZB TX Status message received by the XBee module
/*!This function is used for all protocols, but the 802.15.4
\param uint8_t* ByteIN : array to store the received answer
\return '0' if no error, '1' if error
*/
uint8_t txZBStatusResponse(void);


uint8_t setLinkKey(const char* key);
uint8_t setEncryptionMode(bool mode);
uint8_t getEncryptionMode();


void recebeByte(int8_t b);

uint8_t	data[100];

//! Variable: Channel mask
	uint8_t _channelMask[8];
    
//! Variable: Minimum Frequency Count
	uint8_t _preambleID;
    
//! Variable : It stores if the last call to an AT command has generated an error
/*!    
 */
int8_t error_AT;

//! Variable : 32b Lower Mac Source 
/*!    
 */
uint8_t sourceMacLow[4];

//! Variable : 32b Higher Mac Source
/*!    
 */
uint8_t sourceMacHigh[4];

//! Variable : array to store the AT commands
/*!
 */
uint8_t command[MAX_DATA];

//! Variable : protocol used (depends on de the XBee module)
/*!
 */
uint8_t protocol;
    
//! Variable : It stores if the last received packet has generated an error
/*!    
 */
int8_t error_RX;

//! Variable : It stores if the last sent packet has generated an error
/*!    
 */
int8_t error_TX;

    
//! Variable : 16b PAN ID
/*!    
 */
uint8_t PAN_ID[2];

//! Structure Variable : channel to set after re-programming
/*!    
 */
uint8_t channel;

//! Variable : specifies the maximum number of retries to be done	
/*! If the sending process fails, up to _send_retries are done
 */
uint8_t _send_retries=3;

//! Variable : delivery packet status
/*!
 */
uint8_t delivery_status;

//! Variable : discovery process status
/*!
 */
uint8_t discovery_status;

//! Variable : retries done during the sending
/*!
 */
uint8_t retries_sending;

bool encryptMode=false;
 
volatile union
{
    //uint8_t frameType;
    
    struct
    {
        uint16_t sizeData;
        uint8_t frameType;
        uint8_t reserved[3];
        uint8_t transmitRetryCount;
        uint8_t deliveryStatus;
        uint8_t discoveryStatus;
    } transmitStatus;
    
    struct
    {
        uint16_t sizeData;
        uint8_t frameType;
        uint8_t frameID;
        uint8_t ATCommand[2];
        uint8_t commandStatus;
        uint8_t commandData[MAX_DATA_RECEPCAO-7];
    } ATCommandResponse;
    
    int8_t frameData[MAX_DATA_RECEPCAO];
    
} response;

volatile union
{
    //uint8_t frameType;
    
    struct
    {
        uint16_t sizeData;
        uint8_t frameType;
        uint8_t sourceAddress[8];
        uint8_t reserved[2];
        uint8_t receiveOptions;
        uint8_t receivedData[MAX_DATA_RECEPCAO-14];
    } receivePacketAO0;
    
    struct
    {
        uint16_t sizeData;
        uint8_t frameType;
        uint8_t sourceAddress[8];
        uint8_t reserved[2];
        uint8_t sourceEndpoint;
        uint8_t destinationEndpoint;
        uint8_t clusterID[2];
        uint8_t profileID[2];
        uint8_t receiveOptions;
        uint8_t receivedData[MAX_DATA_RECEPCAO-20];
    } receivePacketAO1;
    
    int8_t frameData[MAX_DATA_RECEPCAO];
    
} receivePacket;


#ifdef	__cplusplus
}
#endif

#endif	/* XBEECORE_H */

