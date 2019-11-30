| CanOpen库官方网站 | https://canfestival.org/code.html.en                         |
| ----------------- | :----------------------------------------------------------- |
| 官方代码库        | https://hg.beremiz.org/                                      |
| 移植方案1         | https://www.strongerhuang.com/CANOpen/CANOpen%E7%B3%BB%E5%88%97%E6%95%99%E7%A8%8B13_%E5%8D%8F%E8%AE%AE%E6%BA%90%E7%A0%81%E7%A7%BB%E6%A4%8D%EF%BC%88%E4%B8%80%EF%BC%89.html |
| 移植方案2         | https://blog.csdn.net/bood123/article/details/49281885       |



https://wenku.baidu.com/view/d21e901aa58da0116c1749f4.html

Construction of CANopen Platform Based onμC/OS-Ⅱ and CanFestival：http://xueshu.baidu.com/usercenter/paper/show?paperid=41f16da7f866de124e785b767c62dce0&site=xueshu_se



CanFestival协议栈从站实现和源码简析：https://blog.csdn.net/sinat_19440229/article/details/86712013



canfestival-3源码详解一：重要结构体：https://blog.csdn.net/u014170067/article/details/99968013

https://blog.csdn.net/eliot_shao/article/details/49873679



https://blog.csdn.net/sinat_19440229/article/details/86712013



字典配置

https://blog.csdn.net/bood123/article/details/49835619



canfestival库的代码结构



| 文件路径   | 文件说明                            |
| ---------- | ----------------------------------- |
| src        | CANopen协议ANSI-C源代码，也硬件无关 |
| include    | 头文件                              |
| drivers    | 硬件驱动                            |
| examples   | 测试程序                            |
| objdictgen | 带有图形用户界面的对象字典编辑器    |
| doc        | 说明文档                            |





不论是TPDO还是RPDO都有通信参数和映射参数两种参数，通信参数有如下六种：

| subindex | name                | type       |
| -------- | ------------------- | ---------- |
| 0x01     | COB ID              | UNSIGNED32 |
| 0x02     | Transmission Type   | UNSIGNED8  |
| 0x03     | Inhibit Time        | UNSIGNED16 |
| 0x04     | Compatibility Entry | UNSIGNED8  |
| 0x05     | Event Time          | UNSIGNED16 |
| 0x06     | SYNC start value    | UNSIGNED8  |

1. COB ID，通过COB ID可以让CAN节点知道，这一帧报文属于PDO、SDO、NMT、SYNC还是其他

2. Transmission Type表示PDO的通信类型，有同步、异步、周期、非周期等

3. Inhibit Time表示PDO发送的最小时间间隔，避免发送频率太快，总线负载太大，单位是100us。

4. Compatibility Entry这个不知道是啥，文档里面都没提到，先不管。
5. Event Time如果是**定时发送PDO**，那么这个参数表示的定时时间，如果这个参数为0，那么表示事件触发发送PDO，单位是ms。
6. SYNC start value同步起始值。当PDO为**同步发送时**，比如Transmission Type=10，那么收到10个同步包后才发送PDO，如果SYNC start value=2，那么刚开始时收到2个同步包就开始发送PDO，之后就按10个同步包发送。

# CANopen系列[1]-SYNC

2016-04-21 21:45:33  更多



