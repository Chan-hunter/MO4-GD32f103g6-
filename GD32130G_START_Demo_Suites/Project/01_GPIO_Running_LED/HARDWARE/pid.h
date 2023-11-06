#ifndef __PID_H
#define __PID_H


// PID参数
//typedef struct
//{   
    float Kp ; // 比例增益
    float Ki ; // 积分增益
    float Kd ; // 微分增益                                                                                                     /*!< SPI prescale factor */
//}pid_struct;   

// 目标值
float setpoint;

// 当前值
float current_value;

// 积分项和微分项的累积误差
float integral;
float prev_error;

float pid_control(float current, float setpoint) ;
		 
#endif

