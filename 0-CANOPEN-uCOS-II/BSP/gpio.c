/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
  * 1. 本程序主要存放引脚的配置，针对GPIO以及其他复用功能TIME，ADC，USART，CAN...
  * 2. “事件控制”，“重映射”，“调试IO配置”，“外部中断”，时需要开启AFIO
  *
  ******************************************************************************
  */
#include "gpio.h"

void GPIO_Config(void){

    GPIO_InitTypeDef GPIO_InitStructure;


//@{LED}
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);                //添加PA口时钟线

    /*********串口GPIO端口配置***********/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;                           /* 配置串口1 （USART1 Tx (PA.09)）*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure); 

}

