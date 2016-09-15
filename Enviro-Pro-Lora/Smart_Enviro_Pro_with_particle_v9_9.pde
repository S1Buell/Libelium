// Code 9.6 Change  the nodeAddress and nodeID.
//Alex & Tom
// Change Log // Things you need to Change
// 1. char nodeID[] = "SEPro03_Node26"; // change line ##
// 2.
// 3. 


// library
  #include <WaspSX1272.h>
  #include <WaspFrame.h>
  #include <WaspOPC_N2.h>
  #include <WaspSensorGas_Pro.h>
  #include <WaspAES.h>

//not used
  #define ALL_OFF_ALEX SENS_OFF | UART0_OFF | UART1_OFF | BAT_OFF | RTC_OFF

// Each object will be used by each gas sensor
  Gas CO(SOCKET_A);
  Gas O2(SOCKET_B);
  Gas CO2(SOCKET_C);
  Gas NO2(SOCKET_F);

// define the Waspmote ID 
// CHANGING NODEID FOR A NEW DEVICE

//////////////////////////////////////////
  char nodeID[] = "node26";
//////////////////////////////////////////

// Define the Meshlium address to send packets
// The default Meshlium address is '1'
  uint8_t meshlium_address = 2;

// Define private a 16-Byte key to encrypt message  
char password[] = "libeliumlibelium"; 


////////// IMPORTANT //////////////////////////
// Select the node address value: from 2 to 255
// CHANGING NODE ADDRESS FOR A NEW DEVICE
  uint8_t node_address = 26;

  
  
