#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 2         //随机变量个数
#define K 100000    //抽样总次数

double p(double x)
{
    double temp=0;
    if(-1.0<=x&&x<=0)
        temp = x+1;
    else if(0<x&&x<=1)
        temp = 1-x;
    else temp = 0;
    return temp;
}

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
    double mu = 0.0, sigma = sqrt(6.0)/3.0;          //定义期望和方差
    double *rdm;                           //用于产生2*N*K个随机数
    double *x,*xi_1,*xi_2;              
    rdm = (double *)malloc(2*N* K * sizeof(double));
    xi_1 = (double *)malloc(N* K * sizeof(double));
    xi_2 = (double *)malloc(N* K * sizeof(double));
    x = (double *)malloc(N* K * sizeof(double));   
    FILE *Data = NULL;
    Data = fopen("self_px_data_N=2.txt", "w+");
    
    //产生随机数xi_1和xi_2
    for (int j = 0; j < 2*N*K; j++)
    {
        I = schrage(a, m, I);
        rdm[j] = (double)I / m;
    }
    for(int j = 0;j<N*K;j++)
    {
        xi_1[j]=rdm[2*j];
        xi_2[j]=rdm[2*j+1];
        xi_1[j]=2*xi_1[j]-1;
    }
    
    for(int i = 0; i<K; i++)
    {
        double sum = 0;
        for(int j = 0; j<N; j++)
        {
            if(xi_2[N*i+j]<=p(xi_1[N*i+j])) //舍选抽样
            {
            sum = sum + xi_1[N*i+j];    //sum=X_1+X_2+...+X_N
            }
        }
        x[i]=((double)sum/N-mu)/sigma*sqrt(N);
        fprintf(Data,"%f\n",x[i]);
    }
    fclose(Data);
    free(x);
    free(rdm);
    return 0;
}