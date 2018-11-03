#include <stdio.h>

int main()
{
	int a[10] = {1,3,4,5,12,14,21,32,44,54};
	int b[7]  = {2,4,6,8,10,33,55};

	int a_len = sizeof(a)/sizeof(a[0]);
	int b_len = sizeof(b)/sizeof(b[0]);
	const int c_len = a_len + b_len;
	int c[c_len];
//	c[c_len] = {0};

	int i = 0, j = 0, k = 0;
	while(i < a_len && j < b_len)
	{
		if(a[i] < b[j])
			c[k++] = a[i++];
		else if(a[i] == b[j])
		{		
			c[k++] = a[i++];
			++j;
		}
		else
			c[k++] = b[j++];
//		printf("j:%d ", j);				
//		printf("i:%d\n", i);
	}
	printf("k:%d\n", k);
	while(i < a_len)
		c[k++] = a[i++];
	while(j < b_len)
		c[k++] = b[j++];
	printf("k:%d\n", k);
	for(int i = 0; i < k; ++i)
		printf("%d ", c[i]);
	printf("\n");

	return 0;
}
