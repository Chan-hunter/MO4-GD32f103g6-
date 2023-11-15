#ifndef __FILTER_H
#define __FILTER_H	 

#include "gd32f1x0.h"


float LimitFilter(float input,float MAX_VALUE,float MIN_VALUE,float THRESHOLD);
//float filter(u8 ch);
float filter(float input);
int Constrain(int input,int MAX_VALUE,int MIN_VALUE);

#endif
