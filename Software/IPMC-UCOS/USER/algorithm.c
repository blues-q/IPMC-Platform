#include "algorithm.h"

INT16U RefV[4];

void ADCCarlib(void)
{
    static INT8U i=20;
    int D0,D1,D2;
    while(i>0)
    {
        D0+=ADS_Buff[0];
        D1+=ADS_Buff[1];
        D2+=ADS_Buff[2];
        delay_ms(5*4*2);//let OS scheduling
        i--;
    }
    RefV[0]=D0/20;
    RefV[1]=D1/20;
    RefV[2]=0;
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
