#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

void Timer0_Delay100us(uint32_t count)
{
	clr_T0M;				//T0M=0, Timer0 Clock = Fsys/12
	TMOD |= 0x01;			//Timer0 is 16-bit mode
	set_TR0;				//Start Timer0
	while (count--) {
		TL0 = LOBYTE(TIMER_DIV12_VALUE_100us);
		TH0 = HIBYTE(TIMER_DIV12_VALUE_100us);
		while (TF0 != 1);	//Check Timer0 Time-Out Flag
		clr_TF0;
	}
	clr_TR0;				//Stop Timer0
}

void Timer0_Delay1ms(uint32_t count)
{
	clr_T0M;				//T0M=0, Timer0 Clock = Fsys/12
	TMOD |= 0x01;			//Timer0 is 16-bit mode
	set_TR0;				//Start Timer0
	while (count--) {
		TL0 = LOBYTE(TIMER_DIV12_VALUE_1ms);
		TH0 = HIBYTE(TIMER_DIV12_VALUE_1ms);
		while (TF0 != 1);	//Check Timer0 Time-Out Flag
		clr_TF0;
	}
	clr_TR0;				//Stop Timer0
}

void Timer0_Delay40ms(uint32_t count)
{
	clr_T0M;				//T0M=0, Timer0 Clock = Fsys/12
	TMOD |= 0x01;			//Timer0 is 16-bit mode
	set_TR0;				//Start Timer0
	while (count--) {
		TL0 = LOBYTE(TIMER_DIV12_VALUE_40ms);
		TH0 = HIBYTE(TIMER_DIV12_VALUE_40ms);
		while (TF0 != 1);	//Check Timer0 Time-Out Flag
		clr_TF0;
	}
	clr_TR0;				//Stop Timer0
}

void Timer1_Delay10ms(uint32_t count)
{
	clr_T1M;				//T1M=0, Timer1 Clock = Fsys/12
	TMOD |= 0x10;			//Timer1 is 16-bit mode
	set_TR1;				//Start Timer1
	while (count--) {
		TL1 = LOBYTE(TIMER_DIV12_VALUE_10ms);
		TH1 = HIBYTE(TIMER_DIV12_VALUE_10ms);
		while (TF1 != 1);	//Check Timer1 Time-Out Flag
		clr_TF1;
	}
	clr_TR1;				//Stop Timer1
}

void Timer2_Delay500us(uint32_t count)
{
	clr_T2DIV2;				//Timer2 Clock = Fsys/4 
	clr_T2DIV1;
	set_T2DIV0;
	set_TR2;				//Start Timer2
	while (count--) {
		TL2 = LOBYTE(TIMER_DIV4_VALUE_500us);
		TH2 = HIBYTE(TIMER_DIV4_VALUE_500us);
		while (TF2 != 1);	//Check Timer2 Time-Out Flag
		clr_TF2;
	}
	clr_TR2;				//Stop Timer2
}

void Timer3_Delay10us(uint32_t count)
{
	T3CON = 0x07;			//Timer3 Clock = Fsys/128
	set_TR3;				//Trigger Timer3
	while (count--) {
		RL3 = LOBYTE(TIMER_DIV4_VALUE_10us);
		RH3 = HIBYTE(TIMER_DIV4_VALUE_10us);
		while ((T3CON&SET_BIT4) != SET_BIT4);	//Check Timer3 Time-Out Flag
		clr_TF3;
	}
	clr_TR3;				//Stop Timer3
}

void Timer3_Delay100ms(uint32_t count)
{
	T3CON = 0x07;			//Timer3 Clock = Fsys/128
	set_TR3;				//Trigger Timer3
	while (count--) {
		RL3 = LOBYTE(TIMER_DIV128_VALUE_100ms);
		RH3 = HIBYTE(TIMER_DIV128_VALUE_100ms);
		while ((T3CON&SET_BIT4) != SET_BIT4);	//Check Timer3 Time-Out Flag
		clr_TF3;
	}
	clr_TR3;				//Stop Timer3
}
