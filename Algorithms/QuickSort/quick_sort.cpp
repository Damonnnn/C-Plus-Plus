// quick_sort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int partition(int * arr, int low, int high)
{
	int pivot = arr[high];  // take the highest element as a pivot
	int i = low - 1;
	int j, temp;
	for (j = low; j < high; ++j) {
		if (arr[j] < pivot) { // by default, it is sorted by assending.if we change < to >, it will be sorted by dessending.
			temp = arr[++i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	temp = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = temp;
	return i + 1;
}

void quick_sort(int * arr, int low, int high)
{
	if (low < high) {
		int mid = partition(arr, low, high);
		quick_sort(arr, low, mid - 1);
		quick_sort(arr, mid + 1, high);
	}
}


int main()
{
	int arr[10] = { 1, 4, 6, 2, 5, 8, 7, 6, 9, 12 };
	quick_sort(arr, 0, 9);
	int i;
	for (i = 0; i < 10; ++i) {
		printf("%d ", arr[i]);
	}
	getchar();
    return 0;
}

