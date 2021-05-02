#ifndef _DELAY_H_
#define _DELAY_H_

#include "N76E003.h"
#include "Common.h"
#include "SFR_Macro.h"
#include "Function_define.h"

void Timer0_Delay100us(uint32_t count);
void Timer0_Delay1ms(uint32_t count);
void Timer0_Delay40ms(uint32_t count);
void Timer1_Delay10ms(uint32_t count);
void Timer2_Delay500us(uint32_t count);
void Timer3_Delay10us(uint32_t count);
void Timer3_Delay100ms(uint32_t count);

#endif
