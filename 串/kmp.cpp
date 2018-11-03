#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct{
	char* ch;
	int length;
}HString;

int StrLength(const HString &T)  {return T.length;}


void GetNext(const HString &P, int next[])
{
	int j = 0;
	int k = -1;
	int plen = StrLength(P);
	next[0] = -1;
	
	while(j < plen-1)
	{
		if(k==-1 || P.ch[j] == P.ch[k])
		{
			++k;
			++j;
			if(P.ch[j] == P.ch[k])
			{
				next[j] = next[k];
			}
			else
			{
				next[j] = k;
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



void GetNext(const HString &P, int next[])
{
	int plen = StrLength(P);
	int j = 0;
	int k = -1;
	next[0] = -1;
	while(j < plen-1)
	{
		if(k==-1 || P.ch[j]==P.ch[k])
		{
			++j;
			++k;
			if(P.ch[j] == P.ch[k])
			{
				next[j] = next[k];
			}
			else
			{
				next[j] = k;
			}
		}
		else
		{
			k = next[k]
		}
	}
}

int Index_KMP(const HString &S, const HString &P)
{
	int i = 0;
	int j = 0;
	int slen = StrLength(S);
	int plen = StrLength(P);
	int next[StrLength[P]] = {0};
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
		return i-j+1;
	else
		return -1;
}





















































