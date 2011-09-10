#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

#define MAX 10000000;
#define N 110
int way[N][N];
int dis[N], dir[N], w[N];
bool visit[N];
int n, m, ans;

void input()
{
	int i, j, id, val, num;
	scanf("%d %d", &m, &n);
	for (i = 1; i <= n; ++i)
		for (j = 1; j <= n; ++j) way[i][j] = MAX;
	for (i = 1; i <= n; ++i)
	{
		scanf("%d %d %d", &dir[i], &w[i], &num);
		for (j = 0; j < num; ++j)
			{
				scanf("%d %d", &id, &val);
				if (way[id][i] > val) way[id][i] = val;
			}
	}
}

void dijkstra()
{
	int i, j, k, minval;
	for (i = 1; i <= n; ++i) dis[i] = dir[i];
	for (i = 1; i <= n; ++i)
	{
		minval = MAX;
		for (j = 1; j <= n; ++j)
			if (visit[j] && dis[j] < minval) { k = j; minval = dis[j];}
		if (k == 1) break;
		visit[k] = false;
		for (j = 1; j <= n; ++j)
			if (visit[j] && dis[j] > dis[k] + way[k][j]) dis[j] = dis[k] + way[k][j];
	}
	if (dis[1] < ans) ans = dis[1];
	//printf("dis[1]: %d\n", dis[1]);
}

void conduct()
{
	int low, high, i, j;
	ans = dir[1];
	low = w[1] - m;
	high = w[1] + m;
	if (low < 1) low = 1;
	if (high > n) high = n;
	for (i = low; i <= high; ++i)
	{
		memset(visit, false, sizeof(visit));
		for (j = 1; j <= n; ++j)
			if (w[j] >= i && w[j] <= i + m)	visit[j] = true;
		dijkstra();
	}
	cout << ans << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	input();
	conduct();
	//fclose(stdin);
	//fclose(stdout);
}

