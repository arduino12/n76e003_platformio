#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdint.h>

#define CID_READ		0x0B
#define DID_READ		0x0C
#define ERASE_APROM		0x22
#define READ_APROM		0x00
#define PROGRAM_APROM	0x21
#define ERASE_LDROM
#define READ_LDROM
#define PROGRAM_LDROM
#define READ_CFG		0xC0
#define PROGRAM_CFG		0xE1
#define READ_UID		0x04

typedef __bit bit_t;

void InitialUART0_Timer1(uint32_t baudrate);
void InitialUART0_Timer3(uint32_t baudrate);
void InitialUART1_Timer3(uint32_t baudrate);
void Send_Data_To_UART0(uint8_t c);
uint8_t Receive_Data_From_UART0(void);
void Send_Data_To_UART1(uint8_t c);
uint8_t Receive_Data_From_UART1(void);
void InitialUART1(uint32_t baudrate);

#endif
