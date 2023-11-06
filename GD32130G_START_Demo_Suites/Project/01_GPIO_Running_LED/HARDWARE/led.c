#include "led.h"
#include "gd32f130g_start.h"

void LED_Init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOA);
    /* configure led GPIO port */ 
    gpio_mode_set(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OTYPE_PP,  GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
    gpio_bit_reset(GPIOA,  GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
    
}
 
 

