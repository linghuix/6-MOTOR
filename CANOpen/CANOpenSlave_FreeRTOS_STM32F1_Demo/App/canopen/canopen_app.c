/**
  ******************************************************************************
  * @�ļ���     �� canopen_app.c
  * @����       �� strongerHuang
  * @�汾       �� V1.0.0
  * @����       �� 2018��11��14��
  * @ժҪ       �� CANOpenӦ�ó���Դ�ļ�
  ******************************************************************************/
/*----------------------------------------------------------------------------
  ������־:
  2018-11-14 V1.0.0:��ʼ�汾
  ----------------------------------------------------------------------------*/
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "canopen_app.h"
#include "canopen_drv.h"
#include "TestSlave.h"


/* ��̬���� ------------------------------------------------------------------*/
static void CANOpen_App_Task(void *pvParameters);


/************************************************
�������� �� CANOpen_App_Init
��    �� �� CANOpenӦ�ó����ʼ��
��    �� �� ��
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
void CANOpen_App_Init(void)
{
  BaseType_t xReturn;

  CANOpen_Driver_Init();

  xReturn = xTaskCreate(CANOpen_App_Task, "CANOpen_App_Task", CANOPEN_STACK_SIZE, NULL, CANOPEN_TASK_PRIORITY, NULL);
  if(pdPASS != xReturn)
  {
    return;                                      //������������ʧ��
  }
}

/************************************************
�������� �� CANOpen_App_Task
��    �� �� CANOpenӦ���������
��    �� �� pvParameters --- ��ѡ����
�� �� ֵ �� ��
��    �� �� strongerHuang
*************************************************/
static void CANOpen_App_Task(void *pvParameters)
{
  unsigned char nodeID = 0x01;                   //�ڵ�ID

  setNodeId(&TestSlave_Data, nodeID);
  setState( &TestSlave_Data, Initialisation);
  setState( &TestSlave_Data, Operational);

  for(;;)
  {
    vTaskDelay(500);

    /* Ӧ�ô��� */
  }
}


/**** Copyright (C)2018 strongerHuang. All Rights Reserved **** END OF FILE ****/
