#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define pi  3.141592653589793
#define Total 10000              //总的时间步数

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
    double A = 1.0;                        //正弦外场的影响因子A
    double omega = pi/2;                  //正弦电场的频率                                            
    double *rdm;                          //待产生的随机数
    double *x;                            //记录每一步的位移
    x = (double *)malloc(Total* sizeof(double));
    rdm = (double *)malloc(Total* sizeof(double));
    FILE *result_1d=NULL;
    result_1d = fopen("1D_data_10000.txt","w+");
    
    for (int j = 0; j < Total; j++)
    {
        I = schrage(a, m, I);
        rdm[j] = (double)I / m;
    }
    x[0]=0;
    for(int i=1;i<Total;i++)
    {
        if(rdm[i] < 0.5*(1+a*sin(omega*i)))
            x[i]=x[i-1]+1;
        else x[i]=x[i-1]-1;
        fprintf(result_1d,"%d\t%f\n",i,x[i]);
    }
    fclose(result_1d);
    free(rdm);
    free(x);
    return 0;
}