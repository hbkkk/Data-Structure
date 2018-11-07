/****************************************直接插入排序****************************************/
//
//基本思想: 把n个待排序的元素看成为一个有序表和一个无序表。开始时有序表中只包含1个元素，无序表中包含有n-1个元素，排序过程中每次从无序表中取出第一个元素，
//        将它插入到有序表中的适当位置，使之成为新的有序表，重复n-1次可完成排序过程。
//
//	时间复杂度：O(N^2)     假设被排序的数列中有N个数。遍历一趟的时间复杂度是O(N)，需要遍历多少次呢？N-1次！因此，冒泡排序的时间复杂度是O(N2)。
//			
//	算法稳定性：稳定

#include <stdio.h>
#include <stdlib.h>

//参数：
//	a:待排序数列
//	n:数列中数的个数
void insert_sort(int a[], int n)
{
	int i, j, k, tmp;

	for(i = 1; i < n; ++i) //n-1次排序
	{
		for(j = i-1; j >= 0; --j)  //为a[i]在前面的a[0...i-1]有序区间中找一个合适的位置
		{
			//******注：这里必须是小于等于，否则值相同的元素排序后位置变为了排序前位置的逆序，这样就不是稳定算法了
			if(a[j] <= a[i])    //当a[j]<=a[i]，说明在这0到i-1的区间里，a[i]应该放在第j个数后面。 
				break;
		}//for
//		printf("j=%d, i-1=%d\n", j, i-1);
		//如果找到了一个合适的位置，如果j等于i-1的话就代表a[i]前面的a[0...i-1]有序区间里的数都比a[i]小，无需插入
		if(j != i-1)  
		{
			
			tmp = a[i];
			for(k = i-1; k > j; --k)  //将比a[i]大的数据向后移
			{
				a[k+1] = a[k];
			}
			a[k+1] = tmp;  //把a[i]放到a[j]后面，这里的k+1就等于j+1
		}//if
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
	
	insert_sort(a, num);

	printf("直接插入排序后数列:");
	for(int i = 0; i < num; ++i)
	{
		printf("%d ", *tmp++);
	}
	printf("\n");
	
	free(a);
	return 0;
}













