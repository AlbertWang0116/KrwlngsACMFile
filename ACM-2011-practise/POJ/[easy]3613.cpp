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

#define N 210
#define M 1010
const long long inf = 2000000000;
long long dis[N][N][30], ans[N], tmp[N];
int len[N], l1[N], l2[N], col[M];
bool use[M];
int n, m, t, st, ed;

void input()
{
	int i, j;
	scanf("%d %d %d %d", &t, &m, &st, &ed);
	for (i = 1; i <= m; ++i) scanf("%d %d %d", &len[i], &l1[i], &l2[i]);
	memset(use, false, sizeof(use));
	for (i = 1; i <= m; ++i) { use[l1[i]] = true; use[l2[i]] = true; }
	for (i = 1, n = 0; i <= 1000; ++i) if (use[i]) col[i] = ++n;
	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) dis[i][j][0] = inf;
	for (i = 1; i <= m; ++i) if (dis[col[l1[i]]][col[l2[i]]][0] > len[i]) { dis[col[l1[i]]][col[l2[i]]][0] = dis[col[l2[i]]][col[l1[i]]][0] = len[i]; }
//	printf("n:%d\n", n);
//	for (i = 1; i <= n; ++i) {
//		for (j = 1; j <= n; ++j) if (dis[i][j][0] != inf) printf("%2lld ", dis[i][j][0]); else printf("-1 ");
//		printf("\n"); }
}

void conduct()
{
	int i, j, k, l;
	for (l = 1; l < 20; ++l)
	{
		for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) dis[i][j][l] = inf;
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= n; ++j)
				for (k = 1; k <= n; ++k) if (dis[i][j][l] > dis[i][k][l-1] + dis[k][j][l-1]) dis[i][j][l] = dis[i][k][l-1] + dis[k][j][l-1];
	}
	for (i = 1; i <= n; ++i) ans[i] = inf; ans[col[st]] = 0;
	for (l = 0; l < 20; ++l) if ((t & (1 << l)) != 0)
	{
		for (i = 1; i <= n; ++i) tmp[i] = inf;
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= n; ++j) if (tmp[i] > ans[j] + dis[j][i][l]) tmp[i] = ans[j] + dis[j][i][l];
		for (i = 1; i <= n; ++i) ans[i] = tmp[i];
	}
	printf("%lld\n", ans[col[ed]]);
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

