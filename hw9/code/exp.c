#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 2         //随机变量个数
#define K 100000    //抽样总次数

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
    double mu = 1.0,sigma = 1.0;          //定义期望和方差
    double *rdm;                           //用于产生N*K个随机数
    double *x;                             //x是我们最终得到的标准化和
    rdm = (double *)malloc(N* K * sizeof(double));
    x = (double *)malloc(K * sizeof(double));   
    FILE *Data = NULL;
    Data = fopen("exp_data.txt", "w+");
    for (int j = 0; j < N*K; j++)
    {
        I = schrage(a, m, I);
        rdm[j] = (double)I / m; //产生随机数
    }
    for(int i = 0; i<K; i++)
    {
        double sum = 0;
        for(int j = 0; j<N; j++)
        {
            sum = sum - log(rdm[N*i+j]);    //sum=X_1+X_2+...+X_N
        }
        x[i]=((double)sum/N-mu)/sigma*sqrt(N);
        fprintf(Data,"%f\n",x[i]);
    }
    fclose(Data);
    free(x);
    free(rdm);
    return 0;
}