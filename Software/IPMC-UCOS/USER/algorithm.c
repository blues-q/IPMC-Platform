#include "algorithm.h"

INT32S RefV[4];

void ADCCarlib(void)
{
    static INT8U i=10;
    int D0=0,D1=0,D2=0;
    delay_ms(100);
    while(i>0)
    {
        D0+=ADS_Buff[0];
        D1+=ADS_Buff[1];
        D2+=ADS_Buff[2];
        delay_ms(20*4*2);//let OS scheduling
        i--;
    }
    RefV[0]=D0/10.0;
    RefV[1]=D1/10.0;
    RefV[2]=D2/10.0;
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
