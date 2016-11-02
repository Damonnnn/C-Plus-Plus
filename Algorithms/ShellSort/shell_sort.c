// shell_sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdlib.h>  
#include <stdio.h>  

void shellSort(int list[], int len) 
{
	int gap = len / 2;

	while (1 <= gap) {
		// 把距离为 gap 的元素编为一个组，扫描所有组
		for (int i = gap; i < len; i++) {
			int j = 0;
			int temp = list[i];

			// 对距离为 gap 的元素组进行排序
			for (j = i - gap; j >= 0 && temp < list[j]; j = j - gap) {
				list[j + gap] = list[j];
			}
			list[j + gap] = temp;
		}
		gap = gap / 2; // 减小增量
	}
}

int main()
{
	int x[] = {36, 9, 1, 2, 5, 7, 4, 8, 6, 3, 5, 37 };
	shellSort(x,12);
	for (int i = 0; i < 12; ++i) {
		printf("%d ", x[i]);
	}
	system("pause");
}

