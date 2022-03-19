#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int N=1000000;
int n0=100000;

//比较大小的函数
double min(double x,double y)
{
    if(x < y)
        return x;
    else 
        return y;
} 

//定义能量函数，方便后续表示
double H(double x,double y)
{
    double temp;
    temp = -2.0*(x*x+y*y)+0.5*(x*x*x*x+y*y*y*y)+0.5*(x-y)*(x-y)*(x-y)*(x-y);
    return temp;
}

int main()
{
    double x0,y0,x1,y1,E0,E1,r,t;
    double sumx=0,sumy=0,sumxy=0;               //分别表示x^2,y^2,x^2+y^2的和
    double avgx,avgy,avgxy;                     //x^2,y^2,x^2+y^2之平均值
    double beta=5.0;                            //定义beta值
    FILE *xy_data = NULL;
    x0=8.0;                                     //起始点
    y0=8.0;                                     //起始点
    xy_data = fopen("xy_data_beta=5.0.txt","a+");
    for(int i=0;i<N;i++)
    {
        x1 = x0+0.2*rand()/RAND_MAX-0.1;            //改变坐标
        y1 = y0+0.2*rand()/RAND_MAX-0.1;            //改变坐标
        E0 = H(x0,y0);
        E1 = H(x1,y1);                          //计算相邻两步的能量
        if(i>n0)                                //舍去热化阶段的点
        {
            sumx = sumx + x1*x1;
            sumy = sumy + y1*y1;
            sumxy = sumxy + x1*x1+y1*y1;
        }
        if(E1-E0<=0)
        {
            x0 = x1;
            y0 = y1;                             //若能量降低，则直接更新状态
            fprintf(xy_data,"%f\t%f\n",x1,y1);
        }
        else {
            r = 1.0*rand()/RAND_MAX;
            t = exp(-beta*(E1-E0));
            if(r<t)                             //根据r和t的大小关系判断下一步的取舍
            {
                x0 = x1;
                y0 = y1;
                fprintf(xy_data,"%f\t%f\n",x1,y1);
            }
        }
    }
    avgx = (double)sumx/(N-n0);
    avgy = (double)sumy/(N-n0);
    avgxy = (double)sumxy/(N-n0);
    printf("beta=%f\n<x^2>=%lf\t<y^2>=%lf\t<x^2+y^2>=%lf\n",beta,avgx,avgy,avgxy);
    return 0;
}
