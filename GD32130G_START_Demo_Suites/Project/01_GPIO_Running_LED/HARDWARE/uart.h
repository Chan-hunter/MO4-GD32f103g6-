#ifndef __UART_H
#define __UART_H	 

#include "gd32f130g_start.h"

#define USART_REC_LEN  			200  	//定义最大接收字节数 200

void UART0_Init(void);
void usart0_data_receive(void);
		 				    

extern uint16_t rxcount0 ; 

extern uint8_t receiver_buffer0[100];

ErrStatus memory_compare(uint8_t* src, uint8_t* dst, uint16_t length) ;

//uint8_t receiver_buffer0[100];

#endif


