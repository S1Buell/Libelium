#ifndef CONSTANTS_H
#define	CONSTANTS_H

#include "UT.h"

// Gases v20
#define SENSOR_CO	 		0
#define SENSOR_CO2 			1
#define SENSOR_O2			2
#define SENSOR_CH4			3
#define SENSOR_LPG			4
#define SENSOR_NH3			5
#define SENSOR_AP1			6
#define SENSOR_AP2			7
#define SENSOR_SV			8
#define SENSOR_NO2			9
#define SENSOR_O3			10
#define SENSOR_VOC			11
#define SENSOR_TCA			12
#define SENSOR_TFA			13
#define SENSOR_HUMA			14
#define SENSOR_PA			15
	
// Events v20	
#define SENSOR_PW  			16
#define SENSOR_BEND 		17
#define SENSOR_VBR  		18
#define SENSOR_HALL 		19
#define SENSOR_LP  			20
#define SENSOR_LL  			21
#define SENSOR_LUM  		22
#define SENSOR_PIR  		23
#define SENSOR_ST  			24
	
// Smart Cities		
#define SENSOR_MCP  		25
#define SENSOR_CDG  		26
#define SENSOR_CPG  		27
#define SENSOR_LD  			28
#define SENSOR_DUST			29
#define SENSOR_US  			30	
	
// Smart parking	
#define SENSOR_MF			31
#define SENSOR_PS			32
	
// Agriculture	
#define SENSOR_TCB			33
#define SENSOR_TFB			34
#define SENSOR_HUMB			35
#define SENSOR_SOILT 		36
#define SENSOR_SOIL 		37
#define SENSOR_LW  			38
#define SENSOR_PAR  		39
#define SENSOR_UV  			40
#define SENSOR_TD  			41	
#define SENSOR_SD  			42
#define SENSOR_FD  			43
#define SENSOR_ANE  		44
#define SENSOR_WV  			45
#define SENSOR_PLV  		46
	
// Radiation		
#define SENSOR_RAD  		47
	
// Smart metering	
#define SENSOR_CU  			48
#define SENSOR_WF  			49
#define SENSOR_LC  			50
#define SENSOR_DF  			51
	
// Additional	
#define SENSOR_BAT  		52
#define SENSOR_GPS  		53
#define SENSOR_RSSI  		54
#define SENSOR_MAC  		55
#define SENSOR_NA  			56
#define SENSOR_NID  		57
#define SENSOR_DATE 		58
#define SENSOR_TIME 		59
#define SENSOR_GMT  		60
#define SENSOR_RAM			61
#define SENSOR_IN_TEMP		62
#define SENSOR_ACC			63
#define SENSOR_MILLIS		64
	
// Special	
#define SENSOR_STR	 		65
	
// Meshlium	
#define SENSOR_MBT	 		66
#define SENSOR_MWIFI 		67
	
// RFID	
#define SENSOR_UID			68
#define SENSOR_RB	 		69

// Smart Water
#define SENSOR_PH			70
#define SENSOR_ORP	 		71
#define SENSOR_DO	 		72
#define SENSOR_COND	 		73
#define SENSOR_WT	 		74
#define SENSOR_DINA	 		75
#define SENSOR_DICA	 		76
#define SENSOR_DIF	 		77
#define SENSOR_DICL	 		78
#define SENSOR_DIBR	 		79
#define SENSOR_DII	 		80
#define SENSOR_DICU2		81
#define SENSOR_DIK	 		82
#define SENSOR_DIMG2		83
#define SENSOR_DINO3		84

// Smart Libelium
#define SENSOR_TX_PWR		85
#define SENSOR_DM_ST		86
#define SENSOR_DM_SP		87
#define SENSOR_LUX			88

// GPS
#define SENSOR_SPEED		89
#define SENSOR_COURSE		90
#define SENSOR_ALTITUDE		91
#define SENSOR_HDOP			92
#define SENSOR_VDOP			93
#define SENSOR_PDOP			94

// Finite State Machine status
#define SENSOR_FSM			95

// New pluviometer values
#define SENSOR_PLV1  		96
#define SENSOR_PLV2  		97
#define SENSOR_PLV3  		98

// P&S watermark sensors (Smart Agriculture)
#define SENSOR_SOIL_C  		99
#define SENSOR_SOIL_D  		100
#define SENSOR_SOIL_E  		101
#define SENSOR_SOIL_F  		102

// Waspmote OEM watermark sensors
#define SENSOR_SOIL1  		103
#define SENSOR_SOIL2  		104
#define SENSOR_SOIL3  		105

// DS18B20
#define SENSOR_TCC  		106

// P&S Ultrasound depending on socket voltage ref (Smart Cities & Smart Metering)
#define SENSOR_US_3V3  		107
#define SENSOR_US_5V  		108

// P&S Security sensors depending on socket (Smart Security)
#define SENSOR_LUM_D		109
#define SENSOR_LUM_E		110
#define SENSOR_LUM_F		111
#define SENSOR_LP_D			112
#define SENSOR_LP_E			113
#define SENSOR_LP_F			114
#define SENSOR_LL_D			115
#define SENSOR_LL_E			116
#define SENSOR_LL_F			117
#define SENSOR_HALL_D		118
#define SENSOR_HALL_E		119
#define SENSOR_HALL_F		120

// P&S liquid flow sensor depending on socket (Smart Metering)
#define SENSOR_WF_C			121
#define SENSOR_WF_E			122
	
// Unix/Epoch timestamp
#define SENSOR_TST			123
	
// Turbidity sensor
#define SENSOR_TURB			124

// Version parameters
#define SENSOR_VAPI			125
#define SENSOR_VPROG		126
#define SENSOR_VBOOT		127


// Gases PRO
#define SENSOR_GP_CL2		128
#define SENSOR_GP_CO		129
#define SENSOR_GP_ETO		130
#define SENSOR_GP_H2		131
#define SENSOR_GP_H2S		132
#define SENSOR_GP_HCL		133
#define SENSOR_GP_HCN		134
#define SENSOR_GP_NH3		135
#define SENSOR_GP_NO		136
#define SENSOR_GP_NO2		137
#define SENSOR_GP_O2		138
#define SENSOR_GP_PH3		139
#define SENSOR_GP_SO2		140
#define SENSOR_GP_CH4		141
#define SENSOR_GP_O3		142
#define SENSOR_GP_CO2		143
#define SENSOR_GP_TC		144
#define SENSOR_GP_TF		145
#define SENSOR_GP_HUM		146
#define SENSOR_GP_PRES		147

