#include "uart.h"
#include "gd32f130g_start.h"
#include "delay.h"


__IO uint8_t txcount0 = 0; 
uint16_t rxcount0 = 0; 

uint8_t transmitter_buffer0[20];
uint8_t receiver_buffer0[20];

ErrStatus memory_compare(uint8_t* src, uint8_t* dst, uint16_t length) ;

void UART0_Init(void)
{
    /* enable USART and GPIOA clock */
//    rcu_periph_clock_disable(RCU_DMA);
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_USART0);
    
    /* configure the USART0 Tx pin and USART1 Tx pin */
    gpio_af_set(GPIOA, GPIO_AF_1, GPIO_PIN_9);
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_9);

 
    
    /* USART0  baudrate configuration */
    usart_deinit(USART0);
    usart_baudrate_set(USART0, 4800);                       //设置波特率
    usart_word_length_set(USART0, USART_WL_8BIT);           //8bit长度
    usart_parity_config(USART0, USART_PM_NONE);             //校验位
    usart_stop_bit_set(USART0, USART_STB_2BIT);             //2bit停止位
    usart_hardware_flow_rts_config(USART0, USART_RTS_DISABLE);
    usart_hardware_flow_cts_config(USART0, USART_CTS_DISABLE);//硬件流控设置
    usart_clock_disable(USART0);                            //禁止clock
    usart_irda_mode_disable(USART0);                        //禁止irDA
    usart_lin_mode_disable(USART0);                         //禁止LIN
    usart_smartcard_mode_disable(USART0);                   //禁止SD卡
 
    /* enable USART0 half duplex mode*/
    usart_halfduplex_enable(USART0);
    
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);    //使能发送
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);      //使能接收

    /* enable USART */
    usart_enable(USART0);
    
        /* USART0中断初始化*/
    nvic_priority_group_set(NVIC_PRIGROUP_PRE2_SUB2);   //设置分组方式
    nvic_irq_enable(USART0_IRQn, 2, 2);                 //中断优先级、子优先级
    usart_interrupt_enable(USART0, USART_INT_IDLE);     //使能空闲中断
    usart_interrupt_enable(USART0, USART_INT_RBNE);     //使能接收器非空中断
    
    /* USART0 transmit and receive*/
//    usart_data_receive(USART0);
    

  
//           for(;i<Length;i++)
//        {
//            while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
//            usart_data_transmit(USART0,buff[i]);
//            Delay(0xff);
//        }
}


void USART0_StopReceive(void)
{
        /*停止接收行为*/
    usart_interrupt_disable(USART0, USART_INT_IDLE);        //禁止空闲中断
    usart_interrupt_disable(USART0, USART_INT_RBNE);        //禁止接收器非空中断
    usart_receive_config(USART0, USART_RECEIVE_DISABLE);    //停止接收
}

void USART0_RestoreReceive(void)
{
        /*开启接收行为*/
    usart_interrupt_enable(USART0, USART_INT_IDLE);        //开启空闲中断
    usart_interrupt_enable(USART0, USART_INT_RBNE);        //开启接收器非空中断
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);    //开启接收
    usart_transmit_config(USART0, USART_TRANSMIT_DISABLE); //关闭发送
}

void usart0_data_send(uint8_t* Buff, uint16_t Length)
{
     u16 i=0;   
     u16 size;
    size = Length;
//     while(size)
//     {
//       while(RESET == usart_flag_get(USART0, USART_FLAG_RBNE));
//       usart_data_transmit(USART0,transmitter_buffer0[i++]);
//       size--;
//    }
         for(;i<=size;i++)
        {
            usart_data_transmit(USART0,Buff[i]);
            while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
            
//            Delay(0xf);
        }
        
       
        
}

void usart0_data_receive(void)
{
//     while(transfersize0--)
//     {
        while(RESET == usart_flag_get(USART0, USART_FLAG_RBNE));
        /* store the received byte in the receiver_buffer1 */
        receiver_buffer0[rxcount0++] = usart_data_receive(USART0);
//     }
}



 void USART0_IRQHandler(void)
{
    /*接收器非空中断*/
    if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_RBNE))
    {
        receiver_buffer0[rxcount0++] = usart_data_receive(USART0);
        usart_interrupt_flag_clear(USART0, USART_INT_FLAG_RBNE);                        //清接收非空中断标志位
        
        /*读取数据*/
//        if(USART_RX_STA < USART_REC_LEN)
//        {
//            USART0_BuffCtrl.RxBuff[USART0_BuffCtrl.RxPos] = usart_data_receive(USART0); //正常接收
//            USART0_BuffCtrl.RxPos++;
//        }
//        else
//        {
//            USART0_BuffCtrl.RxBuff[USART_BuffSize-1] = usart_data_receive(USART0);      //溢出接收
//        }
    }
    
	/*IDLE线检测中断*/
	else if(RESET != usart_interrupt_flag_get(USART0, USART_INT_FLAG_IDLE))
	{
        usart_data_receive(USART0);
        usart_interrupt_flag_clear(USART0, USART_INT_FLAG_IDLE);    //清理空闲中断标志位
//        LED_Open(LEDColor_Blue);                                    //蓝灯亮说明进入IDLE中断了
        SmartAudio_VTX_VerifyRx(receiver_buffer0,rxcount0);
        Delay(0xff);
        if( SmartAudio_VTX_VerifyRx(receiver_buffer0,rxcount0) == 1)
        {
            SmartAudio_VTX_PckTx(transmitter_buffer0);
            length = SmartAudio.length;
        }
        
        
        if(rxcount0 > 0)
        {
            USART0_StopReceive();           //停止接收
            
            set_flag = 1;
//            USART0_BuffCtrl.FlagRC = 1;     //接收完成的标志置1
//            LED_Open(LEDColor_Red);         //红灯亮说明收到数据了
            rxcount0 = 0;
        }
	}
}






