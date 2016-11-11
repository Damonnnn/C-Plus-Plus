#include <stdio.h>
#include <stdlib.h>
int SequenceSearch(int a[], int value, int n)
{
	int i;
	for(i = 0; i < n; ++i) {
		if(a[i] == value) {
			return i;
		}
	}
	return -1;
}

int main(void)
{
	int a[] = {12, 45, 37, 98, 48, 10};
	int position;

	position = SequenceSearch(a, 48, 6);
	if(position == -1) {
		printf("Error, can not find the value\n");
	}
	printf("The value is found. the index is : %d\n",position);

	return 0;
}
