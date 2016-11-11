// heap_sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdlib.h>
#define PARENT(i) (i)/2
#define LEFT(i) 2*(i)+1
#define RIGHT(i) 2*(i+1)

void swap(int *a, int *b)
{
	*a = *a^*b;
	*b = *a^*b;
	*a = *a^*b;
}
void max_heapify(int *arr, int index, int len)
{
	int l = LEFT(index);
	int r = RIGHT(index);
	int largest;
	if (l<len && arr[l]>arr[index])
		largest = l;
	else
		largest = index;
	if (r<len && arr[r]>arr[largest])
		largest = r;
	if (largest != index) {//将最大元素提升，并递归
		swap(&arr[largest], &arr[index]);
		max_heapify(arr, largest, len);
	}
}

void build_maxheap(int *arr, int len)
{
	int i;
	if (arr == NULL || len <= 1)
		return;
	for (i = len / 2 + 1; i >= 0; --i) // (len/2+1) means the last point who has children.
		max_heapify(arr, i, len);
}
void heap_sort(int *arr, int len)
{
	int i;
	if (arr == NULL || len <= 1)
		return;
	build_maxheap(arr, len);

	for (i = len - 1; i >= 1; --i) {
		swap(&arr[0], &arr[i]);
		max_heapify(arr, 0, --len);
	}
}

int main()
{
	int arr[10] = { 1,4,6,2,5,8,7,6,9,12 };
	int i;
	heap_sort(arr, 10);
	for (i = 0; i<10; ++i)
		printf("%d ", arr[i]);
	system("pause");
}

