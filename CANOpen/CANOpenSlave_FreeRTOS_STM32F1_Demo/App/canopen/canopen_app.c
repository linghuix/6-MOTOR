/**
  ******************************************************************************
  * @文件名     ： canopen_app.c
  * @作者       ： strongerHuang
  * @版本       ： V1.0.0
  * @日期       ： 2018年11月14日
  * @摘要       ： CANOpen应用程序源文件
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2018-11-14 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
/* 包含的头文件 --------------------------------------------------------------*/
#include "canopen_app.h"
#include "canopen_drv.h"
#include "TestSlave.h"


/* 静态申明 ------------------------------------------------------------------*/
static void CANOpen_App_Task(void *pvParameters);


/************************************************
函数名称 ： CANOpen_App_Init
功    能 ： CANOpen应用程序初始化
参    数 ： 无
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
void CANOpen_App_Init(void)
{
  BaseType_t xReturn;

  CANOpen_Driver_Init();

  xReturn = xTaskCreate(CANOpen_App_Task, "CANOpen_App_Task", CANOPEN_STACK_SIZE, NULL, CANOPEN_TASK_PRIORITY, NULL);
  if(pdPASS != xReturn)
  {
    return;                                      //创建接收任务失败
  }
}

/************************************************
函数名称 ： CANOpen_App_Task
功    能 ： CANOpen应用任务程序
参    数 ： pvParameters --- 可选参数
返 回 值 ： 无
作    者 ： strongerHuang
*************************************************/
static void CANOpen_App_Task(void *pvParameters)
{
  unsigned char nodeID = 0x01;                   //节点ID

  setNodeId(&TestSlave_Data, nodeID);
  setState( &TestSlave_Data, Initialisation);
  setState( &TestSlave_Data, Operational);

  for(;;)
  {
    vTaskDelay(500);

    /* 应用代码 */
  }
}


/**** Copyright (C)2018 strongerHuang. All Rights Reserved **** END OF FILE ****/
