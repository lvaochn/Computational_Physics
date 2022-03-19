#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10000
#define TotalNum 114 //题中所给数据点的个数

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
    int sum = 0;                          //计频数之和的变量
    double *x;                            //随机数序列
    x = (double *)malloc(N * sizeof(double));
    double p[TotalNum];   //每个区间的概率
    double P[TotalNum]; //累积区间概率之和
    int energy[TotalNum],counts[TotalNum]; //能量和相应频数的值
    FILE *Data = NULL;    //题中原始文件指针
    FILE *Result = NULL;  //抽样结果文件指针

    //从题中所给文本中读入数据
    Data = fopen("data.txt", "r");
    for (int i = 0; i < TotalNum; i++)
    {
        fscanf(Data, "%d", &energy[i]);
        fscanf(Data, "%d", &counts[i]);
        sum = sum + counts[i];
    }
    fclose(Data);

    //直接抽样
    for (int j = 0; j < N; j++)
    {
        I = schrage(a, m, I);
        x[j] = (double)I / m; //产生随机数
    }
    P[0] = 0; 
    for (int i = 1; i < TotalNum; i++) //计算p和P
    {
        p[i] = (double)counts[i] / sum;
        P[i] = p[i] + P[i - 1];
    }
    Result = fopen("direct_sample.txt", "w+");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < TotalNum; j++)
        {
            if (x[i] < P[j])
            {
                fprintf(Result, "%d\n", energy[j]);
                break;
            }
        }
    }
    fclose(Result);
    free(x);
    return 0;
}
