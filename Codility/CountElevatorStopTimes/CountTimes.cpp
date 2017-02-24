// TekniqueCodelity.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");

int solution(int A[], int B[], int N, int M, int X, int Y) {
	// write your code in C99 (gcc 6.2.0)
	int* floors = (int*)malloc(sizeof(int) * (M + 1));
	memset(floors, 0, sizeof(int) * (M + 1));
	int cursor = 0;
	long total_weight = 0;
	int people_number = 0;
	int times = 0;
	int need_count = 0;

	while (cursor < N) {
		total_weight += A[cursor];
		people_number++;
		if (total_weight <= Y && people_number <= X) {
			floors[B[cursor]] = 1;
			cursor++;
			need_count = 1;
		}
		else {
			for (int j = 0; j < M + 1; j++) {
				if (floors[j] == 1) {
					times++;
				}
			}
			times++;  // ground floor
			total_weight = 0;
			people_number = 0;
			memset(floors, 0, sizeof(int) * (M + 1));
			need_count = 0;
		}
	}

	if (need_count == 1) {  //this is for the last loop
		for (int j = 0; j < M + 1; j++) {
			if (floors[j] == 1) {
				times++;
			}
		}
		times++;  // ground floor
	}

	free(floors);
	return times;
}

int main()
{
	int A[] = { 40, 40, 100, 80, 20 };
	int B[] = { 3,3,2,2,3 };
	int N = 5;
	int M = 3;
	int X = 5;
	int Y = 200;
	printf("result: %d\n", solution(A, B, N, M, X, Y));
	getchar();
	return 0;
}

