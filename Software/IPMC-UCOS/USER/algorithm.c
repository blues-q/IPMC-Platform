#include "algorithm.h"

INT32S RefV[4];
PID_t   algPID;
Bang_t  algBang;

void Carlib(void)
{
    OS_CPU_SR cpu_sr=0;
    INT8U i=20;
    int D0=0,D1=0,D2=0;
    CARLIB_OK_Flag=false;
    OS_ENTER_CRITICAL();
    OSTaskSuspend(LED_TASK_PRIO);
    OSTaskSuspend(DBG_TASK_PRIO);
    OS_EXIT_CRITICAL();
    LED0=0;
    while(i>0)
    {
        delay_ms(20*4*2);//let OS scheduling to acquire data;
        D0+=ADS_Buff[0];
        D1+=ADS_Buff[1];
        D2+=ADS_Buff[2];
        i--;
    }
    RefV[0]=D0/20.0;
    RefV[1]=D1/20.0;
    RefV[2]=D2/20.0;
    LaserCMDToZero();
    LED0=1;
    
    OSTaskResume(LED_TASK_PRIO);
    OSTaskResume(DBG_TASK_PRIO);
    CARLIB_OK_Flag=true;
}

//4λ���ȸ�����תASCII
void myftoa(double data,char str[])
{
	int Int, Dec;
	char strHead[9], strTail[5], pt[] = ".";
	Int = (int)data;
    
	Dec = 10000.0*fabs(data - Int);//Ҫע��-1<data<1ʱ�������

	sprintf(strHead, "%03d", Int);//��������ת�ַ���
	sprintf(strTail, "%04d", Dec);//С������ת�ַ���
	strcat(strHead, pt);//�����ַ�����ӵ�
	strcat(strHead, strTail);//�ټ�С���ַ���
    
    memset(str,0,strlen(strHead)); //���str��ַ��strHead���ȵ�����
	
    if (strHead[0]=='0')
        strHead[0] = '+';
    if(data<0)
        strHead[0] = '-'; //-0.8ȡ��Ϊ0����ʧ���ţ�
    
    strcat(str, strHead);
}

//BangBang����
//@param Target:������Ŀ��λ��
//       Bind:�����������ֵ(����)��Ҫ��Ҫ�ĳɰٷֱ���ʽ����
bool BangBangController(double SetPoint,double Bind)
{
    double UpperLim,LowerLim;
    
    if(LaserOffset==Laser_OutOfRange||SetPoint<=Bind)
        return false;
    
    
    LowerLim=SetPoint-Bind/2.0;
    UpperLim=SetPoint+Bind/2.0;
    if(LaserOffset<LowerLim)
    {
        AD5722_Output(3,CH0);
    }else if(LaserOffset>UpperLim)
    {
        AD5722_Output(0,CH0);
    }
    return true;
}

double PIDController(double SetPoint,double Bind)
{
    #define OUT_UPPERLIM  3.5 //����źŵ�������
    #define OUT_LOWERLIM -3.5
    
    static double KP=0.5;//Pϵ��
    static double KI=0.05;//Iϵ��
    static double KD=0.01;//Dϵ��
    static double LastErr1,LastErr2,SumErr,dErr,Err;//err[k-1],err[k-2],���֣�΢�֣�ƫ��
    static double output;
//    static int8_t direction=0;//�����ۺ�bangbang���ƣ�
    
    double UpperLim,LowerLim;//λ�ƵĿ���������
    
    if(LaserOffset==Laser_OutOfRange)
        return 0;
    
    LowerLim=SetPoint-Bind/2.0;
    UpperLim=SetPoint+Bind/2.0;
    
    Err=SetPoint-LaserOffset;
    if(output>OUT_LOWERLIM&&output<OUT_UPPERLIM)SumErr+=Err;//������
//    if(LaserOffset>LowerLim&&LaserOffset<UpperLim)SumErr=0;//�����������ӽ�Ŀ��ʱ�رջ���
    dErr=LastErr1-LastErr2;
    LastErr2=LastErr1;
    LastErr1=Err;
    
    output=KP*Err+KI*SumErr+KD*dErr;
    
    if(output>OUT_UPPERLIM)output=OUT_UPPERLIM;
    if(output<OUT_LOWERLIM)output=OUT_LOWERLIM;
    
    AD5722_Output(output,CH0);
//    printf("Err:%.1f SumErr:%.1f dErr:%.1f LastErr1:%.1f LastErr2:%.1f out:%.1f\r\n",Err,SumErr,dErr,LastErr1,LastErr2,output);
    return output;
}
