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

#define N 100010
int n, m;
int seq[N];

int main()
{
	long long ans;
	int i;
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	scanf("%d %d", &n, &m);
	for (i = 0; i < m; ++i) scanf("%d", &seq[i]);
	n--; ans = 0;
	for (i = 0; i < m; ++i)
		if (seq[i] > 1) { ans += n; n -= 2; }
	printf("%lld\n", ans);
//	fclose(stdin);
//	fclose(stdout);
}

