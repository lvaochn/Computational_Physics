#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int fac(int n)
{
    int temp=1;
    if(n>0)
    {
        for(int i = 1;i<=n;i++)
        {
            temp = i*temp;
        }

    }
    return temp;
}

//定义Poisson分布函数
double p(int k)
{
    double temp;
    temp = 1.0/fac(k)*exp(-1);
    return temp;
}

//定义累积函数P(x)
double P(int k)
{
    double temp=0;
    for (int i = 0; i <=k; i++)
    {
        temp = temp+p(i);
    }
    return temp;
}

//定义Poisson分布的直接抽样方法
int Poisson_sample(double x)
{
    int temp;
    if(0<=x&&x<P(0)) 
    {
        temp = 0;
    }
    for(int i=0;i<10;i++)
    {
        if(P(i)<=x&&x<P(i+1))
            temp = i+1;
    }
    if(x>P(10)) temp = 11;
    return temp;
}

int main()
{
    double x=0.75;
    int y,z;
    y=Poisson_sample(x);
    z=fac(3);
    printf("z=%d\n",z);
    return 0;
}