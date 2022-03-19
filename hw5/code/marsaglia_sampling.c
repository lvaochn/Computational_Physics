#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10000
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

int main()
{
    int a = 16807, b = 0, m = 2147483647; //输入相应参数
    int I = 1;                            //种子的初值
    double *rdm;                          //rdm用于产生随机数序列
    double *x, *y, *z;                    //x,y,z为直角坐标
    double *r2;                           //r2表示r^2
    double *u, *v;
    FILE *marsaglia_xyz = NULL;
    rdm = (double *)malloc(2 * N * sizeof(double));
    x = (double *)malloc(N * sizeof(double));
    y = (double *)malloc(N * sizeof(double));
    z = (double *)malloc(N * sizeof(double));
    r2 = (double *)malloc(N * sizeof(double));
    u = (double *)malloc(N * sizeof(double));
    v = (double *)malloc(N * sizeof(double));

    for (int i = 0; i < 2 * N; i++)
    {
        I = schrage(a, m, I);
        rdm[i] = (double)I / m; //产生随机数
    }
    for (int i = 0; i < N; i++)
    {
        u[i] = rdm[2 * i] * 2 - 1;
        v[i] = rdm[2 * i + 1] * 2 - 1;     //用rdm生成[-1,1]之间的随机数(u,v)
        r2[i] = u[i] * u[i] + v[i] * v[i]; //计算r^2
    }
    marsaglia_xyz = fopen("marsaglia_xyz.txt", "w+");
    for (int i = 0; i < N; i++)
    {
        if (r2[i] <= 1)
        {
            x[i] = 2 * u[i] * sqrt(1 - r2[i]);
            y[i] = 2 * v[i] * sqrt(1 - r2[i]);
            z[i] = 1 - 2 * r2[i]; //计算直角坐标
            fprintf(marsaglia_xyz, "%f\t%f\t%f\n", x[i], y[i], z[i]);
        }
    }
    fclose(marsaglia_xyz);
    free(x);
    free(y);
    free(z);
    free(rdm);
    free(u);
    free(v);
    free(r2);
    return 0;
}