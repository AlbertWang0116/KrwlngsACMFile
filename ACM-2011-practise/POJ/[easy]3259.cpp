#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

#define N 510
#define M 2710
#define MAX 1000000
int out[N], dis[N], dis2[N], des[N][M], cst[N][M];
bool cg[N], cg2[N];
int n;

void input()
{
	int i, s, e, t, m, w;
	scanf("%d %d %d", &n, &m, &w);
	for (i = 1; i <= n; ++i)
	{
		dis[i] = MAX;
		out[i] = 0;
		cg[i] = false;
	}
	for (i = 0; i < m; ++i)
	{
		scanf("%d %d %d", &s, &e, &t);
		if (s == e) continue;
		out[s]++; out[e]++;
		des[s][out[s]] = e; cst[s][out[s]] = t;
		des[e][out[e]] = s; cst[e][out[e]] = t;
	}
	for (i = 0; i < w; ++i)
	{
		scanf("%d %d %d", &s, &e, &t);
		dis[s] = 0;
		cg[s] = true;
		out[s]++;
		des[s][out[s]] = e;
		cst[s][out[s]] = -t;
	}
}

void conduct()
{
	int i, j, k, dp;
	bool change;
	for (i = 0; i < n; ++i)
	{
		change = false;
		for (j = 1; j <= n; ++j) dis2[j] = dis[j];
		memset(cg2, false, sizeof(cg2));
		for (j = 1; j <= n; ++j)
		{
			if (!cg[j]) continue;
			for (k = 1; k <= out[j]; ++k)
			{
				dp = des[j][k];
				if (dis2[dp] > dis[j] + cst[j][k])
				{
					//printf("dp:%d from:%d to:%d\n", dp, dis2[dp], dis[j]+cst[j][k]);
					dis2[dp] = dis[j] + cst[j][k];
					change = true;
					cg2[dp] = true;
				}
			}
		}
		for (j = 1; j <= n; ++j) dis[j] = dis2[j];
		for (j = 1; j <= n; ++j) cg[j] = cg2[j];
		if (!change) break;
	}
	if (i == n) cout << "YES" << endl;
	else cout << "NO" << endl;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int time;
	scanf("%d", &time);
	while (time--)
	{
		input();
		conduct();
	}
	//fclose(stdin);
	//fclose(stdout);
}

