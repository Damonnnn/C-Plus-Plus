/*
A zero-indexed array A consisting of N different integers is given. The array contains integers in the range [1..(N + 1)], which means that exactly one element is missing.

Your goal is to find that missing element.

Write a function:

int solution(int A[], int N);
that, given a zero-indexed array A, returns the value of the missing element.

For example, given array A such that:

A[0] = 2
A[1] = 3
A[2] = 1
A[3] = 5
the function should return 4, as it is the missing element.

Assume that:

N is an integer within the range [0..100,000];
the elements of A are all distinct;
each element of array A is an integer within the range [1..(N + 1)].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(1), beyond input storage (not counting the storage required for input arguments).
Elements of input arrays can be modified.

*/

#include "stdafx.h"


/*
	solution1: sort the array, then find the missing number.
	solution2: make another array wich is N+1 long. 
*/
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
#if 0
int solution(int A[], int N) {
	// write your code in C99 (gcc 6.2.0)
	int missing_number = -1;
	int i;

	if (N == 0) {
		printf("the array is empty\n");
		return 1;
	}
	quick_sort(A, 0, N - 1);
	if (A[0] != 1) {
		missing_number = 1;
	}
	else {
		if (N == 1) {
			missing_number = 2;

		}
		else {
			for (i = 1; i < N; ++i) {
				if (A[i - 1] + 1 != A[i]) {
					missing_number = A[i - 1] + 1;
					break;
				}
			}
			if (i == N) {
				missing_number = A[i - 1] + 1;
			}
		}
	}
	return missing_number;
}
#endif
#include <stdio.h>
#include <stdlib.h>
int solution(int A[], int N)
{
	int missing_number = 1;
	int i = 0;
	if (N == 0) {
		return 1;
	}
	int *B = (int *)malloc(sizeof(int) * (N + 2));
	memset(B, 0, sizeof(int) * (N + 2));
	for (i = 0; i < N; ++i) {
		B[A[i]] = 1;
	}
	for (i = 1; i < N + 2; ++i) {
		if (B[i] == 0) {
			missing_number = i;
			break;
		}
	}
	if (i == N + 1) {
		missing_number = N + 1;
	}
	free(B);
	return missing_number;
}
int main()
{
	int missing_number = -1;
	//int A[] = { 4,1,3,2 };
	int A[] = { 2 };
	missing_number = solution(A, sizeof(A)/sizeof(int));
	printf("missing_number = %d\n", missing_number);
	getchar();
    return 0;
}

