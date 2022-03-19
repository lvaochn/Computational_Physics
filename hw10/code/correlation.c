#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi  3.141592653589793
#define Total 10000              //总的时间步数
#define D  0.05  
#define N   10000 

//用Schrage方法产生azmodm
int schrage(int a, int m, int z)
{
    int q, r, temp1, temp2;
    q = m / a;
    r = m % a;
    temp1 = z % q;
    temp2 = z / q;
    int t;
    t = a * temp1 - r * temp2;
    if (t < 0)
    {
        t = t + m;
    }
    return t;
}

int main()
{
    int a = 16807, b = 0, m = 2147483647; //输入相应参数
    int I = 1;                            //种子的初值  
    double A = 0.5;                       //正弦外场的影响因子A
    double v0=0.5;                        //初速度
    double omega = pi/2;                  //正弦电场的频率
    double tau = 0.00001;                   //时间常数tau                                           
    double *vx;                         //记录每一步的速度
    double *C;                          //自相关函数的值
    vx = (double *)malloc(Total* sizeof(double));
    C = (double *)malloc(Total* sizeof(double));
    FILE *result = NULL;
    result=fopen("correlation.txt","w+");
    C[0]=v0*v0;
    for(int i = 1;i<Total;i++)
    {
        vx[i] = -(1.0/(omega*omega)+tau*tau)*(omega*cos(omega*i)-1.0/omega*tau*sin(omega*i))+0.5*exp(-i*tau);
        C[i]=vx[i]*v0/i;
        fprintf(result,"%d\t%f\n",i,C[i]);
    }
    free(vx);
    free(C);
    fclose(result);
    return 0;
}