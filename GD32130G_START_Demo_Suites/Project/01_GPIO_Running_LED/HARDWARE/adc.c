#include "adc.h"
#include "delay.h"
#include "filter.h"


void Vpd_ADC_Init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_adc_clock_config(RCU_ADCCK_APB2_DIV6);
    
    /* configure led GPIO port */ 
    gpio_mode_set(GPIOA, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_1);
//    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OTYPE_PP,  GPIO_PIN_1);
    
    rcu_periph_clock_enable(RCU_ADC); ////使能ADC时钟
//    rcu_periph_clock_enable(RCU_TIMER1);    //使能tim1时钟
    
    adc_external_trigger_source_config(ADC_REGULAR_CHANNEL, ADC_EXTTRIG_REGULAR_NONE);
    
//    adc_external_trigger_config(ADC_REGULAR_CHANNEL,DISABLE);		//配置触发方式为软件触发
   
    adc_software_trigger_enable(ADC_REGULAR_CHANNEL);				//使能ADC软件触发
    
    adc_data_alignment_config(ADC_DATAALIGN_RIGHT);			//数据对齐方式,靠右对齐
    
    adc_channel_length_config(ADC_REGULAR_CHANNEL, 1);	//配置使用ADC规则通道,使用1个
    
    adc_external_trigger_config(ADC_REGULAR_CHANNEL, ENABLE);				//外部触发
    adc_enable();
    Delay(0xffff);
    
    adc_calibration_enable();			//进行ADC校准
    
}


u16 get_adc_ch( u8 ch)
{
	adc_regular_channel_config(0, ch, ADC_SAMPLETIME_239POINT5);	//ch参数为ADC通道:ADC_CHANNEL_x  x = 0...15
	adc_software_trigger_enable(ADC_REGULAR_CHANNEL);			//使用软件触发
	
	while(!adc_flag_get( ADC_FLAG_EOC));			//等待转换结束
	adc_flag_clear(ADC_FLAG_EOC);
	return (adc_regular_data_read()& 0xFFFF);// & 0xFFFF
   
}

u16 get_adc_filter_ch(u8 ch)
{
    u16 sum;
    sum = filter(get_adc_ch(ch));
    return sum ;
}
 




