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





## 代码框架：

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
	& NODE_PREFIX ## _bDeviceNodeId,     /* bDeviceNodeId */\
	NODE_PREFIX ## _objdict,             /* objdict  */\
	NODE_PREFIX ## _PDO_status,          /* PDO_status */\
	NULL,                                /* RxPDO_EventTimers */\
	_RxPDO_EventTimers_Handler,          /* RxPDO_EventTimers_Handler */\
	& NODE_PREFIX ## _firstIndex,        /* firstIndex */\
	& NODE_PREFIX ## _lastIndex,         /* lastIndex */\
	& NODE_PREFIX ## _ObjdictSize,       /* ObjdictSize */\
	& NODE_PREFIX ## _iam_a_slave,       /* iam_a_slave */\
	NODE_PREFIX ## _valueRangeTest,      /* valueRangeTest */\
	\
	/* SDO, structure s_transfer */\
	{\
          REPEAT_SDO_MAX_SIMULTANEOUS_TRANSFERS_TIMES(s_transfer_Initializer)\
	},\
	\
	/* State machine*/\
	Unknown_state,      /* nodeState */\
	/* structure s_state_communication */\
	{\
		0,          /* csBoot_Up */\
		0,          /* csSDO */\
		0,          /* csEmergency */\
		0,          /* csSYNC */\
		0,          /* csHeartbeat */\
		0,           /* csPDO */\
		0           /* csLSS */\
	},\
	_initialisation,     /* initialisation */\
	_preOperational,     /* preOperational */\
	_operational,        /* operational */\
	_stopped,            /* stopped */\
	NULL,                /* NMT node reset callback */\
	NULL,                /* NMT communications reset callback */\
	\
	/* NMT-heartbeat */\
	& NODE_PREFIX ## _highestSubIndex_obj1016, /* ConsumerHeartbeatCount */\
	NODE_PREFIX ## _obj1016,                   /* ConsumerHeartbeatEntries */\
	NODE_PREFIX ## _heartBeatTimers,           /* ConsumerHeartBeatTimers  */\
	& NODE_PREFIX ## _obj1017,                 /* ProducerHeartBeatTime */\
	TIMER_NONE,                                /* ProducerHeartBeatTimer */\
	_heartbeatError,           /* heartbeatError */\
	\
	{REPEAT_NMT_MAX_NODE_ID_TIMES(NMTable_Initializer)},\
                                                   /* is  well initialized at "Unknown_state". Is it ok ? (FD)*/\
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
	_post_sync,                 /* post_sync */\
	_post_TPDO,                 /* post_TPDO */\
	_post_SlaveBootup,			/* post_SlaveBootup */\
  _post_SlaveStateChange,			/* post_SlaveStateChange */\
	\
	/* General */\
	0,                                         /* toggle */\
	NULL,                   /* canSend */\
	NODE_PREFIX ## _scanIndexOD,                /* scanIndexOD */\
	_storeODSubIndex,                /* storeODSubIndex */\
    /* DCF concise */\
    NULL,       /*dcf_odentry*/\
	NULL,		/*dcf_cursor*/\
	1,		/*dcf_entries_count*/\
	0,		/* dcf_status*/\
    0,      /* dcf_size */\
    NULL,   /* dcf_data */\
	\
	/* EMCY */\
	Error_free,                      /* error_state */\
	sizeof(NODE_PREFIX ## _obj1003) / sizeof(NODE_PREFIX ## _obj1003[0]),      /* error_history_size */\
	& NODE_PREFIX ## _highestSubIndex_obj1003,    /* error_number */\
	& NODE_PREFIX ## _obj1003[0],    /* error_first_element */\
	& NODE_PREFIX ## _obj1001,       /* error_register */\
    & NODE_PREFIX ## _obj1014,       /* error_cobid */\
	/* error_data: structure s_errors */\
	{\
	REPEAT_EMCY_MAX_ERRORS_TIMES(ERROR_DATA_INITIALIZER)\
	},\
	_post_emcy,              /* post_emcy */\
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



## SDO

CO_data结构 的修改



## PDO







