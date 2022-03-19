#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define pi 3.14159265358979                              
#define N 1000                                 //每个参数lambda的迭代步数

int main()
{
    double x = 0;                             //迭代变量
    double lambda = 0;                        //参数
    double max = 0.880;          
    double min = 0.700;                       //参数lambda的变化范围
    double step = (max - min)/100000;          //参数lambda变化步长
    int M = 100;                              //对于每一个lambda，迭代M步后输出x的值
    long double error = 0.0001;               //判断同一个lambda下两步迭代值的差即是否分叉
    FILE *feigenbaum_data = NULL;
    feigenbaum_data = fopen("Feigenbaum.txt","w+");
    
    for(lambda=min;lambda<=max;lambda=lambda+step)
    {
        x = 0.1;
        double T[64];                          //T数组存M步开始后面64个迭代结果
        int count = 0;                         //周期计数
        for(int i=0;i<N;i++)
        {
            x = lambda*sin(pi*x);
            if(i>M&&i<M+64)
            {
                T[i-M]=x;
            }
        }
        int k = 1;
        for(int j = 0;j<64;j++)                //遍历每个lambda下64步迭代结果
        {
            if(count<=2)
            {
            if(fabs(T[j]-T[0])>error*5) 
                count++;
            else 
                break;
            }
            else if(count>2&&count<=4)
            {
            if(fabs(T[j]-T[0])>error) 
                count++;
            else 
                break;
            }
            else if(count>4&&count<=8)
            {
            if(fabs(T[j]-T[0])>error/2) 
                count++;
            else 
                break;
            }
            else if(count>8&&count<=16)
            {
            if(fabs(T[j]-T[0])>error/4) 
                count++;
            else 
                break;
            }
            else if(count>16&&count<=32)
            {
            if(fabs(T[j]-T[0])>error/8) 
                count++;
            else 
                break;
            }
            else if(count>32&&count<=64)
            {
            if(fabs(T[j]-T[0])>error/16) 
                count++;
            else 
                break;
            }
        }
        if(count>k&&(count==2||count==4||count==8||count==16||count==32||count==64))
        {
            fprintf(feigenbaum_data,"%d\t%.10f\n",count,(double) lambda);  
            if(k<=32)
            k=2*k;
            else break;
        }
        
    }
    fclose(feigenbaum_data);
    return 0;
}
