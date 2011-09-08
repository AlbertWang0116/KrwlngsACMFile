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

#define N 510
int seq[N], dis[N], e[N][N];
bool vst[N];
int n, m, ans;
const int MAX = 1000000000;

int getmin(int x, int y) { return x < y ? x : y; }

void input()
{
	int i, st, ed, len;
	memset(e, 0, sizeof(e));
	for (i = 0; i < m; ++i) { scanf("%d%d%d", &st, &ed, &len); e[++st][++ed] += len; e[ed][st] += len; }
}

int mst()
{
	int i, j, k, l;
	memset(vst, false, sizeof(vst)); memset(dis, 0, sizeof(dis));
	for (i = 1; i <= n; ++i) dis[i] += e[1][i]; vst[1] = true; seq[1] = 1;
	for (i = 2; i <= n; ++i)
	{
		for (j = 1, k = -1; j <= n; ++j) if (!vst[j] && dis[j] > k) { k = dis[j]; l = j; }
		vst[l] = true; seq[i] = l;
		for (j = 1; j <= n; ++j) if (!vst[j]) dis[j] += e[l][j];
	}
	return dis[seq[n]];
}

void merge(int st, int ed)
{
	int i;
	for (i = 1; i <= n; ++i) e[st][i] += e[ed][i]; for (i = 1; i <= n; ++i) e[i][st] += e[i][ed]; e[st][st] = 0;
	for (i = 1; i <= n; ++i) e[ed][i] = e[n][i]; for (i = 1; i <= n; ++i) e[i][ed] = e[i][n]; e[ed][ed] = 0; --n;
}


void conduct()
{
	ans = MAX;
	while (n > 1)
	{
		ans = getmin(ans, mst());
		merge(seq[n-1], seq[n]);
	}
	printf("%d\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d%d", &n, &m) != EOF)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

