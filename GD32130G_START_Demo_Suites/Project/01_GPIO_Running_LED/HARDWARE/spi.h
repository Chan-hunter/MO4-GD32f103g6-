#ifndef __SPI_H
#define __SPI_H

 				  	    													  
void SPI_Init(void);			         //SPI初始化函数 
char SPI_ReadWriteByte(char TxData);     //模拟SPI读写数据函数
		 
#define         RCU_SPI_GPIOx       RCU_GPIOB    //使能SPI的GPIO时钟
#define         RCU_SPI_SCK_GPIOx   RCU_GPIOA    //使能SPI的GPIO时钟
#define         SPI_GPIOx       GPIOB            //SPI的GPIO
#define         SPI_SCK_GPIOx   GPIOA            //SPI的GPIO

#define         SPI_GPIO_CSN     GPIO_PIN_3      //片选
#define         SPI_GPIO_SCK     GPIO_PIN_15     //时钟
#define         SPI_GPIO_MISO    GPIO_PIN_4      //输入（本项目没有）
#define         SPI_GPIO_MOSI    GPIO_PIN_4      //输出

//SPI时钟
#define 		SCK_L	gpio_bit_reset(SPI_SCK_GPIOx , SPI_GPIO_SCK)
#define 		SCK_H	gpio_bit_set(SPI_SCK_GPIOx , SPI_GPIO_SCK)
 
//SPI输入
#define 		READ_MISO	GPIO_ReadInputDataBit(SPI_GPIOx, SPI_GPIO_MISO)
 
//SPI片选信号	
#define 		CSN_L     gpio_bit_reset(SPI_GPIOx, SPI_GPIO_CSN)
#define 		CSN_H     gpio_bit_set(SPI_GPIOx, SPI_GPIO_CSN)
 
//SPI输出
#define 		MOSI_L	gpio_bit_reset(SPI_GPIOx , SPI_GPIO_MOSI)
#define 		MOSI_H	gpio_bit_set(SPI_GPIOx , SPI_GPIO_MOSI)
         
#endif

