#ifndef __DMA_H
#define __DMA_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F429������
//DMA��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

extern DMA_HandleTypeDef  UART1TxDMA_Handler;      //DMA���

void MYDMA_Config(DMA_Stream_TypeDef *DMA_Streamx,u32 chx);
void MYDMA_USART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
#endif