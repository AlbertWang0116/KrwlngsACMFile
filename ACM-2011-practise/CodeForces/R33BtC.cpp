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

#define N 100010
int a[N], s[N], f[N];
int n;

void conduct()
{
	int i, ans, sum;
	memset(f, 0, sizeof(f));
	for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
	for (f[0] = s[0] = 0, i = 1; i <= n; ++i) {
		s[i] = s[i-1] + a[i];
		f[i] = min(f[i-1], s[i]);
	} ans = s[n] - 2*f[n];
	for (sum = 0, i = n; i > 0; --i) {
		sum -= a[i]; ans = max(ans, s[i-1]-2*f[i-1]+sum);
	} printf("%d\n", ans);
}

int main() {
	while (scanf("%d", &n) != EOF) conduct();
	return 0;
}