// OPCN2 Dust Sensor
#define SENSOR_OPC_TC		148
#define SENSOR_OPC_TF		149
#define SENSOR_OPC_P		150
#define SENSOR_OPC_PM1		151
#define SENSOR_OPC_PM2_5	152
#define SENSOR_OPC_PM10		153
#define SENSOR_OPC_PART		154

// Smart Water Ions
#define SENSOR_SWI_CA		155
#define SENSOR_SWI_FL		156
#define SENSOR_SWI_FB		157
#define SENSOR_SWI_NO		158
#define SENSOR_SWI_BR		159
#define SENSOR_SWI_CL		160
#define SENSOR_SWI_CU		161
#define SENSOR_SWI_IO		162
#define SENSOR_SWI_PB		163
#define SENSOR_SWI_AG		164
#define SENSOR_SWI_PH		165

// P&S Smart Water sensors depending on socket (Smart Water)
#define SENSOR_PH_A			166
#define SENSOR_PH_B			167
#define SENSOR_PH_C			168
#define SENSOR_ORP_A		169
#define SENSOR_ORP_B		170
#define SENSOR_ORP_C		171




/// Flash defines //////////////////////////////////////////////////////////////


/******************************************************************************* 
 * The following Flash strings, define the tags for all Waspmote sensors.
 * These TAGs are used in ASCII frames in order to indicate every sensor field
 * that has been included inside the frame.
 * 
 ******************************************************************************/

// Gases
const char	str_CO[]    = "CO";		// 0	
const char 	str_CO2[] 	= "CO2";	// 1
const char 	str_O2[] 	= "O2";		// 2	
const char 	str_CH4[] 	= "CH4";	// 3	
const char 	str_LPG[] 	= "LPG";	// 4	
const char 	str_NH3[] 	= "NH3";	// 5	
const char 	str_AP1[] 	= "AP1";	// 6	
const char 	str_AP2[] 	= "AP2";	// 7	
const char 	str_SV[] 	= "SV";		// 8	
const char 	str_NO2[] 	= "NO2";	// 9	
const char 	str_O3[] 	= "O3";		// 10	
const char 	str_VOC[] 	= "VOC";	// 11	
const char 	str_TCA[] 	= "TCA";	// 12	
const char 	str_TFA[] 	= "TFA";	// 13	
const char 	str_HUMA[] 	= "HUMA";	// 14	
const char 	str_PA[] 	= "PA";		// 15	

// Events
const char	str_PW[] 	= "PW";		// 16
const char	str_BEND[] 	= "BEND";	// 17
const char	str_VBR[] 	= "VBR";	// 18
const char	str_HALL[] 	= "HALL";	// 19
const char	str_LP[] 	= "LP";		// 20
const char	str_LL[] 	= "LL";		// 21
const char	str_LUM[] 	= "LUM";	// 22
const char	str_PIR[] 	= "PIR";	// 23
const char	str_ST[] 	= "ST";		// 24

// Smart cities
const char	str_MCP[] 	= "MCP";	// 25
const char	str_CDG[] 	= "CDG";	// 26
const char	str_CPG[] 	= "CPG";	// 27
const char	str_LD[] 	= "LD";		// 28
const char	str_DUST[] 	= "DUST";	// 29
const char	str_US[] 	= "US";		// 30

// Smart parking
const char	str_MF[] 	= "MF";		// 31
const char	str_PS[] 	= "PS";		// 32

// Agriculture
const char	str_TCB[] 	= "TCB";	// 33
const char	str_TFB[]	="TFB";	// 34
const char	str_HUMB[]	="HUMB";	// 35
const char	str_SOILT[] = "SOILT";	// 36
const char	str_SOIL[] 	= "SOIL";	// 37
const char	str_LW[] 	= "LW";		// 38
const char	str_PAR[] 	= "PAR";	// 39
const char	str_UV[] 	= "UV";		// 40
const char	str_TD[] 	= "TD";		// 41
const char	str_SD[] 	= "SD";		// 42
const char	str_FD[] 	= "FD";		// 43
const char	str_ANE[] 	= "ANE";	// 44
const char	str_WV[] 	= "WV";		// 45
const char	str_PLV[] 	= "PLV";	// 46

// Radiation
const char	str_RAD[] 	= "RAD";	// 47

// Smart meetering
const char	str_CU[] 	= "CU";		// 48
const char	str_WF[] 	= "WF";		// 49
const char	str_LC[] 	= "LC";		// 50
const char	str_DF[] 	= "DF";		// 51

// Additional
const char	str_BAT[] 	= "BAT";	// 52
const char	str_GPS[] 	= "GPS";	// 53
const char	str_RSSI[] 	= "RSSI";	// 54
const char	str_MAC[] 	= "MAC";	// 55
const char	str_NA[] 	= "NA";		// 56
const char	str_NID[] 	= "NID";	// 57
const char	str_DATE[] 	= "DATE";	// 58
const char	str_TIME[] 	= "TIME";	// 59
const char	str_GMT[] 	= "GMT";	// 60
const char	str_RAM[] 	= "RAM";	// 61
const char	str_IN_TEMP[] 	= "IN_TEMP";	// 62
const char	str_ACC[]	="ACC";	// 63
const char	str_MILLIS[] ="MILLIS"; // 64

// Special
const char	str_STR[] 	= "STR";	// 65

// Meshlium
const char	str_MBT[] 	= "MBT";	// 66
const char	str_MWIFI[] = "MWIFI";	// 67

// RFID
const char	str_UID[] 	= "UID";	// 68
const char	str_RB[] 	= "RB";		// 69

// Smart Water
const char	str_PH[] 	= "PH";		// 70
const char	str_ORP[] 	= "ORP";	// 71
const char	str_DO[] 	= "DO";		// 72
const char	str_COND[] 	= "COND";	// 73
const char	str_WT[] 	= "WT";		// 74
const char	str_DINA[] 	= "DINA";	// 75
const char	str_DICA[] 	= "DICA";	// 76
const char	str_DIF[] 	= "DIF";	// 77
const char	str_DICL[] 	= "DICL";	// 78
const char	str_DIBR[] 	= "DIBR";	// 79
const char	str_DII[] 	= "DII";	// 80
const char	str_DICU2[] = "DICU2";	// 81
const char	str_DIK[] 	= "DIK";	// 82
const char	str_DIMG2[] = "DIMG2";	// 83
const char	str_DINO3[] = "DINO3";	// 84

