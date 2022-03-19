#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define pi 3.14159265358979                              
#define N 1000                                 //每个参数lambda的迭代步数

int main()
{
    double x = 0;                             //迭代变量
    double lambda = 0;                        //参数
    double max = 0.870;          
    double min = 0.700;                       //参数lambda的变化范围
    double step = (max - min)/1000;           //参数lambda变化步长
    int M = 100;                              //对于每一个lambda，迭代M步后输出x的值
    FILE *lambda_data = NULL;
    lambda_data = fopen("lambda_0.7~0.87.txt","w+");
    
    for(lambda=min;lambda<=max;lambda=lambda+step)
    {
        x = 0.1;
        for(int i=0;i<N;i++)
        {
            x = lambda*sin(pi*x);
            if(i>M)
            {
                fprintf(lambda_data,"%f\t%f\n",lambda,x);
            }
        }
    }
    return 0;
}