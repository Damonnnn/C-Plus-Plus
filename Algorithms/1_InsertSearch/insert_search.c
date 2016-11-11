#include <stdio.h>

int InsertSearch(int a[], int value, int low, int high)
{
	int mid = low + (value - a[low]) / (a[high] - a[low]) * (high - low);
	if(a[mid] == value) {
		return mid;
	} else if(a[mid] > value) {
		return InsertSearch(a, value, low, mid - 1);
	} else if(a[mid] < value) {
		return InsertSearch(a, value, mid + 1, high);
	}
}

int main()
{
	int a[] = {2,5,7,8,12,15,18,19,25,29,31,39,46,49,100};
	int position;

	position = InsertSearch(a, 46, 0, 14);
	printf("the position = %d\n", position);

	return 0;
}
