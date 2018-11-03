#include <iostream>
using namespace std;

void move(int i, char A, char B)
{
	static int n = 1;
	cout << "第" << n << "次移动，" << "将圆盘" << i << "号从柱" << A << "移动到柱" << B << endl;
	++n;
}

void hanoi(int n, char A, char B, char C)
{
	if(n <= 1)
		move(n, A, C);		
//		cout << "\"" << 1 << "\": " << A << " move to " << C << endl;
	else
	{
		hanoi(n-1, A, C, B);
		move(n, A, C);		
//		cout << "\"" << n << "\": " << A << " move to " << C << endl;
		hanoi(n-1, B, A, C);
	}
}

int main()
{
	cout << "enter num:";
	int num;
	cin >> num;
	char a = 'A';
	char b = 'B';
	char c = 'C';

	hanoi(num, a, b, c);

	return 0;
}