//Smart Libelium
const char	str_TX_PWR[]	="TX_PWR";	// 85
const char	str_DM_ST[]		="DM_ST";	// 86
const char	str_DM_SP[]		="DM_SP";	// 87
const char	str_LUX[]		="LUX";	// 88

//GPS
const char	str_SPEED[]		="SPEED_OG";	// 89
const char	str_COURSE[]	="COURSE_OG";	// 90
const char	str_ALTITUDE[]	="ALT";		// 91
const char	str_HDOP[]		="HDOP";		// 92
const char	str_VDOP[]		="VDOP";		// 93
const char	str_PDOP[]		="PDOP";		// 94

// Finite State Machine status
const char	str_FSM[]	="FSM";		// 95

// New Pluviometer values
const char	str_PLV1[]	="PLV1";		// 96
const char	str_PLV2[]	="PLV2";		// 97
const char	str_PLV3[]	="PLV3";		// 98

// P&S Watermarks depending on P&S connector
const char	str_SOIL_C[]	="SOIL_C";		// 99
const char	str_SOIL_D[]	="SOIL_D";		// 100
const char	str_SOIL_E[]	="SOIL_E";		// 101
const char	str_SOIL_F[]	="SOIL_F";		// 102

// Waspmote OEM watermark sensors (same as library)
const char	str_SOIL1[]	="SOIL1";		// 103
const char	str_SOIL2[]	="SOIL2";		// 104
const char	str_SOIL3[]	="SOIL3";		// 105

// DS18B20 (temperature: air, water, soil)
const char	str_TCC[]	="TCC";		// 106

// P&S Ultrasound depending on socket voltage ref
const char	str_US_3V3[]	="US_3V3";	// 107
const char	str_US_5V[]		="US_5V";	// 108

// P&S Security sensors depending on socket (Events board)
const char	str_LUM_D[]		="LUM_D";	// 109
const char	str_LUM_E[]		="LUM_E";	// 110
const char	str_LUM_F[]		="LUM_F";	// 111
const char	str_LP_D[]		="LP_D";	// 112
const char	str_LP_E[]		="LP_E";	// 113
const char	str_LP_F[]		="LP_F";	// 114
const char	str_LL_D[]		="LL_D";	// 115
const char	str_LL_E[]		="LL_E";	// 116
const char	str_LL_F[]		="LL_F";	// 117
const char	str_HALL_D[]	="HALL_D";	// 118
const char	str_HALL_E[]	="HALL_E";	// 119
const char	str_HALL_F[]	="HALL_F";	// 120

// P&S liquid flow sensor depending on socket (Smart Metering)
const char	str_WF_C[]		="WF_C";	// 121
const char	str_WF_E[]		="WF_E";	// 122

// Unix Epoch timestamp
const char	str_TST[]		="TST";	// 123

// Turbidity sensor
const char	str_TURB[]		="TURB";	// 124

// Version parameters
const char	str_VAPI[]	="VAPI";	// 125
const char	str_VPROG[]	="VPROG";	// 126
const char	str_VBOOT[]	="VBOOT";	// 127


// Gases PRO board
const char	str_GP_CL2[]	="GP_CL2";		// 128
const char	str_GP_CO[]		="GP_CO";		// 129
const char	str_GP_ETO[]	="GP_ETO";		// 130
const char	str_GP_H2[]		="GP_H2";		// 131
const char	str_GP_H2S[]	="GP_H2S";		// 132
const char	str_GP_HCL[]	="GP_HCL";		// 133
const char	str_GP_HCN[]	="GP_HCN";		// 134
const char	str_GP_NH3[]	="GP_NH3";		// 135
const char	str_GP_NO[]		="GP_NO";		// 136
const char	str_GP_NO2[]	="GP_NO2";		// 137
const char	str_GP_O2[]		="GP_O2";		// 138
const char	str_GP_PH3[]	="GP_PH3";		// 139
const char	str_GP_SO2[]	="GP_SO2";		// 140
const char	str_GP_CH4[]	="GP_CH4";		// 141
const char	str_GP_O3[]		="GP_O3";		// 142
const char	str_GP_CO2[]	="GP_CO2";		// 143
const char	str_GP_TC[]		="GP_TC";		// 144
const char	str_GP_TF[]		="GP_TF";		// 145
const char	str_GP_HUM[]	="GP_HUM";		// 146
const char	str_GP_PRES[]	="GP_PRES";	// 147

// OPCN2 Dust Sensor
const char	str_OPC_tc[]	="OPC_TC";		// 148
const char	str_OPC_tf[]	="OPC_TF";		// 149
const char	str_OPC_p[]		="OPC_P";		// 150
const char	str_OPC_pm1[]	="OPC_PM1";	// 151
const char	str_OPC_pm2_5[]	="OPC_PM2_5";	// 152
const char	str_OPC_pm10[]	="OPC_PM10";	// 153
const char	str_OPC_part[]	="OPC_PART";	// 154

// Smart Water Ions
const char	str_SWI_CA[]	="SWICA";	// 155
const char	str_SWI_FL[]	="SWIFL";	// 156
const char	str_SWI_FB[]	="SWIFB";	// 157
const char	str_SWI_NO[]	="SWINO";	// 158
const char	str_SWI_BR[]	="SWIBR";	// 159
const char	str_SWI_CL[]	="SWICL";	// 160
const char	str_SWI_CU[]	="SWICU";	// 161
const char	str_SWI_IO[]	="SWIIO";	// 162
const char	str_SWI_PB[]	="SWIPB";	// 163
const char	str_SWI_AG[]	="SWIAG";	// 164
const char	str_SWI_PH[]	="SWIPH";	// 165

// P&S Smart Water sensors depending on socket (Smart Water)
const char	str_PH_A[]		="PH_A";	//	166
const char	str_PH_B[]		="PH_B";	//	167
const char	str_PH_C[]		="PH_C";	//	168
const char	str_ORP_A[]		="ORP_A";	//	169
const char	str_ORP_B[]		="ORP_B";	//	170
const char	str_ORP_C[]		="ORP_C";	//	171

