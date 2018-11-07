/****************************************快速排序****************************************/
//
//  基本思想：首先在未排序的数列中找到最小(or最大)元素，然后将其存放到数列的起始位置；接着，再从剩余未排序的元素中继续寻找最小(or最大)元素，
//	    然后放到已排序序列的末尾。以此类推，直到所有元素均排序完毕。
//
//  时间复杂度：O(N^2)，平均的时间复杂度是O(N*lgN)。
//			
//  算法稳定性：不稳定

#include <stdio.h>
#include <stdlib.h>

#define swap(a, b) ((a)^=(b), (b)^=(a), (a)^=(b))

void select_sort(int a[], int n)
{
	int j;	  //无序区的起始位置
	int min;  //无序区中最小元素位置
	//***注:i必须是0开始，不然随后的交换swap拥有不会对数组中第一个数(下标为0)进行交换
	for(int i = 0; i < n; ++i) 
	{
		min = i;
		//找出"a[i+1] ... a[n]"之间的最小元素，并赋值给min。
		for(j = i+1; j < n; ++j)
		{
			if(a[j] < a[min])
				min = j;
		}
		//若min!=i，则交换 a[i] 和 a[min]。
		//交换之后，保证了a[0] ... a[i] 之间的元素是有序的。
		if(min != i)
			swap(a[i], a[min]);
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
	
//	quick_sort1(a, 0, num-1);
	select_sort(a, num);

	printf("简单选择排序后数列:");
	for(int i = 0; i < num; ++i)
	{
		printf("%d ", *tmp++);
	}
	printf("\n");
	
	free(a);
	return 0;
}












