// shell_sort.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <stdlib.h>  
#include <stdio.h>  

void shellSort(int list[], int len) 
{
	int gap = len / 2;

	while (1 <= gap) {
		// �Ѿ���Ϊ gap ��Ԫ�ر�Ϊһ���飬ɨ��������
		for (int i = gap; i < len; i++) {
			int j = 0;
			int temp = list[i];

			// �Ծ���Ϊ gap ��Ԫ�����������
			for (j = i - gap; j >= 0 && temp < list[j]; j = j - gap) {
				list[j + gap] = list[j];
			}
			list[j + gap] = temp;
		}
		gap = gap / 2; // ��С����
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

