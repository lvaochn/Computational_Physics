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
    int N = 100000;                       //N为产生随机数的总数
    int I = 1;                            //种子的初值定为1

    //用16807随机数产生器产生随机数
    double *x;
    x = (double *)malloc(N * sizeof(double)); //指针x用于存储16807产生器产生的随机数
    for (int i = 0; i < N; i++)
    {
        I = schrage(a, m, I);
        x[i] = (double)I / m; //产生随机数
    }

    //计算16807随机数产生器中X_n+1>X_n-1>X_n的比例
    int count1 = 0;      //数目
    double account1 = 0; //比例
    for (int i = 0; i < N - 2; i++)
    {
        if (x[i] < x[i - 1] && x[i - 1] < x[i + 1])
            count1++;
    }
    account1 = (double)account1 / N;
    printf("The account X_n+1>X_n-1>X_n of 16807 generator is %f\n", account1);

    //用Fibonacci延迟产生器生成随机数
    double *fib;
    fib = (double *)malloc(N * sizeof(double));                       //指针fib用于存储Fibonacci延迟产生器产生的随机数
    int p[5] = {24, 37, 38, 30, 103}, q[5] = {55, 100, 89, 127, 250}; //存储延迟整数对
    for (int j = 0; j < 5; j++)                                       //用j遍历上面定义的五个延迟整数对
    {
        I = 1;
        for (int i = 0; i < q[j]; i++)
        {
            I = schrage(a, m, I) + b % m;
            fib[i] = I; //先生成Fibonacci初始序列
        }
        for (int i = q[j]; i < N; i++)
        {
            fib[i] = (double)(((int)fib[i - q[j]] + (int)fib[i - p[j]]) % m);
        }
        for (int i = 0; i < N; i++)
        {
            fib[i] = fib[i] / m;
        }

        //下面我们计算Fibonacci产生器中满足题中要求关系的占比
        int count2 = 0;      //数目
        double account2 = 0; //比例
        for (int i = 0; i < N - 2; i++)
        {
            if (fib[i] < fib[i + 1] && fib[i + 1] < fib[i - 1])
                count2++;
        }
        account2 = (double)count2 / N;
        printf("The account X_n+1>X_n-1>X_n of Fibonacci generator(p=%d,q=%d) is %f\n", p[j], q[j], account2);
    }
    free(x);
    free(fib);
    return 0;
}