#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x, double y, double z, double u, double v) //定义f(x)的函数形式
{
    return 5. - x * x + y * y - z * z + u * u * u - v * v * v;
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
    int a = 16807, b = 0, m = 2147483647;                          //输入16807产生器相应参数
    int I = 1;                                                     //种子的初值
    double mc_integral = 0;                                        //用MC方法计算的积分值
    double IntValue = 5.32911646773318;                            //积分准确值
    double *x;                                                     // x为函数自变量
    int N = 1;                                                     //随机点数的初值
    double lim[5] = {7 / 10.0, 4 / 7.0, 9 / 10.0, 2.0, 13 / 11.0}; //定义积分上限
    double sum = 0;
    FILE *integral = NULL;
    integral = fopen("integral2.txt", "w+");
    fprintf(integral, "%15s%25s%30s%30s\n", "N", "Integral", "Error", "1/sqrt(N)"); //文件中写入N的值，积分值以及误差
    for (int i = 1; i < 8; i++)
    {
        N = 10 * N;
        double sum = 0;
        double *x; // x为函数自变量
        x = (double *)malloc(5 * N * sizeof(double));
        for (int j = 0; j < 5 * N; j++)
        {
            I = schrage(a, m, I);
            x[j] = (double)I / m; //产生随机数
        }
        for (int k = 0; k < N; k++)
        {
            sum = sum + f(x[5 * k] * lim[0], x[5 * k + 1] * lim[1], x[5 * k + 2] * lim[2], x[5 * k + 3] * lim[3], x[5 * k + 4] * lim[4]);
        }
        sum = sum * lim[0] * lim[1] * lim[2] * lim[3] * lim[4];
        mc_integral = (double)sum / N;
        fprintf(integral, "%15d\t%.8lf\t%.8le\t%.8le\n", N, mc_integral, fabs(mc_integral - IntValue), (double)1 / sqrt(N));
        free(x);
    }
    fclose(integral);
    free(x);
    return 0;
}
