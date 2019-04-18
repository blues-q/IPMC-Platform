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

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Ҫ�����ڲ�FLASH����ʼ��ַ */
#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_8   
/* Ҫ�����ڲ�FLASH�Ľ�����ַ */
#define FLASH_USER_END_ADDR     ADDR_FLASH_SECTOR_12  
//��ȡ��ַ�������� 
static uint32_t GetSector(uint32_t Address);

///**
//  * @brief  InternalFlash_Test,���ڲ�FLASH���ж�д����
//  * @param  None
//  * @retval None
//  */
//int InternalFlash_Test(void)
//{
//    /*׼��д��Ĳ�������*/
//    #define DATA_32                 ((uint32_t)0x00000000)
//	/*Ҫ��������ʼ����(����)����������(������)����8-12����ʾ����8��9��10��11����*/
//	uint32_t uwStartSector = 0;
//	uint32_t uwEndSector = 0;
//	
//	uint32_t uwAddress = 0;
//	uint32_t uwSectorCounter = 0;

//	__IO uint32_t uwData32 = 0;
//	__IO uint32_t uwMemoryProgramStatus = 0;
//	
//  /* FLASH ���� ********************************/
//  /* ʹ�ܷ���FLASH���ƼĴ��� */
//  HAL_FLASH_Unlock();
//    
//  /* �����û����� (�û�����ָ������û��ʹ�õĿռ䣬�����Զ���)**/
//  /* �������FLASH�ı�־λ */  
//  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
//                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 
//    

//	uwStartSector = GetSector(FLASH_USER_START_ADDR);
//	uwEndSector = GetSector(FLASH_USER_END_ADDR);

//  /* ��ʼ�������� */
//  uwSectorCounter = uwStartSector;
//  while (uwSectorCounter <= uwEndSector) 
//  {
//    /* VoltageRange_3 �ԡ��֡��Ĵ�С���в��� */ 
//      
//    FLASH_Erase_Sector(uwSectorCounter,FLASH_VOLTAGE_RANGE_3);
//    /* ������ָ����һ������ ������F4������������������δ����*/
//    if (uwSectorCounter == FLASH_SECTOR_11)
//    {
//      uwSectorCounter += 40;
//    } 
//    else 
//    {
//      uwSectorCounter += 8;
//    }
//  }

//  /* �ԡ��֡��Ĵ�СΪ��λд������ ********************************/
//  uwAddress = FLASH_USER_START_ADDR;

//  while (uwAddress < FLASH_USER_END_ADDR)
//  {
//      
//    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,uwAddress,DATA_32) == HAL_OK)
//    {
//      uwAddress = uwAddress + 4;
//    }
//    else
//    { 
//      /*д��������أ�ʵ��Ӧ���пɼ��봦�� */
//			return -1;
//    }
//  }
//	

//  /* ��FLASH��������ֹ���ݱ��۸�*/
//  HAL_FLASH_Lock(); 


//  /* ��FLASH�ж�ȡ�����ݽ���У��***************************************/
//  /*  MemoryProgramStatus = 0: д���������ȷ
//      MemoryProgramStatus != 0: д������ݴ�����ֵΪ����ĸ��� */
//  uwAddress = FLASH_USER_START_ADDR;
//  uwMemoryProgramStatus = 0;
//  
//  while (uwAddress < FLASH_USER_END_ADDR)
//  {
//    uwData32 = *(__IO uint32_t*)uwAddress;

//    if (uwData32 != DATA_32)
//    {
//      uwMemoryProgramStatus++;  
//    }

//    uwAddress = uwAddress + 4;
//  }  
//  /* ����У�鲻��ȷ */
//  if(uwMemoryProgramStatus)
//  {    
//		return -1;
//  }
//  else /*����У����ȷ*/
//  { 
//		return 0;   
//  }
//}

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


