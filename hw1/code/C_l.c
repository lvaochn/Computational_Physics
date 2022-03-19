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
    int N = 1E7;                          //N为产生随机数的总数
    int I = 1;                            //种子的初值定为1
    int i = 0;
    double *x; //指针x用于存储产生的随机数
    FILE *data2 = NULL;
    int lmax = 300;                           //lmax用于后续产生大量的C(l)
    x = (double *)malloc(N * sizeof(double)); //指针x用于存储产生的随机数
    for (i = 0; i < N; i++)
    {
        I = schrage(a, m, I);
        x[i] = (double)I / m; //产生随机数
    }
    double sum = 0;
    double *moment; //数组moment用来存储下面计算出的x的各阶矩
    moment = (double *)malloc(4 * sizeof(double));

    //计算x的k阶矩
    for (int k = 1; k < 5; k++)
    {
        sum = 0;
        for (i = 0; i < N; i++)
        {
            sum = sum + pow(x[i], k);
        }
        moment[k - 1] = sum / N;
    }

    //下面计算C(l)
    int l = l;
    double *C;
    C = (double *)malloc(lmax * sizeof(double));
    for (l = 1; l < lmax; l++)
    {
        double sum1 = 0;
        for (int i = 0; i < N; i++)
        {
            sum1 = sum1 + x[i] * x[i + l]; //计算x_i*x_i+l
        }
        C[l] = (sum1 / N - moment[0] * moment[0]) / (moment[1] - moment[0] * moment[0]);
    }

    //将C(l)写入文本文档,用于绘图观察
    char str[50];
    sprintf(str, "C(l)(N=%d).txt", N);
    data2 = fopen(str, "w+");
    for (int i = 1; i < lmax; i++)
    {
        fprintf(data2, "%f\n", C[i]);
    }
    fclose(data2);
    
    return 0;
}