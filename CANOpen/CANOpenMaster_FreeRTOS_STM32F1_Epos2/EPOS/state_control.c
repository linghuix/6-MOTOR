
#include "state_control.h"
#include "TestMaster.h"
#include "HW_epos.h"
#include "sdo_control.h"
#include "nmt_control.h"
#include "states.h"

UNS32 Edit_Dict(CO_Data* d, Uint32 Index_Type,Uint8 SubIndex, void* pdata)
{
	UNS32 retcode;
	UNS16 Index = Index_Type>>16;
	UNS32 ByteSize = (Index_Type&(UNS32)0xFF)>>3;

	retcode = setODentry( d, Index, SubIndex, pdata, &ByteSize, 1 );

	return retcode;
}

void _preOperational(CO_Data* d){
	
uint32_t data;
	
	if (!(*(d->iam_a_slave)))
	{
			
			masterNMT(d, Controller[0], NMT_Reset_Node);
			Epos_INIT();

			data = SDO_Read(Controller[0],OD_CTRL_WORD,0x00);
			MSG_WAR(0x1000,"GetWrite",data);

			masterNMT(d, Controller[0], NMT_Start_Node);
	}
}

void _operational(CO_Data* d)
{
    (void)d;
	MSG("complete operational\r\n");
}


#include "gait.h"
uint8_t pdoindex = 0;
uint8_t Index = 0;
void _post_TPDO(CO_Data* d)
{
	UNS32 re;
	UNS32 angle = test_angle[Index];
	re = Edit_Dict(d , Pos_SET_VALUE, 0, &angle);

	if(re == OD_SUCCESSFUL)
		MSG("-TPDO_update- index %d\r\n",Index);
	else
		MSG("-TPDO update error- 0x%lx\r\n",re);
	if(++Index == 120) Index = 0;
}
