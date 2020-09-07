#ifndef _PID_H_
#define _PID_H_	 



typedef struct
{
	float ref;//输入：系统待调节量的给定值
	float fdb;//输入：系统待调节量的反馈值
	float inte;//积分值
	float err[2];
	float kp;
	float ki;
	float kd;
	float componentKp;
	float componentKi;
	float componentKd;
	float componentKpMax;
	float componentKiMax;
	float componentKdMax;
	float output;
	float outputMax;
} PID_Regulator_t;

typedef struct
{
	PID_Regulator_t Position;
	PID_Regulator_t Speed;
} PID_Regulator_Double_Loop_t;



void PID_Init(PID_Regulator_t *pid,float kp,float ki,float kd,float componentKpMax,float componentKiMax,float componentKdMax,float outputMax);
void PID_Calc(PID_Regulator_t *pid);
void PID_ALL_Init(void);

#endif
