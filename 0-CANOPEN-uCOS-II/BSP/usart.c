/**
  ******************************************************************************
  * @file    delay.c
  * @author  Linghui Xu
  * @version V1.0
  * @date    2019.4.27
  * @brief   用3.5.0版本库建的工程模板
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
  
#include "usart.h"
#include <stdarg.h>

USART_handle husart1;
USART_handle husart2;
USART_handle husart3;
USART_handle husart4;

uint8_t usart1_Rxmsg[5];
uint8_t usart2_Rxmsg[5];
uint8_t usart3_Rxmsg[5];
uint8_t usart4_Rxmsg[5];

/**
  * @brief  串口1的中断配置，总中断使能
  * @param  None
  * @retval None
  */
void USART1_NVIC_Configuration(void){

    NVIC_InitTypeDef NVIC_InitStructure;
	
    /*UART1 中断*/
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	
    /*先占优先级0级*/	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	
    /*从优先级3级*/	
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	
    /*IRQ通道被使能*/	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 

    /*根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器*/
    NVIC_Init(&NVIC_InitStructure);  
	
		husart1.USART = USART1;
}
	
void USART2_NVIC_Configuration(void){
	
    NVIC_InitTypeDef NVIC_InitStructure;
	
    /*UART2 中断*/
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 
	
    /*先占优先级0级*/	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	
    /*从优先级3级*/	
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		
    /*根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器*/
    NVIC_Init(&NVIC_InitStructure);  

		husart2.USART = USART2;
}


void USART3_NVIC_Configuration(void){
	
    NVIC_InitTypeDef NVIC_InitStructure;
	
    /*UART3 中断*/
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; 
	
    /*先占优先级0级*/	
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	
    /*从优先级3级*/	
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		
    /*根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器*/
    NVIC_Init(&NVIC_InitStructure);  

		husart3.USART = USART3;
}

/**
  * @brief  USART1 GPIO 配置,工作模式配置。115200 8-N-1
  * @param  None
  * @retval None
  */
void USART1_Config(){
    
    USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	

    /*********串口GPIO端口配置***********/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;                           /* 配置串口1 （USART1 Tx (PA.09)）*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                          /* 配置串口1 USART1 Rx (PA.10)*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*********串口GPIO端口配置END*********/


    /* 串口1工作模式（USART1 mode）配置 */
    USART_InitStructure.USART_BaudRate = 2000000;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure); 

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                  //开启接收中断

    USART_Cmd(USART1, ENABLE);                                      //使能串口

    //USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);                  //USART1向DMA发出Tx请求，此时CPU是空闲的,,在主程序中配置
}


/**
  * @brief  USART1 GPIO 配置,工作模式配置。115200 8-N-1
  * @param  None
  * @retval None
  */
void USART2_Config(){
    
    USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	

    /*********串口GPIO端口配置***********/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;                           /* 配置串口2 （USART2 Tx (PA.02)）*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;                          /* 配置串口2 	USART2 Rx (PA.03)		*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*********串口GPIO端口配置END*********/


    /* 串口2工作模式（USART2 mode）配置 */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART2, &USART_InitStructure); 

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                  //开启接收中断

    USART_Cmd(USART2, ENABLE);                                      //使能串口

    //USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);                  //USART1向DMA发出Tx请求，此时CPU是空闲的,,在主程序中配置
}


/**
  * @brief  USART1 GPIO 配置,工作模式配置。115200 8-N-1
  * @param  None
  * @retval None
  */
void USART3_Config(){
    
    USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	

    /*********串口GPIO端口配置***********/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                           /* 配置串口3 （USART2 Tx (PB.10)）*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); 

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;                          	/* 配置串口3 	USART2 Rx (PB.11)		*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*********串口GPIO端口配置END*********/


    /* 串口2工作模式（USART2 mode）配置 */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART3, &USART_InitStructure); 

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);                  //开启接收中断

    USART_Cmd(USART3, ENABLE);                                      //使能串口

    //USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);                  //USART1向DMA发出Tx请求，此时CPU是空闲的,,在主程序中配置
}

void USART_init(void){
	
	USART1_Config();
	USART2_Config();
	//USART3_Config();
	//USART1_NVIC_Configuration();
	USART2_NVIC_Configuration();
	//USART3_NVIC_Configuration();
}
