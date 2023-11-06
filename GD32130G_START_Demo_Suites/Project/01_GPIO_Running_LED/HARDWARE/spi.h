#ifndef __SPI_H
#define __SPI_H

 				  	    													  
void SPI_Init(void);			 //��ʼ��SPI��
void SPI_SetSpeed(char SpeedSet); //����SPI�ٶ�   
char SPI_ReadWriteByte(char TxData);//SPI���߶�дһ���ֽ�

#define W25QXX_DUMMY_BYTE 0xA5

#define SPI0_CS_PORT	GPIOA
#define SPI0_CS_PIN		GPIO_PIN_15

#define SET_SPI0_CS		gpio_bit_set(SPI0_CS_PORT, SPI0_CS_PIN)
#define CLR_SPI0_CS		gpio_bit_reset(SPI0_CS_PORT, SPI0_CS_PIN)
		 
#endif

