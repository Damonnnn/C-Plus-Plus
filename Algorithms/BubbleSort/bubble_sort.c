// bubble_sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdlib.h>  
#include <stdio.h>  

void bubble_sort(int unsorted[],int len)
{
	int i, j;
	for (i = 0; i < len; i++)
	{
		for (j = i; j < len; j++)
		{
			if (unsorted[i] > unsorted[j])
			{
				int temp = unsorted[i];
				unsorted[i] = unsorted[j];
				unsorted[j] = temp;
			}
		}
	}
}

int main()
{
	int x[] = { 6, 2, 4, 1, 5, 9 };
	bubble_sort(x,6);
	for (int i = 0; i < 6; ++i) {
		printf("%d ", x[i]);
	}
	system("pause");
}

