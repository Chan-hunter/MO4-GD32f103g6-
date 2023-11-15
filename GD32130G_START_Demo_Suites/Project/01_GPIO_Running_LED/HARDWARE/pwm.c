#include "gd32f130g_start.h"
#include "gd32f1x0_timer.h"
#include "pwm.h"

void TIM2_PWM_Init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_BIAS_GPIOx);     //使能pb5时钟
    rcu_periph_clock_enable(RCU_TIMER2);    //使能tim2时钟
    /* configure led GPIO port */ 
    gpio_mode_set(BIAS_GPIOx, GPIO_MODE_AF, GPIO_PUPD_NONE, BIAS_GPIO);
    gpio_output_options_set(BIAS_GPIOx, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, BIAS_GPIO);
//    gpio_bit_reset(BIAS_GPIOx, BIAS_GPIO);
    

		/*使能复用时钟 */
//    rcu_periph_clock_enable(RCU_AF);

		/*设置io口,设置为复用模式 */
    gpio_af_set(BIAS_GPIOx,GPIO_AF_1,BIAS_GPIO);
//    gpio_init(GPIOB,GPIO_MODE_AF_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_11);
		/*TIMER1全部重映射*/
//		gpio_pin_remap_config (GPIO_TIMER1_FULL_REMAP, ENABLE);
    
    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

		/*定时器复位 */
    timer_deinit(TIMER2);

    /* TIMER1 configuration */
		/*时钟分频系数 */
    timer_initpara.prescaler         = 1 -1;
    /*边沿对齐 */
		timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    /*上升计数 */
		timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    /*计数值 */
		timer_initpara.period            = 6000-1;
    /*根据prescaler,clockdivision最终该定时器时钟评率为1M */
		timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    /*重复计数器的值 */
		timer_initpara.repetitioncounter = 0;
    /* */
		timer_init(TIMER2,&timer_initpara);

    /* CH0,CH1 and CH2 configuration in PWM mode */
		/*是否使能输出 */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    /*是否互补通道输出 */
		timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    /*输出极性 */
		timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_LOW;
    /*输出死区延迟的极性 */
		timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_LOW;
    /*空闲状态下通道输出极性通道 */
		timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_HIGH;
    /*空闲时互补通道输出极性 */
		timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_HIGH;

    /*配置通道 */
		timer_channel_output_config(TIMER2,TIMER_CH_1,&timer_ocintpara);



    /* CH3 configuration in PWM mode0,duty cycle 30% */
    /*设置阈值(比较值,调节占空比的时候调节这个值) */
		timer_channel_output_pulse_value_config(TIMER2,TIMER_CH_1,900);
    /*输出模式配置 */
		timer_channel_output_mode_config(TIMER2,TIMER_CH_1,TIMER_OC_MODE_PWM0);
    /*不使用影子寄存器 */
		timer_channel_output_shadow_config(TIMER2,TIMER_CH_1,TIMER_OC_SHADOW_DISABLE);



    /* 使能定时器自动重装载值 */
    timer_auto_reload_shadow_enable(TIMER2);
    /* 使能定时器 */
    timer_enable(TIMER2);
    
//    timer_autoreload_value_config (TIMER2, 500-1);
//    
//    timer_prescaler_config (TIMER2, 60-1, TIMER_PSC_RELOAD_NOW);




}


void TIM1_PWM_Init(void)
{
    /* enable the led clock */
    rcu_periph_clock_enable(RCU_GPIOA);     //使能PA时钟
    rcu_periph_clock_enable(RCU_TIMER1);    //使能tim1时钟
    /* configure led GPIO port */ 
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_3);
//    gpio_bit_reset(GPIOA, GPIO_PIN_3);
    

		/*使能复用时钟 */
//    rcu_periph_clock_enable(RCU_AF);

		/*设置io口,设置为复用模式 */
    gpio_af_set(GPIOA,GPIO_AF_2,GPIO_PIN_3);
		/*TIMER1全部重映射*/
//		gpio_pin_remap_config (GPIO_TIMER1_FULL_REMAP, ENABLE);
    
    timer_oc_parameter_struct timer_ocintpara;
    timer_parameter_struct timer_initpara;

		/*定时器复位 */
    timer_deinit(TIMER1);

    /* TIMER1 configuration */
		/*时钟分频系数 */
    timer_initpara.prescaler         = 72-1;
    /*边沿对齐 */
		timer_initpara.alignedmode       = TIMER_COUNTER_EDGE;
    /*上升计数 */
		timer_initpara.counterdirection  = TIMER_COUNTER_UP;
    /*计数值 */
		timer_initpara.period            = 1000-1;
    /*根据prescaler,clockdivision最终该定时器时钟评率为1M */
		timer_initpara.clockdivision     = TIMER_CKDIV_DIV1;
    /*重复计数器的值 */
		timer_initpara.repetitioncounter = 0;
    /* */
		timer_init(TIMER1,&timer_initpara);

    /* CH0,CH1 and CH2 configuration in PWM mode */
		/*是否使能输出 */
    timer_ocintpara.outputstate  = TIMER_CCX_ENABLE;
    /*是否互补通道输出 */
		timer_ocintpara.outputnstate = TIMER_CCXN_DISABLE;
    /*输出极性 */
		timer_ocintpara.ocpolarity   = TIMER_OC_POLARITY_HIGH;
    /*输出死区延迟的极性 */
		timer_ocintpara.ocnpolarity  = TIMER_OCN_POLARITY_HIGH;
    /*空闲状态下通道输出极性通道 */
		timer_ocintpara.ocidlestate  = TIMER_OC_IDLE_STATE_LOW;
    /*空闲时互补通道输出极性 */
		timer_ocintpara.ocnidlestate = TIMER_OCN_IDLE_STATE_LOW;

    /*配置通道 */
		timer_channel_output_config(TIMER1,TIMER_CH_3,&timer_ocintpara);


    /*设置阈值(比较值,调节占空比的时候调节这个值) */
		timer_channel_output_pulse_value_config(TIMER1,TIMER_CH_3,100);
    /*输出模式配置 */
		timer_channel_output_mode_config(TIMER1,TIMER_CH_3,TIMER_OC_MODE_PWM0);
    /*不使用影子寄存器 */
		timer_channel_output_shadow_config(TIMER1,TIMER_CH_3,TIMER_OC_SHADOW_DISABLE);



    /* 使能定时器自动重装载值 */
    timer_auto_reload_shadow_enable(TIMER1);
    /* 使能定时器 */
    timer_enable(TIMER1);
//    
//    timer_autoreload_value_config (TIMER1, 500-1);
//    
//    timer_prescaler_config (TIMER1, 60-1, TIMER_PSC_RELOAD_NOW);




}
