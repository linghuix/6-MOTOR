
#include "HW_epos.h"
#include "canfestival.h"
#include "TestMaster.h"
#include "sdo_control.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
/*
 * 函数名：接收传感器数
 * 描述 
 * 调用  
 */

Uint8 NODE_ID = 0;                          //EPOS ID
Uint8 NODE_ID1 = 2;

Epos Controller,Controller1;        				//控制器对

void Epos_INIT()
{
    Epos_Init(&Controller1, NOT_USED, NODE_ID1);	//初始化最大加速度，速度，跟踪误差，波特1M/s
	
	
    ///通过canopen设定EPOS控制器参
    printf("Epos_SInit\r\n");
    Epos_ParamInit(&Controller1);
    printf("\r\ninitial EPOS done!\r\n\r\n");
		vTaskDelay(500); 
	
    
    //******** 控制模式设置 *******
    //Epos_setMode(&Controller1, Profile_Velocity_Mode);
		Epos_setMode(&Controller1, Profile_Position_Mode);
    vTaskDelay(500); 

    printf("\r\n Mode set \r\n");
    
    //******** 使能EPOS *******
    Epos_OperEn(&Controller1);                                               //Switch On Disable to Operation Enable
    printf("\r\n Enable EPOS \r\n\r\n");
}




/** 速度模式的速度设置 */
void Epos_SpeedSet(Uint32 speed){
	
		 SDO_Write(&Controller1,Target_Velocity,0x00,speed);
		 SDO_Write(&Controller1,OD_CTRL_WORD ,0x00,0x0F);	
}

/**************Position Mode*********************************/
void PM_SetAngle(Epos* epos, Uint32 angle){
    
    #if defined SDO
    SDO_Write(epos, Target_pos, 0x00, angle);
        #endif 
}


/** Position Set */
void Epos_PosSet(Epos* epos, Uint32 pos){
	
	SDO_Write(&Controller1,OD_CTRL_WORD ,0x00,0x0F);	
		 PM_SetAngle(epos,pos);
		 SDO_Write(&Controller1,OD_CTRL_WORD ,0x00,0x7F);	
}


/**控制器启*/
void Epos_Start(void){
	
    //******** EPOS basic COMMANDING PARAMETERS *******
		SDO_Write(&Controller1, Profile_Acceleration,0x00,4000);
		SDO_Write(&Controller1, Profile_Deceleration,0x00,4000);	
		SDO_Write(&Controller1, Motion_Profile_Type,0x00,0);
		
		SDO_Write(&Controller1, OD_P_VELOCITY ,0x00, 50);
	
    Epos_Delay(2000); 
		printf("\r\n EPOS control beginning!\r\n\r\n");

}


/*
 * 函数名：实时控制任务
 * 描述  
 * 调用  
 */
/**实现速度摇摆控制 */
void speed_Task(void){
	
	Uint32 speed = 50;
	
	Epos_SpeedSet(speed);
	Epos_Delay(1000); 
	
	Epos_SpeedSet(-speed);
	Epos_Delay(1000); 
	
	Epos_SpeedSet(speed*5);
	Epos_Delay(1000); 

	Epos_SpeedSet(-speed*5);
	Epos_Delay(1000); 
}


/** position task 摇摆*/
void pos_Task(void){
	
	Uint32 pos = 20000,i;
	
	for(i=0;i<5;i++){
		Epos_PosSet(&Controller1 ,pos*i);
		Epos_Delay(50); 
	}
	
	for(i=0;i<5;i++){
		Epos_PosSet(&Controller1,-pos*i);
		Epos_Delay(50); 
	}
}


void Epos_ControlTask(void){
	
	pos_Task();
}


/*
 * 函数名：接收传感器数
 * 描述  
 * 调用  
 */
Uint32 status;
Uint32 velocity, speed;
void Epos_ReceiveDate(){
	
		status = SDO_Read(&Controller, 0x6041,0x00);
		Epos_Delay(2); 
		speed = SDO_Read(&Controller, Velocity_Demand_Value,0x00);		
		Epos_Delay(2); 
		printf("status:0x%X\t%d\r\n",status,speed);
		speed = SDO_Read(&Controller, OP_MODE_Read,0x00);	
		velocity = SDO_Read(&Controller, Target_Velocity,0x00);	
		Epos_Delay(2); 
		printf("mode:%d\t%d\r\n",speed, velocity);
		Epos_Delay(10); 
}


//状态的控制
void State(void){

    NMT_Pre(&Controller, ALL);                        
    SDO_Read(&Controller,OD_STATUS_WORD,0x00);            

    PDO_Config(&Controller);
    SDO_Read(&Controller,0x1400,0x01);
    SDO_Read(&Controller,0x1600,0x00);
    SDO_Read(&Controller,0x1600,0x01);

    NMT_Start(&Controller, ALL);
}


/*
 * 函数名：接收传感器数
 * 描述  
 * 调用  
 */
#define PI 3.1415
#include "gait.h"

__IO uint32_t flag = 0xff;          //用于标志是否接收到数据，在中断函数中赋
UNS32 pos=0;                       //电机位置
int x=0;                            //角度自变
int angle_sensor;
	
void Epos_Conroller_TIMBack(){

		//printf("%d\r\n", TIM_GetITStatus(TIM2, TIM_IT_Update));
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		//清除中断标志


		//if(flag==0xff) flag = 0;

		pos = (x>=323) ? angle_2[x-323]:angle_1[x];

		//angle_sensor = SDO_Read(&Controller,Pos_Actual_Value,0x00);

		PM_SetAngle(&Controller, pos);
		PM_SetAngle(&Controller1,pos);

		if( ++x==727 ) x = 0;

}

