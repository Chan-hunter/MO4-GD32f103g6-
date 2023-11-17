#ifndef __SmartAudio_H
#define __SmartAudio_H	 

#include "gd32f130g_start.h"

uint8_t crc8(const uint8_t * ptr, uint8_t len);

		 				    
//unsigned char crc8tab[256] ;

typedef struct 
{
    uint8_t Version;        //版本（见参数预编译）
    uint8_t Power;       //功率（见参数预编译）
    uint8_t Channel;        //频道（范围0-39）
    uint8_t Mode;           //模式（见参数预编译）
    uint16_t Freq;          //频率（5.6G ~ 6.0G）
    uint8_t Cmd;        //主机命令（转化为预编译中的SmartAudio命令）
}SmartAudio_StructTypedef;

#define Get_Settings_cmd  0x03
#define Set_Power_cmd     0x05
#define Set_Channel_cmd   0x07
#define Set_Frequency_cmd 0x09
#define Set_Mode_cmd      0x0B



#endif

