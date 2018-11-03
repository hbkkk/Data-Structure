#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

typedef struct{
	char *ch;
	int length;
}HString;

int StrInit(HString &T)
{
	T.ch = (char*)malloc(sizeof(char));
	if(!T.ch)
	{
		cout << "malloc failed\n";
		return -1;
	}
	
	T.length = 0;
	
	return 0;
}

int StrAssign(HString &T, char *chars)
{
	if(T.ch) free(T.ch);    //这里会报错Error in `./string_fun': munmap_chunk(): invalid pointer: 0x00007fff6a8efe00
				//就是因为main中创建了HString对象后，没有为char* ch动态分配内存，但又调用了free，所以出错！！！

	int i = 0;   //chars中字符个数
	char *c = chars;
	for(i = 0, c = chars; *c; ++i,++c);  //********注：这行代码可以计算chars中字符个数！ 当c为最后那个字符地址+1后，*c为NULL会退出循环

	T.ch = (char *)malloc((i+1) * sizeof(char));  //i+1是因为多一个字节放结束符\0！！！！！
	if(!T.ch)
	{
		cout << "malloc failed\n";
		return -1;
	}

//	c = chars;
//	cout << "c:" << c << endl;
	for(int j = 0; j < i; ++j)
	{
		T.ch[j] = chars[j];
	}
	T.ch[i] = '\0';
//	cout << "*T.ch: " << T.ch << endl;

	T.length = i;
//	cout << "lenght:" << T.length << endl;
	return 0;
}

int StrLength(const HString &T)
{
	return T.length;
}

bool IsEmpty(const HString &T)
{
	return (NULL==T.ch && T.length==0);
}

void PrintStr(const HString &T)
{
	if(!IsEmpty(T))
	{
		cout << T.ch << endl;
	}
	else
	{
		cout << "In PrintStr, empty HString\n";
	}
}

int StrCompare(const HString &S, const HString &T)
{
	for(int i = 0; i<S.length && i<T.length; ++i)
	{
		if(S.ch[i] != T.ch[i])
		{
			return S.ch[i] - T.ch[i];
		}
	}

	return S.length - T.length;
}

int ClearString(HString &T)
{
	if(T.ch)
	{
		free(T.ch);
		T.ch = NULL;  //防止野指针！！！
	}
	T.length = 0;
	return 0;
}

int Concat(HString &T, const HString &S1, const HString &S2)
{
	if(T.ch)
		ClearString(T);
	T.ch = (char*)malloc((S1.length+S2.length)*sizeof(char));
	for(int i = 0; i < S1.length; ++i)
	{
		T.ch[i] = S1.ch[i];
	}
	for(int i = 0; i < S2.length; ++i)
	{
		T.ch[S1.length+i] = S2.ch[i];
	}
	
//	cout << "S1.length: " << S1.length << " ,S2.length: " << S2.length << endl;
	T.length = S1.length + S2.length;

	return 0;
}

int SubString(HString &Sub, const HString &S, int pos, int len)
{
	if(pos<1 || pos>S.length+1 || len<1 || len>S.length-pos+1)
	{
		cout << "In SubString, wrong pos or len\n";
		return -1;
	}
	if(Sub.ch)
	{
		ClearString(Sub);
	}	
	Sub.ch = (char*)malloc(len * sizeof(char));
	for(int i = 0; i < len; ++i)
	{
		Sub.ch[i] = S.ch[pos+i-1];
	}
	
	Sub.length = len;
	return 0;
}

