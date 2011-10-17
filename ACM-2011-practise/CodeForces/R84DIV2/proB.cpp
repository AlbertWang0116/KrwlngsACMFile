#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<climits>
#include<algorithm>
#include<map>
using namespace std;

int main()
{
	int n, i;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) printf("%c", 'a'+i%4);
	printf("\n");
}
