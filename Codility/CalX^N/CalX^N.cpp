// Teknique_codility_task3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");

#define MAX_LENGTH 100000
#define MAX_DIGITS 10000  // one element should not exceed 9999, it is changable

int solution(int N) {
	// write your code in C99 (gcc 6.2.0)
	int base = 11; // base
	int exp = N; // exponentiation
	int result[MAX_LENGTH] = { 0 };// to save the space and time, not one element one digit. this one element represent 4 digits.
	int section = 1; // sections
	int count = 0;
	int i, j;

	int v = 0; // recording advance digital
	result[0] = 1;

	for (j = 0; j < exp; j++) {
		for (i = 0; i < section; i++) {
			result[i] = result[i] * base + v; // calculate one section and add advanced number
			v = result[i] / MAX_DIGITS; // any numbers need to be advanced to next section
			result[i] = result[i] % MAX_DIGITS; // leave no more than 8 digits within one section
			if (v > 0 && i + 1 == section) { //two conditions: v should larger that 1; i+1==section means this is the last section, we need to add one more.
				// check if one more section need to be calculated
				section++;
			}
		}
	}
	//for (int i = section-1; i >= 0; i--) {
	//	printf("%d",result[i]);
	//}
	printf("\n");
	for (int i = 0; i < section; i++) {
		while (result[i] > 0) {
			if (result[i] % 10 == 1) {
				count++;
			}
			result[i] = result[i] / 10;
		}
	}
	return count;
}
int main()
{
	int N = 11;
	int result = 0;
	int time_begin = GetTickCount();
	//for (int i = 0; i < 10000; i++) {
		result = solution(N);
	//}
	int time_end = GetTickCount();
	printf("time_begin:%d\n", time_begin);
	printf("time_end:%d\n", time_end);
	printf("time_interval:%d\n", time_end - time_begin);
	printf("result: %d", result);
	getchar();
    return 0;
}

