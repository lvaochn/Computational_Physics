#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10000

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

//比较大小的函数
double min(double x,double y)
{
    if(x < y)
        return x;
    else 
        return y;
} 



int main()
{   
    int a = 16807, b = 0, m = 2147483647; //输入16807随机数产生器的相应参数
    int I = 1;                            //种子的初值
    double alpha = 2.0,beta = 1.0;        //定义alpha和beta
    double gamma = 0.1;
    for(gamma = 0.1;gamma<5.0;gamma=gamma+0.05)
    {
    double Integral = 0;                  //待求的积分值
    double *x;                            //x为每一步的取值
    double *R;                            //R为[0,1]上的随机数
    double *x_1;                          //x_1存x'的取值
    double *rdm;
    int n0 = N/10;                        //定义热化长度n0
    double r = 0;                         //r为两步概率之比值
    R = (double*)malloc(N*sizeof(double));
    x = (double*)malloc(N*sizeof(double));
    x_1 = (double*)malloc(N*sizeof(double));
    rdm = (double*)malloc(2*N*sizeof(double));
    x[0]=1;
    FILE *error_data = NULL;
    
    //产生2N个随机数
    for (int j = 0; j < 2*N; j++)
    {
        I = schrage(a, m, I);
        rdm[j] = (double)I / m; 
    }
    for(int i = 0;i<N;i++)
    {
        x_1[i] = rdm[2*i];
        R[i] = rdm[2*i+1];
    }
    //对x_1进行抽样
    for(int i = 0;i<N;i++)
    {
    x_1[i]=-gamma*log(R[i]);
    }
    //计算r,进行选择
    for(int i = 0;i<N-1;i++)
    {
        r=pow(x_1[i]/x[i],alpha-1.0)*exp(-(x_1[i]-x[i])/beta)*exp((x_1[i]-x[i])/gamma);
        if(R[i]<min(1.0,r))
            x[i+1]=x_1[i];
        else
            x[i+1]=x[i];
    }
    //计算积分值
    for(int k=n0;k<N;k++)
    {
        Integral = Integral+(x[k]-alpha*beta)*(x[k]-alpha*beta)/(N-n0);
    }
    
    error_data=fopen("error_data_3.txt","a");
    fprintf(error_data,"%f\t%f\n",gamma,fabs(Integral-alpha*beta*beta));
    }

}