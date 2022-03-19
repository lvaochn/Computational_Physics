#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    int N = 100000;                        //N为产生随机数的总数
    int I = 1;                            //种子的初值定为1
    int i = 0;
    FILE *data = NULL;
    double *x;
    x = (double *)malloc(N * sizeof(double)); //指针x用于存储产生的随机数

    for (i = 0; i < N; i++)
    {
        I = schrage(a, m, I);
        x[i] = (double)I / m; //产生随机数
    }

    //将数据写入文本文档
    char str[50];
    sprintf(str, "RNG16807(N=%d).txt", N);
    data = fopen(str, "w+");
    for (int i = 0; i < N; i++)
    {
        fprintf(data, "%f\t", x[i]);
        if (i % 2 == 1)
            fprintf(data, "\n");
    }
    fclose(data);

    //下面计算x的k阶矩,为方便起见，我们只取k=1,2,3,4
    double sum = 0;
    double moment[4];//数组moment用来存储下面计算出的x的各阶矩
    for(int k=1;k<5;k++)
    {
        sum = 0;
        for(i=0;i<N;i++)
        {
            sum = sum + pow(x[i],k);
        }
        moment[k-1]=sum/N;
        printf("随机数x的%d阶矩为%f\n",k,moment[k-1]);//打印计算结果
    }

    return 0;
}