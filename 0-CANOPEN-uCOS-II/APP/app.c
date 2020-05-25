
#include "includes.h"
#include "TestMaster.h"

#define N_MESSAGES 10

INT8U error;


OS_STK canrcv_task_stk[TASK_A_STK_SIZE];		  	//定义栈
OS_STK cansend_task_stk[TASK_B_STK_SIZE];
OS_STK remote_task_stk[TASK_B_STK_SIZE];
OS_STK canapp_task_stk[TASK_B_STK_SIZE];



//预先分配好消息队列中的数据
void		*cantxMsgGrp[N_MESSAGES];				//定义队列消息指针数组	
void		*canrxMsgGrp[N_MESSAGES];	

CanTxMsg cantxmsg[N_MESSAGES];						//数据缓冲区(消息指针对应的数据)
CanRxMsg canrxmsg[N_MESSAGES];


OS_EVENT * CANRcv_Q, * CANSend_Q;


/* 定时器TIM相关变量 */
static TIMEVAL last_counter_val = 0;
static TIMEVAL elapsed_time = 0;


/********************************** CANOpen接口函数(需自己实现) **********************************/


/************************************************
功    能 ： CAN接收数据, 在接收中断函数中调用
参    数 ： RxMsg --- 接收数据(队列)
返 回 值 ： 无
作    者 ： xlh
*************************************************/
INT8U rxindex = 0;

void CANRcv_DateFromISR(void)
{
	OSIntEnter();
	
	CAN_Receive(CANx, CAN_FIFO0, &canrxmsg[rxindex]);
	rxindex++;															//**执行下个缓冲区，避免覆盖原来的按键数据**
	if(rxindex == N_MESSAGES)	rxindex=0;
	
	OSQPost (CANRcv_Q, &canrxmsg[rxindex]);

  OSIntExit();
}

/************************************************
功    能 ： 定时调度(从定时器中断), 
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void TIMx_DispatchFromISR(void){

	last_counter_val = 0;
	elapsed_time = 0;
	TimeDispatch();				// canopen 定时调度

}



/************************************************
功    能 ： 获取从上一次中断触发以来经过的时间
参    数 ： 无
返 回 值 ： (消逝的)时间
作    者 ： strongerHuang
*************************************************/
TIMEVAL getElapsedTime(void)
{
  uint32_t timer = TIM_GetCounter(CANOPEN_TIMx); // Copy the value of the running timer

  if(timer < last_counter_val)	//可以实现超过TIM最大定时时间的定时
    timer += CANOPEN_TIM_PERIOD;

  TIMEVAL elapsed = timer - last_counter_val + elapsed_time;
  //若中断前加入两次新的定时事件，必须加上旧的elapsed_time

  return elapsed;
}


/************************************************
功    能 ： Set the timer for the next alarm.
参    数 ： value --- 参数
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void setTimer(TIMEVAL value)
{
  uint32_t timer = TIM_GetCounter(CANOPEN_TIMx); 

  elapsed_time += timer - last_counter_val;
  last_counter_val = CANOPEN_TIM_PERIOD - value;
  
  //强制修改定时器计数，因此有elapsed_time
  TIM_SetCounter(CANOPEN_TIMx, CANOPEN_TIM_PERIOD - value);
  //TIM_Cmd(CANOPEN_TIMx, ENABLE);	//value后触发中断
}


/************************************************
功    能 ： CAN发送
参    数 ： notused --- 未使用参数
            m --------- 消息参数
返 回 值 ： 0:失败  1:成功
作    者 ： xlh
*************************************************/
INT8U txindex = 0;
unsigned char canSend(CAN_PORT notused, Message *m)
{
	uint8_t i;

	/*CanTxMsg TxMsg = cantxmsg[txindex];
	txindex++;									// 执行下个缓冲区，避免覆盖原来的数据
	if(txindex == N_MESSAGES)   txindex=0;

	TxMsg.StdId = m->cob_id;

	if(m->rtr)	TxMsg.RTR = CAN_RTR_REMOTE;
	else	TxMsg.RTR = CAN_RTR_DATA;

	TxMsg.IDE = CAN_ID_STD;
	TxMsg.DLC = m->len;
	for(i=0; i<m->len; i++)
	TxMsg.Data[i] = m->data[i];

	// 判断是否在执行中断 
	if(OSQPost(CANSend_Q, &TxMsg) != OS_ERR_NONE)
	{                                            //加入队列失败
	  return 0xFF;
	}*/
	printf("can send\r\n");
  return 0;
}



/********************************** 任务函数**********************************/


void CANOpen_App_Init(void);
void Remote_App_Init(void);

void Task_Start(void *p_arg)
{
    (void)p_arg;                // 'p_arg' 并没有用到，防止编译器提示警告

		printf("canopen motor controller ...\r\n");
	  printf("task: \r\n2 3 5 6 7\r\n");

		CANOpen_App_Init();			// canopen协议
		Remote_App_Init();			// 红外通讯远程遥控
		OSStatInit();

    while (1)
    {

			OSTimeDlyHMSM(0, 0,10,0);
			printf("CPU Usage = %d %% \r\n", OSCPUUsage);
   
    }
}

