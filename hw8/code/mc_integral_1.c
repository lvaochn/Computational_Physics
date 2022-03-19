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
    int a = 16807, b = 0, m = 2147483647; //输入16807产生器相应参数
    int I = 1;                            //种子的初值
    double mc_integral = 0;               //用MC方法计算的积分值
    double IntValue = 11.3179614888953;   //积分准确值
    double *x;                            //x为函数自变量
    int N = 1;                            //随机点数的初值
    double sum = 0;
    FILE *integral = NULL;
    integral = fopen("integral1.txt", "w+");
    fprintf(integral, "%15s%25s%30s%30s\n", "N", "Integral", "Error", "1/sqrt(N)"); //文件中写入N的值，积分值以及误差
    for (int i = 1; i < 9; i++)
    {
        N = 10 * N;
        double sum = 0;
        double *x; //x为函数自变量
        x = (double *)malloc(N * sizeof(double));
        for (int j = 0; j < N; j++)
        {
            I = schrage(a, m, I);
            x[j] = (double)I / m; //产生随机数
        }
        for (int k = 0; k < N; k++)
        {
            x[k] = 5 * x[k];
            sum = sum + sqrt(x[k] + 2 * sqrt(x[k]));
        }
        mc_integral = (double)5 * sum / N;
        fprintf(integral, "%15d\t%.8lf\t%.8le\t%.8le\n", N, mc_integral, fabs(mc_integral - IntValue), (double)1 / sqrt(N));
        free(x);
    }
    fclose(integral);
    free(x);
    return 0;
}
