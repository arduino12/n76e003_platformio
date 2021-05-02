/*
 * N76E003 GPIOs toggle.
 *
 * arad.rgb@gmail.com
 */
#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

void main(void)
{
	Set_All_GPIO_Quasi_Mode;	// Reset all GPIOs to inputs

	P0M1 = P1M1 = 0x00;			// set P0.0-P0.7 and P1.0-P1.7 GPIOs to PushPull
	P0M2 = P1M2 = 0xff;

	P30_PushPull_Mode;			// set P3.0 to PushPull

	while(1) {					// Toggle GPIOs every 100ms
		P0 ^= 0xff;
		P1 = ~P1;
		P30 = !P30;
		Timer0_Delay1ms(100);
	}
}
