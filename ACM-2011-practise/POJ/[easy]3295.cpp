#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cmath>
using namespace std;

#define N 5

bool cal(char* express, int &index, int value)
{
	bool valueA, valueB;
	if (express[index] > 'a' && express[index] - 'p' < 5) return (value & (1 << (express[index] - 'p')));
	switch (express[index])
	{
	case 'N':
		index++;
		valueA = cal(express, index, value);
		return !valueA;
		break;
	case 'K':
		index++;
		valueA = cal(express, index, value);
		index++; 
		valueB = cal(express, index, value);
		return valueA && valueB;
		break;
	case 'A':
		index++;
		valueA = cal(express, index, value);
		index++;
		valueB = cal(express, index, value);
		return valueA || valueB; 
		break;
	case 'C':
		index++;
		valueA = cal(express, index, value);
		index++;
		valueB = cal(express, index, value);
		return !valueA || valueB;
		break;
	case 'E':
		index++;
		valueA = cal(express, index, value);
		index++;
		valueB = cal(express, index, value);
		return (valueA == valueB);
		break;
	}
}

int main()
{
	char express[200];
	int i, index;
	do
	{
		scanf("%s", express);
	    if (strcmp(express, "0") == 0) break;
		for (i = 0; i < (1 << N); ++i)
		{
			index = 0;
			if (!cal(express, index, i)) break;
		}
		if (i == (1 << N)) printf("tautology\n");
		else printf("not\n");
	}while (true);
} 