/******************************************************************************* 
 * SENSOR_TABLE - Sensor label table
 * 
 * This table specifies the tag for each sensor. Every tag has been previously 
 * defined in Flash memory
 ******************************************************************************/
const char* const SENSOR_TABLE[] = 	  
{
	// Gases
	str_CO,			// 0	
 	str_CO2,		// 1	
 	str_O2,			// 2	
 	str_CH4,		// 3	
 	str_LPG,		// 4	
 	str_NH3,		// 5	
 	str_AP1,		// 6	
 	str_AP2,		// 7	
 	str_SV,			// 8	
 	str_NO2,		// 9	
 	str_O3,			// 10	
 	str_VOC,		// 11	
 	str_TCA,		// 12	
 	str_TFA,		// 13	
 	str_HUMA,		// 14	
 	str_PA,			// 15	

	// Events
	str_PW,			// 16
	str_BEND,		// 17
	str_VBR,		// 18
	str_HALL,		// 19
	str_LP,			// 20
	str_LL,			// 21
	str_LUM,		// 22
	str_PIR,		// 23
	str_ST,			// 24

// Smart cities
	str_MCP,		// 25
	str_CDG,		// 26
	str_CPG,		// 27
	str_LD,			// 28
	str_DUST,		// 29
	str_US,			// 30

// Smart parking
	str_MF,			// 31
	str_PS,			// 32

// Agriculture
	str_TCB,		// 33
	str_TFB,		// 34
	str_HUMB,		// 35
	str_SOILT,		// 36
	str_SOIL,		// 37
	str_LW,			// 38
	str_PAR,		// 39
	str_UV,			// 40
	str_TD,			// 41
	str_SD,			// 42
	str_FD,			// 43
	str_ANE,		// 44
	str_WV,			// 45
	str_PLV,		// 46

	// Radiation
	str_RAD,		// 47

	// Smart meetering
	str_CU,			// 48
	str_WF,			// 49
	str_LC,			// 50
	str_DF,			// 51

	// Additional
	str_BAT,		// 52
	str_GPS,		// 53
	str_RSSI,		// 54
	str_MAC,		// 55
	str_NA,			// 56
	str_NID,		// 57
	str_DATE,		// 58
	str_TIME,		// 59
	str_GMT,		// 60
	str_RAM,		// 61
	str_IN_TEMP,	// 62
	str_ACC,		// 63
	str_MILLIS,		// 64

	// Special
	str_STR,		// 65

	// Meshlium
	str_MBT,		// 66
	str_MWIFI,		// 67

	// RFID
	str_UID,		// 68	
	str_RB,			// 69
	
	// Smart Water
	str_PH,			// 70
	str_ORP,		// 71
	str_DO,			// 72
	str_COND,		// 73
	str_WT, 		// 74
	str_DINA,		// 75
	str_DICA,		// 76
	str_DIF,		// 77
	str_DICL,		// 78
	str_DIBR,		// 79
	str_DII,		// 80
	str_DICU2,		// 81
	str_DIK,		// 82
	str_DIMG2,		// 83
	str_DINO3,		// 84
	
	//Smart Libelium
	str_TX_PWR,		// 85
	str_DM_ST,		// 86
	str_DM_SP,		// 87
	str_LUX,		// 88
	
	str_SPEED,		// 89
	str_COURSE,		// 90
	str_ALTITUDE,	// 91
	str_HDOP,		// 92
	str_VDOP,		// 93
	str_PDOP,		// 94
	
	// Finite State Machine
	str_FSM,		// 95
	
	// New Pluviometer values
	str_PLV1,		// 96
	str_PLV2,		// 97
	str_PLV3,		// 98
	
	// P&S watermarks
	str_SOIL_C,		// 99
	str_SOIL_D,		// 100
	str_SOIL_E,		// 101
	str_SOIL_F,		// 102
	
	// Waspmote OEM watermarks
	str_SOIL1,		// 103
	str_SOIL2,		// 104
	str_SOIL3,		// 105
	
	// DS18B20
	str_TCC, 		// 106
	
	// P&S ultrasound sensors depending on voltage ref
	str_US_3V3,		// 107
	str_US_5V,		// 108

	// P&S Security sensors depending on socket (Events board)
	str_LUM_D,	// 109
	str_LUM_E,	// 110
	str_LUM_F,	// 111
	str_LP_D,	// 112
	str_LP_E,	// 113
	str_LP_F,	// 114
	str_LL_D,	// 115
	str_LL_E,	// 116
	str_LL_F,	// 117
	str_HALL_D,	// 118
	str_HALL_E,	// 119
	str_HALL_F,	// 120	
	
	// P&S liquid flow sensor depending on socket (Smart Metering)
	str_WF_C,	// 121
	str_WF_E,	// 122
	
	// Unix/Epoch timestamp
	str_TST,	// 123
	
	// Turbidity sensor
	str_TURB,	// 124
	
	// Version parameters
	str_VAPI,	// 125
	str_VPROG,	// 126
	str_VBOOT,	// 127
	
	// Gases PRO Board
	str_GP_CL2,		// 128
	str_GP_CO,		// 129
	str_GP_ETO,		// 130
	str_GP_H2,		// 131
	str_GP_H2S,		// 132
	str_GP_HCL,		// 133
	str_GP_HCN,		// 134
	str_GP_NH3,		// 135
	str_GP_NO,		// 136
	str_GP_NO2,		// 137 
	str_GP_O2,		// 138
	str_GP_PH3,		// 139
	str_GP_SO2,		// 140
	str_GP_CH4,		// 141
	str_GP_O3,		// 142
	str_GP_CO2,		// 143
	str_GP_TC,		// 144
	str_GP_TF,		// 145
	str_GP_HUM,		// 146
	str_GP_PRES,	// 147

	// OPCN2 Dust Sensor
	str_OPC_tc,	// 148
	str_OPC_tf,	// 149
	str_OPC_p,	// 150
	str_OPC_pm1,	// 151
	str_OPC_pm2_5,	// 152
	str_OPC_pm10,	// 153
	str_OPC_part,	// 154
	
	// Smart Water Ions
	str_SWI_CA,	// 155
	str_SWI_FL,	// 156
	str_SWI_FB,	// 157
	str_SWI_NO,	// 158
	str_SWI_BR,	// 159
	str_SWI_CL,	// 160
	str_SWI_CU,	// 161
	str_SWI_IO,	// 162
	str_SWI_PB,	// 163
	str_SWI_AG,	// 164
	str_SWI_PH,	// 165
	
	// P&S Smart Water sensors depending on socket (Smart Water)
	str_PH_A,	//	166
	str_PH_B,	//	167
	str_PH_C,	//	168
	str_ORP_A,	//	169
	str_ORP_B,	//	170
	str_ORP_C,	//	171

};


