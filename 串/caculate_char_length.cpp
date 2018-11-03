#include <iostream>
using namespace std;

void caculate(char *chars)
{
	int i = 0;
	char *c = chars;
	for(i = 0,c = chars; *c; ++i, ++c);
	cout << "i: " << i << endl;
	if(0 == *c)
		cout << "*c == NULL\n";
	cout << "*c: " << *c << endl;
}

int main()
{
	char ch[10] = "hello";
	if(ch[5] == '\0') cout << "ch[5] == 0" << endl; 
	caculate(ch);
	return 0;
}
