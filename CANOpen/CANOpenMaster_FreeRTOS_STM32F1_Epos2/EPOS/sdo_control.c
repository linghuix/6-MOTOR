#include "HW_epos.h"
#include "epos.h"

#include "canfestival.h"
#include "TestMaster.h"
#include "sdo_control.h"

#include "FreeRTOS.h"//vTaskDelay
#include "semphr.h"
#include "task.h"
/***** 
write parameter to Object Dictionary through CAN use SDO messages
******/

int NEST = 0;           //嵌套层数

/**
 *
 */
void _sdocallback(CO_Data* d, UNS8 nodeId){
	MSG_WAR(0x0000, "sdocallback in nodeid: ", nodeId);
	//resetSDO(d);
}

u_int8_t last_success = 1;	//上一次是否发送成功，这关系到发送ｌｉｎｅ是否被初始化
uint8_t SDO_Write(Epos* epos,Uint32 Index_Type,Uint8 SubIndex,Uint32 param)
{
	UNS32 abortCode;
	UNS16 Index = Index_Type>>16;
	UNS32 Size = (Index_Type&(UNS32)0xFF)>>3;
	UNS8 Type;
	if(Size == 4){Type = uint32;}
	if(Size == 2){Type = uint16;}
	if(Size == 1){Type = uint8;}

    do{
		if(last_success == 0)
		    resetSDO(&TestMaster_Data);
		_writeNetworkDict(&TestMaster_Data,epos->node_ID ,Index, SubIndex, Size, Type, &param, _sdocallback, 1, 0);
		vTaskDelay(500);
	}while( i-- && (SDO_state = getWriteResultNetworkDict(&TestMaster_Data, epos->node_ID , &abortCode)) == SDO_DOWNLOAD_IN_PROGRESS );

	if (SDO_state == SDO_FINISHED){
		last_success = 1;
		MMSG("write SDO OK!\r\n");
	}
	else{
		last_success = 0;
		MMSG("write SDO error! state = %u \r\n",SDO_state);
	}
	return 0;
}


/**** 发送CAN SDO读报文，并接受返回值 ***/
Uint32 SDO_Read(Epos* epos,Uint32 Index_Type,Uint8 SubIndex)
{	
	UNS32 data;
	UNS32 abortCode;
	UNS16 Index = Index_Type>>16;
	UNS32 Size = (Index_Type&(UNS32)0xFF)>>3;
	UNS8 Type;
	if(Size == 4){Type = uint32;}
	if(Size == 2){Type = uint16;}
	if(Size == 1){Type = uint8;}
	
    do{
		resetSDO(&TestMaster_Data);
		readNetworkDict(&TestMaster_Data,epos->node_ID ,Index, SubIndex, Type, 0);
		vTaskDelay(500);
	}while( i-- && (getReadResultNetworkDict(&TestMaster_Data, epos->node_ID, &data, &Size, &abortCode) == SDO_UPLOAD_IN_PROGRESS));


	return data;
}
