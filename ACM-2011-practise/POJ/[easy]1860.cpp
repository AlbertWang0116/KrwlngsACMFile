#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
using namespace std;

#define N 150
int des[N][N], out[N];
double dis[N], dis2[N], r[N][N], c[N][N];
int n, m;

void input()
{
	int i, a, b, st;
	double amt, rab, cab, rba, cba;
	scanf("%d %d %d %lf", &n, &m, &st, &amt);
	for (i = 1; i <= n; ++i) dis[i] = 0;
	for (i = 1; i <= n; ++i) out[i] = 0;
	dis[st] = amt;
	for (i = 1; i <= m; ++i)
	{
		scanf("%d %d %lf %lf %lf %lf", &a, &b, &rab, &cab, &rba, &cba);
		++out[a];++out[b];
		r[a][out[a]] = rab; c[a][out[a]] = cab; des[a][out[a]] = b;
		r[b][out[b]] = rba; c[b][out[b]] = cba; des[b][out[b]] = a;
	}
}

void conduct()
{
	bool change = true;
	int i, j, k, dp;
	for (i = 0; i < n && change; ++i)
	{
		for (j = 1; j <= n; ++j) dis2[j] = dis[j];
		change = false;
		for (j = 1; j <= n; ++j)
			for (k = 1; k <= out[j]; ++k)
			{
				if (c[j][k] > dis[j]) continue;
				dp = des[j][k];
				if (dis2[dp] < (dis[j] - c[j][k]) * r[j][k])
				{
					dis2[dp] = (dis[j] - c[j][k]) * r[j][k];
					change = true;
				}
			}
		for (j = 1; j <= n; ++j) dis[j] = dis2[j];
		if (!change) break;
	}
	if (i == n) cout << "YES" << endl;
	else cout << "NO" << endl;
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

