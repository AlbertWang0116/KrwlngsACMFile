#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;

#define N 10000000
short ans[N];

int main()
{
	long long i, j, k, l, num;
	int n;
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	j = 100000; k = 10000; l = 1; num = 10000; i = 1; ans[0] = 1;
	for (; i <= N-1; ++i)
	{
		if (i / l == 10) l *= 10;
		num = num * i / l;
		while (num > j) num /= 10; 
		ans[i] = num / k;
	}
	while (scanf("%d", &n) != EOF) printf("%d\n", ans[n]);
//	fclose(stdin);
//	fclose(stdout);
}

