#ifndef __RTC6705_H
#define __RTC6705_H

#include "spi.h"
#include "systick.h"
#include <stdio.h>
#include "gd32f1x0.h"
#include "delay.h"

#define         RCU_BIAS_GPIOx       RCU_GPIOB    
#define         BIAS_GPIOx   GPIOB           
#define         BIAS_GPIO    GPIO_PIN_5      

void SetFreq(u32 freq);
void RTC6705_WriteREG(u8 address,u32 data);
void BIAS_Init(void);
void PA_Init(void);
extern uint16_t const VTX_Freq[];
         
#endif

