#include "N76E003.h"
#include "Common.h"
#include "SFR_Macro.h"
#include "Function_define.h"

bit_t BIT_TMP;

void InitialUART0_Timer1(uint32_t baudrate) //T1M = 1, SMOD = 1
{
	P06_Quasi_Mode;			//Setting UART pin as Quasi mode for transmit
	P07_Quasi_Mode;			//Setting UART pin as Quasi mode for transmit

	SCON = 0x50;			//UART0 Mode1,REN=1,TI=1
	TMOD |= 0x20;			//Timer1 Mode1

	set_SMOD;				//UART0 Double Rate Enable
	set_T1M;
	clr_BRCK;				//Serial port 0 baud rate clock source = Timer1
 
#if defined(FOSC_160000)	//16 MHz
	TH1 = 256 - (1000000/baudrate+1);
#elif defined(FOSC_166000)	//16.6 MHz
	TH1 = 256 - (1037500/baudrate);
#endif

	set_TR1;
	set_TI;					//For printf function must setting TI = 1
}

void InitialUART0_Timer3(uint32_t baudrate) //use timer3 as Baudrate generator
{
	P06_Quasi_Mode;			//Setting UART pin as Quasi mode for transmit
	P07_Quasi_Mode;			//Setting UART pin as Quasi mode for transmit	

	SCON = 0x50;			//UART0 Mode1,REN=1,TI=1
	set_SMOD;				//UART0 Double Rate Enable
	T3CON &= 0xF8;			//T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
	set_BRCK;				//UART0 baud rate clock source = Timer3

#if defined(FOSC_160000)	//16 MHz
	RH3 = HIBYTE(65536 - (1000000/baudrate)-1);
	RL3 = LOBYTE(65536 - (1000000/baudrate)-1);
#elif defined(FOSC_166000)	//16.6 MHz
	RH3 = HIBYTE(65536 - (1037500/baudrate));
	RL3 = LOBYTE(65536 - (1037500/baudrate));
#endif

	set_TR3;				//Trigger Timer3
	set_TI;					//For printf function must setting TI = 1
}

uint8_t Receive_Data_From_UART0(void)
{
	uint8_t c;
	while (!RI);
	c = SBUF;
	RI = 0;
	return (c);
}

void Send_Data_To_UART0 (uint8_t c)
{
	TI = 0;
	SBUF = c;
	while(TI==0);
}

void InitialUART1_Timer3(uint32_t baudrate) //use timer3 as Baudrate generator
{
	P02_Quasi_Mode;			//Setting UART pin as Quasi mode for transmit
	P16_Quasi_Mode;			//Setting UART pin as Quasi mode for transmit

	SCON_1 = 0x50;			//UART1 Mode1,REN_1=1,TI_1=1
	T3CON = 0x08;			//T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1), UART1 in MODE 1
	clr_BRCK;

#if defined(FOSC_160000)	//16 MHz
	RH3 = HIBYTE(65536 - (1000000/baudrate)-1);
	RL3 = LOBYTE(65536 - (1000000/baudrate)-1);
#elif defined(FOSC_166000)	//16.6 MHz
	RH3 = HIBYTE(65536 - (1037500/baudrate));
	RL3 = LOBYTE(65536 - (1037500/baudrate));
#endif

	set_TR3;				//Trigger Timer3
}

uint8_t Receive_Data_From_UART1(void)
{
	uint8_t c;
	while (!RI_1);
	c = SBUF_1;
	RI_1 = 0;
	return (c);
}

void Send_Data_To_UART1 (uint8_t c)
{
	TI_1 = 0;
	SBUF_1 = c;
	while(TI_1==0);
}

#ifdef SW_Reset
void SW_Reset(void)
{
	TA = 0xAA;
	TA = 0x55;
	set_SWRST;
}
#endif
