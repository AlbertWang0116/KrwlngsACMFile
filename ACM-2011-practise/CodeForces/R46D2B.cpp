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

#define N 110
int a[N], b[N];
int n, m;

int sum(int *a, int *b, int top) {
	int i;
	for (i = 1; i <= max(a[0], b[0]); ++i) {
		a[i] = a[i] + b[i];
		a[i+1] += a[i]/top; a[i] = a[i]%top;
	} if (a[i]) return i; else return i-1;
}

void conduct()
{
	int ans, top = 0;
	memset(a, 0, sizeof(a)); memset(b, 0, sizeof(b));
	for (a[0] = 0; !a[0] || n; n /= 10) { a[++a[0]] = n % 10; top = max(top, a[a[0]]); }
	for (b[0] = 0; !b[0] || m; m /= 10) { b[++b[0]] = m % 10; top = max(top, b[b[0]]); }
	ans = sum(a, b, top+1);
	printf("%d\n", ans);
}

int main()
{
	while (scanf("%d%d", &n, &m) != EOF) conduct();
	return 0;
}
