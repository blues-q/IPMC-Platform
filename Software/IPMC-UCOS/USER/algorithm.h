#ifndef __ALGORITHM_H
#define __ALGORITHM_H

#include "includes.h"

//λ��mm������mW������mA����mN��λ�Ʊ仯��
typedef enum CtrlObj_s{
    LASER=0,
    POWER,
    CURRENT,
    FORCE,
    dLaser,
}CtrlObj_t;

typedef enum CtrlType_s{
    TYPE_PID=0,
    TYPE_BANG,
    TYPE_SERIAL_PID,
    TYPE_UNKNOWN=0xff
}CtrlType_t;

typedef struct PID_s{
    CtrlObj_t ObjType;//���ض���
    double nowPoint;
    double SetPoint;
    double KP;//Pϵ��
    double KI;//Iϵ��
    double KD;//Dϵ��
    double LastErr1,LastErr2,SumErr,dErr,Err;//err[k-1],err[k-2],���֣�΢�֣�ƫ��
    double Bind;//����
    double getPoint;//�洢���Է��������趨ֵ����ΪsetPoint���ܻ�����㷨��Ҫ�ı䣩
    double output;
}PID_t;

typedef struct Bang_s{
    double SetPoint;
    CtrlObj_t ObjType;
    double Bind;//����
    double HV;//�ߵ�ѹ
    double LV;//�͵�ѹ
    double output;
}Bang_t;

extern INT32S   RefV[4];
extern PID_t    algPID,algOuterPID,algPID_1;
extern Bang_t   algBang;
extern CtrlType_t CtrlType;
extern double setEnergy;

void Carlib(void);
void myftoa(double data,char str[]);

//������
void step1_step2(double getPoint_IN,double nowPoint_IN,double* newSetPoint_OUT,CtrlObj_t ObjType);
u8 UpdateController(PID_t* Ctrl);
bool BangBangController(Bang_t* Ctrl);
double PIDController(PID_t* Ctrl);
void ClearController(void);

//������100Hz���˲���
double WeightedFilter(double input);
double RC_LowPassFilter(double nowInput,double lastValue, double frqc);
double IIR_LowPassFilter2P5Hz_Current(double xk);
double IIR_LowPassFilter2P5Hz_Power(double xk);
#endif
