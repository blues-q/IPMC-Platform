#ifndef _USART_H
#define _USART_H
#include "sys.h"
#include "stdio.h"	
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.csom
//�޸�����:2015/6/23
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.0�޸�˵�� 
////////////////////////////////////////////////////////////////////////////////// 	

#define RS232_TX_Pin        GPIO_PIN_2
#define RS232_TX_GPIO_Port  GPIOA
#define RX232_RX_Pin        GPIO_PIN_3
#define RX232_RX_GPIO_Port  GPIOA

extern UART_HandleTypeDef UART1_Handler; //UART���
extern UART_HandleTypeDef UART2_Handler; //UART���
extern UART_HandleTypeDef UART3_Handler; //UART���

void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
#endif
