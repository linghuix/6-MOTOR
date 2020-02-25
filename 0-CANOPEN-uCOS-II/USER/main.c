/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * 文件名  ：main.c
 * 描述    ：建立3个任务，每个任务控制一个LED，以固定的频率轮流闪烁（频率可调）。         
 * 实验平台：野火STM32开发板
 * 库版本  ：ST3.0.0
 *
 * 作者    ：wildfire team 
 * 论坛    ：http://www.amobbs.com/forum-1008-1.html
 * 淘宝    ：http://firestm32.taobao.com
**********************************************************************************/
#include "includes.h"


OS_STK startup_task_stk[STARTUP_TASK_STK_SIZE];		  //定义栈
  
int main(void)
{
	BSP_Init();
	OSInit();
	OSTaskCreate(Task_Start,(void *)0,
	   &startup_task_stk[STARTUP_TASK_STK_SIZE-1], STARTUP_TASK_PRIO);

	OSStart();
	return 0;
 }


/*
*********************************************************************************************************
*                                              TaskIdleHook
*
* Description: 闪烁灯提示
*
* Arguments  : none
*
* Returns    : none
*
* Note(s)    : 
*********************************************************************************************************
*/

void App_TaskIdleHook(void){
	GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))));
}


void          App_TaskCreateHook      (OS_TCB          *ptcb){};

void          App_TaskDelHook         (OS_TCB          *ptcb){};

void          App_TaskReturnHook      (OS_TCB          *ptcb){};

/*
*********************************************************************************************************
*                                              TaskIdleHook
*
* Description: CPU 使用率提示
*
* Arguments  : none
*
* Returns    : none
*
* Note(s)    : 必须OS启动后才能调用
*********************************************************************************************************
*/

void          App_TaskStatHook        (void){

	printf("CPU Usage = %d %% \r\n", OSCPUUsage);
};


void          App_TaskSwHook          (void){
	printf("\r\ntask %d->task %d\r\n",*(OSTCBCur->OSTCBTaskName),*(OSTCBHighRdy->OSTCBTaskName));
};

/*TCB初始化时调用的函数，可以在这里定义TCB的名称，等属性。此时传入TCB优先级等都已经初始化好了*/
void          App_TCBInitHook         (OS_TCB          *ptcb){
	ptcb->OSTCBTaskName =  &(ptcb->OSTCBPrio);
};

void          App_TimeTickHook        (void){};



/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/
