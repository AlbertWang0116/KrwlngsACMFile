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

#define N 1010
#define inf 1e10
#define eps 1e-6
double x[N], y[N], z[N], llen[N], hlen[N], dis[N], way[N][N], len[N][N], hei[N][N];
double rate, rtot, ltot, htot;
bool vst[N];
int n;

double getdis(int p1, int p2) { return sqrt((x[p1]-x[p2])*(x[p1]-x[p2]) + (y[p1]-y[p2])*(y[p1]-y[p2])); }
double gethei(int p1, int p2) { return fabs(z[p1]-z[p2]); }

void input()
{
	int i, j;
	for (i = 1; i <= n; ++i) scanf("%lf %lf %lf", &x[i], &y[i], &z[i]);
	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) { len[i][j] = getdis(i, j); hei[i][j] = gethei(i, j); }
}

double prim()
{
	int i, j, l; double k;
	for (i = 1; i <= n; ++i) for (j = 1; j <= n; ++j) way[i][j] = hei[i][j] - rate * len[i][j];
	rtot = 0; ltot = 0; htot = 0; for (i = 1; i <= n; ++i) dis[i] = inf; dis[1] = 0; llen[1] = 0; hlen[1] = 0;
	memset(vst, false, sizeof(vst));
	for (i = 1; i <= n; ++i)
	{
		k = inf;
		for (j = 1; j <= n; ++j) if (!vst[j] && dis[j] < k) { k = dis[j]; l = j; }
		vst[l] = true; rtot += k; ltot += llen[l]; htot += hlen[l];
		for (j = 1; j <= n; ++j) if (!vst[j] && way[l][j] < dis[j]) { dis[j] = way[l][j]; llen[j] = len[l][j]; hlen[j] = hei[l][j]; }
	}
	return rtot;
}

void conduct()
{
	rate = 1;
	while (fabs(prim()) > eps) rate = htot / ltot;
	printf("%.3f\n", rate);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d", &n) != EOF && n)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

