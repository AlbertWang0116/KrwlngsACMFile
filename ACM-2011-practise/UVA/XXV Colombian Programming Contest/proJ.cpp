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

#define N 1010
const int MAX = LONG_MAX;
int f[N][N];
int t[N], b[N], seq[N];
int n;

int cmp(const int &x, const int &y) { return t[x] > t[y]; }

void conduct()
{
	int i, j, ans;
	for (i = 0; i < n; ++i) scanf("%d%d", &t[i], &b[i]);
	for (i = 0; i < n; ++i) seq[i] = i; sort(seq, seq+n, cmp);
	for (ans = i = 0; i < n; ++i) {
		for (j = seq[i]-1; j >= 0; --j) if (b[j]) break;
		if (j >= 0) { b[j]--; ans += t[seq[i]] / 2; }
		else ans += t[seq[i]];
	} printf("%d\n", ans);
}

int main()
{
//	freopen("jay.in", "r", stdin);
	while (scanf("%d", &n) != EOF && n) conduct();
	return 0;
}
