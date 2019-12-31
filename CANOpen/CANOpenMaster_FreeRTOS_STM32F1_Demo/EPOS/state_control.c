
#include "state_control.h"
#include "TestMaster.h"
#include "HW_epos.h"
#include "sdo_control.h"
#include "nmt_control.h"
#include "states.h"


void _preOperational(CO_Data* d){
	
	uint32_t data;
	
	if (!(*(d->iam_a_slave)))
	{
			
			masterNMT(d, Controller[0], NMT_Reset_Node);
			Epos_INIT();
			data = SDO_Read(Controller[0],OD_CTRL_WORD,0x00);
			
			MSG_WAR(0x1000,"GetWrite",data);
			data = SDO_Read(Controller[0],OD_CTRL_WORD,0x00);
			masterNMT(d, Controller[0], NMT_Start_Node);
	}
}
