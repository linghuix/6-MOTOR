#ifndef	_APP_H_
#define	_APP_H_


/**************** 用户任务声明 *******************/
void Task_Start(void *p_arg);

void CANApp_Task(void *p_arg);
void CANRcv_Task(void *p_arg);
void CANSend_Task(void *p_arg);
void Remote_Task(void *p_arg);
//void CANSend_Task(void *p_arg);


void TIMx_DispatchFromISR(void);
void CANRcv_DateFromISR(void);

#endif	//_APP_H_
