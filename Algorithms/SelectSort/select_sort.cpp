// select_sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdlib.h>  
#include <stdio.h>  

void selectSort(int array[], int n)
{
	int i, j, d;
	int temp;
	for (i = 0; i < n - 1; ++i)
	{
		d = i;   //开始一趟选择排序，假定第i个元素是后面n - i + 1个未排序的元素中最小的元素  
		for (j = i + 1; j < n; ++j)
			if (array[j] < array[d])  //如果发现比当前最小元素还小的元素，则更新记录最小元素的下标d  
				d = j;

		if (d != i)   //如果最小元素的下标不是后面n - i + 1的未排序序列的第一个元素，则需要交换第i个元素和后面找到的最小元素的位置  
		{
			temp = array[d];
			array[d] = array[i];
			array[i] = temp;
		}
	}
}

int main()
{
	int array[] = { 3, 1, 15, 11, 89, 5 };
	int size = sizeof(array) / sizeof(int);
	selectSort(array, size);

	for (int i = 0; i < size; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
	system("pause");
}