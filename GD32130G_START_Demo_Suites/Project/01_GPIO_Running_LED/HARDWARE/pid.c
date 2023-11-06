#include <stdio.h>
#include "pid.h"

// PID参数
float Kp = 1.0; // 比例增益
float Ki = 0.1; // 积分增益
float Kd = 0.01; // 微分增益   

// 目标值
float setpoint = 50.0;

// 当前值
float current_value = 0.0;

// 积分项和微分项的累积误差
float integral = 0.0;
float prev_error = 0.0;

// PID控制函数
float pid_control(float current, float setpoint) {
    float derivative;
    float output;

    // 计算误差
    float error = setpoint - current;

    // 计算积分项
    integral += error;

    // 讘算微分项
    derivative = error - prev_error;

    // 计算PID输出
    output = Kp * error + Ki * integral + Kd * derivative;

    // 更新prev_error
    prev_error = error;

    return output;
}

//int test() {
//    for (int i = 0; i < 100; i++) {
//        // 模拟当前值的变化
//        current_value += 1.0;

//        // 使用PID控制器计算控制输出
//        float control_output = pid_control(current_value, setpoint);

//        // 打印控制输出
//        printf("Current: %.2f, Control Output: %.2f\n", current_value, control_output);
//    }

//    return 0;
//}



