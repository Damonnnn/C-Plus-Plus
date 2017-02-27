#if 0
A non - empty zero - indexed array A consisting of N integers is given.The array contains 
an odd number of elements, and each element of the array can be paired with another element 
that has the same value, except for one element that is left unpaired.

For example, in array A such that :

A[0] = 9  
A[1] = 3  
A[2] = 9
A[3] = 3  
A[4] = 9  
A[5] = 7
A[6] = 9

the elements at indexes 0 and 2 have value 9,
the elements at indexes 1 and 3 have value 3,
the elements at indexes 4 and 6 have value 9,
the element at index 5 has value 7 and is unpaired.
Write a function :

int solution(int A[], int N);
that, given an array A consisting of N integers fulfilling the above conditions, returns the value of the unpaired element.

For example, given array A such that :

A[0] = 9  A[1] = 3  A[2] = 9
A[3] = 3  A[4] = 9  A[5] = 7
A[6] = 9
the function should return 7, as explained in the example above.

Assume that :

N is an odd integer within the range[1..1, 000, 000];
each element of array A is an integer within the range[1..1, 000, 000, 000];
all but one of the values in A occur an even number of times.
Complexity:

expected worst - case time complexity is O(N);
expected worst - case space complexity is O(1), 
beyond input storage(not counting the storage required for input arguments).
Elements of input arrays can be modified.
#endif


#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
/*
	solution 1: performance test fail.
*/
int solution(int A[], int N)
{
	int i = 0, j = 0;
	int *temp_array;
	temp_array = (int *)malloc(sizeof(int) * N); //this array is used to mark the compared elements. use space to exchange time.
	memset(temp_array, 0, sizeof(int)  * N);
	do {
		if (temp_array[i] != 1) {
			for (j = i + 1; j < N; ++j) {
				if (A[j] == A[i]) {
					temp_array[i] = 1;
					temp_array[j] = 1;
					break;
				}
			}
			if (temp_array[i] != 1) {
				return A[i];
			}
		}
		++i;
	} while (i < N);

	return -1;


}
#endif

#if 0
/*
solution 2: performance test fail.
*/
int solution(int A[], int N) {
	// write your code in C99 (gcc 6.2.0)
	int i = 0, j = 0;

	do {
		if (A[i] != 0) {
			for (j = i + 1; j < N; ++j) {
				if (A[j] == A[i]) {
					A[i] = 0;
					A[j] = 0;
					break;
				}
			}
			if (A[i] != 0) {
				return A[i];
			}
		}
		++i;
	} while (i < N);

	return -1;
}
#endif

#if 1
/*
	solution3: use XOR. test pass. this should be the best solution.
	the rules for XOR:
		1. a ^ b = b ^ a
		2. a ^ b ^ c = a ^ (b ^ c) = (a ^ b) ^ c;
		3. d = a ^ b ^ c 可以推出 a = d ^ b ^ c.
		4. a ^ b ^ a = b.
	从交换律和结合律（第1，2条）可以知道：a ^ b ^ c ^ a ^ b = a ^ a  ^ b ^ b ^ c = (a ^ a) ^ (b ^ b) ^ c = 0 ^ 0 ^ c = c
 */
int solution(int A[], int N) {
	// write your code in C99 (gcc 6.2.0)
	int result = A[0];
	for (int i = 1; i < N; ++i) {
		result = result ^ A[i];
	}
	return result;
}
#endif

#if 0
/*
	solution4: test pass.
	this solution use quik sort algrithm.
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
int solution(int A[], int N) {
	// write your code in C99 (gcc 6.2.0)
	int i;
	quick_sort(A, 0, N - 1);
	for (i = 0; i < N - 1;) {
		if (A[i] == A[i + 1]) {
			i += 2;
		} else {
			return A[i];
		}
	}
	return A[i];
}
#endif

int main()
{
	//int A[] = {9, 3, 9, 3, 9, 7, 9};
	int A[] = { 5,6,5,6,8,200,0,200,0,1,1,2,2,3,5,5,3,8,150};
	int result = solution(A, sizeof(A) / sizeof(int));
	printf("result = %d\n", result);
	getchar();
    return 0;
}

