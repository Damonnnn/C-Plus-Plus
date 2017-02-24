// FindBrackets.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>

void find_first_bracket(char *S, int begin, int end, int *cursor1, int *cursor2)
{
	int i;
	//find the first "()"
	for (i = begin; i < end - 1; ++i) {
		if (S[i] == '(' && S[i + 1] == ')') {
			*cursor1 = i;
			*cursor2 = i + 1;
			break;
		}
	}
}

int extend_left(char *S, int begin, int end, int *cursor1, int *cursor2)
{
	while (*cursor1 - 1 >= begin && *cursor2 + 1 <= end) {
		if (S[*cursor2 + 1] == ')' && S[*cursor1 - 1] == '(') {
			(*cursor1)--;
			(*cursor2)++;
		} else if(S[*cursor2 + 1] == ')'){
			//this means we no need to handle the extent_right()
			return -1;
		} else {
			return 0;
		}
	}
	return -1;
}

void handle_str(char *S, int begin, int end, int *r_begin, int *r_end)
{
	int cursor1 = -1, cursor2 = -1;
	int cursor3 = -1, cursor4 = -1;
	
	//find the first ()
	find_first_bracket(S, begin, end, &cursor1, &cursor2);
	if (cursor1 == cursor2) {
		*r_begin = -1;
		*r_end = -1;
		return;
	}
	while (1) {
		//handle the ')' case
		if (-1 == extend_left(S, begin, end, &cursor1, &cursor2)) {
			*r_begin = cursor1;
			*r_end = cursor2;
			return; // over, no need to handle extend_right().
		}
		//handle the '(' case
		//extent_right();
		cursor3 = -1;
		cursor4 = -1;
		handle_str(S, cursor2 + 1, end, &cursor3, &cursor4); //recursive calling
		if ((cursor3 == cursor4) || ((cursor2 + 1) != cursor3)) {
			*r_begin = cursor1;
			*r_end = cursor2;
			return; // can not merge, return
		}
		else { // yes, we merge
			*r_begin = cursor1;
			*r_end = cursor4;
			cursor2 = cursor4;
		}
	}
}

int solution(char *S, int K)
{
	int str_len = strlen(S);
	//int valid_bracket_len = 0;
	int cursor1 = -1, cursor2 = -1; // cursor1, cursor2 represent the begin index and end index of the valid brackets.
	int begin = 0, end = str_len - 1;
	int max_valid_bracket_length = 0;
	int ret_begin = -1, ret_end = -1;
	//TODO: check the total str_len should exceed 2.
	while (cursor2 <= end) {
		cursor1 = -1, cursor2 = -1;
		handle_str(S, begin, end, &cursor1, &cursor2);
		if (cursor1 == cursor2) {
			//printf("sorry, I can find a valid braket string!\n");
			printf("The max_lent = %d, cursor1 = %d, cursor2 = %d\n", max_valid_bracket_length, ret_begin, ret_end);
			return max_valid_bracket_length;
		} else {
			printf("cursor1=%d, cursor2 = %d\n", cursor1, cursor2);
			begin = cursor2 + 1;
			if (max_valid_bracket_length < (cursor2 - cursor1 + 1)) {
				max_valid_bracket_length = cursor2 - cursor1 + 1;
				ret_begin = cursor1;
				ret_end = cursor2;
			}
		}
	
	
	}
	return cursor2 == cursor1 ? 0 : cursor2 - cursor1 + 1;
}
int main()
{
	int bracket_len = 0;
	//char  *test_str = "((()()))";
	//char  *test_str = "))((()())((";
	//char  *test_str = "()(((()(())))(";
	char  *test_str = ")())(()()(())((()())";
	bracket_len = solution(test_str, 2);
	printf("bracket_len = %d\n", bracket_len);
	getchar();
    return 0;
}