int Index(const HString &S, const HString &T, const int pos)
{
	if(!T.ch)
	{
		cout << "Empty T\n";
		return -1;
	}
	if(pos<1 || (pos+T.length)>(S.length+1))
	{
		cout << "In Index, wrong pos\n";
		return -1;
	}

	int i = pos-1;
	int j = 0;
	int n = 1;
//	cout << "out of while, i: " << i << " ,S.length-T.length+1: " 
//	<< (S.length-T.length+1) << " ,T.length: " << T.length << endl;

	while(i<S.length && j<T.length)   //*****注： 这里的判断条件不能是：i<(S.length-T.length+2)，
	{					       //因为如果是最后那几位符合，那到最后1、2位的时候i肯定大于S.length-T.length+2，所以应该用i<S.length!!!
		if(S.ch[i] == T.ch[j])
		{
//			cout << "In if\n";
			++i;
			++j;
		}
		else
		{
//			cout << "In else\n";
			j = 0;
			i = pos-1+n;
			++n;
		}
//		cout << "i: " << i << ", j: " << j << endl << endl;
	}
	
	if(j == T.length)
		return (pos+n-1);
	else
	{
//		cout << "j: " << j << endl;
		return 0;
	}
}


void GetNext(const HString &T, int next[])
{
	int plen = StrLength(T);
	int j = 0;
	int k = -1;
	next[0] = -1;
	while(j < plen-1)
	{
		if(k==-1 || T.ch[j]==T.ch[k])  	//T.ch[k]表示前缀，T.ch[j]表示后缀
		{
			++j;
			++k;
			if(T.ch[j] == T.ch[k])
			{     //因为不能出现p[j] = p[next[j]]，所以当出现时需要继续递归，k = next[k] = next[next[k]]
				next[j] = next[k]; 
			}
			else
			{     
				next[j] = k; //这里的j和k已经是加1以后的j、k，即当P[j]==P[k]时，next[j+1]=next[j]+1
			}
		}
		else
		{
			k = next[k];
		}
	}
}


int Index_KMP(const HString &S, const HString &P)
{
	int i = 0;
	int j = 0;
	int slen = StrLength(S);
	int plen = StrLength(P);
	int next[plen] = {0};

	GetNext(P, next);	
	
	while(i<slen && j<plen)
	{
		if(j==-1 || S.ch[i]==P.ch[j])
		{
			++i;
			++j;
		}
		else
		{
			j = next[j];
		}
	}
	
	if(j == plen)
	{
		return i-j+1;
	}
	else
		return -1;
}

//将串T中第pos起的len个子串删除
//思路：重新申请一个数组，大小为原串删除指定大小子串后的大小，然后把要删除的子串之前和之后的内容都拷给新申请的数组，
//     然后把原来串的内容free掉，再让串的内容指向新申请数组的首地址，同时更新串的长度！
int StrDelete(HString &T, int pos, int len)
{
	if(pos<1 || pos>T.length)
	{
		cout << "In StrDelete, wrong pos\n";
		return -1;
	}
	if(len<1 || len>T.length || (pos+len-2)>T.length)
	{
		cout << "In StrDelete, wrong len\n";
		return -1;
	}

	int nlength = T.length - len;                                //-------------------------------------注！！！！--------------------------------------//
	char *cbuf = (char*)malloc((nlength+1)*sizeof(char));        //       这个cbuf作为头地址别动它，重新定义一个字符指针指向他，然后在那个上操作！！！！！！！
//	char *cbuf = new char[nlength + 1];
	if(!cbuf) {cout << "In StrDelete, malloc failed\n"; return -1;}
	
	char *ctmp = cbuf;
	char *stmp = T.ch;
	for(int i = 0; i < pos-1; ++i)
	{
		*ctmp++ = *stmp++;
	}

	stmp = T.ch + pos + len - 1;  //这句话没问题！别理后面那些 妈的。。.....这句可能有问题，加上T.ch这个就可能出错，T.ch的值不确定啊

	while(*stmp)
	{
		*ctmp++ = *stmp++;
	}
	*ctmp = '\0';
	
	free(T.ch);
	T.ch = cbuf;
//	cout << "T.ch:" << T.ch << endl;
	T.length = nlength;

	return 0;
}


