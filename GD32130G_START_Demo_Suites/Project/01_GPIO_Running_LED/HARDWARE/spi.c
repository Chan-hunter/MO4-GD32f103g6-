#include "spi.h"
#include "systick.h"
#include <stdio.h>
#include "gd32f1x0.h"


void SPI_Init(void)
{
    spi_parameter_struct spi_init_struct;//Define SPI parameter structure
	
	rcu_periph_clock_enable(RCU_GPIOA); // 使能GPIOA时钟，SPI0对应的PA15引脚在GPIOA
	rcu_periph_clock_enable(RCU_GPIOB); // 使能GPIOA时钟，SPI0对应的PB3/PB4/PB5引脚在GPIOB
	rcu_periph_clock_enable(RCU_SPI0); // 使能SPI0时钟

	gpio_af_set(GPIOB, GPIO_AF_0, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5); //将PB3/PB4/PB5配置为AF_0(SPI)
	gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5); //将PB3/PB4/PB5配置为复用模式，浮空
	gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5); //将PB3/PB4/PB5配置为推挽模式，IO速率50MHz
	
	gpio_mode_set(SPI0_CS_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, SPI0_CS_PIN); //将SPI0_CS_PORT(PA15)置为复用模式，浮空
    gpio_output_options_set(SPI0_CS_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, SPI0_CS_PIN); //将SPI0_CS_PORT(PA15)配置为推挽模式，IO速率50MHz
	
	spi_i2s_deinit(SPI0); // 复位外设SPI0至默认参数
	spi_struct_para_init(&spi_init_struct); // 初始化SPI参数结构体（spi_init_struct）
	
	spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX; // 传输模式=全双工模式
	spi_init_struct.device_mode = SPI_MASTER; // 将GD32设置位SPI主机
	spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT; // 每帧大小=8位
	spi_init_struct.clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE; // 极性=低电平 且 奇数边沿采集数据	模式0
	spi_init_struct.nss = SPI_NSS_SOFT; // 软件NSS
	spi_init_struct.prescale = SPI_PSC_8; // 主频4分频，GD32E230主频72M，SPI0主频最高18M
	spi_init_struct.endian = SPI_ENDIAN_MSB; // 传输时高位在前
	spi_init(SPI0, &spi_init_struct); // 用配置好的SPI参数结构体对SPI0进行初始化
	
	spi_enable(SPI0); // 使能SPI0
}


void SPI_SetSpeed(char SPI_BaudRatePrescaler)
{

} 


char SPI_ReadWriteByte(char TxData)
{		
//	u8 retry=0;				 	
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
//		{
//		retry++;
//		if(retry>200)return 0;
//		}			  
//	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
//	retry=0;

//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
//		{
//		retry++;
//		if(retry>200)return 0;
//		}	  						    
//	return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����					    
}




