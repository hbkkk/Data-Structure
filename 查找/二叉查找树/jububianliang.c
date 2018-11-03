#include <stdio.h>
#include <stdlib.h>


//测试1：函数能否返回局部变量的值
//结论：函数可以返回局部变量的值，主函数调用该函数后，结果是10。 返回局部变量b是可以的，返回的值就是b的一个副本10，
//     但是如果要返回b的地址(即&b)，那么会有问题，变量b在离开函数fun1后会被释放，则返回的这个地址就不是原来b的地址了
int fun1(int a)
{
	int b = 10;
	return b;
}

//测试2：
//结果：
static int *q;
int *fun2()
{
	int i = 29;
//	int *b = 90;
	q = &i;
	printf("In fun2, q=%d\n", *q);
	return q;
}

//测试：能否返回局部指针变量
//结论：可以返回指针的值，返回的是一个副本，但是不能返回指针的地址！！！
int *fun3(int *i)
{
	int *d = i;
	*d += 1;
	printf("In fun3, d's address:%p, i's address:%p\n", d, i);
	return d;//可以返回局部指针变量d，此时返回的是指针d的一个副本，但若要返回指针d的地址(&d)，就会出错！
}		//*********确切的说：此时返回的d就会形参i的地址，而i是main函数调用fun3时产生的一个指针c的副本，可以这么理解，传进来的c是main函数中指针c的一个副本，即它的地址不同，但地址上的内容相同，

int *fun4(int x, int y) 
{
//	int *i = x + y; //这句话本身就有问题，x+y的值怎么可能是一个地址值
	printf("In fun4, x's address:%p, y's address:%p\n", &x, &y);
	int *i = &x;
	*i += y;
	printf("In fun4, i's address:%p\n", i);
	return i;
}
int main()
{
	int f = 3;
	int g = 4;
	int *sum = fun4(f, g);
	printf("In main, f's address:%p, g's address:%p\n", &f, &g);
	printf("sum's address:%p\n", sum);
	printf("%d+%d = %d\n", f, g, *sum);


	int a = 0;
	a = fun1(0);
	printf("after fun1, %d\n", a);

	int *i = fun2();
	printf("%d\n", i);

	int d = 892;
	int *c = &d;

	int *e = fun3(c);
	printf("In main, d's address:%p, e's address:%p\n", d, e);
	printf("after fun3, *e:%d， *c:%d, d:%d\n", *e, *c, d);



	return 0;
}