版权声明：本文为博主原创文章，遵循[ CC 4.0 BY-SA ](http://creativecommons.org/licenses/by-sa/4.0/)版权协议，转载请附上原文出处链接和本声明。本文链接：https://blog.csdn.net/unsv29/article/details/51213062

一个CANopen网络中，

(1) 只有一个站点发送SYNC

(2) 发送SYNC的为生产者，接收SYNC的为消费者，就是说符合生产/消费模型

(3) 不一定让主站发送SYNC，从站也可以。

(4) 對象字典中Index 1005 & 1006是指的主站發送SYNC的COD-ID和時間, 1007指的是窗口，(博主接触的资料是SYNC的50%或75%作为窗口)

----------------明天继续---------------------

(5) SYNC同步什么情况下用到？[本博主答道]答案：至少伺服驱动器用到。据说伺服对实时性要求较高。

(6) [学无止境2013]想让主站来发SYNC报文，是主站一上电就发出SYNC报文呢，还是待主站发现有从机接入后再发送SYNC报文？

第一种方法是不管有没有从机接入，我主机都一直发送SYNC报文，这两种哪一个思路是正确的？

[YUANFANG] 上一个贴子里已经讨论过了，你可以考虑，主站在上电时加载从站配置的时候，如果发现有从站使用同步PDO，就开始发，当然，你也可以等到有同步PDO的从站连接正常后再发，就是稍麻烦一点，所有的做法都可以，只要保证需要SYNC信号的时候有，就行  

(7) 学无止境2013，如果有的从机有，有的从机没有，那主机发SYNC报文好呢还是不发呢？
遇到这种情况一般都怎么处理，采取什么办法和对策，请远方指点。

远方，如果有些从站的PDO是配置成同步模式，你就一定要发SYNC，不然PDO没法启动啊，就算目前的配置，所以PDO都没有使用SYNC模式，你也可以发SYNC，不影响数据交换，因为SYNC报文只是提供一个同步信号而已，需要的时候用，不需要就不用  

(8) 远方说不要用远程帧，协议不推荐

(9) ODD_SYNC_COB_ID       0x00000080L    /*index 0x1005*/     //if bit30=0, node produces SYNC 只接受，不发送

(10)

---------------------------------question----------

对CANopen使用有一段时间了，有一个问题，请问高手或者版主，不知道如何实现SYNC同步，即通过周期发送SYNC消息后触发，同步得到PDO数据。
同步(通过接收SYNC对象实现同步)

--------------answer----------

简单的来说，CANOPEN里的同步实现方法，就是使用PDO把控制数据发送给每一个从站，但因为是同步模式，每个收到PDO控制命令的从站，都只是把命令暂时保存起来，当所有的从站命令都发送完毕后，主站才会送出SYNC广播报文，所有支持同步传输模式的从站，在收到SYNC报文后，大家一起开始执行之前保存好的控制命令，这就是同步机制  

(11)------------question-------------

另外加上一个问题 就是SYNC同步，比如我让两个驱动器同步，给两个驱动顺序赋值完，主动的发一个SYNC信号，这样可以吧？SYNC不需要是周期性的吧？就是每次我对所有从节点赋值完 就发一个SYNC。这样应该没有问题吧？

---------anser------------

SYNC周期永远都不会变，速度的变化与SYNC周期没有关系，速度曲线是由你的上位控制器算出来的，按SYNC周期取点送给伺服即可

如果你要做这方便的开发，就要潜心研究一下，没有那么简单 

(12)：SYNC一定要通过对象字典设置成固定周期的吗？答案：是。

问：

|      | 那么比如两轴进行插补，有加减速，在加速阶段周期应该越来越小吧？时刻变化的，那这个SYNC周期怎么办？ |
| ---- | ------------------------------------------------------------ |
|      |                                                              |

------------------------------------------------answer----------------------------------------------------------



| ![img](http://www.dndev.com/non-cgi/posticons/19.gif) | 1。同步周期应该是恒定的，它基本上就是系统通信部分的节拍了，节拍乱了，一切都是浮云了。 2。不要把通信协议和实际的应用混在一起，按照你的最高应用需求去设计通信周期。 3。涉及到数控系统，插补、加减速和通信周期是没有任何关系的，速度的高低可并不意味着通信周期的大小。 |
| ----------------------------------------------------- | ------------------------------------------------------------ |
|                                                       |                                                              |



(13)--------------

请问如果在402插补模式下，如果遇到其他紧急报文的发送，延迟了SYNC的发送，怎么处理？谢谢 

----------------answer-----------------------

可以在通讯周期上为紧急报文设计一个发送时间窗，避开SYNC.不光紧急报文，其它的SDO PDO也都可能会使SYNC延迟，即这些帧已经先产生了并且已经放到CAN控制器的发送队列，甚至可能已经开始上载到总线上，你不可能把它拉下来吧，这种情况可能会带来百微秒级的延时，更坏的情况，先产生的低优先级的比如SDO一直竞争不到总线的控制权，将高优先级的SYNC堵在后面，这样SYNC的发送延迟可能会更久。这样看来你的SYNC要么忍受，要么避开。选择避开的话，就需要规规划你的通信周期，在一个通信周期上分时段，哪一段留给实时通信，哪一段留给非实时通信，更详细的，那一段分给SYNC，哪一段分给EMCY，哪一段分给PDO。可以看看DS301协议，有一段这方面介绍。  

(14)在从站可配置为SYNC producer时，如果把该从站配置为SYNC producer，在整个can网络处于Operational状态时，如果主站检测到该从站异常，主站应该采取哪些异常处理措施？？？

答案：winshton-这个是你的错误处理程序需要关心的问题，跟协议栈无关，协议栈只负责提供错误检测机制，由你的上层错误处理程序查询到这个异常，然后是应该停掉整个网络的通讯还是忽略这个错误，继续指定一个节点作为sync producer，这些都由你来决定，如果这个节点很重要，出现异常后整个系统瘫痪(例如作为整个系统闭环控制的反馈)，不能正常工作，那么就可能要把网络切换到停止状态，更换板卡维修... 

问：如果从站Object 1005h Default value 为80000080h
Object 1006h设为0，是不是从站也是一个SYNC对象的消费者。？

答案：

1. 1005h生成SYNC的控制位是第30位，所以你想说的是40000080h吧。 
2. 我不赞同你的理解，1005h和1006h共同决定是否产生SYNC，有一个条件不满足就不能够成为SYNC的生产者，但这两个条件是有区别的，1005是基本条件，是控制SYNC的开关，而1006只是个限制条件，如果它为0的话，SYNC的周期将无意义，因此要限制它。你描述的情况可以这样说，1005决定了这个节点是SYNC生产者，但是1006的设置对于产生SYNC是个笑话，周期为0是不可能实现的。





## 代码框架

data.h	一个canopen节点的数据结构定义

App 文件夹 程序线程tasks函数
BSP 文件夹 外设配置
App/CanOpen 文件夹 CanOpen的App配置

底层CAN发送包代码
	canopen_drv.c



1. 中断配置

```
TIM2中断——bsp_timer.h/c 中断分频CANOPEN_TIM_PRESCALER_VALUE ，优先级 CANOPEN_TIM_Priority=12

CAN1接收中断——bsp_can.h/c   1MBps，无过滤，CANx`			
```

2. 初始任务

```c
APP_Task   			//LED闪烁 启动 CANOpen_App_Task【CANOpen_app.c】 启动 CANSend_Task，CANRcv_Task【CANOpen_Drv.c】
CANOpen_App_Task	//CANOpen初始化
CANSend_Task		//如果队列中有需要发送的数据，发送 CAN 帧，
CANRcv_Task			//接收数据，调用重要函数 canDispatch
```

3. 核心数据结构

> 设计理念很先进，使用宏定义这样一个CO_data结构，整个宏定义与data.h中

```c
#define CANOPEN_NODE_DATA_INITIALIZER(NODE_PREFIX) {\
	/* Object dictionary*/\
	& NODE_PREFIX ## _bDeviceNodeId,     /* bDeviceNodeId */\	//设备的ID  1, 127
	NODE_PREFIX ## _objdict,             /* objdict  */\		//字典对象指针，见词条Objdict
	NODE_PREFIX ## _PDO_status,          /* PDO_status */\		//发送PDO通信参数的数组
	NULL,                                /* RxPDO_EventTimers */\
	_RxPDO_EventTimers_Handler,          /* RxPDO_EventTimers_Handler */\
	& NODE_PREFIX ## _firstIndex,        /* firstIndex */\//?存储SDO、PDO Objdict的开始位置(包含)
	& NODE_PREFIX ## _lastIndex,         /* lastIndex */\ //?存储SDO、PDO Objdict的结束位置(包含)
	& NODE_PREFIX ## _ObjdictSize,       /* ObjdictSize */\	//index字条数量
	& NODE_PREFIX ## _iam_a_slave,       /* iam_a_slave */\	//主从配置， 0表示主机，1表示从机
	NODE_PREFIX ## _valueRangeTest,      /* valueRangeTest */\//???????函数指针，检测值是否的超出范围
	\
	
	/* SDO, structure s_transfer */\
	{\
     REPEAT_SDO_MAX_SIMULTANEOUS_TRANSFERS_TIMES(s_transfer_Initializer)\ //SDO 发送结构
	},\
	\
	/* State machine*/\
	Unknown_state,      /* nodeState */\		//can节点状态，初始化为未知
	/* structure s_state_communication */\		//CANopen不同的初始化操作阶段，初始化如下
	{\
		0,          /* csBoot_Up */\
		0,          /* csSDO */\
		0,          /* csEmergency */\
		0,          /* csSYNC */\
		0,          /* csHeartbeat */\
		0,           /* csPDO */\
		0           /* csLSS */\
	},\
	_initialisation,     /* initialisation */\	//函数指针，初始化空，可以覆盖，进入这些状态后调用
	_preOperational,     /* preOperational */\	//函数指针
	_operational,        /* operational */\		//函数指针
	_stopped,            /* stopped */\			//函数指针
	NULL,                /* NMT node reset callback */\//函数指针，初始化为NULL，节点重置回调
	NULL,                /* NMT communications reset callback */\//函数指针，初始化为NULL，communications重置回调
	\
	
	/* NMT-heartbeat */\
	& NODE_PREFIX ## _highestSubIndex_obj1016, /* ConsumerHeartbeatCount */\
	NODE_PREFIX ## _obj1016,                   /* ConsumerHeartbeatEntries */\
	NODE_PREFIX ## _heartBeatTimers,           /* ConsumerHeartBeatTimers  */\ 
	& NODE_PREFIX ## _obj1017,  /* ProducerHeartBeatTime */\  //生产者发送时间，初始化为obj1017，单位ms
	TIMER_NONE,                 /* ProducerHeartBeatTimer */\ //定时器，初始化为无定时器，需要周期定时存储定时器
	_heartbeatError,           /* heartbeatError */\		  //心跳检测出错函数指针，初始化空，可以覆盖，进入这些状态后调用
	\
	{REPEAT_NMT_MAX_NODE_ID_TIMES(NMTable_Initializer)},\ /*NMTable[NMT_MAX_NODE_ID]*/\ //初始化NMT状态，初始化42个状态为unknown
	\
	
	/* NMT-nodeguarding */\
	TIMER_NONE,                                /* GuardTimeTimer */\
	TIMER_NONE,                                /* LifeTimeTimer */\
	_nodeguardError,           /* nodeguardError */\
	& NODE_PREFIX ## _obj100C,                 /* GuardTime */\
	& NODE_PREFIX ## _obj100D,                 /* LifeTimeFactor */\
	{REPEAT_NMT_MAX_NODE_ID_TIMES(nodeGuardStatus_Initializer)},\
	\
	
	/* SYNC */\
	TIMER_NONE,                                /* syncTimer */\
	& NODE_PREFIX ## _obj1005,                 /* COB_ID_Sync */\
	& NODE_PREFIX ## _obj1006,                 /* Sync_Cycle_Period */\
	/*& NODE_PREFIX ## _obj1007, */            /* Sync_window_length */\
	_post_sync,                 /* post_sync */\//函数指针，初始化空，可以覆盖，proceedSYNC调用
	_post_TPDO,                 /* post_TPDO */\//发送同步PDO函数指针，初始化空，可以覆盖，proceedSYNC 后调用
	_post_SlaveBootup,			/* post_SlaveBootup */\//函数指针，初始化空，可以覆盖，后调用
  _post_SlaveStateChange,		/* post_SlaveStateChange */\//函数指针，初始化空，可以覆盖，后调用
	\
	
	/* General */\
	0,                                         /* toggle */\
	NULL,                   /* canSend */\
	NODE_PREFIX ## _scanIndexOD,                /* scanIndexOD */\//函数指针，返回对应的字典中的index，需要提前定义(用字典生成器的话，会自动生成)，否则代码无法运行
	_storeODSubIndex,                /* storeODSubIndex */\//函数指针，初始化空，可以覆盖
    
    /* DCF concise */\
    NULL,       /*dcf_odentry*/\
	NULL,		/*dcf_cursor*/\
	1,		/*dcf_entries_count*/\
	0,		/* dcf_status*/\
    0,      /* dcf_size */\
    NULL,   /* dcf_data */\
	\
	
	/* EMCY */\
	Error_free,                      /* error_state */\	//错误标志，初始化为无错
	sizeof(NODE_PREFIX ## _obj1003) / sizeof(NODE_PREFIX ## _obj1003[0]), /*error_history_size */\ //历史错误数目
	& NODE_PREFIX ## _highestSubIndex_obj1003,    /* error_number */\
	& NODE_PREFIX ## _obj1003[0],    /* error_first_element */\
	& NODE_PREFIX ## _obj1001,       /* error_register */\
    & NODE_PREFIX ## _obj1014,       /* error_cobid */\		//Can-id
	/* error_data: structure s_errors */\
	{\
	REPEAT_EMCY_MAX_ERRORS_TIMES(ERROR_DATA_INITIALIZER)\/*error_data[EMCY_MAX_ERRORS];*/
	},\ //初始化为全零，EMCY_MAX_ERRORS为8
	_post_emcy,             /* post_emcy */\//函数指针，初始化空，可以覆盖，proceedEMCY中调用
	
	/* LSS */\
	lss_Initializer\
}

---------------------------------------------------------------------
struct struct_CO_Data {
	/* Object dictionary */
	UNS8 *bDeviceNodeId; 							//1, 127
	const indextable *objdict; 						//字典对象指针，指向字典数组
	s_PDO_status *PDO_status;						//发送PDO通信参数的数组
	TIMER_HANDLE *RxPDO_EventTimers;
	void (*RxPDO_EventTimers_Handler)(CO_Data*, UNS32);
	const quick_index *firstIndex;					//存储SDO、PDO索引值index
	const quick_index *lastIndex;
	const UNS16 *ObjdictSize;						//对象字典里面对象的个数
	const UNS8 *iam_a_slave;						//主机或从机标志 0表示主机，1表示从机。
	valueRangeTest_t valueRangeTest;				//函数指针，用于检测值是否的超出范围
	
	/* SDO */
	s_transfer transfers[SDO_MAX_SIMULTANEOUS_TRANSFERS];
	/* s_sdo_parameter *sdo_parameters; */

	/* State machine */
	e_nodeState nodeState;
	s_state_communication CurrentCommunicationState;
	initialisation_t initialisation;
	preOperational_t preOperational;
	operational_t operational;
	stopped_t stopped;
     void (*NMT_Slave_Node_Reset_Callback)(CO_Data*);
     void (*NMT_Slave_Communications_Reset_Callback)(CO_Data*);
     
	/* NMT-heartbeat */
	UNS8 *ConsumerHeartbeatCount;
	UNS32 *ConsumerHeartbeatEntries;
	TIMER_HANDLE *ConsumerHeartBeatTimers;
	UNS16 *ProducerHeartBeatTime;
	TIMER_HANDLE ProducerHeartBeatTimer;
	heartbeatError_t heartbeatError;
	e_nodeState NMTable[NMT_MAX_NODE_ID]; 

	/* NMT-nodeguarding */
	TIMER_HANDLE GuardTimeTimer;
	TIMER_HANDLE LifeTimeTimer;
	nodeguardError_t nodeguardError;
	UNS16 *GuardTime;
	UNS8 *LifeTimeFactor;
	UNS8 nodeGuardStatus[NMT_MAX_NODE_ID];

	/* SYNC */
	TIMER_HANDLE syncTimer;
	UNS32 *COB_ID_Sync;
	UNS32 *Sync_Cycle_Period;
	/*UNS32 *Sync_window_length;;*/
	post_sync_t post_sync;
	post_TPDO_t post_TPDO;
	post_SlaveBootup_t post_SlaveBootup;
    post_SlaveStateChange_t post_SlaveStateChange;
	
	/* General */
	UNS8 toggle;
	CAN_PORT canHandle;	
	scanIndexOD_t scanIndexOD;				//返回对应的字典条indextable
	storeODSubIndex_t storeODSubIndex; 
	
	/* DCF concise */
    const indextable* dcf_odentry;
	UNS8* dcf_cursor;
	UNS32 dcf_entries_count;
	UNS8 dcf_status;
    UNS32 dcf_size;
    UNS8* dcf_data;
	
	/* EMCY */
	e_errorState error_state;
	UNS8 error_history_size;
	UNS8* error_number;
	UNS32* error_first_element;
	UNS8* error_register;
    UNS32* error_cobid;
	s_errors error_data[EMCY_MAX_ERRORS];
	post_emcy_t post_emcy;
	
#ifdef CO_ENABLE_LSS
	/* LSS */
	lss_transfer_t lss_transfer;
	lss_StoreConfiguration_t lss_StoreConfiguration;
#endif	
};
```

这两个变量主要用来存储SDO、PDO在1.1.2中所述的对象字典中的索引值，主要是为了让后面使用SDO、PDO对象更方便。具体来说，结构体quick_index的源码如下：



```

typedef struct s_quick_index{
	UNS16 SDO_SVR;
	UNS16 SDO_CLT;
	UNS16 PDO_RCV;
	UNS16 PDO_RCV_MAP;
	UNS16 PDO_TRS;
	UNS16 PDO_TRS_MAP;
}quick_index;

```
SDO_SVR表示SDO server的索引；

SDO_CLT表示SDO client的索引；

PDO_RCV表示RPDO的索引；

PDO_RCV_MAP表示RPDO映射对象的索引；

PDO_TRS表示TPDO的索引；

PDO_TRS_MAP表示TPDO映射对象的索引。



CANOpen_App_Task 的调用树状图


```c
//初始化，切换Master的状态为Initialisation，Operational
CANOpen_App_Task
    setState(&TestMaster_Data, Initialisation)
        switchCommunicationState()
            StartOrStop()  		//start LSS
    

    setState(&TestMaster_Data, Operational)
        switchCommunicationState()
            StartOrStop()  		//start SDO,SYNC,LifeGuard,csEmergency,PDO

```

## DEBUG

调试可以通过串口打印当前 **调用的函数 和 进行的操作**

```c
#ifdef DEBUG_WAR_CONSOLE_ON
#    define MSG_WAR(num, str, val)          \
              MSG("%s,%d : 0X%x %s 0X%x \r\n",__FILE__, __LINE__,num, str, val);
#else
#    define MSG_WAR(num, str, val)
#endif


#define MSG(...) printf (__VA_ARGS__)
```

STM32F10X_HD,DEBUG_ERR_CONSOLE_ON,DEBUG_WAR_CONSOLE_ON

## Objdict

> 与CAN-ID无关，是一个元素为index的数组
>
> | -- index 包含了该词条的index值，和对应的subindex数目，还有一个指向subindex的指针
>
> ​	| -- subindex 包含了数据内容，数据类型，数据长度等重要参数

https://strongerhuang.blog.csdn.net/article/details/99826973

https://blog.csdn.net/bood123/article/details/49835619  字典配置详解

* objdictedit 是自带的objdict的生活器。需要安装：

```c
python2.7			      //apt-get install python2.7
Gnosis xml tools 	//自动安装了
wxPython				 // python2.7 -mpip install wxPython
```



#### First and Last Index

#### Slave or Master

#### ObjdictSize



![1574923286856](D:\3-motor\0-MOTOR controller\SDO1)



## HeartBeat

启动条件  CAN-ID = 0x700+

`if ( *d->ProducerHeartBeatTime )`  周期单位ms



## SYNC

> void startSYNC(CO_Data* d)   CAN-ID=0x80

启动条件 

`if(*d->COB_ID_Sync & 0x40000000ul && *d->Sync_Cycle_Period)`  周期单位us

字典1005h 生成SYNC的控制位是第30位，即这个奇怪的数字0x40000000ul 

1005h和1006h共同决定是否产生SYNC，有一个条件不满足就不能够成为SYNC的生产者，但这两个条件是有区别的，1005是基本条件，是控制SYNC的开关，而1006只是个限制条件，如果它为0的话，SYNC的周期将无意义，因此要限制它。

1005决定了这个节点是SYNC生产者，但是1006的设置控制产生SYNC的周期



Epos4 中并没有SYNC的周期设定，只有对应的0x80标识符的设置，因此必须由上位机产生对应的标识符的SYNC



* startSYNC中，注册定时器，回调函数为SyncAlarm，
* SyncAlarm - sendSYNC 发送SYNC帧，调用proceedSYNC
* proceedSYNC - 调用_sendPDOevent，同步触发



## SDO

一个line 是否就是 一个服务器与客户端的连接，有几个客户端，就需要几个line



CO_data结构 的修改

发送流程：

* 首先是要发送的数据sdo_data,以数组形式存储。
* Line是发送接收管道，具有数据结构，可以发送SDO帧。
* objdict是字典结构体

sdo_data  <---->  Line  <---->   objdict



SDO 发送结构  `struct_s_transfer`   `s_transfer`

初始化为s_transfer_Initializer

```c
struct struct_s_transfer {
  UNS8           CliServNbr; /**< The index of the SDO client / server in our OD minus 0x1280 / 0x1200 */

  UNS8           whoami;     /**< Takes the values SDO_CLIENT or SDO_SERVER */
  UNS8           state;      /**< state of the transmission : Takes the values SDO_... */
  UNS8           toggle;	
  UNS32          abortCode;  /**< Sent or received */
  /**< index and subindex of the dictionary where to store */
  /**< (for a received SDO) or to read (for a transmit SDO) */
  UNS16          index;
  UNS8           subIndex;
  UNS32          count;      /**< Number of data received or to be sent. */
  UNS32          offset;     /**< stack pointer of data[]
                              * Used only to tranfer part of a line to or from a SDO.
                              * offset is always pointing on the next free cell of data[].
                              * WARNING s_transfer.data is subject to ENDIANISATION
                              * (with respect to CANOPEN_BIG_ENDIAN)
                              */
  UNS8           data [SDO_MAX_LENGTH_TRANSFER];
#ifdef SDO_DYNAMIC_BUFFER_ALLOCATION
  UNS8           *dynamicData;
  UNS32          dynamicDataSize;
#endif //SDO_DYNAMIC_BUFFER_ALLOCATION
                                    
  UNS8           peerCRCsupport;    /**< True if peer supports CRC */
  UNS8           blksize;           /**< Number of segments per block with 0 < blksize < 128 */
  UNS8           ackseq;            /**< sequence number of last segment that was received successfully */
  UNS32          objsize;           /**< Size in bytes of the object provided by data producer */
  UNS32          lastblockoffset;   /**< Value of offset before last block */
  UNS8           seqno;             /**< Last sequence number received OK or transmitted */   
  UNS8           endfield;          /**< nbr of bytes in last segment of last block that do not contain data */
  rxStep_t       rxstep;            /**< data consumer receive step - set to true when last segment of a block received */
  UNS8           tmpData[8];        /**< temporary segment storage */

  UNS8           dataType;   /**< Defined in objdictdef.h Value is visible_string
                              * if it is a string, any other value if it is not a string,
                              * like 0. In fact, it is used only if client.
                              */
  TIMER_HANDLE   timer;      /**< Time counter to implement a timeout in milliseconds.
                              * It is automatically incremented whenever
                              * the line state is in SDO_DOWNLOAD_IN_PROGRESS or
                              * SDO_UPLOAD_IN_PROGRESS, and reseted to 0
                              * when the response SDO have been received.
                              */
  SDOCallback_t Callback;   /**< The user callback func to be called at SDO transaction end */
}
```

---

UNS8 writeNetworkDict (CO_Data* d, UNS8 nodeId, UNS16 index,
		UNS8 subIndex, UNS32 count, UNS8 dataType, void *data, UNS8 useBlockMode)

写入can网格中的某个节点。

### 普通模式和快速模式

* SDO的CAN-ID 由Objdict中定义。属于0x1280中的TestMaster_obj1280_COB_ID_Server值，因为读取时，单片机为从机，网络节点变为服务器。 
* SDO的CS command specifier 参考

CS确定方法

![SDO1](D:\3-motor\0-MOTOR controller\CANOpen\SDO1.png)

![1574922726748](D:\3-motor\0-MOTOR controller\SDO2)

* SDO can数据字节前四个data[0-3]为UNS16  index,		UNS8 subIndex
* SDO 剩下四个字节data[4-7]为需要写入的真正数据。长度小于或等于4个字节时，使用SDO expedited；长度超过4个字节，一帧数据传输不完时，使用SDO normal
* 调用sendSDO发送



## PDO

> PDO_status

```c
UNS8 transmit_type_parameter; 		//PDO传输类型,有同步，非同步，周期和非周期，【事件触发】
TIMER_HANDLE event_timer;			//定时器
TIMER_HANDLE inhibit_timer;			//PDO发送间隔定时器
Message last_message;				//
```



```c
//Index 1800h-19FFh，Transmit PDO Communication Parameter，必须如果支持对应的PDO
Sub-index 0，Number，unsigned8（2-5），RO，必须
Sub-index 1，COB-ID used by PDO，unsigned32，RO/RW（如果支持COB-ID配置），必须
    Bit31：1存在PDO，0不存在PDO
    Bit30：1 no RTR allowed on this PDO，0 RTR allowed on this PDO
    Bit29：1 29位ID，0 11位ID
    Bit29-0：29位ID或11位ID（低11位）
Sub-index 2，transmission type，unsigned8，RO/RW（如果支持可变的传输类型），必须
Sub-index 3，inhibit time（not used for RPDO，100us），unsigned16，RW，可选
Sub-index 4，compatibility entry（保留），unsigned8，RW，可选
Sub-index 5，event time（not used for RPDO，ms），unsigned16，RW，可选


//Index 1A00h-1BFFh，Transmit PDO Mapping Parameter，必须如果支持对应的PDO
Sub-index 0，Number，unsigned8（0-64），RO/RW如果支持动态映射，必须
Sub-index 1-40h，PDO Mapping，unsigned32，RW，根据被映射的数量和数据大小来定必须或可选
    Bit31-16：index
    Bit15-8：Sub-index
    Bit7-0：object length
```

* buildPDO是重点，用于对某个TXPDO，尽力发送的PDO帧

* PDOInit(objdict)

  * 调用 _sendPDOevent()    **精妙的代码**
    * 触发非同步pdo
      * 进入状态11
    * 触发同步pdo
      * 进入状态3和5和11，多次调用buildPDO ,实现所有的PDO的发送

## NMT

```
//State
enum enum_nodeState {
  Initialisation  = 0x00, 
  Disconnected    = 0x01,
  Connecting      = 0x02,
  Preparing       = 0x02,
  Stopped         = 0x04,
  Operational     = 0x05,
  Pre_operational = 0x7F,
  Unknown_state   = 0x0F
};
```

## Error

```c
typedef struct {
	UNS16 errCode;
	UNS8 errRegMask;
	UNS8 active;
} s_errors;
```