/*******************************************************************************  
 * SENSOR_TYPE_TABLE - Binary frames sensor types
 * 
 * This table specifies the type of sensor depending on the type of value the
 * user must put as input. These are the possibilities:
 *	
 * 	0: uint8_t
 *	1: int (the same as int16_t)  
 *	2: double 
 *	3: char* 
 *  4: unsigned long
 *  5: uint8_t*
 ******************************************************************************/
const uint8_t SENSOR_TYPE_TABLE[] = 	  
{   
	// Gases
	2, // str_CO,		// 0	
	2, // str_CO2,		// 1
	2, // str_O2,		// 2			
	2, // str_CH4,		// 3
	2, // str_LPG,		// 4		
	2, // str_NH3,		// 5	
	2, // str_AP1,		// 6	
	2, // str_AP2,		// 7	
	2, // str_SV,		// 8		
	2, // str_NO2,		// 9		
	2, // str_O3,		// 10
	2, // str_VOC,		// 11	
	2, // str_TCA,		// 12	
	2, // str_TFA,		// 13	
	2, // str_HUMA,		// 14
	2, // str_PA,		// 15	
	
	// Events
	2, // str_PW,		// 16	
	2, // str_BEND,		// 17
	0, // str_VBR,		// 18
	0, // str_HALL,		// 19	
	0, // str_LP,		// 20	
	0, // str_LL,		// 21	
	2, // str_LUM,		// 22	
	0, // str_PIR,		// 23	
	2, // str_ST,		// 24	
	
	// Smart cities
	0, // str_MCP,		// 25
	0, // str_CDG,		// 26
	2, // str_CPG,		// 27
	2, // str_LD,		// 28
	2, // str_DUST,		// 29
	2, // str_US,		// 30
	
	// Smart parking
	1, //str_MF,		// 31
	0, //str_PS,		// 32
	
	// Agriculture
	2, // str_TCB,		// 33
	2, // str_TFB,		// 34
	2, // str_HUMB,		// 35
	2, // str_SOILT,	// 36
	2, // str_SOIL,		// 37
	2, // str_LW,		// 38
	2, // str_PAR,		// 39	
	2, // str_UV,		// 40		
	2, // str_TD,		// 41		
	2, // str_SD,		// 42		
	2, // str_FD,		// 43		
	2, // str_ANE,		// 44	
	0, // str_WV,		// 45	
	2, // str_PLV,		// 46
	
	// Radiation
	2, // str_RAD,		// 47
	
	// Smart meetering	
	2, // str_CU,		// 48
	2, // str_WF,		// 49
	2, // str_LC,		// 50
	2, // str_DF,		// 51
	
	// Additional
	0, // str_BAT,		// 52
	2, // str_GPS,		// 53
	1, // str_RSSI,		// 54
	3, // str_MAC,		// 55
	3, // str_NA,		// 56
	3, // str_NID,		// 57
	0, // str_DATE,		// 58
	0, // str_TIME,		// 59
	1, // str_GMT,		// 60
	1, // str_RAM,		// 61
	2, // str_IN_TEMP,	// 62
	1, // str_ACC,		// 63
	4, // str_MILLIS,	// 64
	
	
	// Special
	3, // str_STR		// 65

	// Meshlium
	3,	// str_MBT		// 66
	3,	//str_MWIFI		// 67

	// RFID
	3,	//str_UID		// 68
	3,	//str_RB		// 69	
	
	// Smart Water	
	2, // str_PH,		// 70
	2, // str_ORP,		// 71
	2, // str_DO,		// 72
	2, // str_COND,		// 73
	2, // str_WT, 		// 74
	2, // str_DINA,		// 75
	2, // str_DICA,		// 76
	2, // str_DIF,		// 77
	2, // str_DICL,		// 78
	2, // str_DIBR,		// 79
	2, // str_DII,		// 80
	2, // str_DICU2,	// 81
	2, // str_DIK,		// 82
	2, // str_DIMG2,	// 83
	2, // str_DINO3,	// 84	
	

	//Smart Libelium
	0,	//str_TX_PWR	// 85
	0,	//str_DM_ST,	// 86
	0,	//str_DM_SP,	// 87
	4,	//str_LUX		// 88
	
	//GPS
	2,	//str_SPEED		// 89
	2,	//str_COURSE	// 90
	2,	//str_ALTITUDE	// 91
	2,	//str_HDOP		// 92
	2,	//str_VDOP		// 93
	2,	//str_PDOP		// 94
	
	// States Machine
	0,	//str_FSM		// 95
	
	// New Pluviometer values
	2, //str_PLV1		// 96
	2, //str_PLV2		// 97
	2, //str_PLV3		// 98
	
	// P&S watermarks
	2, // str_SOIL_C,	// 99
	2, // str_SOIL_D,	// 100
	2, // str_SOIL_E,	// 101
	2, // str_SOIL_F,	// 102
	
	// Waspmote OEM watermarks
	2, // str_SOIL1,	// 103
	2, // str_SOIL2,	// 104
	2, // str_SOIL3,	// 105
	
	// DS18B20
	2, // str_TCC,		// 106
	
	// P&S ultrasound sensor depending on voltage ref
	2, // str_US_3V3,	// 107
	2, // str_US_5V,	// 108

	// P&S Security sensors depending on socket (Events board)
	2, // str_LUM_D,	// 109
	2, // str_LUM_E,	// 110
	2, // str_LUM_F,	// 111
	0, // str_LP_D,		// 112	
	0, // str_LP_E,		// 113	
	0, // str_LP_F,		// 114
	0, // str_LL_D,		// 115	
	0, // str_LL_E,		// 116
	0, // str_LL_F,		// 117	
	0, // str_HALL_D,	// 118
	0, // str_HALL_E,	// 119
	0, // str_HALL_F,	// 120
	
	// P&S liquid flow sensor depending on socket (Smart Metering)	
	2, // str_WF_C,		// 121
	2, // str_WF_E,		// 122
	
	// Unix/Epoch timestamp
	4, // str_TST,		// 123
	
	// Turbidity sensor
	2, // str_TURB,		// 124
	
	// Version parameters
	0, // str_VAPI,		// 125
	0, // str_VPROG,	// 126
	0, // str_VBOOT,	// 127	
	
	// Gases PRO Board
	2,	//str_GP_CL2,		// 128
	2,	//str_GP_CO,		// 129
	2,	//str_GP_ETO,		// 130
	2,	//str_GP_H2,		// 131
	2,	//str_GP_H2S,		// 132
	2,	//str_GP_HCL,		// 133
	2,	//str_GP_HCN,		// 134
	2,	//str_GP_NH3,		// 135
	2,	//str_GP_NO,		// 136
	2,	//str_GP_NO2,		// 137
	2,	//str_GP_O2,		// 138
	2,	//str_GP_PH3,		// 139
	2,	//str_GP_SO2,		// 140
	2,	//str_GP_CH4,		// 141
	2,	//str_GP_O3,		// 142
	2,	//str_GP_CO2,		// 143
	2,	//str_GP_TC			// 144
	2,	//str_GP_TF			// 145
	2,	//str_GP_HUM		// 146
	2,	//str_GP_PRES		// 147

	// OPCN2 Dust Sensor
	2,	//str_OPC_tc	// 148
	2,	//str_OPC_tf	// 149
	2,	//str_OPC_p		// 150
	2,	//str_OPC_pm1	// 151
	2,	//str_OPC_pm2_5	// 152
	2,	//str_OPC_pm10	// 153
	2,	//str_OPC_part	// 154
	
	// Smart Water Ions
	2,	//str_SWI_CA,	// 155
	2, 	//str_SWI_FL,	// 156
	2,	//str_SWI_FB,	// 157
	2,	//str_SWI_NO,	// 158
	2,	//str_SWI_BR,	// 159
	2,	//str_SWI_CL,	// 160
	2,	//str_SWI_CU,	// 161
	2,	//str_SWI_IO,	// 162
	2,	//str_SWI_PB,	// 163
	2,	//str_SWI_AG,	// 164
	2,	//str_SWI_PH,	// 165
	
	// P&S Smart Water sensors depending on socket (Smart Water)
	2, // str_PH_A,		// 166
	2, // str_PH_B,		// 167
	2, // str_PH_C,		// 168
	2, // str_ORP_A,	// 169
	2, // str_ORP_B,	// 170
	2, // str_ORP_C,	// 171
	
};


