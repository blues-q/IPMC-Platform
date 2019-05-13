#include "sys.h"
#include "includes.h"
/************************************************
 *���ߣ�@inhowe 
************************************************/
static void MX_NVIC_Init(void);
static void BSP_Init(void);

#define VERSION     0x10//�̼��汾

//�û����ñ�����FLASH��ַ
#define USR_CONFIG_ADDR     ((uint32_t)0x08080000)

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

double Current_mA=0,Power_mW=0,Laser_mm=0,Force_mN=0,Energy_mJ=0,dLaser_mm=0;

//DEBUGʱӦ�ر�IWDG������Peripheral-DBG�Ĵ����ﹴѡDBG_IWDEG_STOP
int main(void)
{
	HAL_Init();                     //��ʼ��HAL��   
	Stm32_Clock_Init(336,25,2,8);   //����ʱ��,168Mhz
	delay_init(168);                //��ʼ����ʱ����
	BSP_Init();
	
	OSInit();                       //UCOS��ʼ��
    
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
    uint16_t cnt=0;
    
	MX_NVIC_Init();
	
    uart1_init(460800);//USART
    uart2_init(115200);//RS232
    LED_Init();                     //��ʼ��LED
    KeyInit();

    #ifdef ROBOT_ARM
        IPMC_Init();
    #else
        uart3_init(115200);//RS485
    #endif
    if(DBG_Flag==false)
        MYDMA_Config(DMA2_Stream7,DMA_CHANNEL_4);//��ʼ��DMA

    IIC_Init();
    CAN1_Mode_Init(CAN_SJW_1TQ,CAN_BS2_6TQ,CAN_BS1_8TQ,6,CAN_MODE_NORMAL); //CAN��ʼ��,������500Kbps      
    AD5722_Init();
    Channel_Group_Init();	
    SHT2x_Init();
    LaserCMDToZero();
    Queue_Init(&UART_RXqueue);
    Queue_Init(&CAN_RXqueue);
    
    cnt=0;
    while(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)==GPIO_PIN_RESET )//��������
    {
        delay_ms(100);
        LED0=LED1=LED_ON;
        delay_ms(100);
        LED0=LED1=LED_OFF;
        cnt++;
        if(cnt>=25)break;
    }
    if(cnt>=25)
    {
        UpgradeSystem();
    }
    else if(cnt>=1)//short press
    {
        DBG_Flag=true;
//        IWDG_Init();
    }
    else
    {
        IWDG_Init();
    }
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

void JumpToISP(void)
{
    //ISP�����ַ
    #define ISPAddress 0x1FFF0000 
    
    //������ת����λ���裬�����һЩ���ܵ��������������з���ʼ��DeInit����SysTick��
    //���Ź�һ����ʼ�����ܱ��رգ�������ʹ���˿��Ź������ڵ��øú���ǰ�������ȸ�λϵͳ�����ڳ�ʼ�����Ź�֮ǰ���øú�����
    uint32_t ispJumpAddr;//ISP�������ת��ַ���ȳ������
    uint32_t ispSpValue;//IAP�����SP��ֵ����ջָ��
    void (*Jump_To_ISP)(void);//����һ������ָ��
    
    SysTick->CTRL=0x00;       //�رռ�����
    SysTick->VAL =0X00;       //��ռ�����	
    //__set_PRIMASK(1);

    if (((*(__IO uint32_t*)ISPAddress) & 0x2FFE0000 ) == 0x20000000)
    { 
        ispSpValue  = *(__IO uint32_t*)ISPAddress;
        ispJumpAddr = *(__IO uint32_t*)(ISPAddress+4);


        /* ��ʼ�� Stack Pointer */
        __set_MSP(ispSpValue);

        /* Jump to isp */
        Jump_To_ISP = (void (*)(void))ispJumpAddr;
        Jump_To_ISP();
    }
}

void UpgradeSystem(void)
{
    LED0=LED1=LED_ON;
    printf("\r\nPlease release your COM port, and call the stm32isp.exe.");
    printf("\r\nEntering booloader...");
    JumpToISP();
}
