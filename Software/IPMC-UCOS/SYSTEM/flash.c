/**
  ******************************************************************************
  * @file    bsp_internalFlash.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   �ڲ�FLASH��д���Է���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:����  STM32 F429 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "flash.h"   

/* Ҫ�����ڲ�FLASH����ʼ��ַ */
#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_8   
/* Ҫ�����ڲ�FLASH�Ľ�����ַ */
#define FLASH_USER_END_ADDR     ADDR_FLASH_SECTOR_12  
//��ȡ��ַ�������� 
static uint32_t GetSector(uint32_t Address);


/**
  * @brief  ��������ĵ�ַ���������ڵ�sector
  *         ���磺
            uwStartSector = GetSector(FLASH_USER_START_ADDR);
            uwEndSector = GetSector(FLASH_USER_END_ADDR);	
  * @param  Address����ַ
  * @retval ��ַ���ڵ�sector
  * @note F42xϵ��оƬ����������������δ����
  */
static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_SECTOR_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_SECTOR_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_SECTOR_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_SECTOR_10;  
  }
  
  return sector;
}

//��ָ����ַд��һ���֣�4Byte��
//������ȷ����ַ��4�ֽڶ���
HAL_StatusTypeDef WriteOneWord(uint32_t uwAddress,uint32_t* data)
{
    HAL_StatusTypeDef status=HAL_ERROR;
    HAL_FLASH_Unlock();
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                           FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,uwAddress,(uint64_t)(&data)) == HAL_OK)
        status = HAL_OK;
    else
        status = HAL_ERROR;
    HAL_FLASH_Lock();
    
    return status;
}

//������ȷ������ĵ�ַ��4�ֽڶ���ģ�Ҳ���ǿ��Ա�4����
uint32_t ReadOneWord(uint32_t uwAddress)
{
    return *(__IO uint32_t*)uwAddress;
}

/**
  *@brief  ������ַ���ڵ�����
  *@param  FLASH_USER_START_ADDR <= addr <= FLASH_USER_END_ADDR
  */
void EraseOneSector(uint32_t addr)
{
    uint32_t sector;
    
    sector = GetSector(addr);

    HAL_FLASH_Unlock();
    
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                           FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
    
    FLASH_Erase_Sector(sector,FLASH_VOLTAGE_RANGE_3);
    
    HAL_FLASH_Lock();
}


