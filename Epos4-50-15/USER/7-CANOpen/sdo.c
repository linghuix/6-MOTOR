#include "epos.h"
#include "can.h"
#include "delay.h"

/***** 
write parameter to Object Dictionary through CAN use SDO messages
******/

int NEST = 0;           //Ƕ�ײ���

void SDO_Write(Epos* epos,Uint16 Index,Uint8 SubIndex,Uint32 param)
{
    int temp,n;
    temp++;//��ֹ����������
    
	 printf("Send %d-%X-%X\r\n",epos->node_ID,Index,SubIndex);
    //Epos_Delay(1);
    while((CAN_MessagePending(CAN1, CAN_FIFO0)) > 0){       //����SDOǰ��ȫ��� FIFO0 ���䣬��ֹռ���ڴ�
        Epos_Delay(2);
        CAN_FIFORelease(CAN1, CAN_FilterFIFO0); 
        printf("I\r\n");
    }
    
    //printf("\r\n");
    if(++NEST<6){
    printf("nest = %d\r\n",NEST);
        
    //Epos_Delay(2);    
    epos->buf.msg_id.bit.STDMSGID = 0x600 + epos->node_ID;                          //CANOPEN �� �ͻ��˷��͵����������� SOD����ID���ο�CanOpen ��׼

    //CAN�е�8�������ֽڣ��еĵ��ĸ��ֽڶ���  CS(22H)+Index+SubIndex.CS��ֵCanOpen SDO���ı�׼
    epos->buf.low_4byte = 0x22 + ((Uint32)Index << 8) + ((Uint32)SubIndex<< 24);    
    epos->buf.high_4byte = param;                                                   //SDO Я����ʵ�����ݣ�CS������ֻ��Я���ĸ��ֽ�
    epos->buf.DataLen  = 8;
    epos->buf.IsExtend = 0;
    epos->buf.IsRemote = 0;

    CAN_SetMsg(epos->buf.msg_id.bit.STDMSGID, epos->buf.low_4byte, epos->buf.high_4byte);

    //printf("SDO_Write\r\n");

    //���ձ���
    n = 5;  
    while(((temp = CAN_MessagePending(CAN1, CAN_FIFO0)) == 0)&&(n-- > 0)){
        Epos_Delay(2);
        //printf("FMP0 = %d\r\n", temp);//���CAN_FLAG_FMP0����
    }
    
    //printf("out\r\n");
		
		if(n == -1){
			SDO_Write(epos,Index,SubIndex,param);
			printf("No Received");
			return;
		}
     CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);

     Print(RxMessage);
    
     CAN_FIFORelease(CAN1, CAN_FilterFIFO0); 

    
    //����׼ȷ����
    if(RxMessage.StdId == (0x580+epos->node_ID)){
        //printf("ID OK\r\n");
        //printf("%d \r\n",RxMessage.FMI);      //��֤��Ӧ֡�Ĺ������������
        switch(RxMessage.Data[0]){
            
            case(0x60):
                if((Index==(((Uint16)RxMessage.Data[2]<<8)+RxMessage.Data[1])) && (SubIndex==RxMessage.Data[3])){
                    //printf("WoK\r\n");
                    break;
                }
                else{
                    SDO_Write(epos,Index,SubIndex,param);
                    //printf("eW_In--%X-%X  ",Index,SubIndex);//error Write: Index problem
                    break;//�ݹ����
                }
                
            case(0x80):
                SDO_Write(epos,Index,SubIndex,param);
              //printf("eW_CS--%X-%X  ",Index,SubIndex);//error Write: CS problem
                break;
            
            default:
                SDO_Write(epos,Index,SubIndex,param);
                //printf("eW_CS--%X-%X\r\n",Index,SubIndex); //error write CS
                //Print(RxMessage);
            }
    }
    else{
        SDO_Write(epos,Index,SubIndex,param);
        //printf("wrong ID");
    }
    }
    else{
        printf("\r\nwrong--%d-%X-%X \r\n",epos->node_ID,Index,SubIndex);
		    Print(RxMessage);
		    printf("\r\n");
		}
    NEST=0;
}


/**** ����CAN SDO�����ģ������ܷ���ֵ ***/
Uint32 SDO_Read(Epos* epos,Uint16 Index,Uint8 SubIndex)
{
    int temp,n;
    Uint32 data;
    temp++;
    
    if(++NEST<6){
    //Epos_Delay(2);
    epos->buf.msg_id.bit.STDMSGID = 0x600 + epos->node_ID;                   //CANOPEN �� �ͻ��˷��͵����������� SOD����ID���ο�CanOpen ��׼

    //CAN�е�8�������ֽڣ��еĵ��ĸ��ֽڶ���  CS(22H)+Index+SubIndex.CS��ֵCanOpen SDO���ı�׼
    epos->buf.low_4byte = 0x40 + ((Uint32)Index << 8) + ((Uint32)SubIndex<< 24);   //buf�и�λ��ǰ
    epos->buf.high_4byte = 0;                                                      //SDO Я����ʵ�����ݣ�CS������ֻ��Я���ĸ��ֽ�
    epos->buf.DataLen  = 8;
    epos->buf.IsExtend = 0;
    epos->buf.IsRemote = 0;

    CAN_SetMsg(epos->buf.msg_id.bit.STDMSGID, epos->buf.low_4byte, epos->buf.high_4byte);

    //printf("SDO_Read\r\n");
    //Epos_Delay(2);    

        
    //���ձ���
    n = 5;  
    while(((temp = CAN_MessagePending(CAN1, CAN_FIFO0)) == 0)&&(n-- > 0)){
        Epos_Delay(2);
        //printf("FMP0 = %d\r\n", temp);//���CAN_FLAG_FMP0����
    }
		
		if(n == -1){
			data = SDO_Read(epos,Index,SubIndex);
			return data;
		}
    
     CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
     CAN_FIFORelease(CAN1, CAN_FilterFIFO0); 
    
    //����׼ȷ����
    if(RxMessage.StdId == (0x580+epos->node_ID)){
        switch(RxMessage.Data[0]){
                
                case(0x4F):
                case(0x4B):
                case(0x47):
                case(0x43):
                    if(Index==(((Uint16)RxMessage.Data[2]<<8)+RxMessage.Data[1]) && SubIndex==RxMessage.Data[3])  
                    {
                        data = ((Uint32)RxMessage.Data[7]<<24)+((Uint32)RxMessage.Data[6]<<16)+(RxMessage.Data[5]<<8)+RxMessage.Data[4];
                        //printf("RoK\r\n");
                        return data;
                    }
                    else{
                        data = SDO_Read(epos,Index,SubIndex);
                        //printf("eR_In--%X-%X  ",Index,SubIndex);//error index
                        break;//�ݹ����
                    }
                    
                default:
                    data = SDO_Read(epos,Index,SubIndex);
                    //printf("eR_CS--%X-%X\r\n",Index,SubIndex);
            }
        
        }
    else{
        data = SDO_Read(epos,Index,SubIndex);
        printf("wrong ID");
    }
}
    
    if(NEST==6){
			printf("wrong read--%X-%X\r\n",Index,SubIndex);
			Print(RxMessage);
			NEST=0;
			return 0;
		}           //��ȡ���󷵻���
    
    NEST=0;
    return data;
}