///////////////////////////////////////////
// Set all Global Variables here
///////////////////////////////////////////  
  float conc_CO;		// Stores the concentration level of CO in ppm
  float conc_O2;		// Stores the concentration level of O2 in ppm
  float conc_CO2;		// Stores the concentration level of CO2 in ppm
  float conc_NO2;		// Stores the concentration level of NO2 in ppm
  float temperature;	// Stores the temperature in ºC
  float humidity;		// Stores the realitve humidity in %RH
  float pressure;		// Stores the pressure in Pa
  int status;
  int measure;
  int e;

  void setup()
  {
  }


  void loop()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%END initial %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%Run Loop %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
{
// Init USB port
    USB.ON();
    USB.println(F("node26"));
    USB.println(F("code v9.6"));
    USB.println(F("Semtech SX1272 module. TX in LoRa to MESHLIUM"));

// Switch ON RTC
    RTC.ON();

// Switch ON ACC
    ACC.ON();

// set the Waspmote ID
    frame.setID(nodeID);  

    USB.println(F("----------------------------------------"));
    USB.println(F("Setting configuration:")); 
    USB.println(F("----------------------------------------"));
  
// Init sx1272 module
    sx1272.ON();

// Select frequency channel
  e = sx1272.setChannel(CH_12_900);
    USB.print(F("Setting Channel CH_12_900.\t state ")); 
    USB.println(e);

// Select implicit (off) or explicit (on) header mode
  e = sx1272.setHeaderON();
    USB.print(F("Setting Header ON.\t\t state "));  
    USB.println(e); 

// Select mode (mode 1)
  e = sx1272.setMode(1);  
    USB.print(F("Setting Mode '1'.\t\t state "));
    USB.println(e);  

// Select CRC on or off
  e = sx1272.setCRC_ON();
    USB.print(F("Setting CRC ON.\t\t\t state "));
    USB.println(e); 

// Select output power (Max, High or Low)
  e = sx1272.setPower('H');
    USB.print(F("Setting Power to 'H'.\t\t state ")); 
    USB.println(e); 
    
 // Select the maximum number of retries: from '0' to '5'
  e = sx1272.setRetries(5);
  USB.print(F("Setting Retries to '5'.\t\t state "));
  USB.println(e);
  USB.println();
  
  USB.println(F("----------------------------------------"));
  USB.println(F("Sending:")); 
  USB.println(F("----------------------------------------"));

  delay(1000); 

///////////////////////////////
  // 2. Get channel RSSI
  ///////////////////////////////
  e = sx1272.getRSSI();

  // check status
  if( e == 0 ) 
  {
    USB.print(F("Getting RSSI \t\t--> OK. "));
    USB.print(F("RSSI current value is: "));
    USB.println(sx1272._RSSI);

  }
  else 
  {
    USB.println(F("Getting RSSI --> ERROR"));
  } 



////////// IMPORTANT //////////////////////////
// Select the node address value: from 2 to 255
// CHANGING NODE ADDRESS FOR A NEW DEVICE 
  
  e = sx1272.setNodeAddress(node_address);
    USB.printf("Setting Node Address to %d  ",node_address);
    //USB.println(node_address);
 //   USB.print(F(" state "));
 //   USB.println(e);
    USB.println();

  delay(1000);
  
 
// get Time from RTC
  RTC.getTime();
  
  
///////////////////////////////////////////
// 1a. Turn on particle sensor
///////////////////////////////////////////  

// Power on the OPC_N2 sensor. 
// If the gases PRO board is off, turn it on automatically.
  status = OPC_N2.ON();
  if (status == 1)
  {
      USB.println(F("Particle sensor started"));
  }
  else
  {
      USB.println(F("Error starting the particle sensor"));
  }

///////////////////////////////////////////
// 1b. Read the particle sensor
///////////////////////////////////////////  

  if (status == 1)
  {
// Power the fan and the laser and perform a measure of 8 seconds
  measure = OPC_N2.getPM(8000);
    if (measure == 1)
    {
      USB.println(F("Measure performed"));
      USB.print(F("PM 1: "));
      USB.print(OPC_N2._PM1);
      USB.println(F(" ug/m3"));
      USB.print(F("PM 2.5: "));
      USB.print(OPC_N2._PM2_5);
      USB.println(F(" ug/m3"));
      USB.print(F("PM 10: "));
      USB.print(OPC_N2._PM10);
      USB.println(F(" ug/m3"));
    }
    else
    {
      USB.print(F("Error performing the measure. Error code:"));
      USB.println(measure, DEC);
    }
  }

///////////////////////////////////////////
// 1c. Turn off the particle sensor
/////////////////////////////////////////// 
// Power off the OPC_N2 sensor. If there aren't other sensors powered, 
// turn off the board automatically
    OPC_N2.OFF();

    delay(10000);

///////////////////////////////////////////
// 2a. Turn on gas sensors
/////////////////////////////////////////// 

// Power on the sensors. 
// If the gases PRO board is off, turn it on automatically.
    CO.ON();
    O2.ON();
    CO2.ON();
    NO2.ON();

// The sensor needs time to warm up and get a response from gas
// To reduce the battery consumption, use deepSleep instead delay
// After 2 minutes, Waspmote wakes up thanks to the RTC Alarm

    PWR.deepSleep("00:00:01:00", RTC_OFFSET, RTC_ALM1_MODE1, ALL_ON);

///////////////////////////////////////////
// 2b. Read gas sensors
///////////////////////////////////////////  
// Read the sensors and compensate with the temperature internally
    conc_CO = CO.getConc();
    conc_O2 = O2.getConc();
    conc_CO2 = CO2.getConc();
    conc_NO2 = NO2.getConc();

// Read enviromental variables
// In this case, CO objet has been used.
// O2, CO2 or NO2 objects could be used with the same result
    temperature = CO.getTemp();
    humidity = CO.getHumidity();
    pressure = CO.getPressure();

// And print the values via USB
    USB.println(F("***************************************"));
    USB.print(F("CO concentration: "));
    USB.print(conc_CO);
    USB.println(F(" ppm"));
    USB.print(F("O2 concentration: "));
    USB.print(conc_O2);
    USB.println(F(" ppm"));
    USB.print(F("CO2 concentration: "));
    USB.print(conc_CO2);
    USB.println(F(" ppm"));
    USB.print(F("NO2 concentration: "));
    USB.print(conc_NO2);
    USB.println(F(" ppm"));
    USB.print(F("Temperature: "));
    USB.print(temperature);
    USB.println(F(" Celsius degrees"));
    USB.print(F("RH: "));
    USB.print(humidity);
    USB.println(F(" %"));
    USB.print(F("Pressure: "));
    USB.print(pressure);
    USB.println(F(" Pa"));

// Show the remaining battery level
    USB.print(F("Battery Level: "));
    USB.print(PWR.getBatteryLevel(),DEC);
    USB.print(F(" %"));
  
// Show the battery Volts
    USB.print(F(" | Battery (Volts): "));
    USB.print(PWR.getBatteryVolts());
    USB.println(F(" V"));
  

///////////////////////////////////////////
// 2c. Turn off the gas sensors
/////////////////////////////////////////// 

// Power off the sensors sensor. If there aren't more gas sensors powered, 
// turn off the board automatically
    CO.OFF();
    O2.OFF();
    CO2.OFF();
    NO2.OFF();

///////////////////////////////////////////
// 1. Create ASCII frame
///////////////////////////////////////////  

  USB.println(F("Create a new Frame:"));
  

/////////////////////////////////////////////
// 6. set frame size via parameter given by the user
/////////////////////////////////////////////
//frame.setFrameSize(220);
//USB.print(F("\n frame size given by the user (220):"));
//USB.println(frame.getFrameSize(),DEC);  
//delay(500);


//%%%%%%%%%%%%%%%%%%% Binary %%%%%%%%%%%%%%%%%%%%%%%%%%%
// create new frame (MAX Frame)
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
frame.createFrame(MAX_FRAME);  
USB.println(frame.getFrameSize(),DEC);  
// add frame fields


//%%%%%%%% ASCII Frame %%%%%%%%%%%%%%%%%%%%
  // Create new frame (ASCII)
 //frame.createFrame(ASCII);
 //USB.println(frame.getFrameSize(),DEC); 
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


    frame.addSensor(SENSOR_DATE, RTC.date, RTC.month, RTC.year);
    frame.addSensor(SENSOR_TIME, RTC.hour, RTC.minute, RTC.second);
//  frame.addSensor(SENSOR_ACC, ACC.getX(), ACC.getY(), ACC.getZ());
//  frame.addSensor(SENSOR_BAT, PWR.getBatteryLevel()); 

// Add CO concentration
    frame.addSensor(SENSOR_GP_CO, conc_CO);
// Add O2 concentration
    frame.addSensor(SENSOR_GP_O2, conc_O2);
// Add CO2 concentration
    frame.addSensor(SENSOR_GP_CO2, conc_CO2);
// Add NO2 concentration
    frame.addSensor(SENSOR_GP_NO2, conc_NO2);
// Add temperature
    frame.addSensor(SENSOR_GP_TC, temperature);
// Add humidity
    frame.addSensor(SENSOR_GP_HUM, humidity);
// Add pressure
    frame.addSensor(SENSOR_GP_PRES, pressure);	
// Add PM 1
    frame.addSensor(SENSOR_OPC_PM1, OPC_N2._PM1); 
// Add PM 2.5
    frame.addSensor(SENSOR_OPC_PM2_5, OPC_N2._PM2_5); 
// Add PM 10
    frame.addSensor(SENSOR_OPC_PM10, OPC_N2._PM10); 
// Add PM 10
    frame.addSensor(SENSOR_BAT, PWR.getBatteryLevel()); 

// Prints frame
    frame.showFrame();

////////////////////////////////////////////////
  // 2. Create Frame with Encrypted contents
  ////////////////////////////////////////////////  
  USB.println(F("2. Encrypting Frame"));   

  /* Calculate encrypted message with ECB cipher mode and ZEROS padding
   The Encryption options are:
   - AES_128
   - AES_192
   - AES_256
   */
  frame.encryptFrame( AES_128, password ); 

  // Show the Encrypted frame via USB port
  frame.showFrame();
  USB.println();



///////////////////////////////////////////
// 2. Send packet
///////////////////////////////////////////  
  USB.println(F("----------------------------------------"));
  USB.println(F("Sending:")); 
  USB.println(F("----------------------------------------"));
  
// Sending packet before ending a timeout
//   e = sx1272.sendPacketTimeout ( meshlium_address, frame.buffer, frame.length );
e = sx1272.sendPacketTimeoutACKRetries ( meshlium_address, frame.buffer, frame.length );
// if ACK was received check signal strength
  if( e == 0 )
  {   
    USB.println(F("Packet sent OK"));     
  }
  else 
  {
    USB.println(F("Error sending the packet"));  
    USB.print(F("state: "));
    USB.println(e, DEC);
  } 

  USB.println();
  delay(2500);
      
// Go to deepsleep 
// After 1 hour, Waspmote wakes up thanks to the RTC Alarm
// PWR.deepSleep("00:00:15:00", RTC_OFFSET, RTC_ALM1_MODE1, ALL_OFF);

// Wake UP
  USB.ON();
  USB.println(F("\n Wake UP! \n"));
 
  delay(2500);
}
