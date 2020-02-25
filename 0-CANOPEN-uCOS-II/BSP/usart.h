#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"
#include <stdio.h>


/*****************  function declaration 结构体声明********************************************/

struct struct_Message{
    uint8_t *message;   //数据内容指针
    uint16_t num;       //数据包大小
    uint16_t index;     //发送下标，初始化时为 0
};

typedef struct struct_Message USART_Message;

//串口管理结构体
struct struct_USART_handle{
    USART_TypeDef *USART;   //串口寄存器结构体，用于标志是哪个串口发送的
    uint8_t RxTx;           //发送1还是接受0
    uint8_t Rxuse;          //八位无符号数据，1表示正在使用，0表示未使用
    uint8_t Txuse;          //八位无符号数据，1表示正在使用，0表示未使用
    USART_Message RxMsg;     //分成两个的原因是，发送时，添加接收消息就会覆盖发送消息
    USART_Message TxMsg;     //数据指针
    
};


typedef struct struct_USART_handle USART_handle;


extern USART_handle husart1;
extern USART_handle husart2;
extern USART_handle husart3;
extern USART_handle husart4;

extern uint8_t usart1_Rxmsg[5];
extern uint8_t usart2_Rxmsg[5];
extern uint8_t usart3_Rxmsg[5];
extern uint8_t usart4_Rxmsg[5];

/*****************  function declaration 函数声明********************************************/

void USART_init(void);



/**
  * @attention
  *     使用如下函数，需要定义MICRO-LIB宏
  */
int fputc(int ch, FILE *f);
int fgetc(FILE *f);


#endif /* __USART1_H */
