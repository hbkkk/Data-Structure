/****************************************希尔排序****************************************/
//希尔排序(Shell Sort)是插入排序的一种，它是针对直接插入排序算法的改进，该方法又称缩小增量排序。希尔排序实质上是一种分组插入方法
//
//基本思想:对于n个待排序的数列，取一个小于n的整数gap(gap被称为步长)将待排序元素分成若干个组子序列，所有距离为gap的倍数的记录放在同一个组中。然后，对各组内的元素进行直接插入排序。
//	 这一趟排序完成之后，每一个组的元素都是有序的。然后减小gap的值，并重复执行上述的分组和排序。重复这样的操作，当gap=1时，整个数列就是有序的。
//
//	时间复杂度：希尔排序的时间复杂度与增量(即，步长gap)的选取有关。
//		  例如，当增量为1时，希尔排序退化成了直接插入排序，此时的时间复杂度为O(N²)，而Hibbard增量的希尔排序的时间复杂度为O(N3/2)。
//			
//	算法稳定性：不稳定，对于相同的两个数，可能由于分在不同的组中而导致它们的顺序发生变化。

#include <stdio.h>
#include <stdlib.h>

void shell_sort1(int a[], int n)
{
	int i, j, k, tmp, gap;

	//gap为步长，每次减为原来的一半
	for(gap = n/2; gap > 0; gap /= 2)
	{
		//共gap个组，对每一组都执行直接插入排序
		for(i = 0; i < gap; ++i)
		{
			for(j = i+gap; j < n; j += gap) //从左第2个数开始往右，每个数与子序中前面的数依次比较
			{
				//把每个a[j]插入到正确的位置
				if(a[j-gap] > a[j])
				{
					tmp = a[j];
					k = j-gap;
				//j前面a[i,...,j-gap]数列中，每个数都与a[j](即tmp)比较，若大于它，就后移
					while(k >= 0 && a[k] > tmp) //k大于等于0！！！数组下标从0开始
					{
						a[k+gap] = a[k];
						k -= gap;
					}
					a[k+gap] = tmp;
				}//if
			}//for
		}//for
	}//for
}

void gap_sort(int a[], int i, int n, int gap)
{
	int j, k, tmp;

	for(j = i + gap; j < n; j+=gap)
	{
		if(a[j] < a[j-gap])
		{
			tmp = a[j];
			k = j-gap;
			while(k >= 0 && a[k] > tmp)
			{
				a[k+gap] = a[k];
				k -= gap;
			}
			a[k+gap] = tmp;
		}
	}
}

void shell_sort2(int a[], int n)
{
	for(int gap = n/2; gap > 0; gap /= 2)
	{
		for(int i = 0; i < gap; ++i)
		{
			gap_sort(a, i, n, gap);
		}
	}
}

int main()
{
	int num = 0;
	printf("输入数列中数的个数:");
	scanf("%d", &num);
	fflush(stdin);
	while(num <= 0)
	{
		printf("请输入正确的个数:");
		scanf("%d", &num);
		fflush(stdin);
	}

	int *a = (int *)malloc(num * sizeof(int));
	if(NULL == a)
	{
		fprintf(stderr, "malloc error\n");
		return -1;
	}

	int *tmp = a;
	int *tmp1 = a;
	int *tmp2 = a;

	printf("输入各数的值:\n");
	for(int i = 0; i < num; ++i)
	{
		scanf("%d", tmp1++);
		fflush(stdin);
	}

	printf("排序前数列:");
	for(int i = 0; i < num; ++i)
	{
		printf("%d ", *tmp2++);
	}
	printf("\n");
	
	shell_sort1(a, num);
	shell_sort2(a, num);

	printf("shell排序后数列:");
	for(int i = 0; i < num; ++i)
	{
		printf("%d ", *tmp++);
	}
	printf("\n");
	
	free(a);
	return 0;
}











