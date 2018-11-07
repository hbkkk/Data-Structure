/****************************************快速排序****************************************/
//
//  基本思想： 1、先从数列中取出一个数作为基准数。
//	     2、分区过程，将比这个数大的数全放到它的右边，小于或等于它的数全放到它的左边。
//	     3、再对左右区间重复第二步，直到各区间只有一个数。
//
//  快速排序：挖坑填数+分治法
//
//  对挖坑填数进行总结
//	1．i =L; j = R; 将基准数挖出形成第一个坑a[i]。
//	2．j--由后向前找比它小的数，找到后挖出此数填前一个坑a[i]中。
//	3．i++由前向后找比它大的数，找到后也挖出此数填到前一个坑a[j]中。
//	4．再重复执行2，3二步，直到i==j，将基准数填入a[i]中。
//
//  时间复杂度：快速排序的时间复杂度在最坏情况下是O(N2)，平均的时间复杂度是O(N*lgN)。
//			
//  算法稳定性：快速排序是不稳定的算法，它不满足稳定算法的定义。

#include <stdio.h>
#include <stdlib.h>

//参数：   a:待排序数组、 l：数组首元素下标、 r：数组末元素下标
//返回值： 返回基准数在数列中的下标
int AdjustArray(int a[], int l, int r)//返回调整后基准数的位置
{
	int i, j, X; //X用于保存基准数
	i = l;
	j = r;
	X = a[l]; //基准数,//a[l]即a[i]就是第一个坑
	while(i < j)
	{
		//从右向左找小于X的数来填a[i]
		while(i < j && a[j] >= X)  
		{
			--j;
		}
		if(i < j)
		{
			a[i] = a[j]; //将a[j]填到a[i]中，a[j]就形成了一个新的坑
			++i;
		}

		//从左向右找大于或等于X的数来填a[j]
		while(i < j && a[i] < X)
		{
			++i;
		}
		if(i < j)
		{
			a[j] = a[i]; //将a[i]填到a[j]中，a[i]就形成了一个新的坑
			--j;
		}
	}
	//退出时，i等于j。将X填到这个坑中
	a[i] = X; 
	return i;
}

void quick_sort1(int a[], int l, int r)
{
	if(l < r)
	{
		int i = AdjustArray(a, l, r); //先成挖坑填数法调整a[]
		quick_sort1(a, l, i-1);	 //递归调用 
		quick_sort1(a, i+1, r);
	}
}

//参数  a:待排序数组、 l:数组首元素下标、 r:数组末元素下标
void quick_sort(int a[], int l, int r)
{
	int i, j, X;
	if(l < r)
	{
		i = l;
		j = r;
		X = a[l];
		while(i < j)
		{
			//从右向左找“第一个小于X的数”来填a[i]
			while(i < j && a[j] >= X)
				--j;
			if(i < j)
				a[i++] = a[j];  //将a[j]填到a[i]中，a[j]就形成了一个新的坑
			
			//从左向右找“第一个大于等于x的数”来填a[i]	
			while(i < j && a[i] < X)
				++i;
			if(i < j)
				a[j--] = a[i];  //将a[i]填到a[j]中，a[i]就形成了一个新的坑
		}//while
		a[i] = X;
		quick_sort(a, l, i-1); //递归调用
		quick_sort(a, i+1, r);
	}//if
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
	
//	quick_sort1(a, 0, num-1);
	quick_sort(a, 0, num-1);

	printf("shell排序后数列:");
	for(int i = 0; i < num; ++i)
	{
		printf("%d ", *tmp++);
	}
	printf("\n");
	
	free(a);
	return 0;
}









