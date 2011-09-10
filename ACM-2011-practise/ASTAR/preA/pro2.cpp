#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<algorithm>
using namespace std;

#define a 29
#define b 16
#define N 110
#define MAX 100000
int n, w, h;
int hor[N][N], ver[N][N], line[N][N][5], col[N][N][5], lst[N][N];
bool map[N][N];

int getmin(int x, int y) { return x < y ? x : y;}

void input()
{
	int i, tw, th;
	scanf("%d", &n); memset(map, false, sizeof(map));
	for (i = 0; i < n; ++i) { scanf("%d %d", &tw, &th); map[th][tw] = true; }
}

void conduct()
{
	int i, j, k;
	int ans;
	for (i = 0; i <= h; ++i) for (j = 0; j <= w; ++j) { hor[i][j] = MAX; ver[i][j] = MAX; }
	for (i = 0; i <= h; ++i)
		for (j = 0; j <= w; ++j) if (map[i][j]) line[i][j][0] = 1; else line[i][j][0] = 0;
	for (i = 1; i <= 4; ++i)
		for (j = 0; j <= h; ++j)
			for (k = 0; k <= w - (1 << i) + 1; ++k) line[j][k][i] = line[j][k][i-1] + line[j][k+(1<<(i-1))][i-1];
	for (i = 0; i <= h; ++i)
		for (j = 0; j <= w - a + 1; ++j) col[i][j][0] = line[i][j+1][4] + line[i][j+17][3] + line[i][j+25][1] + line[i][j+27][0];
	for (i = 1; i <= 4; ++i)
		for (j = 0; j <= h - (1 << i) + 1; ++j)
			for (k = 0; k <= w - a + 1; ++k) col[j][k][i] = col[j][k][i-1] + col[j+(1<<(i-1))][k][i-1];
	for (i = 0; i <= h - b + 1; ++i)
		for (j = 0; j <= w - a + 1; ++j) hor[i][j] = col[i+1][j][3] + col[i+9][j][2] + col[i+13][j][1];
	for (i = 0; i <= h; ++i)
		for (j = 0; j <= w - b + 1; ++j) col[i][j][0] = line[i][j+1][3] + line[i][j+9][2] + line[i][j+13][1];
	for (i = 1; i <= 4; ++i)
		for (j = 0; j <= h - (1 << i) + 1; ++j)
			for (k = 0; k <= w - b + 1; ++k) col[j][k][i] = col[j][k][i-1] + col[j+(1<<(i-1))][k][i-1];
	for (i = 0; i <= h - a + 1; ++i)
		for (j = 0; j <= w - b + 1; ++j) ver[i][j] = col[i+1][j][4] + col[i+17][j][3] + col[i+25][j][2] + col[i+27][j][0];
	for (i = 0; i <= w; ++i) lst[h][i] = MAX; for (i = 0; i <= h; ++i) lst[i][w] = MAX;
	for (i = h-1; i >= 0; --i)
		for (j = w-1; j >= 0; --j) { lst[i][j] = getmin(lst[i+1][j], lst[i][j+1]); lst[i][j] = getmin(lst[i][j], ver[i][j]); lst[i][j] = getmin(lst[i][j], hor[i][j]); }
	for (i = h - b + 1; i >= 0; --i)
	{
		printf("line %2d: ", i);
		for (j = 0; j <= w - b + 1; ++j) printf("[%2d][%d] ", j, lst[i][j]);
		printf("\n");
	}
	ans = MAX;
	for (i = 0; i <= h - a + 1; ++i)
		for (j = 0; j <= w - b + 1; ++j) ans = getmin(ans, ver[i][j] + getmin(lst[i+a-1][j], lst[i][j+b-1]));
	for (i = 0; i <= h - b + 1; ++i)
		for (j = 0; j <= w - a + 1; ++j) ans = getmin(ans, hor[i][j] + getmin(lst[i+b-1][j], lst[i][j+a-1]));
	printf("%d\n", ans);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while (scanf("%d %d", &w, &h) != EOF && w && h)
	{
		input();
		conduct();
	}
	fclose(stdin);
	fclose(stdout);
}

