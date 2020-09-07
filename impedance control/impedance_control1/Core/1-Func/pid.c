/**************************************************
* @file      pid.c
* @author    not wwy
* @version   
* @date      
* @brief     
***************************************************
* @attention
for hero robot
***************************************************
*/

/* Include ---------------------------------------*/
#include "pid.h"

/* Global Variable -------------------------------*/
PID_Regulator_t forceControlPID;


void PID_Calc(PID_Regulator_t *pid)
{
	pid->err[0] = pid->err[1];
	pid->err[1] = pid->ref - pid->fdb;
	pid->inte+=pid->err[1];
		
	
	pid->componentKp  = pid->kp * pid->err[1];
	pid->componentKi  = pid->ki * pid->inte;
	pid->componentKd  = pid->kd * (pid->err[1] - pid->err[0]);
	
	if(pid->componentKp > pid->componentKpMax)
		pid->componentKp = pid->componentKpMax;
	else if (pid->componentKp < -pid->componentKpMax)
		pid->componentKp = -pid->componentKpMax;
		
	if(pid->componentKi > pid->componentKiMax)
		pid->componentKi = pid->componentKiMax;
	else if (pid->componentKi < -pid->componentKiMax)
		pid->componentKi = -pid->componentKiMax;
	
	pid->output = pid->componentKp + pid->componentKi+ pid->componentKd;
	
	if(pid->output > pid->outputMax)
		pid->output = pid->outputMax;
	else if (pid->output < -pid->outputMax)
		pid->output = -pid->outputMax;	
}



void PID_Init(PID_Regulator_t *pid,float kp,float ki,float kd,float componentKpMax,float componentKiMax,float componentKdMax,float outputMax)
{
	pid->kp = kp;
	pid->ki = ki;
	pid->kd = kd;
	pid->inte = 0;
	pid->componentKpMax = componentKpMax;
	pid->componentKiMax = componentKiMax;
	pid->componentKdMax = componentKdMax;
	pid->outputMax = outputMax;
}

