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

int a, b, n;

void conduct()
{
	printf("%d\n", min(n-a, b+1));
}

int main()
{
//	while (scanf("%d%d%d", &n, &a, &b) != EOF) conduct();
	scanf("%d%d%d", &n, &a, &b); conduct();
	return 0;
}
