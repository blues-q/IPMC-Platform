/*
************************************************************************************************
主要的包含文件

文 件: INCLUDES.C ucos包含文件
作 者: Jean J. Labrosse
************************************************************************************************
*/

#ifndef __INCLUDES_H__
#define __INCLUDES_H__
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>

#include "ucos_ii.h"
#include "os_cpu.h"
#include "os_cfg.h"

#include <stm32f4xx.h>	    

#include "delay.h"
#include "myiic.h"
#include "usart.h"
#include "led.h"
#include "task.h"
#include "wave.h"
#include "AD5722.h"
#include "ADS1115.h"
#include "queue.h"
#include "key.h"
#include "protocol.h"
#include "can.h"

#define MAXBoardID 0x01

extern OS_EVENT *CAN_Q;
extern OS_EVENT *UART1_Q;
extern void* CAN_QTbl[64];
extern void* UART1_QTbl[64];
extern uint8_t BoardID;

#endif































