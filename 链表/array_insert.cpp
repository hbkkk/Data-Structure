#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int n,i;
	std::vector<int> coll;
	std::vector<int>::iterator pos;

	for(int i = 0; i < 10; i++)
		coll.push_back(i);

	for(pos = coll.begin(); pos != coll.end(); ++pos)
		cout << *pos << " ";
	cout << endl;

	cin >> n;
	if(n < 0 || n > coll.size())
		cout << "wrong n!\n";
/*	for(pos = coll.end(),i = 0; i < n; --pos,++i)
	{
		coll[pos] = *pos--;
	}*/

	coll.insert(coll.begin()+n-1, 999);
	
	for(pos = coll.begin(); pos != coll.end(); ++pos)
		cout << *pos << " ";
	cout << endl;

//	coll.erase(coll.begin()+3);
	coll.erase(coll.begin(), coll.begin()+2);

	for(pos = coll.begin(); pos != coll.end(); ++pos)
		cout << *pos << " ";
	cout << endl;
}
































/*struct{

}array;

int main()
{
	int* a = (int*)malloc(10*sizeof(int));
	int b[10] = {1,3,4,5,14,18,21,32,44,54};
//	a = &b;
	for()
	a = realloc(a, 20*sizeof(int));
	for(int i = 0; i < sizeof(b)/sizeof(b[0]); ++i)
	{
		printf("%d ", *(a+i));
	}
	printf("\n");

	

/*	int n = scanf("%d", &n);
	int a_len = sizeof(a)/sizeof(a[0]);
	printf("%d\n", a_len);
	if(n > a_len)
	{
		printf("enter right n, 1~10\n");
		return -1;
	}

//	while(i = a_len; i >)

	return 0;
}*/
