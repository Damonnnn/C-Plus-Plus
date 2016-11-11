#include <stdio.h>

/* Version 1:  */
int BinarySearch1(int a[], int value, int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while(low <= high) {
		mid = (low + high) / 2;
		if(a[mid] == value) {
			return mid;
		} else if(a[mid] > value) {
			high = mid - 1;
		} else if(a[mid] < value) {
			low = mid + 1;
		}
		
	}
	return -1;
}

/* Version 2: */
int BinarySearch2(int a[], int value, int low, int high)
{
	int mid = low + (high - low) / 2;
	if(a[mid] == value) {
		return mid;
	} else if(a[mid] > value) {
		return BinarySearch2(a, value, low, mid - 1);
	} else if(a[mid] < value) {
		return BinarySearch2(a, value, mid + 1, high);
	}
}

int main()
{
	int a[] = {2,5,7,8,12,15,18,19,25,29,31,39,46,49,100};
	int position;

	position = BinarySearch1(a, 46, 15);
	printf("the position = %d\n", position);

	position = BinarySearch2(a, 46, 0, 14);
	printf("the position = %d\n", position);
		

	return 0;
}
