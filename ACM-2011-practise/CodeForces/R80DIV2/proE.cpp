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

#define N 300010
#define M 510
long long seq[N], ans[N];
int a[N], x[N], y[N], rd[M], next[N];
int n;
const int top = M-10;

void conduct()
{
	int i, j, req;
	for (i = 1; i <= n; ++i) scanf("%d", &a[i]); scanf("%d", &req);
	memset(rd, 0, sizeof(rd));
	for (i = 1; i <= req; ++i) {
		scanf("%d%d", &x[i], &y[i]);
		if (y[i] > top) {
			ans[i] = 0LL;
			for (j = x[i]; j <= n; j += y[i]) ans[i] = ans[i] + a[j];
		} else {
			next[i] = rd[y[i]]; rd[y[i]] = i;
		}
	} for (i = 1; i <= top; ++i) if (rd[i]) {
		for (j = n; j > n-i; --j) seq[j] = a[j];
		for (j = n-i; j > 0; --j) seq[j] = seq[j+i] + a[j];
		for (j = rd[i]; j; j = next[j]) ans[j] = seq[x[j]];
	} for (i = 1; i <= req; ++i) printf("%I64d\n", ans[i]);
}


int main()
{
	while (scanf("%d", &n) != EOF) conduct();
	return 0;
}
