#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10000000
#define TotalNum 114 //题中所给数据点的个数

//定义比较函数F(x)
double F(double x )     
{
    double temp = 0;
    if(2900<=x && x<2994)
    temp=0.0143232;
    else if(2994<=x && x<3005)
    temp=0.0950248;
    else temp=0.0032778;
    return temp;
}

//定义累积函数G(x)的反函数
double G(double x) {
	double a1=0.557371, a2=0.989978;
	double y;
	if (x<=a1) {
		y = 168.649*x+2900;
	}
	else if (x<=a2) {
		y = 25.4206*x+2984.832;
	}
	else {
		y = 733.952*x+2282.32;
	}
	return y;
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
    int a = 16807, b = 0, m = 2147483647; //输入相应参数
    int I = 1;                            //种子的初值
    int sum = 0;                          //计频数之和的变量
    double *rdm;                           //用于产生2N个随机数
    double *xi_1,*xi_2;                   //两个个[0,1]随机数序列
    double *x,*y;                         //需要舍选的坐标点序列
    int EffcientCounts = 0;                     //计数变量，计算效率
    rdm = (double *)malloc(2* N * sizeof(double));
    xi_1 = (double *)malloc(N * sizeof(double));
    xi_2 = (double *)malloc(N * sizeof(double));
    x = (double *)malloc(N * sizeof(double));
    y = (double *)malloc(N * sizeof(double));
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

    //产生随机数
    for (int j = 0; j < 2*N; j++)
    {
        I = schrage(a, m, I);
        rdm[j] = (double)I / m;
    }
    for(int j = 0;j<N;j++)
    {
        xi_1[j]=rdm[2*j];
        xi_2[j]=rdm[2*j+1];
    }
    
    //计算p和P
    P[0] = 0; 
    for (int i = 1; i < TotalNum; i++)
    {
        p[i] = (double)counts[i] / sum;
        P[i] = p[i] + P[i - 1];
    }
    
    //舍选抽样
    Result = fopen("rejection_sample_data.txt", "w+");
    for (int i = 0; i < N; i++)
    {
        x[i]=G(xi_1[i]);
        y[i]=F(x[i])*xi_2[i];
        if(y[i]<p[(int)x[i]-2899])
        {
            fprintf(Result,"%d\n",(int)x[i]);//接受的随机数点
            EffcientCounts++;
        }
    }
    printf("The Efficiency of rejection sampling is %f\n",(double)EffcientCounts/N);
    fclose(Result);
    free(x);
    free(y);
    free(xi_1);
    free(xi_2);
    free(rdm);
    return 0;
}
