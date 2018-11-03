#include <stdio.h>

int main()
{
	int arr[5] = {1,2,3,4,5};
	int* p = arr;
	printf("*p:%d\n", *p);  //输出：1

	*p++ = 999; //把*p指向的值改为999，然后p指向后一位
	printf("after *p++ = 999, *p:%d\n", *p); //输出：2，因为现在p指向的是arr[1]
	for(int i = 0; i < 5; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n\n");  //输出： 999 2 3 4 5

	*++p = 666; //p先指向下一位，然后将其赋值为666
	            //因为之前p指向arr[1]，故现在p指向arr[2]，并将其改为666
	printf("after *++p = 666, *p:%d\n", *p); //输出：666
	for(int i = 0; i < 5; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n\n"); //输出：999 2 666 4 5 

	printf("(*p)++ = %d\n", (*p)++); //输出：666，(*p)++是先取当前位置的值输出，输出后将其加1
	printf("*p:%d\n", *p);//输出：667，因为上一行的(*p)++
			      //(*p)++ 不改变p的指向，只是改变p指向地址的内容！！！！
	for(int i = 0; i < 5; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n\n"); //输出：999 2 667 4 5 

	printf("++(*p) = :%d\n", ++(*p));//输出：668，先改变p指向地址的内容，然后输出，p指向不变！
	printf("*p:%d\n", *p);  //输出：668
	for(int i = 0; i < 5; ++i)
	{
		printf("%d ", arr[i]);  
	}
	printf("\n");  //输出：999 2 668 4 5
}
