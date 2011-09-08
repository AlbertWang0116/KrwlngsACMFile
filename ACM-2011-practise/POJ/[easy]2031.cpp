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
#define MAX 1e9
#define eps 1e-6
int n;
double dis[N][N], des[N], x[N], y[N], z[N], r[N];
bool vst[N];

void input()
{
	int i, j;
	double des;
	for (i = 0; i < n; ++i) scanf("%lf %lf %lf %lf", &x[i], &y[i], &z[i], &r[i]);
	for (i = 0; i < n; ++i)
		for (j = 0; j < n; ++j)
		{
			des = sqrt((x[i] - x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]) + (z[i]-z[j])*(z[i]-z[j]));
			if (des - r[i] - r[j]< eps) dis[i][j] = 0;
			else dis[i][j] = des - r[i] -r[j];
		}
//	for (i = 0; i < n; ++i)
//	{
//		printf("number:%d ", i);
//		for (j = 0; j < n; ++j) printf("%.3f ", dis[i][j]);
//		printf("\n");
//	}
}

void conduct()
{
	int i, j, k;
	double lst;
	memset(vst, false, sizeof(vst));
	for (i = 0; i < n; ++i) des[i] = dis[0][i];
	for (i = 1; i < n; ++i)
	{
		lst = MAX;
		for (j = 1; j < n; ++j)
			if (!vst[j] && des[j] - lst < -eps) { lst = des[j]; k = j; }
		vst[k] = true;
		for (j = 1; j < n; ++j)
			if (!vst[j] && dis[k][j] - des[j] < -eps) des[j] = dis[k][j];
	}
	lst = 0;
	for (i = 1; i < n; ++i) lst += des[i];
	printf("%.3f\n", lst);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d", &n) && n)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

