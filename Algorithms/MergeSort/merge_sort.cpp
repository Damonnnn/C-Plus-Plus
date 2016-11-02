// merge_sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_INT  ~(1<<31)//最大整数
//arr[p,q]  arr[q+1,r]
void merge(int *arr, int p, int q, int r)
{
	if (arr == NULL)
		return;
	int n1 = q - p + 1;
	int n2 = r - q;
	int *L = (int*)malloc((n1 + 1) * sizeof(int));
	int *R = (int*)malloc((n2 + 1) * sizeof(int));
	int i, j;
	for (i = 0; i<n1; ++i)
		L[i] = arr[p + i];
	for (j = 0; j<n2; ++j)
		R[j] = arr[q + j + 1];
	//哨兵元素赋值
	L[n1] = MAX_INT;
	R[n2] = MAX_INT;
	int k;
	i = 0, j = 0;
	for (k = p; k <= r; ++k) {
		if (L[i] <= R[j])
			arr[k] = L[i++];
		else
			arr[k] = R[j++];
	}
	free(L);
	free(R);
}
void merge_sort(int *arr, int p, int r)
{
	if (p<r) {
		int q = (r + p) / 2;
		merge_sort(arr, p, q);//divide
		merge_sort(arr, q + 1, r);
		merge(arr, p, q, r);//merge & sort
	}

}

int main()
{
	int arr[8] = { 32,3,4,5,6,7,9,106 };
	merge_sort(arr, 0, 7);
	for (int i = 0; i<8; i++)
	{
		printf("%d ", arr[i]);
	}
	system("pause");
}


