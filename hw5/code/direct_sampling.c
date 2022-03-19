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
    int I=1;                               //种子的初值
    double *rdm;                  //rdm用于储存两个累积函数，也是下面我们要产生的两个随机数序列
    double *x, *y, *z;                    //xyz坐标
    double *phi, *costh;                  //costh代表cos(theta)
    FILE *direct_xyz = NULL;                     //后续要将xyz坐标写入文件用于绘图
    rdm = (double *)malloc(2* N * sizeof(double));
    x = (double *)malloc(N * sizeof(double));
    y = (double *)malloc(N * sizeof(double));
    z = (double *)malloc(N * sizeof(double));
    phi = (double *)malloc(N * sizeof(double));
    costh = (double *)malloc(N * sizeof(double));

    for (int i = 0; i < 2*N; i++)
    {
        I = schrage(a, m, I);
        rdm[i] = (double)I / m; //产生随机数
    }
    direct_xyz = fopen("direct_xyz.txt", "w+"); //将直角坐标写入文件
    for (int i = 0; i < N; i++)
    {
        phi[i] = 2 * pi * rdm[2*i+1];//rdm的偶序列用于产生phi
        costh[i] = 1 - rdm[2*i];     //rdm的奇序列用于产生costh
        x[i] = sqrt(1 - costh[i] * costh[i]) * cos(phi[i]);
        y[i] = sqrt(1 - costh[i] * costh[i]) * sin(phi[i]);
        z[i] = costh[i];
        fprintf(direct_xyz, "%f\t%f\t%f\n", x[i], y[i], z[i]);
    }
    fclose(direct_xyz);
    free(rdm);
    free(x);
    free(y);
    free(z);
    free(costh);
    free(phi);
    return 0;
}