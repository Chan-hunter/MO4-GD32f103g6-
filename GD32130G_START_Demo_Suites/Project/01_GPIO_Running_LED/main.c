/*!
    \file    main.c
    \brief   GPIO keyboard interrupt mode demo

    \version 2016-01-15, V1.0.0, demo for GD32F1x0
    \version 2016-05-13, V2.0.0, demo for GD32F1x0
    \version 2019-11-20, V3.0.0, demo for GD32F1x0
    \version 2021-12-31, V3.1.0, demo for GD32F1x0
*/

/*
    Copyright (c) 2021, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32f1x0.h"
#include "systick.h"
#include "led.h"
#include "RTC6705.h"
#include "pwm.h"
#include "adc.h"
#include "filter.h"
#include "pid.h"
#include "main.h"
#include "uart.h"
#include "SmartAudio.h"


/*!
    \brief      main function
    \param[in]  none
    \param[out] none
    \retval     none
*/
float Vpd=0,dB=20,set_Vpd;
int dir=1,led0pwmval=0;
float set_pwm;    
u8 set_flag ;
u16 length;


int main(void)
{
    /* enable the led clock */
//    rcu_periph_clock_enable(RCU_GPIOA);
//    /* configure led GPIO port */ 
//    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_1);
//    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OTYPE_PP,  GPIO_PIN_1);
//    gpio_bit_reset(GPIOA,  GPIO_PIN_1);
    LED_Init();
    SPI_Init();
//    BIAS_Init();
    PA_Init();
    RTC6705_WriteREG(0x0F,0000);
    RTC6705_WriteREG(0x00,400);
    SetFreq(5600);
    Vpd_ADC_Init();
    TIM1_PWM_Init();
    TIM2_PWM_Init();
    UART0_Init();
    /* setup SysTick Timer for 1ms interrupts  */
    systick_config();
    set_Vpd=530;  //14dbm:610 20dbm:1005  24dbm:1420    26dbm:1680

    while(1){
        
        /*控制功率*/
        set_Vpd=530;
        Vpd=(LimitFilter((get_adc_ch(1)),4096,0,200));//LimitFilter  filter  *3.3/4096
        set_pwm = Constrain(pid_control(Vpd,set_Vpd,1.4+(set_Vpd/1000),0.07,0.5),1300,800);
        timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_1,set_pwm);
        
        /* SmartAudio通信 */
      if(set_flag == 1)
      {
        usart_transmit_config(USART0, USART_TRANSMIT_ENABLE); //开启发送
        usart0_data_send(transmitter_buffer0,SmartAudio.length);
        memset(receiver_buffer0,0,20);
        USART0_RestoreReceive();
        set_flag = 0;
      }
        
    }
}
