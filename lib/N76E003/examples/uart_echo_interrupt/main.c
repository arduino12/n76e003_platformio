/*
 * N76E003 UART echo with interrupt.
 *   UART0: P0.7(RXD) P0.6(TXD)
 *   UART1: P0.2(RXD) P1.6(TXD)
 *
 * arad.rgb@gmail.com
 */
#include "N76E003.h"
#include "Common.h"
#include "Delay.h"
#include "SFR_Macro.h"
#include "Function_define.h"

#define UART_INDEX		(1)
#define UART_BAUDRATE	(115200)

uint8_t uart_data;
bit_t uart_ri_flag;

#if UART_INDEX
void SerialPort1_ISR(void) __interrupt 15
{
	if (RI_1) {					// uart rx done
		clr_RI_1;				// clear rx flag
		uart_data = SBUF_1;
		uart_ri_flag = 1;
	}
	if(TI_1) {					// uart tx done
		clr_TI_1;				// clear tx flag
	}
}
#else
void SerialPort0_ISR(void) __interrupt 4
{
	if (RI) {					// uart rx done
		clr_RI;					// clear rx flag
		uart_data = SBUF;
		uart_ri_flag = 1;
	}
	if(TI) {					// uart tx done
		clr_TI;					// clear tx flag
	}
}
#endif

void main(void)
{
#if UART_INDEX
	InitialUART1_Timer3(UART_BAUDRATE);
	set_ES_1;					// enable uart interrupt
#else
	InitialUART0_Timer3(UART_BAUDRATE);
	set_ES;						// enable uart interrupt
#endif
	set_EA;

	while(1) {
		if (uart_ri_flag) {
			uart_ri_flag = 0;
#if UART_INDEX
			Send_Data_To_UART1(uart_data);
#else
			Send_Data_To_UART0(uart_data);
#endif
		}
	}
}
