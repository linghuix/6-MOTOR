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
  
#include "func_usart.h"
#include <stdarg.h>


/**
  * @brief  重定向c库函数printf到USART1,由printf调用
  * @param  None
  * @retval None
  */
int fputc(int ch, FILE *f){
    
    USART_SendData(USART1, (unsigned char) ch);                     /* 将Printf内容发往串口 */
    while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
    return (ch);
}


/**
  * @brief  ：重定向c库函数scanf到USART1, 由scanf调用
  * @param  None
  * @retval None
  */
int fgetc(FILE *f){

    while( USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == RESET);     //等待串口输入数据
    return (int) USART_ReceiveData(USART1);
}


/**
  * @brief  ：中断发送函数
  * @param  husart  串口发送数据结构体
  * @retval None    
  */
void USART_Tran_IT(USART_handle *husart){
    
    if(husart->Txuse && husart->TxMsg.num == 0){return;}
    
    husart->Txuse = 1;          //接收标志
    
    //开启接收中断
    USART_ITConfig(husart->USART, USART_IT_RXNE, ENABLE);
    
    //装填第 1 个数据
    husart->USART->DR = husart->TxMsg.message[0];
    
    return;
}


/**
  * @brief  ：中断发送的回调函数，必须在中断函数中调用
  * @param  None
  * @retval None
  */
void USART_Tran_IT_callback(USART_handle *husart){
    
    return;
}

/**
  * @brief  ：中断接收函数。接收一定数量的数据，接收结束后调用回调函数进行数据处理。
  * @param  husart  串口接收数据结构体
  * @retval None    
  */
void USART_Receive_IT(USART_handle *husart, uint8_t *data, uint8_t size){
    
    if(husart->Rxuse && size == 0){return;}
    
    husart->Rxuse = 1;          //接收标志
    husart->RxMsg.index = 0;      //下标从零开始
		husart->RxMsg.num = size;
		husart->RxMsg.message = data;
    
    //开启接收中断
    USART_ITConfig(husart->USART, USART_IT_RXNE, ENABLE);
    
    return;
}


/**
  * @brief  ：中断接收的服务函数，必须在中断函数中调用。
  * @param  None
  * @retval None
  */
void USART_IT(USART_handle *husart){
    
    if(husart->USART == USART1){ 				//接收数据
			
        if(husart->Rxuse && husart->RxMsg.index+1 <= husart->RxMsg.num ){
            //装填第 index+1 个数据
            husart->RxMsg.message[husart->RxMsg.index] = husart->USART->DR;
            husart->RxMsg.index++;
            
            //接收完毕
            if(husart->RxMsg.index == husart->RxMsg.num){
                //关闭中断
                USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
                husart->Rxuse = 0;
                USART_Rx_callback(husart);
            }
        }
        else if(husart->Txuse && husart->TxMsg.index+1 <= husart->TxMsg.num ){        //发送数据
            //发生错误
            printf("%s,%d",__FILE__,__LINE__);
        }
    }
		else if(husart->USART == USART2){			//接收数据
			
        if(husart->Rxuse && husart->RxMsg.index+1 <= husart->RxMsg.num ){
            //装填第 index+1 个数据
            husart->RxMsg.message[husart->RxMsg.index] = husart->USART->DR;
            husart->RxMsg.index++;
            
            //接收完毕
            if(husart->RxMsg.index == husart->RxMsg.num){
                //关闭中断
                USART_ITConfig(husart->USART, USART_IT_RXNE, DISABLE);
                husart->Rxuse = 0;
                USART_Rx_callback(husart);
            }
        }
        else if(husart->Txuse && husart->TxMsg.index+1 <= husart->TxMsg.num ){        //发送数据
            //发生错误
            printf("%s,%d",__FILE__,__LINE__);
        }
    }
		else if(husart->USART == USART3){			//接收数据
			
        if(husart->Rxuse && husart->RxMsg.index+1 <= husart->RxMsg.num ){
            //装填第 index+1 个数据
            husart->RxMsg.message[husart->RxMsg.index] = husart->USART->DR;
            husart->RxMsg.index++;
            
            //接收完毕
            if(husart->RxMsg.index == husart->RxMsg.num){
                //关闭中断
                USART_ITConfig(husart->USART, USART_IT_RXNE, DISABLE);
                husart->Rxuse = 0;
                USART_Rx_callback(husart);
            }
        }
        else if(husart->Txuse && husart->TxMsg.index+1 <= husart->TxMsg.num ){        //发送数据
            //发生错误
            printf("%s,%d",__FILE__,__LINE__);
        }
    }
		
}


//接收结束
uint8_t data[4];
void USART_Rx_callback(USART_handle *husart){
	
    uint8_t i;
	
	if(husart->USART == USART1){
		
		for(i=0;i<1;i++){
			data[i]=usart1_Rxmsg[i];
			printf("%c\r\n",data[i]);
		}
	
		USART_Receive_IT(&husart1, usart1_Rxmsg, 1);
	}
	else if(husart->USART == USART2){
		
		for(i=0;i<3;i++){
			data[i]=usart2_Rxmsg[i];
			printf("%X\r\n",data[i]);
		}

		USART_Receive_IT(&husart2, usart2_Rxmsg, 3);
	}
	else if(husart->USART == USART3){
		
		for(i=0;i<4;i++){
			data[i]=usart3_Rxmsg[i];
			printf("%d\r\n",data[i]);
		}

		USART_Receive_IT(&husart3, usart3_Rxmsg, 4);
	}
	
}
