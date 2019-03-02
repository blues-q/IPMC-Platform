#ifndef __ALGORITHM_H
#define __ALGORITHM_H

#include "includes.h"

typedef struct PID_s{
    double SetPoint;
    double KP;//Pϵ��
    double KI;//Iϵ��
    double KD;//Dϵ��
    double LastErr1,LastErr2,SumErr,dErr,Err;//err[k-1],err[k-2],���֣�΢�֣�ƫ��

    double output;
}PID_t;

typedef struct Bang_s{
    double SetPoint;
    double Bind;//����
    double output;
}Bang_t;

extern INT32S   RefV[4];
extern PID_t    algPID;
extern Bang_t   algBang;

void Carlib(void);
void myftoa(double data,char str[]);
bool BangBangController(double SetPoint,double Bind);
double PIDController(double SetPoint,double Bind);


#endif
