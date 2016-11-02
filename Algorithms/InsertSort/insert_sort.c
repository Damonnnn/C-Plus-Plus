// insert_sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdlib.h>  
#include <stdio.h>  

static void insertion_sort(int unsorted[], int len)
{
	for (int i = 1; i < len; i++)
	{
		if (unsorted[i - 1] > unsorted[i])
		{
			int temp = unsorted[i];
			int j = i;
			while (j > 0 && unsorted[j - 1] > temp)
			{
				unsorted[j] = unsorted[j - 1];
				j--;
			}
			unsorted[j] = temp;
		}
	}
}

int main()
{
	int x[] = { 6, 2, 4, 1, 5, 9 };
	insertion_sort(x,6);
	for (int i = 0; i < 6; ++i) {
		printf("%d ", x[i]);
	}
	system("pause");
}