/*******************************************************************************  
 * SENSOR_FIELD_TABLE - Sensor fields
 * 
 * This table specifies the number of fields per sensor. 
 * 
 * For example, a temperature sensor indicates the temperature in a single field. 
 * On the other hand, the GPS module indicates the position with two fields: 
 * latitude and longitude
 ******************************************************************************/
const uint8_t SENSOR_FIELD_TABLE[] = 	  
{   
	// Gases
	1, // str_CO,		// 0
	1, // str_CO2,		// 1
	1, // str_O2,		// 2
	1, // str_CH4,		// 3
	1, // str_LPG,		// 4
	1, // str_NH3,		// 5
	1, // str_AP1,		// 6
	1, // str_AP2,		// 7
	1, // str_SV,		// 8
	1, // str_NO2,		// 9	
	1, // str_O3,		// 10
	1, // str_VOC,		// 11
	1, // str_TCA,		// 12
	1, // str_TFA,		// 13	
	1, // str_HUMA,		// 14
	1, // str_PA,		// 15
	
	// Events
	1, // str_PW,		// 16
	1, // str_BEND,		// 17
	1, // str_VBR,		// 18
	1, // str_HALL,		// 19
	1, // str_LP,		// 20	
	1, // str_LL,		// 21	
	1, // str_LUM,		// 22	
	1, // str_PIR,		// 23	
	1, // str_ST,		// 24
	
	// Smart cities
	1, // str_MCP,		// 25
	1, // str_CDG,		// 26
	1, // str_CPG,		// 27
	1, // str_LD,		// 28
	1, // str_DUST,		// 29
	1, // str_US,		// 30
	
	// Smart parking
	3, //str_MF,		// 31
	1, //str_PS,		// 32
	
	// Agriculture
	1, // str_TCB,		// 33
	1, // str_TFB,		// 34
	1, // str_HUMB,		// 35
	1, // str_SOILT,	// 36
	1, // str_SOIL,		// 37
	1, // str_LW,		// 38	
	1, // str_PAR,		// 39
	1, // str_UV,		// 40	
	1, // str_TD,		// 41		
	1, // str_SD,		// 42	
	1, // str_FD,		// 43	
	1, // str_ANE,		// 44
	1, // str_WV,		// 45	
	1, // str_PLV,		// 46
	
	// Radiation
	1, // str_RAD,		// 47
	
	// Smart meetering
	1, // str_CU,		// 48
	1, // str_WF,		// 49
	1, // str_LC,		// 50
	1, // str_DF,		// 51
	
	// Additional
	1, // str_BAT,		// 52
	2, // str_GPS,		// 53
	1, // str_RSSI,		// 54
	1, // str_MAC,		// 55
	1, // str_NA,		// 56
	1, // str_NID,		// 57
	3, // str_DATE,		// 58
	3, // str_TIME,		// 59
	1, // str_GMT,		// 60	
	1, // str_RAM,		// 61
	1, // str_IN_TEMP,	// 62
	3, // str_ACC,		// 63
	1, // str_MILLIS,	// 64	
	
	// Special
	1, // str_STR		// 65

	// Meshlium
	1, // str_MBT		// 66
	1, //str_MWIFI		// 67

	// RFID
	1, //str_UID		// 68
	1,  //str_RB		// 69
	
	// Smart Water
	1, //str_PH,		// 70
	1, //str_ORP,		// 71
	1, //str_DO,		// 72
	1, //str_COND,		// 73
	1, //str_WT, 		// 74
	1, //str_DINA,		// 75
	1, //str_DICA,		// 76
	1, //str_DIF,		// 77
	1, //str_DICL,		// 78
	1, //str_DIBR,		// 79
	1, //str_DII,		// 80
	1, //str_DICU2,		// 81
	1, //str_DIK,		// 82
	1, //str_DIMG2,		// 83
	1, //str_DINO3,		// 84

	//Smart Libelium
	1,	//str_TX_PWR	// 85
	3,	//str_DM_ST,	// 86
	3,	//str_DM_SP,	// 87
	1,	//str_LUX		// 88
	
	//GPS
	1,	//str_SPEED		// 89
	1,	//str_COURSE	// 90
	1,	//str_ALTITUDE	// 91
	1,	//str_HDOP		// 92
	1,	//str_VDOP		// 93
	1,	//str_PDOP		// 94
	
	// States Machine
	1,	//str_FSM		// 95
	
	// New Pluviometer values
	1, //str_PLV1		// 96
	1, //str_PLV2		// 97
	1, //str_PLV3		// 98
	
	// P&S watermarks
	1, // str_SOIL_C,	// 99
	1, // str_SOIL_D,	// 100
	1, // str_SOIL_E,	// 101
	1, // str_SOIL_F,	// 102
	
	// Waspmote OEM watermarks
	1, // str_SOIL1,	// 103
	1, // str_SOIL2,	// 104
	1, // str_SOIL3,	// 105
	
	// DS18B20
	1, // str_TCC,		// 106
	
	// P&S ultrasound sensor depending on voltage ref
	1, // str_US_3V3,	// 107
	1, // str_US_5V,	// 108

	// P&S Security sensors depending on socket (Events board)
	1, // str_LUM_D,	// 109
	1, // str_LUM_E,	// 110
	1, // str_LUM_F,	// 111
	1, // str_LP_D,		// 112
	1, // str_LP_E,		// 113
	1, // str_LP_F,		// 114
	1, // str_LL_D,		// 115
	1, // str_LL_E,		// 116
	1, // str_LL_F,		// 117
	1, // str_HALL_D,	// 118
	1, // str_HALL_E,	// 119
	1, // str_HALL_F,	// 120
	
	// P&S liquid flow sensor depending on socket (Smart Metering)
	1, // str_WF_C,		// 121
	1, // str_WF_E,		// 122
	
	// Unix/Epoch timestamp
	1, // str_TST,		// 123
	
	// Turbidity sensor
	1, // str_TURB,		// 124
	
	// Version parameters
	1, // str_VAPI,		// 125
	1, // str_VPROG,	// 126
	1, // str_VBOOT,	// 127
		
	// Gases PRO Board
	1,	//str_GP_CL2,		// 128
	1,	//str_GP_CO,		// 129
	1,	//str_GP_ETO,		// 130
	1,	//str_GP_H2,		// 131
	1,	//str_GP_H2S,		// 132
	1,	//str_GP_HCL,		// 133
	1,	//str_GP_HCN,		// 134
	1,	//str_GP_NH3,		// 135
	1,	//str_GP_NO,		// 136
	1,	//str_GP_NO2,		// 137
	1,	//str_GP_O2,		// 138
	1,	//str_GP_PH3,		// 139
	1,	//str_GP_SO2,		// 140
	1,	//str_GP_CH4,		// 141
	1,	//str_GP_O3,		// 142
	1,	//str_GP_CO2,		// 143
	1,	//str_GP_TC			// 144
	1,	//str_GP_TF			// 145
	1,	//str_GP_HUM		// 146
	1,	//str_GP_PRES		// 147

	// OPC_N2
	1,	//str_OPC_tc		// 148
	1,	//str_OPC_tf		// 149
	1,	//str_OPC_p			// 150
	1,	//str_OPC_pm1		// 151
	1,	//str_OPC_pm2_5		// 152
	1,	//str_OPC_pm10		// 153
	2,	//str_OPC_part		// 154
	
	// Smart Water Ions
	1,	//str_SWI_CA,	// 155
	1, 	//str_SWI_FL,	// 156
	1,	//str_SWI_FB,	// 157
	1,	//str_SWI_NO,	// 158
	1,	//str_SWI_BR,	// 159
	1,	//str_SWI_CL,	// 160
	1,	//str_SWI_CU,	// 161
	1,	//str_SWI_IO,	// 162
	1,	//str_SWI_PB,	// 163
	1,	//str_SWI_AG,	// 164
	1,	//str_SWI_PH,	// 165
	
	// P&S Smart Water sensors depending on socket (Smart Water)
	1, // str_PH_A,		// 166
	1, // str_PH_B,		// 167
	1, // str_PH_C,		// 168
	1, // str_ORP_A,	// 169
	1, // str_ORP_B,	// 170
	1, // str_ORP_C,	// 171
};



