#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	vector<int> coll;
	vector<int>::iterator pos;
	for(int i = 0; i < 10; ++i)
	{
		coll.push_back(i*3);
	}
	

	for(pos = coll.begin(); pos != coll.end(); ++pos)
		cout << *pos << " ";	
	cout << endl;
}
