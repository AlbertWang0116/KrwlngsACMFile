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

#define N 510
long long a[N][N], b[N][N], c[N][N], d[N], f[N], g[N];
const int high = 100, low = 1;
int n;

void input()
{
	int i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) scanf("%lld", &a[i][j]);
	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) scanf("%lld", &b[i][j]);
	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) scanf("%lld", &c[i][j]);
}

void conduct()
{
	int i, j;
	for (i = 1; i <= n; ++i) g[i] = rand() % (high-low) + low;
	for (i = 1; i <= n; ++i) { f[i] = 0; for (j = 1; j <= n; ++j) f[i] += b[i][j] * g[j]; }
	for (i = 1; i <= n; ++i) d[i] = f[i];
	for (i = 1; i <= n; ++i) { f[i] = 0; for (j = 1; j <= n; ++j) f[i] += a[i][j] * d[j]; }
	for (i = 1; i <= n; ++i) d[i] = f[i];
	for (i = 1; i <= n; ++i) { f[i] = 0; for (j = 1; j <= n; ++j) f[i] += c[i][j] * g[j]; }
	for (i = 1; i <= n; ++i) if (d[i] != f[i]) break;
	if (i <= n) printf("NO\n"); else printf("YES\n");
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	input();
	conduct();
//	fclose(stdin);
//	fclose(stdout);
}

