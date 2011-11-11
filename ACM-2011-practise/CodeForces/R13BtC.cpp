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

#define N 5010
int seq[N];
long long f[2][N], a[N];
int n;

int cmp(const int &i, const int &j) { return a[i] < a[j]; }
long long getmin(long long x, long long y) { return x < y ? x : y; }

void conduct() {
	int i, j, cur, nxt; long long tv, ret;
	for (i = 0; i < n; ++i) { scanf("%I64d", &a[i]); seq[i] = i; } sort(seq, seq+n, cmp);
	for (i = 0; i < n; ++i) f[0][i] = abs(a[0]-a[seq[i]]);
	for (cur = i = 1; i < n; ++i, cur = nxt) {
		nxt = 1-cur; tv = f[nxt][0];
		for (j = 0; j < n; ++j) {
			tv = getmin(f[nxt][j], tv);
			f[cur][j] = abs(a[i]-a[seq[j]])+tv;
		}
	} for (cur = 1-cur, ret = f[cur][0], i = 0; i < n; ++i) ret = getmin(ret, f[cur][i]);
	printf("%I64d\n", ret);
}

int main() {
	while (scanf("%d", &n) != EOF) conduct();
	return 0;
}
