// select_sort.cpp : �������̨Ӧ�ó������ڵ㡣
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
		d = i;   //��ʼһ��ѡ�����򣬼ٶ���i��Ԫ���Ǻ���n - i + 1��δ�����Ԫ������С��Ԫ��  
		for (j = i + 1; j < n; ++j)
			if (array[j] < array[d])  //������ֱȵ�ǰ��СԪ�ػ�С��Ԫ�أ�����¼�¼��СԪ�ص��±�d  
				d = j;

		if (d != i)   //�����СԪ�ص��±겻�Ǻ���n - i + 1��δ�������еĵ�һ��Ԫ�أ�����Ҫ������i��Ԫ�غͺ����ҵ�����СԪ�ص�λ��  
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