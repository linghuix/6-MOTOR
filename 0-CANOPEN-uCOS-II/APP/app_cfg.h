#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*******************设置任务优先级*******************/
#define STARTUP_TASK_PRIO     2	   
#define	TASK_canrcv_PRIO			6
#define	TASK_cansend_PRIO			5 
#define	TASK_remote_PRIO			7
#define	TASK_canapp_PRIO			3



/************设置栈大小（单位为 OS_STK ）************/
#define STARTUP_TASK_STK_SIZE   80   
#define	TASK_A_STK_SIZE		150
#define	TASK_B_STK_SIZE		150
#define	TASK_canapp_STK_SIZE		400

#endif

