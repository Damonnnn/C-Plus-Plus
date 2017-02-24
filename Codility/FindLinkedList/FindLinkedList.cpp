// Teknique_codility_task1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");

int solution(int A[], int N) {
	// write your code in C99 (gcc 6.2.0)
	int list_length = 1;
	int index = 0;

/************************
	while (1) {
		list_length++;
		if (A[index] != -1) {
			index = A[index];
		}
		else {
			break;
		}
	}
************************/
/************************
	while (1) {
		list_length++;
		if (A[index] == -1) {
			break;
		}
		index = A[index];
	}
************************/
	while (A[index] != -1) {
		list_length++;
		index = A[index];
	}
	return list_length;
}
int main()
{
	//int A[] = {1, 4, -1, 3, 2};
	//int A[] = {5, 6, 1, 4, 2, 8, 9, -1, 3, 7};
	int A[] = {3, 8, -1, 7, 9, 15, 3, 2, 2, 4, 7};
	int N = 5;
	printf("result: %d\n", solution(A, sizeof(A)));
	getchar();
    return 0;
}

