/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   ��3.5.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
#include "timer.h"

extern int angle_1[323];
extern int angle_2[404];
extern Epos Controller;
extern Epos Controller1;

extern Uint32 pos;										//���λ��
extern int x;												//�Ƕ��Ա��� extern int x=0;�Ǵ��ģ�������һ�γ�ʼ��
extern int angle_sensor;


extern __IO uint32_t flag;	

/**
  * @brief  TIM�ж����ȼ�����
  * @param  None
  * @retval None
  */
void TIME_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                         /*����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�*/

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;                         /*TIM2�ж�*/ 

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;               /*��ռ���ȼ�1��*/

    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;                      /*�����ȼ�2��*/ 
        
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                         /*IRQͨ����ʹ��*/ 

    NVIC_Init(&NVIC_InitStructure);                                         /*����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���*/
}


/**
  * @brief  TIM3 Base ��Ԫ���ã��ж�ʹ��
  * @param  None
  * @retval None
  */
void TIME3_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);                                              /*��ʱ��TIM3ʱ��ʹ��*/

    TIM_TimeBaseStructure.TIM_Period = 10000;                                                         /*��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ,������5000Ϊ500ms*/

    TIM_TimeBaseStructure.TIM_Prescaler =(7200-1);                                                    /*����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ72MHz / (7200) = 10000Hz*/

    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                                                      /*����ʱ�ӷָ�:TDTS = Tck_tim*/ 

    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;                                       /*TIM���ϼ���ģʽ*/

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);                                                   /*����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ*/

    //TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_Trigger,ENABLE);  �������п���                           /*ʹ�ܻ���ʧ��ָ����TIM�ж�*/

    TIM_Cmd(TIM3, ENABLE);                                                                            //ʹ��TIMx����
}



/**
  * @brief  TIME2 Base ��Ԫ���ã��ж�ʹ��
  * @param  None
  * @retval None
  */
void TIME2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);                    /*��ʱ��TIM2ʱ��ʹ��*/
    
    TIM_TimeBaseStructure.TIM_Period = 10000;                              /*��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ,������10000Ϊ10ms*/
    
    TIM_TimeBaseStructure.TIM_Prescaler =(72-1);                            /*����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 72MHz/72 = 1MHz */
    
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;                            /*����ʱ�ӷָ�:TDTS = Tck_tim*/   
    
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;             /*TIM���ϼ���ģʽ*/ 
    
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);                         /*����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ*/ 
    
    //TIM_ITConfig(TIM2,TIM_IT_Update|TIM_IT_Trigger,ENABLE);               /*�������п���,ʹ�ܻ���ʧ��ָ����TIM�ж�*/
    
    TIM_Cmd(TIM2, ENABLE);                                                  //ʹ��TIMx����
}

void TIM2_interrupt(void){
	//printf("%d\r\n", TIM_GetITStatus(TIM2, TIM_IT_Update));
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		//����жϱ�־

	
	//if(flag==0xff) flag = 0;
	//printf("i\r\n");
	
	pos = (x>=323) ? angle_2[x-323]:angle_1[x];
	//printf("%d\r\n",pos);
	angle_sensor = SDO_Read(&Controller,0x6062,0x00);
	//printf("i\r\n");
	PM_SetAngle(&Controller, pos);
	//PM_SetAngle(&Controller1,pos);
	
	printf("%d\t%d\r\n",x,angle_sensor);
	if( ++x==727 ) x = 0;
	
	//printf("%d\r\n\r\n", TIM_GetITStatus(TIM2, TIM_IT_Update));
}