/******************************************************************************* 
 * DECIMAL_TABLE - number of default decimals for each sensor for ASCII frames
 * 
 * This table specifies the number of decimals for each sensor for ASCII frames
 ******************************************************************************/
const uint8_t DECIMAL_TABLE[]=	  
{   
	// Gases
	3, // str_CO,		// 0
	3, // str_CO2,		// 1
	3, // str_O2,		// 2
	3, // str_CH4,		// 3
	3, // str_LPG,		// 4
	3, // str_NH3,		// 5
	3, // str_AP1,		// 6
	3, // str_AP2,		// 7
	3, // str_SV,		// 8	
	3, // str_NO2,		// 9	
	3, // str_O3,		// 10
	3, // str_VOC,		// 11
	2, // str_TCA,		// 12
	2, // str_TFA,		// 13	
	1, // str_HUMA,		// 14
	2, // str_PA,		// 15
	
	// Events
	3, // str_PW,		// 16	
	3, // str_BEND,		// 17
	0, // str_VBR,		// 18

	0, // str_HALL,		// 19
	0, // str_LP,		// 20	
	0, // str_LL,		// 21	
	3, // str_LUM,		// 22	
	0, // str_PIR,		// 23	
	3, // str_ST,		// 24
	
	// Smart cities
	0, // str_MCP,		// 25
	0, // str_CDG,		// 26
	3, // str_CPG,		// 27
	3, // str_LD,		// 28
	3, // str_DUST,		// 29
	2, // str_US,		// 30
	
	// Smart parking
	0, //str_MF,		// 31
	0, //str_PS,		// 32
	
	// Agriculture
	2, // str_TCB,		// 33
	2, // str_TFB,		// 34
	1, // str_HUMB,		// 35
	2, // str_SOILT,	// 36
	2, // str_SOIL,		// 37
	3, // str_LW,		// 38	
	2, // str_PAR,		// 39
	2, // str_UV,		// 40	
	3, // str_TD,		// 41		
	3, // str_SD,		// 42	
	3, // str_FD,		// 43	
	2, // str_ANE,		// 44
	0, // str_WV,		// 45	
	2, // str_PLV,		// 46
	
	// Radiation
	6, // str_RAD,		// 47
	
	// Smart meetering
	2, // str_CU,		// 48
	3, // str_WF,		// 49
	3, // str_LC,		// 50
	3, // str_DF,		// 51
	
	// Additional
	0, // str_BAT,		// 52	
	6, // str_GPS,		// 53
	0, // str_RSSI,		// 54
	0, // str_MAC,		// 55
	0, // str_NA,		// 56
	0, // str_NID,		// 57
	0, // str_DATE,		// 58
	0, // str_TIME,		// 59
	0, // str_GMT,		// 60	
	0, // str_RAM,		// 61
	2, // str_IN_TEMP,	// 62
	0, // str_ACC,		// 63
	0, // str_MILLIS,	// 64	
	
	// Special
	0, // str_STR		// 65

	// Meshlium
	0, // str_MBT		// 66
	0, //str_MWIFI		// 67

	// RFID
	0, //str_UID		// 68
	0, //str_RB			// 69
	
	// Smart Water
	2, //str_PH,		// 70
	3, //str_ORP,		// 71
	1, //str_DO,		// 72
	1, //str_COND,		// 73
	2, //str_WT, 		// 74
	3, //str_DINA,		// 75
	3, //str_DICA,		// 76
	3, //str_DIF,		// 77
	3, //str_DICL,		// 78
	3, //str_DIBR,		// 79
	3, //str_DII,		// 80
	3, //str_DICU2,		// 81
	3, //str_DIK,		// 82
	3, //str_DIMG2,		// 83
	3, //str_DINO3,		// 84

	//Smart Libelium
	0,	//str_TX_PWR	// 85
	0,	//str_DM_ST,	// 86
	0,	//str_DM_SP,	// 87
	3,	//str_LUX		// 88
	
	//GPS
	2,	//str_SPEED		// 89
	2,	//str_COURSE	// 90
	2,	//str_ALTITUDE	// 91
	3,	//str_HDOP		// 92
	3,	//str_VDOP		// 93
	3,	//str_PDOP		// 94	
	
	// States Machine
	0,	//str_FSM		// 95
	
	// New Pluviometer values
	2, //str_PLV1		// 96
	2, //str_PLV2		// 97
	2, //str_PLV3		// 98	
	
	// P&S watermarks
	2, // str_SOIL_C,	// 99
	2, // str_SOIL_D,	// 100
	2, // str_SOIL_E,	// 101
	2, // str_SOIL_F,	// 102
	
	// Waspmote OEM watermarks
	2, // str_SOIL1,	// 103
	2, // str_SOIL2,	// 104
	2, // str_SOIL3,	// 105
	
	// DS18B20 
	2, // str_TCC,		// 106
	
	// P&S ultrasound sensor depending on voltage ref
	2, // str_US_3V3,	// 107
	2, // str_US_5V,	// 108

	// P&S Security sensors depending on socket (Events board)
	3, // str_LUM_D,	// 109
	3, // str_LUM_E,	// 110
	3, // str_LUM_F,	// 111
	0, // str_LP_D,		// 112
	0, // str_LP_E,		// 113
	0, // str_LP_F,		// 114
	0, // str_LL_D,		// 115
	0, // str_LL_E,		// 116
	0, // str_LL_F,		// 117
	0, // str_HALL_D,	// 118
	0, // str_HALL_E,	// 119
	0, // str_HALL_F,	// 120
	
	// P&S liquid flow sensor depending on socket (Smart Metering)
	3, // str_WF_C,		// 121
	3, // str_WF_E,		// 122
	
	// Unix/Epoch timestamp
	0, // str_TST,		// 123
	
	// Turbidity sensor
	1, // str_TURB,		// 124
	
	// Version parameters
	0, // str_VAPI,		// 125
	0, // str_VPROG,	// 126
	0, // str_VBOOT,	// 127
	
	// Gases PRO Board
	3,	//str_GP_CL2,		// 128
	3,	//str_GP_CO,		// 129
	3,	//str_GP_ETO,		// 130
	3,	//str_GP_H2,		// 131
	3,	//str_GP_H2S,		// 132
	3,	//str_GP_HCL,		// 133
	3,	//str_GP_HCN,		// 134
	3,	//str_GP_NH3,		// 135
	3,	//str_GP_NO,		// 136
	3,	//str_GP_NO2,		// 137
	3,	//str_GP_O2,		// 138
	3,	//str_GP_PH3,		// 139
	3,	//str_GP_SO2,		// 140
	3,	//str_GP_CH4,		// 141
	3,	//str_GP_O3,		// 142
	3,	//str_GP_CO2,		// 143	
	3,	//str_GP_TC			// 144
	2,	//str_GP_TF			// 145
	2,	//str_GP_HUM		// 146
	0,	//str_GP_PRES		// 147	
	
	// OPC_N2
	2,	//str_OPC_tc		// 148
	2,	//str_OPC_tf		// 149
	0,	//str_OPC_p			// 150
	4,	//str_OPC_pm1		// 151
	4,	//str_OPC_pm2_5		// 152
	4,	//str_OPC_pm10		// 153
	0,	//str_OPC_part		// 154
	
	// Smart Water Ions
	3,	//str_SWI_CA,	// 155
	3,	//str_SWI_FL,	// 156
	3,	//str_SWI_FB,	// 157
	3,	//str_SWI_NO,	// 158
	3,	//str_SWI_BR,	// 159
	3,	//str_SWI_CL,	// 160
	3,	//str_SWI_CU,	// 161
	3,	//str_SWI_IO,	// 162
	3,	//str_SWI_PB,	// 163
	3,	//str_SWI_AG,	// 164
	3,	//str_SWI_PH,	// 165
	
	// P&S Smart Water sensors depending on socket (Smart Water)
	2, // str_PH_A,		// 166
	2, // str_PH_B,		// 167
	2, // str_PH_C,		// 168
	3, // str_ORP_A,	// 169
	3, // str_ORP_B,	// 170
	3, // str_ORP_C,	// 171
};

#ifdef	__cplusplus
}
#endif

#endif	/* CONSTANTS_H */