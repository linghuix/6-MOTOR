底层CAN发送包代码
	canopen_drv.c
    
    
CANOpen_App_Task
    setState(&TestMaster_Data, Initialisation)
        switchCommunicationState
            StartOrStop  startLSS
    
    setState(&TestMaster_Data, Initialisation)
        switchCommunicationState
            SDO,SYNC,LifeGuard,csEmergency,PDO


​           

// 神奇的宏定义，这样只要用 
// StartOrStop(csSDO,	None,		resetSDO(d)) 就可以调用了

#define StartOrStop(CommType, FuncStart, FuncStop) \
	if(newCommunicationState->CommType && d->CurrentCommunicationState.CommType == 0){\
		MSG_WAR(0x9999,#FuncStart, 9999);\
		d->CurrentCommunicationState.CommType = 1;\
		FuncStart;\
	}else if(!newCommunicationState->CommType && d->CurrentCommunicationState.CommType == 1){\
		MSG_WAR(0x9999,#FuncStop, 9999);\
		d->CurrentCommunicationState.CommType = 0;\
		FuncStop;\
	}