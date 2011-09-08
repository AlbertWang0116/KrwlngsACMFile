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

#define N 1010
int a[N];
int n, m;

int main()
{
	int i, cnt;
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d %d", &n, &m) != EOF)
	{
		for (i = 0; i < n; ++i) scanf("%d", &a[i]);
		std::sort(a, a+n); cnt = 0;
		for (i = 0; i < n; ++i) if (m < a[i]) m += 2; else cnt++;
		m += cnt;
		printf("%d\n", m);
	}
//	fclose(stdin);
//	fclose(stdout);
}

