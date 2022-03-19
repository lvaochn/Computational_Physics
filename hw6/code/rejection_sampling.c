#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 1000000
#define pi 3.141592653589793

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

//定义Gauss函数p(x)
double p(double x)
{
    double temp;
    temp = 1.0/sqrt(2*pi)*exp(-x*x/2.0);
    return temp;
}

//定义比较函数F(x)
double F(double x)
{
    double temp;
    temp = 1.0/sqrt(pi)*1.0/(1+(double)x*x*x*x*1.0/16);
    return temp;
}

//定义累积函数G(x)
double G(double x)
{
    double temp;
    temp = 0.5*(2*atan(1+x/sqrt(2))-2*atan(1-x/sqrt(2))+log((x*x+2*sqrt(2)*x+4)/(x*x-2*sqrt(2)*x+4)))+pi;
    return temp;
}

//二分法解方程xi_1 = G(xi_x)
double find_root(double x)
{
    double x_left =-10.0 ;      //初始区间左端点
    double x_right = 10.0;     //初始区间右端点
    double error = 1E-5;   //定义求解方程的误差限
    double s = 0;          //方程的根
    if( x>6.27565) return 10;
    else if( x<0.009733731) return -10;
    else
    {
        while( fabs(G((x_left+x_right)/2)-x)>=error )
        {
            if((G((x_left+x_right)/2.0)-x)>0)
            {
                x_right = (x_left+x_right)/2.0;
            }
            else
            {
                x_left = (x_left+x_right)/2.0;
            }  
        }
        s = (x_left+x_right)/2.0;
        return s;
    }
}

int main()
{
    int a = 16807, b = 0, m = 2147483647; //输入相应参数
    int I = 1;                            //种子的初值
    double *rdm;                           //用于产生2N个随机数
    double *xi_1,*xi_2;                   //两个个[0,1]随机数序列
    double *x,*y;                         //需要舍选的坐标点序列
    int EffcientCounts = 0;               //计数变量，计算效率
    rdm = (double *)malloc(2* N * sizeof(double));
    xi_1 = (double *)malloc(N * sizeof(double));
    xi_2 = (double *)malloc(N * sizeof(double));
    x = (double *)malloc(N * sizeof(double));
    y = (double *)malloc(N * sizeof(double));
    FILE *Data = NULL;                   
    
    //产生随机数
    for (int j = 0; j < 2*N; j++)
    {
        I = schrage(a, m, I);
        rdm[j] = (double)I / m;
    }
    for(int j = 0;j<N;j++)
    {
        xi_1[j]=rdm[2*j];
        xi_2[j]=rdm[2*j+1];
        xi_1[j]=6.276*xi_1[j];//将区间[0,1]变为[0,6.276]
    }
    
    //产生舍选所需的坐标点
    for(int j = 0;j<N;j++)
    {
        x[j] = find_root(xi_1[j]);
        y[j] = F(x[j])*xi_2[j];
    }

    //舍选抽样
    Data = fopen("rejection_sampling_data.txt","w+");
    for(int i = 0;i<N;i++)
    {
        if(y[i]<p(x[i]))
        {
            fprintf(Data,"%f\n",x[i]);
            EffcientCounts++;
        }
    }
    printf("The efficiency of rejection sampling is %f\n",(double)EffcientCounts/N);
    fclose(Data);
    free(x);
    free(y);
    free(xi_1);
    free(xi_2);
    free(rdm);
    return 0;
}
