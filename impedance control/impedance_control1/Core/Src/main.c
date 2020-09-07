
#include "main.h"
#include "math.h"

extern PID_Regulator_t forceControlPID;


float CalI_target(float f_control ,float currentforce)
{
	forceControlPID.fdb = currentforce;
	forceControlPID.ref = f_control;
	PID_Calc(&forceControlPID);
	float I_control = forceControlPID.output;
	return I_control;
}


typedef struct
{
	float theta;
	float theta_dot;
	float theta_ddot;
	float torque;
} MotorState_t;

MotorState_t desiredTarget = {10,0,0,0};
MotorState_t CurrentState = {0};
float M = 0.5, L=0.5, J = 0.5;
float Jm = 0.5, Dm=0.5, Km = 1.0;

float CalForce_target(MotorState_t * MotorStateTarget, MotorState_t * CurrentMotorState, float currentContactForce)
{
	float f_control = J*MotorStateTarget->theta_ddot+
		J/Jm*Dm*(MotorStateTarget->theta_dot-CurrentMotorState->theta_dot)+
		Km*(MotorStateTarget->theta-CurrentMotorState->theta)+
		(J/Jm - 1)*currentContactForce;
	
	return f_control;
}

float currenttheta, currenttheta_dot, currentforce;	//单位 °

void getMotorState()
{
	CurrentState.theta = 5;		//CANOpen dict 0x6064
	CurrentState.theta_dot = 5;	//CANOpen dict 0x606C
	CurrentState.torque = 5;	//CANOpen dict 
}

/* 指令周期 PDO 中进行调用 */
void contorl_loop(void)
{
	// impedance control algorithm
	float f_control = CalForce_target(&desiredTarget, &CurrentState, 0);	//mNm
	// force control algorithm
	float I_control = CalI_target(f_control , CurrentState.torque);			//mA
	// 发送 Edit_dict
}


int main(void)
{
	Core_Config();
	Jlink_Init();

	PID_Init(&forceControlPID, 0,0,0,1500,1500,1500,8000);
	

	
}


