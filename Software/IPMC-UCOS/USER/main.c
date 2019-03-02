#include "sys.h"
#include "includes.h"
/************************************************
 ALIENTEK ������STM32F429������ʵ��59
 UCOSIIʵ��1-�������-HAL�⺯����
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com  
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
static void MX_NVIC_Init(void);
static void BSP_Init(void);

OS_EVENT * CAN_Q;
OS_EVENT * UART1_Q;
OS_EVENT * COM2Msg;
void*   CAN_QTbl[64];
void* UART1_QTbl[64];

float TEMP=0,HUMI=0;
/*
ErrCode Bit Description
Reference @ErrCodeBitDefine
*/
INT16U ErrCode=0;
INT16U BoardID=0x00;
bool DBG_Flag=false;
bool CTR_Flag=false;
bool CARLIB_OK_Flag=false;
int main(void)
{
	HAL_Init();                     //��ʼ��HAL��   
	Stm32_Clock_Init(336,25,2,8);   //����ʱ��,180Mhz
	delay_init(168);                //��ʼ����ʱ����
	BSP_Init();
	
	OSInit();                       //UCOS��ʼ��
	
    if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==GPIO_PIN_RESET )//����DEBUGģʽ�����ԭʼ���ݡ�
        DBG_Flag=true;
    
	UART1_Q=OSQCreate(&UART1_QTbl[0],64);
	CAN_Q  =OSQCreate(&CAN_QTbl[0],64);
	COM2Msg =OSMboxCreate((void *)0);

	OSTaskCreateExt((void(*)(void*) )start_task,                //������
									(void*          )0,                         //���ݸ��������Ĳ���
									(OS_STK*        )&START_TASK_STK[START_STK_SIZE-1],//�����ջջ��
									(INT8U          )START_TASK_PRIO,           //�������ȼ�
									(INT16U         )START_TASK_PRIO,           //����ID����������Ϊ�����ȼ�һ��
									(OS_STK*        )&START_TASK_STK[0],        //�����ջջ��
									(INT32U         )START_STK_SIZE,            //�����ջ��С
									(void*          )0,                         //�û�����Ĵ洢��
									(INT16U         )OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR|OS_TASK_OPT_SAVE_FP);//����ѡ��,Ϊ�˱���������������񶼱��渡��Ĵ�����ֵ
	OSStart(); //��ʼ����
}

static void BSP_Init(void)
{
	MX_NVIC_Init();
	
    uart1_init(460800);//USART
    uart2_init(115200);//RS232
    #ifdef ROBOT_ARM
        IPMC_Init();
    #else
        uart3_init(115200);//RS485
    #endif
    if(DBG_Flag==false)
        MYDMA_Config(DMA2_Stream7,DMA_CHANNEL_4);//��ʼ��DMA
    LED_Init();                     //��ʼ��LED
    KeyInit();
    IIC_Init();
    CAN1_Mode_Init(CAN_SJW_1TQ,CAN_BS2_6TQ,CAN_BS1_8TQ,6,CAN_MODE_NORMAL); //CAN��ʼ��,������500Kbps      
    AD5722_Init();
    Channel_Group_Init();	
    SHT2x_Init();
    LaserCMDToZero();
    Queue_Init(&UART_RXqueue);
    Queue_Init(&CAN_RXqueue);
}

static void MX_NVIC_Init(void)
{
  /* TIM6_DAC_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);
  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USART2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART2_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* CAN1_RX0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
}