//函数说明：在串T的第pos个位置之前插入串S
//思路： 先将串T中第pos个字符前的子串赋给新分配的数组中，然后将插入的串S接在新分配数组后，最后把串T中剩余的子串接在新分配数组最后
int StrInsert(HString &T, int pos, const HString &S)
{
	if(pos<1 || pos>StrLength(T)) {cout << "In StrInsert, wrong pos!\n"; return -1;}

	int slen = StrLength(S);
	int nlength = StrLength(T) + slen;
//	cout << "length: " << nlength << endl;
	char *cbuf = (char*)malloc((nlength+1)*sizeof(char));
	if(!cbuf) {cout << "In StrInsert, malloc failed\n"; return -1;}	
	char *ctmp = cbuf;
	char *stmp = T.ch;
	char *tmp = S.ch;
	
	for(int i = 0; i < pos-1; ++i)  //把T的第pos位置前的子串赋给cbuf中
	{
//		cout << "in for: " << *stmp << endl;  //这里输出的*stmp有内容是因为stmp这个指针是指向T.ch的，在T.ch里本身就已经有内容了啊！
		*ctmp++ = *stmp++;                   //-------------------------------------------注！！！---------------------------------------------------
//		cout << "*ctmp: " << *ctmp << endl;  //这里输出的*ctmp肯定没内容，因为已经是先赋值然后让ctmp++的，所以此时输出的是下一地址内容，但下一地址内容还未被赋值啊！！！
	}					     //跟上面输出的*stmp对比！因为这里的ctmp是指向动态分配的内存，但那个内存里还没有赋内容，赋内容正是之后要做的事啊！！！！！

//	cout << "&&&&&: " << cbuf << endl; //这里输出的cbuf就是串T第pos位置之前的子串
	
					//--------------------------------注------------------------------------
	while(*tmp)  //将串S接在cbuf后       这里不能是*S.ch，因为传进来的是const S，所以之后不能写成*S.ch++
	{
		*ctmp++ = *tmp++;
	}
//	cout << "#####: " << cbuf << endl;
	while(*stmp)   //将串T中剩余的子串接在cbuf后
	{
		*ctmp++ = *stmp++;
	}
	*ctmp = '\0';
//	cout << "@@@@@: " << cbuf << endl;
	free(T.ch);				//--------------------------------注！！！！------------------------------------------------
	T.ch = cbuf;                            //这里之所以能改变指针变量T.ch的值(即指向的地址值)，而不只是单单能改变T.ch指向地址上的内容，
						//是因为这个函数的形参是HString &T, 是T的引用！！！！也就是说T.ch是一级指针的引用，故能改变指针值！！！！！！！！！！！
//	cout << "****T.ch： " << T.ch << endl;
	
	return 0;
}


int main()
{
	int iRet = 0;
	HString str;
	HString str2;
	StrInit(str);
	StrInit(str2);

	char ch[4][15] = {"hello", "lo", "interest", "people hbk"};

	StrAssign(str, ch[0]);
	PrintStr(str);
	cout << "str's length: " << StrLength(str) << endl;

	StrAssign(str2, ch[1]);
	PrintStr(str2);
	cout << "str2's length: " << StrLength(str2) << endl;

//	iRet = Index(str, str2, 1);
	iRet = Index_KMP(str, str2);
	cout << "Index's iRet: " << iRet << endl;

	iRet = StrCompare(str, str2);
	cout << "StrCompare's iRet: " << iRet << endl;

	HString sum;
	StrInit(sum);
	Concat(sum, str, str2);
	PrintStr(sum);
	cout << "sum's length: " << StrLength(sum) << endl;

	HString sub;
	StrInit(sub);
	SubString(sub, sum, 9, 2);
	PrintStr(sub);

	HString str3;
	StrInit(str3);
	StrAssign(str3, ch[2]);
	cout << "str3: ";
	PrintStr(str3);
	StrDelete(str3, 4, 4);
	cout << "after StrDelete(str3, 4, 4),str3: ";
	PrintStr(str3);

	HString str4;
	StrInit(str4);
	StrAssign(str4, ch[3]);
	cout << "str4: ";
	PrintStr(str4);
	StrInsert(sum, StrLength(sum), str4);
	cout << "after StrInsert(sum, 4, str4), str4: ";
	PrintStr(sum);
	
}





















