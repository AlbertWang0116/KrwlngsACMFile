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
#define M 50
double p[N][M], dp[N][M], tp[N][M][M];
int n, m, r;

void input()
{
	int i, j;
	for (i = 1; i <= m; ++i)
		for (j = 1; j <= n; ++j) { scanf("%lf", &p[i][j]); dp[i][j] = 1 - p[i][j];}
}

void conduct()
{
	int i, j, k;
	double ans, tmp, tt;
	for (i = 1; i <= m; ++i)
	{
		tp[i][0][0] = 1;
		for (j = 0; j <= n; ++j) tp[i][j][j+1] = 0;
		for (j = 1; j <= n; ++j)
		{
			tp[i][j][0] = tp[i][j-1][0] * dp[i][j];
			for (k = 1; k <= j; ++k) tp[i][j][k] = tp[i][j-1][k] * dp[i][j] + tp[i][j-1][k-1] * p[i][j];
		}
	}
	ans = 1;
	for (i = 1; i <= m; ++i) ans *= (1 - tp[i][n][0]);
	tmp = 1;
	for (i = 1; i <= m; ++i)
	{
		tt = 0;
		for (j = 1; j < r; ++j) tt += tp[i][n][j];
		tmp *= tt;
	}
	ans -= tmp;
	printf("%.3f\n", ans);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	while (scanf("%d %d %d", &n, &m, &r) != EOF && n && m && r)
	{
		input();
		conduct();
	}
//	fclose(stdin);
//	fclose(stdout);
}

