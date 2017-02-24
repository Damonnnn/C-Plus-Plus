#if 0
//////////////////////////////////////////////////////////////////////////
A binary gap within a positive integer N is any maximal sequence of 
consecutive zeros that is surrounded by ones at both ends in the binary 
representation of N.

For example, number 9 has binary representation 1001 and contains a binary 
gap of length 2. The number 529 has binary representation 1000010001 and contains 
two binary gaps : one of length 4 and one of length 3. The number 20 has binary 
representation 10100 and contains one binary gap of length 1. The number 15 has 
binary representation 1111 and has no binary gaps.

Write a function :

int solution(int N);
that, given a positive integer N, returns the length of its longest binary gap.The
function should return 0 if N doesn't contain a binary gap.

For example, given N = 1041 the function should return 5, because N has binary 
representation 10000010001 and so its longest binary gap is of length 5.

Assume that :

N is an integer within the range[1..2, 147, 483, 647].
Complexity :

expected worst - case time complexity is O(log(N));
expected worst - case space complexity is O(1).
////////////////////////////////////////////////////////////////////////
#endif

#include "stdafx.h"
#include <stdio.h>

int solution(int N)
{
	int base = N; 
	//int quotient = 0; // base/2
	int remainder = 0; // base%2
	int gap_length = 0, max_gap_length = 0;
	int flag = 0; //to mark the valid gap begin.

	do {
		//remainder = base % 2;
		remainder = base & 0x1;
		if (remainder == 1 && flag == 0) {
			flag = 1;
		} else if (remainder == 0 && flag == 1) {
			++gap_length;
		} else if(remainder == 1 && flag == 1) {
			if (max_gap_length < gap_length) {
				max_gap_length = gap_length;
			}
			gap_length = 0;
			//flag = 1; no need to do this
		}
		//base = base / 2;
		base = base >> 1;
	}while (base != 0);
	return max_gap_length;
}


int main()
{
	int result;
	int test_value;
	while (1) {
		scanf_s("%d", &test_value);
		if (test_value == -1) {
			break;
		}
		result = solution(test_value);
		printf("the max gap length is %d\n", result);
	}
	getchar();
    return 0;
}

