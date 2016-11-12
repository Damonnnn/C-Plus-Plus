// select_sort.cpp
//


#include <stdlib.h>  
#include <stdio.h>  

/*
 * with each loop of this function, a smallest number will be selected.
 * and the smallest number will have the index of i.
 * compare with below function, this function has better performance.
 */
void selectSort(int array[], int n)
{
	int i, j, d;
	int temp;
	for (i = 0; i < n - 1; ++i)
	{
		d = i;   
		for (j = i + 1; j < n; ++j)
			if (array[j] < array[d]) 
				d = j;

		if (d != i) 
		{
			temp = array[d];
			array[d] = array[i];
			array[i] = temp;
		}
	}
}

/*
 * with each loop of this function, a smallest number will be selected.
 * and the smallest number will have the index of i.
 * compare with above function, this function has less performance.
 */
void selectSortV2(int unsorted[],int len)
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

int main()
{
	int array[] = { 3, 1, 15, 11, 89, 5 };
	int size = sizeof(array) / sizeof(int);
	selectSort(array, size);

	for (int i = 0; i < size; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	selectSortV2(array, size);

	for (int i = 0; i < size; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}