OS_Q *	gg;
void CANOpen_App_Init(void)
{
	CANRcv_Q = OSQCreate(&canrxMsgGrp[0],N_MESSAGES); 			//创建消息队列
	CANSend_Q = OSQCreate(&cantxMsgGrp[0],N_MESSAGES);
	
	gg = (OS_Q*)CANRcv_Q->OSEventPtr;

	/*OSTaskCreate(CANRcv_Task,(void *)0,		  				//创建CANRcv_Task任务
	   &canrcv_task_stk[TASK_A_STK_SIZE-1], TASK_canrcv_PRIO);*/
	OSTaskCreateExt(CANRcv_Task,(void *)0,&canrcv_task_stk[TASK_A_STK_SIZE-1], 
		TASK_canrcv_PRIO,0,&canrcv_task_stk[0],TASK_A_STK_SIZE,(void *)0,(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

	/*OSTaskCreate(CANSend_Task,(void *)0,				   	//创建CANSend_Task任务
	  &cansend_task_stk[TASK_B_STK_SIZE-1], TASK_cansend_PRIO);*/
	OSTaskCreateExt(CANSend_Task,(void *)0,&cansend_task_stk[TASK_B_STK_SIZE-1], 
		TASK_cansend_PRIO,0,&cansend_task_stk[0],TASK_B_STK_SIZE,(void *)0,(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	

	/*OSTaskCreate(CANApp_Task,(void *)0,					  	//创建CANApp_Task任务
		 &canapp_task_stk[TASK_A_STK_SIZE-1], TASK_canapp_PRIO);*/
	OSTaskCreateExt(CANApp_Task,(void *)0,&canapp_task_stk[TASK_canapp_STK_SIZE-1], 
		TASK_canapp_PRIO,0,&canapp_task_stk[0],TASK_canapp_STK_SIZE,(void *)0,(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

}

void Remote_App_Init(void)
{
	/*OSTaskCreate(Remote_Task,(void *)0,		  				//创建infrared 控制任务
		   &remote_task_stk[TASK_A_STK_SIZE-1], TASK_remote_PRIO);*/
	OSTaskCreateExt(Remote_Task,(void *)0,&remote_task_stk[TASK_A_STK_SIZE-1], 
		TASK_remote_PRIO,0,&remote_task_stk[0],TASK_A_STK_SIZE,(void *)0,(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
}


void CANApp_Task(void *p_arg){

	printf("CANApp_Task ...\r\n");
	unsigned char nodeID = 0x01;				   //节点ID
	setNodeId(&TestMaster_Data, nodeID);
	setState(&TestMaster_Data, Initialisation);
	setState(&TestMaster_Data, Pre_operational);	//心跳,同步周期协议配置 
	setState(&TestMaster_Data, Operational);

	for(;;)
	{
		OSTimeDlyHMSM(0, 0,0,5); 
	}

}

//CAN 接收任务
void CANRcv_Task(void *p_arg)
{	

	static CanRxMsg *RxMsg;
	static Message msg;

	
	uint8_t i = 0;
	(void)p_arg;   

	
	while(1){
	  if((RxMsg = (CanRxMsg *)OSQPend(CANRcv_Q, 100, &error)) != (void *)0){
			msg.cob_id = RxMsg->StdId;				   //CAN-ID
		
			if(CAN_RTR_REMOTE == RxMsg->RTR)
				msg.rtr = 1;							   //远程帧
			else
				msg.rtr = 0;							   //数据帧
		
			msg.len = (UNS8)RxMsg->DLC;				   //长度
		
			for(i=0; i<RxMsg->DLC; i++)				   //数据
				msg.data[i] = RxMsg->Data[i];
		
			TIM_ITConfig(CANOPEN_TIMx, TIM_IT_Update, DISABLE);
			canDispatch(&TestMaster_Data, &msg);	   //调用协议相关接口
			TIM_ITConfig(CANOPEN_TIMx, TIM_IT_Update, ENABLE);
	  }
	  OSTimeDly(100);
	}
}

//CAN 发送任务
void CANSend_Task(void *p_arg)
{
	static CanTxMsg * TxMsg;

    (void)p_arg;   
     while (1){
			if((TxMsg = (CanTxMsg *)OSQPend(CANSend_Q, 100, &error)) != (void *)0) //获取发送队列中数据
			{
				printf("send can\r\n");
				if(CAN_Transmit(CANx, TxMsg) == CAN_NO_MB){
					OSTimeDly(1);	//第一次发送失败, 延时1个滴答, 再次发送
					CAN_Transmit(CANx, TxMsg);
				}

			}
			OSTimeDlyHMSM(0, 0,0,10);
    }
}

//infrared 控制器
void Remote_Task(void *p_arg)
{
  (void)p_arg;   
	int *i;
	
    while (1){	
     OSTimeDlyHMSM(0, 0,0,5);
    }
}

