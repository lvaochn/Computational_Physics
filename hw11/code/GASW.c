#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX 3000 //随机行走步数最大值
#define M 5000	 //实验中尝试进行随机行走的次数

typedef struct _coordinate
{ 														   //结构体coordinate记录二维平面上行走的两个坐标
	int x[2];
} Coor;

typedef struct _road
{ 														  //结构体road记录步数N,权重w和走过的位置
	int N;
	double w[MAX + 1];
	Coor history[MAX + 1];
} Road;

int direction[][2] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}}; //每一步随机行走的四个方向
int scope[MAX * 2 + 1][MAX * 2 + 1];					 //行走的范围
double r2[MAX] = {0};									 //记录到原点距离的平方
double sum_w[MAX] = {0};								 //记录每一步的权重

//判断每个位置有多少个可以选择的方向
int judge(Coor c, int t)
{
	return !scope[c.x[0] + MAX + direction[t][0]][c.x[1] + MAX + direction[t][1]];
}

// GASW是用来自规避随机行走N步的函数，若成功则返回1，否则返回0
int GASW(int N, Road *path)
{
	memset(scope, 0, (MAX * 2 + 10) * (MAX * 2 + 10) * sizeof(int));
	Coor coordinate;										 //随机行走每一步的坐标
	coordinate.x[1] = coordinate.x[0] = 0;					 //初始化位置坐标
	scope[coordinate.x[0] + MAX][coordinate.x[1] + MAX] = 1; //初始化行走的边界
	int i, j, k;
	double w;
	w = 1;
	path->N = N;
	for (i = 0; i < N; i++)
	{
		k = 0;
		int choice[4]; //每一步的方向最多4个
		int possible_direction = 0;
		for (j = 0; j < 4; j++)
		{
			if (judge(coordinate, j))
			{
				possible_direction++; //确定可选择的方向
				choice[k++] = j;
			}
		}
		if (possible_direction == 0)
			return 0;
		int onechoice = choice[rand() % possible_direction]; //用随机数从可能的方向中进行选择
		coordinate.x[0] = coordinate.x[0] + direction[onechoice][0];
		coordinate.x[1] = coordinate.x[1] + direction[onechoice][1];
		scope[coordinate.x[0] + MAX][coordinate.x[1] + MAX] = 1;
		path->history[i] = coordinate;			 //行走的坐标将被记录在path指针中
		w = w * (double)possible_direction / 3.; //计算每一步的权重
		path->w[i] = w;
	}
	return 1;
}

// finishGASW函数用于接收成功的GASW
void finishGASW(int N, Road *p)
{

	while (!GASW(N, p))
	{
	}
}

int main()
{
	int N = 50; //需要行走的步数
	Road p;
	srand((unsigned)time(0)); //指定随机数种子，使下面每次产生的随机数序列不相同

	//下面将计算某一次成功的随机行走的轨迹坐标，用于画图观察
	finishGASW(N, &p);
	printf("0");
	for (int i = 0; i < N; i++)
	{
		printf("%d ", p.history[i].x[0]);
	}
	printf("\n");
	printf("0 ");
	for (int i = 0; i < N; i++)
	{
		printf("%d ", p.history[i].x[1]);
	}
	printf("\n");

	//下面将计算r(N)*r(N),并计算加权平均
	for (int i = 0; i < M; i++)
	{
		finishGASW(N, &p);
		for (int j = 0; j < N; j++)
		{
			r2[j] = r2[j] + p.w[j] * (p.history[j].x[0] * p.history[j].x[0] + p.history[j].x[1] * p.history[j].x[1]); // r^2加权和
			sum_w[j] = sum_w[j] + p.w[j];																			  //权重之和
		}
	}
	for (int i = 0; i < N; i++)
	{
		r2[i] = (double)r2[i] / sum_w[i];
	}
	for (int i = 0; i < N; i++)
	{
		printf("%lf ", r2[i]);
	}
	printf("\n");
	return 0;
}