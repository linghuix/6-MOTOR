#ifndef __HW_EPOS_H
#define __HW_EPOS_H

#include "stm32f10x.h"

#include "epos.h"

extern Epos Controller,Controller1; 

void Epos_INIT(void);
void Epos_ReceiveDate(void);
void Epos_Conroller_TIMBack(void);
void Epos_Start(void);

void Epos_ControlTask(void);

#endif

