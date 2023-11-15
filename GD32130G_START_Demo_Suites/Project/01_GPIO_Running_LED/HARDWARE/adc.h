#ifndef __ADC_H
#define __ADC_H	 

#include "gd32f130g_start.h"

void Vpd_ADC_Init(void);
u16 get_adc_ch( u8 ch);
u16 get_adc_filter_ch(u8 ch);
		 				    
#endif
