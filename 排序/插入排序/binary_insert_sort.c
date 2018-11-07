/****************************************折半插入排序****************************************/
//
//基本思想: 把n个待排序的元素看成为一个有序表和一个无序表。开始时有序表中只包含1个元素，无序表中包含有n-1个元素，排序过程中每次从无序表中取出第一个元素，
//        将它插入到有序表中的适当位置，（查找这个位置的方法是采用折半查找的方法，即在a[0...i-1]这个有序区间里通过折半查找来满足a[j]<a[i]的那个a[j]），
//	  使之成为新的有序表，重复n-1次可完成排序过程。
//
//	时间复杂度：O(N^2)     假设被排序的数列中有N个数。遍历一趟的时间复杂度是O(N)，需要遍历多少次呢？N-1次！因此，冒泡排序的时间复杂度是O(N2)。
//			
//	算法稳定性：稳定

#include <stdio.h>
#include <stdlib.h>

//参数：
//	a:待排序数列
//	n:数列中数的个数
void binary_insert_sort(int a[], int n)
{
	int i, k, tmp;
	int low, mid, high;

	//****注：因为是在一个有序表中插入，表中的数从只有1个数开始，
	//	 所以这个数列肯定是有序的，故可以直接使用折半查找！
	for(i = 1; i < n; ++i)
	{
		low = 0;     //折半查找，找第一个小于a[i]的那个a[j]
		high = i-1;
		while(low <= high)
		{
			mid = (low + high)/2;
			if(a[mid] <= a[i])  //找从右向左的第一个比a[i]小的数
			{
				low = mid+1; //因为low=mid+1，所以之后a[i]就放在low这个位置
			}
			else
			{
				high = mid-1;
			}
		}//while

//		printf("low:%d, i-1:%d\n", low, i-1);

		tmp = a[i];
		//将比a[i]大的数据向后移
		for(k = i-1; k >= low; --k) //****注:这里必须是大于等于，因为low=mid+1！
		{			    
			a[k+1] = a[k];
		}
		a[k+1] = tmp;	
	}//for
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
	
	binary_insert_sort(a, num);

	printf("折半插入排序后数列:");
	for(int i = 0; i < num; ++i)
	{
		printf("%d ", *tmp++);
	}
	printf("\n");
	
	free(a);
	return 0;
}

















