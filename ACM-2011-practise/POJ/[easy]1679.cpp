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

#define N 110
#define inf 1e8
int n, m;
int way[N][N], mst[N][N], dis[N], pre[N];
bool vst[N];

int getmax(int x, int y) { return x > y ? x : y; }

void input()
{
	int i, j;
	int st, ed, len;
	scanf("%d %d", &n, &m);
	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) way[i][j] = inf;
	for (i = 0; i < m; ++i) { scanf("%d %d %d", &st, &ed, &len); way[st][ed] = len; way[ed][st] = len; }
}

void conduct()
{
	int i, j, k, l, ans;
	for (i = 1; i <= n; ++i) mst[i][i] = -1; ans = 0;
	for (i = 1; i <= n; ++i) dis[i] = inf; memset(vst, false, sizeof(vst)); dis[1] = 0;
	for (i = 1; i <= n; ++i)
	{
		k = inf;
		for (j = 1; j <= n; ++j) if (!vst[j] && dis[j] < k) { k = dis[j]; l = j; }
		for (j = 1; j <= n; ++j) if (vst[j]) mst[l][j] = mst[j][l] = getmax(mst[pre[l]][j], k);
		ans += k; vst[l] = true;
		for (j = 1; j <= n; ++j) if (!vst[j] && way[l][j] < dis[j]) { pre[j] = l; dis[j] = way[l][j]; }
	}
//	for (i = 1; i <= n; ++i) printf("pre[%d][%d]\n", i, pre[i]);
//	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) printf("[%d][%d][%d]\n", i, j, mst[i][j]);
	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) if (i != j && i != pre[j] && j != pre[i] && mst[i][j] == way[i][j]) { printf("Not Unique!\n"); return; }
	printf("%d\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

