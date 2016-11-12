/****************************************
*           bubble sort
****************************************/

#include <stdlib.h>  
#include <stdio.h>  

/*
 * with each loop of this function, a smallest number will be selected.
 * and the smallest number will have the index of i.
 * In fact, this is NOT bubble sort, this is select sort.
 */
void bubble_sort(int unsorted[],int len)
{
	int i, j;
	for (i = 0; i < len; i++)
	{
		for (j = i; j < len; j++)
		{
			if (unsorted[i] > unsorted[j])
			{
				int temp = unsorted[i];
				unsorted[i] = unsorted[j];
				unsorted[j] = temp;
			}
		}
	}
}

/*
 * with each loop of this function, a biggest number will be selected.
 * and the biggest number will have the index of j+1.
 */
void bubble_sort_v2(int unsorted[], int len)
{
	int i,j;
	for(i = 0; i < len - 1; ++i) {
		for(j = 0; j < (len -1 - i); ++j) {
			if(unsorted[j] > unsorted[j + 1]) {
            	unsorted[j] = unsorted[j] ^ unsorted[j + 1]; // use XOR to exchange
                unsorted[j + 1] = unsorted[j + 1] ^ unsorted[j];
                unsorted[j] = unsorted[j] ^ unsorted[j + 1];
			}
		}
	}
}

int main()
{
	int x[] = { 5, 10, 4, 1, 4,5, 9 };
	bubble_sort(x,7);
	for (int i = 0; i < 7; ++i) {
		printf("%d ", x[i]);
	}
	printf("\n");
	int x1[] = { 5, 10, 4, 1, 4,5, 9 };
	bubble_sort_v2(x1, 7);
	for (int i = 0; i < 7; ++i) {

		printf("%d ", x1[i]);

	}
	printf("\n");
	return 0;
}

