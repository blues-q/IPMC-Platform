#include "key.h"

void KeyInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStruct.Pin = KEY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY_GPIO_Port, &GPIO_InitStruct);

}

//������ʽ�������
void TimerCheckKey(void)
{
//  static uint8_t cnt=0;
//  if( cnt<CYCLEINDEX && HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==GPIO_PIN_RESET )//press down
//    cnt++;
//  else if( cnt==CYCLEINDEX && HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==GPIO_PIN_SET )//release
//  {
//    BoardID++;
//    cnt=0;
//    if(BoardID>MAXBoardID)BoardID=0;
//  }
//  else
//    return;
    
  static uint8_t cnt=0;
  if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==GPIO_PIN_RESET )//press down
    cnt++;
  
  if(cnt>=255||HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==GPIO_PIN_SET)//release
  {
    if(cnt>200)
    {
//        UpgradeSystem();
        //δ��ɵĹ���
    }
    else if(cnt>2)
    {
        BoardID++;
        cnt=0;
        if(BoardID>MAXBoardID)BoardID=0;
    }
    cnt=0;
  }
}
