#if 0
A zero - indexed array A consisting of N integers is given.Rotation of 
the array means that each element is shifted right by one index, and the 
last element of the array is also moved to the first place.

For example, the rotation of array A = [3, 8, 9, 7, 6] is[6, 3, 8, 9, 7].The goal is to rotate 
array A K times; that is, each element of A will be shifted to the right by K indexes.

Write a function :

struct Results solution(int A[], int N, int K);
that, given a zero - indexed array A consisting of N integers and an integer K, returns the array A 
rotated K times.

For example, given array A = [3, 8, 9, 7, 6] and K = 3, the function should return[9, 7, 6, 3, 8].

Assume that :

N and K are integers within the range[0..100];
each element of array A is an integer within the range[−1, 000..1, 000].
In your solution, focus on correctness.The performance of your solution 
will not be the focus of the assessment.

#endif

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Results {
	int *A;
	int N;
};

#if 0
/*
  solution1: use a copy array. this methods is very fast and simple.
*/
struct Results solution(int A[], int N, int K)
{
	int shif_index;
	struct Results res = {A, N};
	if (N == 0 || K % N == 0) {
		return res;
	}
	int *copy_of_A = (int *)malloc(sizeof(int) * N);
	memcpy(copy_of_A, A, sizeof(int)*N);
	shif_index = (0 + K) % N; //(i + k) % N means the index after shifting.
	for (int i = 0; i < N; ++i) { 
		A[shif_index] = copy_of_A[i];
		shif_index = (shif_index + 1) % N;
	}
	res.A = A;
	res.N = N;
	free(copy_of_A);
	return res;
}
#endif

#if 1
/*
  solution2: finish it without another array.
*/
struct Results solution(int A[], int N, int K)
{
	//when K is even number, there are many different cases.
	//like when K % N = N / 2, we need only exchange the i and i+N/2.
	// and also, there is cases that one loop can not go through all the elements. so we need to
	// add start_index and count to judge if all the elment are handled.
	int shif_index = 0, start_index = 0; 
	int temp = 0, temp_save = 0;
	int count = 0, cursor = 0;
	struct Results res = { A, N };
	if (N == 0 || K % N == 0) {
		return res;
	}
	temp_save = A[cursor];

	do {
		shif_index = (cursor + K) % N;
		temp = A[shif_index];
		A[shif_index] = temp_save;
		temp_save = temp;
		count++;

		if (shif_index == start_index) { // here, if we reach the start_index, we need to start another loop.
			start_index++;
			cursor = start_index;
			temp_save = A[cursor];
		} else {
			cursor = shif_index;
		}
				
	} while (count < N);

	return res;
}
#endif

int main()
{

	int A[] = { 3, 8, 9, 7, 6, 8, 2, 7 };
	//int A[] = {3, 8, 9, 7, 6};
	int length = sizeof(A) / sizeof(int);
	solution(A, length, 9);

	for (int i = 0; i < length; ++i) {
		printf("%d ",A[i]);
	}
	printf("\n");

	getchar();

    return 0;
}

