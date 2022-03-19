#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define limit 200				//设置行走矩阵的大小

//初始化行走矩阵：中心置1，其它置0
void initialize(int *p, long size)
{
	int *q = p;
	while(q<(p+size))
	{
		*q = 0;
		q++;
	}
	*(q-size/2+limit/2) = 1;
}

//用0~7之间的随机数控制粒子随机行走函数 
void walk(int *x, int *y, int s)
{
	int step = rand() % 8;
	int p1 = *x-1;
	int p2 = *x+1;
	int s1 = *y-1;
	int s2 = *y+1;
	if(*x==0)					//遇到边界停止
		p1 = s-1; 
	else if(*x==s-1)
		p2 = 0;
	
	if(*y==0)					//遇到边界停止
		s1 = s-1; 
	else if(*y==s-1)
		s2 = 0;
		
	switch(step)				//按随机数决定下一步的方向
	{
	case 0:
		*x = p2;				//+
		break;
	case 1:
		*x = p1;				//-
		break;
	case 2:
		*y = s2;				//+
		break;
	case 3:
		*y = s1;				//-
		break;
	case 4:
		*x = p2; *y = s2;		//++
		break;
	case 5:
		*x = p1; *y = s1;		//--
		break;
	case 6:
		*x = p2; *y = s1;		//+-
		break;
	case 7:
		*x = p1; *y = s2;		//-+
		break;
	default:
		printf("error");
		break;
	}
}

//judge()用于判断下一步是否接触已经走过的点
int judge(int x, int y, int space[][limit], int s)
{
	int p1 = x-1;
	int p2 = x+1;
	int s1 = y-1;
	int s2 = y+1;
	if(x==0)
		p1 = s-1; 
	else if(x==s-1)
		p2 = 0;
	
	if(y==0)
		s1 = s-1; 
	else if(y==s-1)
		s2 = 0;
		
	if(space[p2][y]==1) return 1;			//即将接触返回1
	if(space[p1][y]==1) return 1;
	if(space[x][s2]==1) return 1;
	if(space[x][s1]==1) return 1;
	if(space[p2][s2]==1) return 1;
	if(space[p2][s1]==1) return 1;
	if(space[p1][s2]==1) return 1;
	if(space[p1][s1]==1) return 1;
	
	return 0;
}

//DLA生长函数
void DLA(int width, int space[][limit])
{
	for(int i=0; i<3000; i++)
	{
		int x = rand()% width;			
		int y = rand()% width;				//在整个行走矩阵上生成随机起始点
		if(space[x][y]==1) continue;
		while(!judge(x,y,space,width))
		{
			walk(&x, &y, width);
		}
		space[x][y] = 1;					//接触到核心时会停下并置1
	}
}
int main()
{
	int space[limit][limit];
	long size = sizeof(space)/4;			//行走矩阵里元素总个数 
	int width = sqrt(size);					//行走矩阵的尺寸
    FILE *dla_data = NULL;
	FILE *sandbox_data = NULL;
	FILE *Rg_data = NULL;
    dla_data = fopen("dla_data.txt","w+");
	Rg_data = fopen("Rg_data.txt","w+");
	sandbox_data = fopen("sandbox_data.txt","w+");
	
	initialize(*space,size);
	
	DLA(width,space);

	int m, n;
	for(m=0; m<width; m++)
	{
		for(n=0; n<width; n++)
		{
			if(space[m][n]==1) 
                fprintf(dla_data,"%d\t%d\n",m,n);	//输出粒子位置
		}
	}
	
	
	//sandbox法
	int count1 = 0;							//记录每一个sandbox中的粒子数
	for(int r = 0;r <= width/2;r++)			//r为sanbox的尺寸
	{
		count1 = 0;
		for(int l = width/2-r;l<=width/2+r;l++)
		{
			for(int s = width/2-r;s<=width/2+r;s++)
			{
				if(space[l][s]==1)
					count1++;
			}
		}
		fprintf(sandbox_data,"%d\t%d\n",r,count1);
	}
	
	//回转半径法
	int count2 = 0;							//粒子数计数
	double R = 0;							//回转半径
	for(int r = 0;r <= width/2;r++)
	{
		count2 = 0;
		for(int l = width/2-r;l<=width/2+r;l++)
		{
			for(int s = width/2-r;s<=width/2+r;s++)
			{
				if(space[l][s]==1)
					{
						count2++;
						R = R + (double)((l-width/2)*(l-width/2)+(s-width/2)*(s-width/2));
					}
			}
		}
		if(count2 == 0)	continue;
		R = sqrt(R/(double)count2);
		fprintf(Rg_data,"%f\t%d\n",R,count2);
	}
	
	fclose(sandbox_data);
	fclose(dla_data);
	fclose(Rg_data);
	return 0;
}

