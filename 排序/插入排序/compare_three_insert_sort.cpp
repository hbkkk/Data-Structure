/****************************************比较三种插入排序的新能优劣****************************************/
//
//方法：对直接插入排序、折半插入排序、希尔排序这三种插入排序各随机取1000个数，然后分别对这些数进行排序，比较这三种算法各自所花费的时间。
//     可能有点误差，因为不是同一组数列。不过其实也可以采用同一组数列。。。先写写看吧

// 实验后结果：
//	    当对随机生成的1000个数的数列排序时，直接插入排序：10000ms
//					  折半插入排序：5000ms
//					  希尔排序：625ms
// 可见，在待排序数列比较大时，希尔排序的效率远高于其他两种插入排序。

#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>

using namespace std;

class Array{
private:
	int num;
	vector<int> numbers;
	
	void gap_sort(const int &i, const int &gap);
	void produceRandomNumbers(const int &n);
public:
	Array();
	Array(int i); //i为数列中数的个数
	Array(const Array &A);
	~Array();

	void insert_sort();
	void binary_insert_sort();
	void shell_sort();
	void print();
};

Array::Array():num(10)
{
	produceRandomNumbers(num);
}

Array::Array(int i):num(i)
{
	produceRandomNumbers(num);
}

Array::~Array()
{
	//cout << "Destructor" << endl;
}

Array::Array(const Array &A)
{
	this->num = A.num;
	this->numbers = A.numbers;
}

////函数功能，随机产生n个start——end内的随机数并存入指定容器
//函数参数，随机数范围起点，随机数范围终点，随机数生成数量
void Array::produceRandomNumbers(const int &n)
{
	int start = 1;
	int end = n;
	srand((unsigned)time(NULL));
	for(int i = 1; i <= n; ++i)
	{
		numbers.push_back(start + (rand() % (end - start)));
	}
}


void Array::insert_sort()
{
	int i, j, k, tmp;
	for(i = 1; i < num; ++i)
	{
		for(j = i-1; j >= 0; --j)
		{
			if(numbers[i] >= numbers[j])
				break;
		}
		if(j != i-1)
		{
			tmp = numbers[i];
			for(k = i-1; k > j; --k)
			{
				numbers[k+1] = numbers[k];
			}
			numbers[k+1] = tmp;			
		}
	}
}

void Array::binary_insert_sort()
{
	int i, j, k, tmp;
	int low, high, mid;
	for(i = 1; i < num; ++i)
	{
		low = 0;
		high = i-1;
		while(low <= high)
		{
			mid = (low+high)/2;
			if(numbers[mid] <= numbers[i])
			{
				low = mid + 1;
			}
			else
			{
				high = mid - 1;
			}
		}//while
		tmp = numbers[i];
		for(k = i-1; k >= low; --k)
		{
			numbers[k+1] = numbers[k];
		}
		numbers[k+1] = tmp;
	}//for
}

void Array::gap_sort(const int &i, const int &gap)
{
	int j, k, tmp;
	for(j = i+gap; j < num; j+=gap)
	{
		if(numbers[j] < numbers[j-gap])
		{
			tmp = numbers[j];
			k = j-gap;
			while(k >= 0 && numbers[k] > tmp)
			{
				numbers[k+gap] = numbers[k];
				k -= gap;
			}
			numbers[k+gap] = tmp;
		}//if
	}//for
}

void Array::shell_sort()
{
	int i, gap;
	for(gap = num/2; gap > 0; gap /= 2)
	{
		for(i = 0; i < gap; ++i)
		{
			gap_sort(i, gap);
		}
	}
}

void Array::print()
{
	vector<int>::iterator pos;
//	cout << "排序后数列:" << endl;
	for(pos = numbers.begin(); pos != numbers.end(); ++pos)
	{
		cout << *pos << " ";
	}
	cout << endl;
}


int main()
{
	time_t c_start, c_end;

	Array array1(1000);
	Array array2(1000);
	Array array3(1000);

//	Array array1(200);
//	Array array2(200);
//	Array array3(200);

//直接插入排序
	cout << "排序前数列:" << endl;
	array1.print();

	c_start = clock();
	array1.insert_sort();
	c_end = clock();
	
	cout << "直接插入排序法花费时间为:" << difftime(c_end, c_start) << "ms" << endl;
	cout << "排序后数列:" << endl;
	array1.print();
	cout << endl;
	
//折半插入排序
	cout << "排序前数列:" << endl;
	array2.print();

	c_start = clock();
	array2.binary_insert_sort();
	c_end = clock();

	cout << "折半插入排序法花费时间为:" << difftime(c_end, c_start) << "ms" << endl;
	cout << "排序后数列:" << endl;
	array2.print();
	cout << endl;

//希尔排序
	cout << "排序前数列:" << endl;
	array3.print();

	c_start = clock();
	array3.shell_sort();
	c_end = clock();

	cout << "希尔排序法花费时间为:" << difftime(c_end, c_start) << "ms" << endl;
	cout << "排序后数列:" << endl;
	array3.print();
	cout << endl;

	return 0;
}






