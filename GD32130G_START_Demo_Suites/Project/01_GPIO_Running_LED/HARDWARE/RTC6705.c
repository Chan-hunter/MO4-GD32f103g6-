#include "RTC6705.h"


void BIAS_Init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOB);
    /* configure led GPIO port */ 
    gpio_mode_set(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_5);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OTYPE_PP,  GPIO_PIN_5);
    gpio_bit_set(GPIOB,  GPIO_PIN_5);
    
}

void PA_Init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    /* configure led GPIO port */ 
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_0);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OTYPE_PP,  GPIO_PIN_0);
    gpio_bit_set(GPIOA,  GPIO_PIN_0);
    
}


void RTC6705_WriteREG(u8 address,u32 data)
{
	u32 i;
	SCK_L;
	CSN_L;
//	RTC6715_STATE_W();
	Delay(0xff);
	SCK_L;
	for(i=0;i<4;i++)
	{
//		if((address&0x01)==1) MOSI_H;
//		else MOSI_L;
//		address>>=1;
//		Delay(0xff);
//		SCK_H;
//		Delay(0xff);
//		SCK_L;
//		Delay(0xff);
        
        Delay(0xff);
		if((address&0x01)==1) MOSI_H;
		else MOSI_L;
		SCK_H;
		address>>=1;
		Delay(0xff);
		SCK_L;
	}
	
	MOSI_H;Delay(0xff);	//写
	SCK_H;Delay(0xff);
	SCK_L;
	
//	RTC6715_STATE_W();
	for(i=0;i<20;i++)
	{
		Delay(0xff);
		if((data&0x01)==1) MOSI_H;
		else MOSI_L;
		SCK_H;
		data>>=1;
		Delay(0xff);
		SCK_L;
	}
	Delay(0xff);
	CSN_H;
	Delay(0xffff);
}


void SetFreq(u32 freq)  //8705
{
	u32 N,A,data;
    
    freq = freq /0.04;
    N = freq /64;
    A = freq -N*64;
    
	
	data=N<<7;
	data+=A;
	RTC6705_WriteREG(0x01,data);
}


uint16_t const VTX_Freq[] =
{
    //A
    5865,5845,5825,5805,5785,5765,5745,5725,
    //B
    5733,5752,5771,5790,5809,5828,5847,5866,
    //E
    5705,5685,5665,5645,5885,5905,5925,5945,
    //F
    5740,5760,5780,5800,5820,5840,5860,5880,
    //R
    5658,5695,5732,5769,5806,5843,5880,5917,
    //L
    5362,5399,5436,5473, 5510,5547,5584,5621,
};

