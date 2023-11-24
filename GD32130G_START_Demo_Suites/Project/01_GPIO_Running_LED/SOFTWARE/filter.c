#include "filter.h"
#include "math.h"
#include "adc.h"

//#define MAX_VALUE 3.6
//#define MIN_VALUE 0
//#define THRESHOLD 0.1


float LimitFilter(float input,float MAX_VALUE,float MIN_VALUE,float THRESHOLD) //限幅滤波法
{ 
    static char flag = 1;
    static float previous_output = 0; // 上一次的输出值
    float output = input; // 当前的输出值
    
    // 限制输出值在一定范围内
    if (output > MAX_VALUE) 
    {
       output = MAX_VALUE;
    } 
    else if (output < MIN_VALUE) 
    {
       output = MIN_VALUE;
    }
    if(flag == 1)
    {
            // 消除信号抖动
        if (output - previous_output > THRESHOLD)
        {
            output = previous_output + THRESHOLD;
        } 
        else if (previous_output - output > THRESHOLD) 
        {
            output = previous_output - THRESHOLD;
        }
        
        if (fabs(output - previous_output) < THRESHOLD/20) flag=0;
         
    }
    
    else 
    {
         // 消除信号抖动
        if (output - previous_output > THRESHOLD)
        {
            output = previous_output ;//+ THRESHOLD;
        } 
        else if (previous_output - output > THRESHOLD) 
        {
            output = previous_output ;//- THRESHOLD;
        }
    }

     
    previous_output = output; // 保存当前输出值
    return output;
}


//float  A=10;
//#define N 30
//float value=0,new_value;
//float filter(float input)
//{
// static int count=0;
// new_value=input;
// while(value!=new_value)
// {
//  if(fabs(value-new_value)<A)
//  {
//      A = 1;
//	  count++;
//	  if(count>=N) return new_value;
//	  value=new_value;
//  }
// return value;
// }
//}

#define N 12
float filter(float input)
{
 int sum = 0;
 for(int count = 0;count<N;count++)
 {
 	sum +=input;// LimitFilter((get_adc_ch(ch)),4096,0,200);
 } 
 return (float)(sum/N);
}




int Constrain(int input,int MAX_VALUE,int MIN_VALUE) //限制最大最小值
{
    float output = input; // 当前的输出值
    
    // 限制输出值在一定范围内
    if (output > MAX_VALUE) 
    {
       output = MAX_VALUE;
    } 
    else if (output < MIN_VALUE) 
    {
       output = MIN_VALUE;
    }
    return output;
}



