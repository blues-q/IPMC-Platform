#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/11/23
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

//��ʼ��PB1Ϊ���.��ʹ��ʱ��	    
//LED IO��ʼ��
void LED_Init(void)
{
    //GPIOB�ǿ������ϵ�LED
    GPIO_InitTypeDef GPIO_Initure;
//    __HAL_RCC_GPIOB_CLK_ENABLE();         
	__HAL_RCC_GPIOC_CLK_ENABLE();
	
    GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1; 
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  
    GPIO_Initure.Pull=GPIO_PULLUP;          
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     
	
//    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	HAL_GPIO_Init(GPIOC,&GPIO_Initure);
	
//    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_SET);	
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_SET);
}
