// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"
#include <math.h>
float Ave(int a[], int n)
{
	int i;
	float ave, sum = 0;
	for (i = 0; i < n; i++)
	{
		sum = sum + a[i];
	}
	ave = sum / n;
	return ave;
}

float SD(int a[], int n)
{
	float Ave(int a[], int n);
	int i;
	float sum = 0, sd;
	for (i = 0; i < n; i++)
	{
		sum = (a[i] - Ave(a, n)) * (a[i] - Ave(a, n)) + sum;
	}
	sd = sqrt(sum / n);
	return sd;
}

int maxs(int a[], int n)
{
	int i, Max = 0;
	for (i = 0; i < n; i++)
	{

		if (Max < a[i])
			Max = a[i];

	}

	return Max;
}

int mins(int a[], int n)
{
	int i, Min = 750;
	for (i = 0; i < n; i++)
	{

		if (Min > a[i])
			Min = a[i];

	}

	return Min;
}
// 当使用预编译的头时，需要使用此源文件，编译才能成功。
